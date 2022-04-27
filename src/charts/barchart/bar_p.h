/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

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
class Q_CHARTS_PRIVATE_EXPORT Bar : public QObject, public QGraphicsRectItem
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
