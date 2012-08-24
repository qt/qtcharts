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

#ifndef DECLARATIVEAREASERIES_H
#define DECLARATIVEAREASERIES_H

#include "qareaseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class DeclarativeLineSeries;

class DeclarativeAreaSeries : public QAreaSeries
{
    Q_OBJECT
    Q_PROPERTY(DeclarativeLineSeries *upperSeries READ upperSeries WRITE setUpperSeries)
    Q_PROPERTY(DeclarativeLineSeries *lowerSeries READ lowerSeries WRITE setLowerSeries)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)

public:
    explicit DeclarativeAreaSeries(QObject *parent = 0);
    void setUpperSeries(DeclarativeLineSeries* series);
    DeclarativeLineSeries* upperSeries() const;
    void setLowerSeries(DeclarativeLineSeries* series);
    DeclarativeLineSeries* lowerSeries() const;
    QAbstractAxis *axisX() { return m_axisX; }
    void setAxisX(QAbstractAxis *axis) { m_axisX = axis; emit axisXChanged(axis); }
    QAbstractAxis *axisY() { return m_axisY; }
    void setAxisY(QAbstractAxis *axis) { m_axisY = axis; emit axisYChanged(axis); }

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);

private:
    QAbstractAxis *m_axisX;
    QAbstractAxis *m_axisY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEAREASERIES_H
