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
    // Our texture node must have a texture, so use a default one pixel texture
    QImage dummyImage(QSize(1, 1), QImage::Format_ARGB32);
    uchar *imageData = dummyImage.bits();
    imageData[0] = 0;
    imageData[1] = 0;
    imageData[2] = 0;
    imageData[3] = 0;
    QQuickWindow::CreateTextureOptions defaultTextureOptions = QQuickWindow::CreateTextureOptions(
            QQuickWindow::TextureHasAlphaChannel | QQuickWindow::TextureOwnsGLTexture);
    m_texture = m_window->createTextureFromImage(dummyImage, defaultTextureOptions);

    setTexture(m_texture);
    setFiltering(QSGTexture::Linear);

    if (QOpenGLContext::currentContext()) {
        // Create child node for rendering GL graphics
        m_glRenderNode = new DeclarativeRenderNode(m_window);
        m_glRenderNode->setFlag(OwnedByParent);
        appendChildNode(m_glRenderNode);
        m_glRenderNode->setRect(0, 0, 0, 0); // Hide child node by default
    }
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
