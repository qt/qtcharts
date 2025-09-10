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

#ifndef BAR_H
#define BAR_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>

QT_BEGIN_NAMESPACE

class QBarSet;

// Single visual bar item of chart
class Q_CHARTS_EXPORT Bar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bar(QBarSet *barset, QGraphicsItem *parent = 0);
    ~Bar();

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void setVisualsDirty(bool dirty) { m_visualsDirty = dirty; }
    bool visualsDirty() const { return m_visualsDirty; }
    void setLabelDirty(bool dirty) { m_labelDirty = dirty; }
    bool labelDirty() const { return m_labelDirty; }

    void setLabelItem(QGraphicsTextItem *labelItem) { m_labelItem = labelItem; }
    QGraphicsTextItem *labelItem() const { return m_labelItem; }

    void setIndex(int index) { m_index = index; }
    int index() const { return m_index; }
    void setLayoutIndex(int index) { m_layoutIndex = index; }
    int layoutIndex() const { return m_layoutIndex; }

Q_SIGNALS:
    void clicked(int index, QBarSet *barset);
    void hovered(bool status, int index, QBarSet *barset);
    void pressed(int index, QBarSet *barset);
    void released(int index, QBarSet *barset);
    void doubleClicked(int index, QBarSet *barset);

private:
    int m_index;
    int m_layoutIndex;
    QBarSet *m_barset;
    QGraphicsTextItem *m_labelItem;
    bool m_hovering;
    bool m_mousePressed;
    bool m_visualsDirty;
    bool m_labelDirty;
};

QT_END_NAMESPACE

#endif // BAR_H
