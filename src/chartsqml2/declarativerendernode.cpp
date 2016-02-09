/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "declarativerendernode.h"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFramebufferObjectFormat>
#include <QtGui/QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QtGui/QOpenGLBuffer>

//#define QDEBUG_TRACE_GL_FPS
#ifdef QDEBUG_TRACE_GL_FPS
#  include <QElapsedTimer>
#endif

QT_CHARTS_BEGIN_NAMESPACE

// This node draws the xy series data on a transparent background using OpenGL.
// It is used as a child node of the chart node.
DeclarativeRenderNode::DeclarativeRenderNode(QQuickWindow *window) :
    QObject(),
    QSGSimpleTextureNode(),
    m_texture(0),
    m_window(window),
    m_textureOptions(QQuickWindow::TextureHasAlphaChannel),
    m_textureSize(1, 1),
    m_recreateFbo(false),
    m_fbo(0),
    m_program(0),
    m_shaderAttribLoc(-1),
    m_colorUniformLoc(-1),
    m_minUniformLoc(-1),
    m_deltaUniformLoc(-1),
    m_pointSizeUniformLoc(-1),
    m_renderNeeded(true)
{
    initializeOpenGLFunctions();

    // Our texture node must have a texture, so use a default one pixel texture
    GLuint defaultTexture = 0;
    glGenTextures(1, &defaultTexture);
    glBindTexture(GL_TEXTURE_2D, defaultTexture);
    uchar buf[4] = { 0, 0, 0, 0 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buf);

    QQuickWindow::CreateTextureOptions defaultTextureOptions = QQuickWindow::CreateTextureOptions(
            QQuickWindow::TextureHasAlphaChannel | QQuickWindow::TextureOwnsGLTexture);
    m_texture = m_window->createTextureFromId(defaultTexture, QSize(1, 1), defaultTextureOptions);

    setTexture(m_texture);
    setFiltering(QSGTexture::Linear);
    setTextureCoordinatesTransform(QSGSimpleTextureNode::MirrorVertically);
}

DeclarativeRenderNode::~DeclarativeRenderNode()
{
    delete m_texture;
    delete m_fbo;

    delete m_program;
    m_program = 0;

    cleanXYSeriesResources(0);
}

static const char *vertexSource =
        "attribute highp vec2 points;\n"
        "uniform highp vec2 min;\n"
        "uniform highp vec2 delta;\n"
        "uniform highp float pointSize;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "  vec2 normalPoint = vec2(-1, -1) + ((points - min) / delta);\n"
        "  gl_Position = matrix * vec4(normalPoint, 0, 1);\n"
        "  gl_PointSize = pointSize;\n"
        "}";
static const char *fragmentSource =
        "uniform highp vec3 color;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(color,1);\n"
        "}\n";

// Must be called on render thread and in context
void DeclarativeRenderNode::initGL()
{
    recreateFBO();

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);
    m_program->bindAttributeLocation("points", 0);
    m_program->link();

    m_program->bind();
    m_colorUniformLoc = m_program->uniformLocation("color");
    m_minUniformLoc = m_program->uniformLocation("min");
    m_deltaUniformLoc = m_program->uniformLocation("delta");
    m_pointSizeUniformLoc = m_program->uniformLocation("pointSize");
    m_matrixUniformLoc = m_program->uniformLocation("matrix");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

#if !defined(QT_OPENGL_ES_2)
    if (!QOpenGLContext::currentContext()->isOpenGLES()) {
        // Make it possible to change point primitive size and use textures with them in
        // the shaders. These are implicitly enabled in ES2.
        // Qt Quick doesn't change these flags, so it should be safe to just enable them
        // at initialization.
        glEnable(GL_PROGRAM_POINT_SIZE);
    }
#endif

    m_program->release();
}

void DeclarativeRenderNode::recreateFBO()
{
    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setAttachment(QOpenGLFramebufferObject::NoAttachment);
    delete m_fbo;
    m_fbo = new QOpenGLFramebufferObject(m_textureSize.width(),
                                         m_textureSize.height(),
                                         fboFormat);

    delete m_texture;
    m_texture = m_window->createTextureFromId(m_fbo->texture(), m_textureSize, m_textureOptions);
    setTexture(m_texture);

    m_recreateFbo = false;
}

// Must be called on render thread and in context
void DeclarativeRenderNode::setTextureSize(const QSize &size)
{
    m_textureSize = size;
    m_recreateFbo = true;
    m_renderNeeded = true;
}

