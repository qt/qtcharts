// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "declarativechartnode_p.h"
#include "declarativeabstractrendernode_p.h"

#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGImageNode>
#include <QtQuick/QSGRendererInterface>

#ifndef QT_NO_OPENGL
# include "declarativeopenglrendernode_p.h"
#endif

QT_BEGIN_NAMESPACE

// This node handles displaying of the chart itself
DeclarativeChartNode::DeclarativeChartNode(QQuickWindow *window) :
    QSGRootNode(),
    m_window(window),
    m_renderNode(nullptr),
    m_imageNode(nullptr)
{
    // Create a DeclarativeRenderNode for correct QtQuick Backend
#ifndef QT_NO_OPENGL
    if (m_window->rendererInterface()->graphicsApi() == QSGRendererInterface::OpenGL)
        m_renderNode = new DeclarativeOpenGLRenderNode(m_window);
#endif

    if (m_renderNode) {
        m_renderNode->setFlag(OwnedByParent);
        appendChildNode(m_renderNode);
        m_renderNode->setRect(QRectF(0, 0, 0, 0)); // Hide child node by default
    }
}

DeclarativeChartNode::~DeclarativeChartNode()
{
}

// Must be called on render thread and in context
void DeclarativeChartNode::createTextureFromImage(const QImage &chartImage)
{
    static auto const defaultTextureOptions = QQuickWindow::CreateTextureOptions(QQuickWindow::TextureHasAlphaChannel |
                                                                                 QQuickWindow::TextureOwnsGLTexture);

    auto texture = m_window->createTextureFromImage(chartImage, defaultTextureOptions);
    // Create Image node if needed
    if (!m_imageNode) {
        m_imageNode = m_window->createImageNode();
        m_imageNode->setFlag(OwnedByParent);
        m_imageNode->setOwnsTexture(true);
        m_imageNode->setTexture(texture);
        prependChildNode(m_imageNode);
    } else {
        m_imageNode->setTexture(texture);
    }
    if (!m_rect.isEmpty())
        m_imageNode->setRect(m_rect);
}

void DeclarativeChartNode::setRect(const QRectF &rect)
{
    m_rect = rect;

    if (m_imageNode)
        m_imageNode->setRect(rect);
}

QT_END_NAMESPACE
