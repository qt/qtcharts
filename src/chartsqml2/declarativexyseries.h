/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef DECLARATIVE_XY_SERIES_H
#define DECLARATIVE_XY_SERIES_H

#include <QtCharts/QXYSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QChart;
class QAbstractSeries;

class DeclarativeXySeries
{
public:
    explicit DeclarativeXySeries();
    ~DeclarativeXySeries();

public:
    void classBegin();
    void componentComplete();
    virtual QXYSeries *xySeries() = 0;

    void append(qreal x, qreal y);
    void replace(qreal oldX, qreal oldY, qreal newX, qreal newY);
    void replace(int index, qreal newX, qreal newY);
    void remove(qreal x, qreal y);
    void remove(int index);
    void removePoints(int index, int count);
    void insert(int index, qreal x, qreal y);
    void clear();
    QPointF at(int index);
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVE_XY_SERIES_H
