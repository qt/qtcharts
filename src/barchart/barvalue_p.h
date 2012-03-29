/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef BARVALUE_P_H
#define BARVALUE_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;

// Visual class for floating bar values
// By default these are not visible.
class BarValue : public QGraphicsObject
{
    Q_OBJECT
public:
    BarValue(QBarSet &set, QGraphicsItem *parent = 0);

    void setText(QString str);
    QString text() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void resize(qreal w, qreal h);
    void setPos(qreal x, qreal y);

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public Q_SLOTS:
    void toggleVisible();

private:

    QBarSet &m_barSet;
    QPen m_pen;
    QString m_valueString;

    qreal m_xPos;
    qreal m_yPos;
    qreal m_width;
    qreal m_height;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARVALUE_P_H
