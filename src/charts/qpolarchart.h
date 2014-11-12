/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QPOLARCHART_H
#define QPOLARCHART_H

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractSeries;
class QAbstractAxis;

class QT_CHARTS_EXPORT QPolarChart : public QChart
{
    Q_OBJECT
    Q_ENUMS(PolarOrientation)
    Q_FLAGS(PolarOrientations)

public:
    enum PolarOrientation {
        PolarOrientationRadial = 0x1,
        PolarOrientationAngular = 0x2
    };
    Q_DECLARE_FLAGS(PolarOrientations, PolarOrientation)

public:
    explicit QPolarChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~QPolarChart();

    void addAxis(QAbstractAxis *axis, PolarOrientation polarOrientation);

    QList<QAbstractAxis*> axes(PolarOrientations polarOrientation = PolarOrientations(PolarOrientationRadial | PolarOrientationAngular), QAbstractSeries *series = 0) const;

    static PolarOrientation axisPolarOrientation(QAbstractAxis *axis);

private:
    Q_DISABLE_COPY(QPolarChart)
};

QT_CHARTS_END_NAMESPACE

#endif // QCHART_H
