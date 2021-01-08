/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVECHARTNODE_P_H
#define DECLARATIVECHARTNODE_P_H

#include <QtCharts/QChartGlobal>
#include <QtQuick/QSGNode>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGImageNode>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeAbstractRenderNode;
class DeclarativeChartNode : public QSGRootNode
{
public:
    DeclarativeChartNode(QQuickWindow *window);
    ~DeclarativeChartNode();

    void createTextureFromImage(const QImage &chartImage);
    DeclarativeAbstractRenderNode *renderNode() const { return m_renderNode; }

    void setRect(const QRectF &rect);

private:
    QRectF m_rect;
    QQuickWindow *m_window;
    DeclarativeAbstractRenderNode *m_renderNode;
    QSGImageNode *m_imageNode;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVECHARTNODE_P_H
