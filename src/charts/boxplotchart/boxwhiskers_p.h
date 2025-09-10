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

#ifndef BOXWHISKERS_H
#define BOXWHISKERS_H

#include <private/boxwhiskersdata_p.h>
#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QBoxSet>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsLayoutItem>
#include <QtGui/QPainterPath>

QT_BEGIN_NAMESPACE

class QBarSet;

class Q_CHARTS_EXPORT BoxWhiskers : public QGraphicsObject
{
    Q_OBJECT

public:
    BoxWhiskers(QBoxSet *set, AbstractDomain *domain, QGraphicsObject *parent);
    ~BoxWhiskers();

    void setBrush(const QBrush &brush);
    void setPen(const QPen &pen);
    void setLayout(const BoxWhiskersData &data);
    void setBoxOutlined(const bool outlined) { m_boxOutlined = outlined; }
    void setBoxWidth(const qreal width);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    void updateGeometry(AbstractDomain *domain);
protected:
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void setGeometry(const QRectF &rect);

Q_SIGNALS:
    void clicked(QBoxSet *boxset);
    void hovered(bool status, QBoxSet *boxset);
    void pressed(QBoxSet *boxset);
    void released(QBoxSet *boxset);
    void doubleClicked(QBoxSet *boxset);

private:
    friend class BoxPlotChartItem;
    friend class BoxPlotAnimation;

    QBoxSet *m_boxSet;
    AbstractDomain *m_domain;
    QPainterPath    m_boxPath;
    QRectF m_boundingRect;
    Q_DECL_UNUSED_MEMBER
    bool m_hovering;
    bool m_validData;
    QBrush  m_brush;
    QPen m_pen;
    QPen m_medianPen;
    QPen m_outlinePen;
    bool m_boxOutlined;
    qreal m_boxWidth;
    BoxWhiskersData m_data;
    QSizeF m_domainSize;
    QRectF m_middleBox;
    qreal m_geometryMedian;
    qreal m_geometryLeft;
    qreal m_geometryRight;

    bool m_mousePressed;
};

QT_END_NAMESPACE

#endif // BOXWHISKERS_H