// Must be called on render thread while gui thread is blocked, and in context
void DeclarativeRenderNode::setSeriesData(bool mapDirty, const GLXYDataMap &dataMap)
{
    if (mapDirty) {
        // Series have changed, recreate map, but utilize old data where feasible
        GLXYDataMap oldMap = m_xyDataMap;
        m_xyDataMap.clear();

        GLXYDataMapIterator i(dataMap);
        while (i.hasNext()) {
            i.next();
            GLXYSeriesData *data = oldMap.take(i.key());
            const GLXYSeriesData *newData = i.value();
            if (!data || newData->dirty) {
                data = new GLXYSeriesData;
                *data = *newData;
            }
            m_xyDataMap.insert(i.key(), data);
        }
        // Delete remaining old data
        i = oldMap;
        while (i.hasNext()) {
            i.next();
            delete i.value();
            cleanXYSeriesResources(i.key());
        }
    } else {
        // Series have not changed, so just copy dirty data over
        GLXYDataMapIterator i(dataMap);
        while (i.hasNext()) {
            i.next();
            const GLXYSeriesData *newData = i.value();
            if (i.value()->dirty) {
                GLXYSeriesData *data = m_xyDataMap.value(i.key());
                if (data)
                    *data = *newData;
            }
        }
    }
    markDirty(DirtyMaterial);
    m_renderNeeded = true;
}

void DeclarativeRenderNode::renderGL()
{
    glClearColor(0, 0, 0, 0);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_fbo->bind();

    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);

    glViewport(0, 0, m_textureSize.width(), m_textureSize.height());

    GLXYDataMapIterator i(m_xyDataMap);
    while (i.hasNext()) {
        i.next();
        QOpenGLBuffer *vbo = m_seriesBufferMap.value(i.key());
        GLXYSeriesData *data = i.value();

        m_program->setUniformValue(m_colorUniformLoc, data->color);
        m_program->setUniformValue(m_minUniformLoc, data->min);
        m_program->setUniformValue(m_deltaUniformLoc, data->delta);
        m_program->setUniformValue(m_matrixUniformLoc, data->matrix);

        if (!vbo) {
            vbo = new QOpenGLBuffer;
            m_seriesBufferMap.insert(i.key(), vbo);
            vbo->create();
        }
        vbo->bind();
        if (data->dirty) {
            vbo->allocate(data->array.constData(), data->array.count() * sizeof(GLfloat));
            data->dirty = false;
        }

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        if (data->type == QAbstractSeries::SeriesTypeLine) {
            glLineWidth(data->width);
            glDrawArrays(GL_LINE_STRIP, 0, data->array.size() / 2);
        } else { // Scatter
            m_program->setUniformValue(m_pointSizeUniformLoc, data->width);
            glDrawArrays(GL_POINTS, 0, data->array.size() / 2);
        }
        vbo->release();
    }

#ifdef QDEBUG_TRACE_GL_FPS
    static QElapsedTimer stopWatch;
    static int frameCount = -1;
    if (frameCount == -1) {
        stopWatch.start();
        frameCount = 0;
    }
    frameCount++;
    int elapsed = stopWatch.elapsed();
    if (elapsed >= 1000) {
        elapsed = stopWatch.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
        qDebug() << "FPS:" << fps;
        frameCount = 0;
    }
#endif

    markDirty(DirtyMaterial);
    m_window->resetOpenGLState();
}

// Must be called on render thread as response to beforeRendering signal
void DeclarativeRenderNode::render()
{
    if (m_renderNeeded) {
        if (m_xyDataMap.size()) {
            if (!m_program)
                initGL();
            if (m_recreateFbo)
                recreateFBO();
            renderGL();
        } else {
            if (rect() != QRectF()) {
                glClearColor(0, 0, 0, 0);
                m_fbo->bind();
                glClear(GL_COLOR_BUFFER_BIT);

                // If last series was removed, zero out the node rect
                setRect(QRectF());
            }
        }
        m_renderNeeded = false;
    }
}

void DeclarativeRenderNode::cleanXYSeriesResources(const QXYSeries *series)
{
    if (series) {
        delete m_seriesBufferMap.take(series);
        delete m_xyDataMap.take(series);
    } else {
        foreach (QOpenGLBuffer *buffer, m_seriesBufferMap.values())
            delete buffer;
        m_seriesBufferMap.clear();
        foreach (GLXYSeriesData *data, m_xyDataMap.values())
            delete data;
        m_xyDataMap.clear();
    }
}

QT_CHARTS_END_NAMESPACE
