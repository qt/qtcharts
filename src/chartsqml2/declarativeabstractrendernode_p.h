// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVEABSTRACTRENDERNODE_H
#define DECLARATIVEABSTRACTRENDERNODE_H

#include <QtCharts/QChartGlobal>
#include <QtQuick/QSGNode>
#include <QtQuick/QQuickWindow>
#include <private/glxyseriesdata_p.h>
#include <private/declarativechartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT MouseEventResponse {
public:
    enum MouseEventType {
        None,
        Pressed,
        Released,
        Clicked,
        DoubleClicked,
        HoverEnter,
        HoverLeave
    };

    MouseEventResponse()
        : type(None),
          series(nullptr) {}
    MouseEventResponse(MouseEventType t, const QPoint &p, const QXYSeries *s)
        : type(t),
          point(p),
          series(s) {}
    MouseEventType type;
    QPoint point;
    const QXYSeries *series;
};

class Q_CHARTSQML_EXPORT DeclarativeAbstractRenderNode : public QSGRootNode
{
public:
    DeclarativeAbstractRenderNode() {}

    virtual void setTextureSize(const QSize &textureSize) = 0;
    virtual QSize textureSize() const = 0;
    virtual void setRect(const QRectF &rect) = 0;
    virtual void setSeriesData(bool mapDirty, const GLXYDataMap &dataMap) = 0;
    virtual void setAntialiasing(bool enable) = 0;
    virtual void addMouseEvents(const QList<QMouseEvent *> &events) = 0;
    virtual void takeMouseEventResponses(QList<MouseEventResponse> &responses) = 0;
};

QT_END_NAMESPACE


#endif // DECLARATIVEABSTRACTRENDERNODE_H
