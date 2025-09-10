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

#ifndef CANDLESTICK_P_H
#define CANDLESTICK_P_H

#include <QtGui/QBrush>
#include <QtGui/QPainterPath>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsObject>
#include <private/candlestickdata_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class AbstractDomain;
class QCandlestickSet;

class Q_CHARTS_EXPORT Candlestick : public QGraphicsObject
{
    Q_OBJECT

public:
    Candlestick(QCandlestickSet *set, AbstractDomain *domain, QGraphicsObject *parent);
    ~Candlestick();

    void setTimePeriod(qreal timePeriod);
    void setMaximumColumnWidth(qreal maximumColumnWidth);
    void setMinimumColumnWidth(qreal minimumColumnWidth);
    void setBodyWidth(qreal bodyWidth);
    void setBodyOutlineVisible(bool bodyOutlineVisible);
    void setCapsWidth(qreal capsWidth);
    void setCapsVisible(bool capsVisible);
    void setIncreasingColor(const QColor &color);
    void setDecreasingColor(const QColor &color);
    void setBrush(const QBrush &brush);
    void setPen(const QPen &pen);
    void setLayout(const CandlestickData &data);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;

Q_SIGNALS:
    void clicked(QCandlestickSet *set);
    void hovered(bool status, QCandlestickSet *set);
    void pressed(QCandlestickSet *set);
    void released(QCandlestickSet *set);
    void doubleClicked(QCandlestickSet *set);

private:
    void updateGeometry(AbstractDomain *domain);

private:
    QCandlestickSet *m_set;
    AbstractDomain *m_domain;
    qreal m_timePeriod;
    qreal m_maximumColumnWidth;
    qreal m_minimumColumnWidth;
    qreal m_bodyWidth;
    bool m_bodyOutlineVisible;
    qreal m_capsWidth;
    bool m_capsVisible;
    QColor m_increasingColor;
    QColor m_decreasingColor;
    QBrush m_brush;
    QPen m_pen;
    CandlestickData m_data;
    bool m_hovering;
    bool m_mousePressed;
    QRectF m_boundingRect;
    QRectF m_bodyRect;
    QPainterPath m_wicksPath;
    QPainterPath m_capsPath;

    friend class CandlestickAnimation;
    friend class CandlestickChartItem;
};

QT_END_NAMESPACE

#endif // CANDLESTICK_P_H
