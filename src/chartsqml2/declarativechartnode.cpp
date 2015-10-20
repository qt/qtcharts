/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "declarativechartnode.h"
#include "declarativerendernode.h"
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFramebufferObjectFormat>
#include <QtGui/QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QtGui/QOpenGLBuffer>

QT_CHARTS_BEGIN_NAMESPACE

// This node handles displaying of the chart itself
DeclarativeChartNode::DeclarativeChartNode(QQuickWindow *window) :
    QSGSimpleTextureNode(),
    m_texture(0),
    m_window(window),
    m_textureOptions(0),
    m_textureSize(1, 1),
    m_glRenderNode(0)
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

    // Create child node for rendering GL graphics
    m_glRenderNode = new DeclarativeRenderNode(m_window);
    m_glRenderNode->setFlag(OwnedByParent);
    appendChildNode(m_glRenderNode);
    m_glRenderNode->setRect(0, 0, 0, 0); // Hide child node by default
}

DeclarativeChartNode::~DeclarativeChartNode()
{
    delete m_texture;
}

// Must be called on render thread and in context
void DeclarativeChartNode::createTextureFromImage(const QImage &chartImage)
{
    if (chartImage.size() != m_textureSize)
        m_textureSize = chartImage.size();

    delete m_texture;
    m_texture = m_window->createTextureFromImage(chartImage, m_textureOptions);
    setTexture(m_texture);
}

QT_CHARTS_END_NAMESPACE
