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

#ifndef DECLARATIVECHARTNODE_P_H
#define DECLARATIVECHARTNODE_P_H

#include <QtCharts/QChartGlobal>
#include <QtQuick/QSGSimpleTextureNode>
#include <QtQuick/QQuickWindow>
#include <QtGui/QOpenGLFunctions>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeRenderNode;

class DeclarativeChartNode : public QSGSimpleTextureNode, QOpenGLFunctions
{
public:
    DeclarativeChartNode(QQuickWindow *window);
    ~DeclarativeChartNode();

    void createTextureFromImage(const QImage &chartImage);
    DeclarativeRenderNode *glRenderNode() const { return m_glRenderNode; }

private:
    QSGTexture *m_texture;
    QQuickWindow *m_window;
    QQuickWindow::CreateTextureOptions m_textureOptions;
    QSize m_textureSize;
    DeclarativeRenderNode *m_glRenderNode;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVECHARTNODE_P_H
