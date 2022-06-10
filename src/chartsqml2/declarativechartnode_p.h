// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE

#endif // DECLARATIVECHARTNODE_P_H
