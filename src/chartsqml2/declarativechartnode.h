/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

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
