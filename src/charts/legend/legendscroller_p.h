// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.


#ifndef LEGENDSCROLLER_P_H
#define LEGENDSCROLLER_P_H

#include <QtCharts/qlegend.h>
#include <private/qlegend_p.h>
#include <private/scroller_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT LegendScroller: public QLegend, public Scroller
{
    Q_OBJECT

public:
    LegendScroller(QChart *chart);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setOffset(const QPointF &point) override;
    QPointF offset() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    void handleInteractiveChanged(bool interactive);
    void updateForResizerChange();

    bool m_forwardMouseEvents{false};
    bool m_forwardHoverEvents{false};
    bool m_cachedShouldShowMoveEvents{false};

private slots:
    void handleDetached(bool attached);
};

QT_END_NAMESPACE

#endif
