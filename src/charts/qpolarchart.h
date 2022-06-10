// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QPOLARCHART_H
#define QPOLARCHART_H

#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE

class QAbstractSeries;
class QAbstractAxis;

class Q_CHARTS_EXPORT QPolarChart : public QChart
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
    explicit QPolarChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~QPolarChart();

    void addAxis(QAbstractAxis *axis, PolarOrientation polarOrientation);

    QList<QAbstractAxis*> axes(PolarOrientations polarOrientation = PolarOrientations(PolarOrientationRadial | PolarOrientationAngular), QAbstractSeries *series = nullptr) const;

    static PolarOrientation axisPolarOrientation(QAbstractAxis *axis);

private:
    Q_DISABLE_COPY(QPolarChart)
};

QT_END_NAMESPACE

#endif // QCHART_H
