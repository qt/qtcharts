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

#ifndef DECLARATIVE_XY_SERIES_H
#define DECLARATIVE_XY_SERIES_H

#include <QtCharts/QXYSeries>
#include <private/declarativechartglobal_p.h>

QT_BEGIN_NAMESPACE

class QChart;

class Q_QMLCHARTS_PRIVATE_EXPORT DeclarativeXySeries
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

QT_END_NAMESPACE

#endif // DECLARATIVE_XY_SERIES_H
