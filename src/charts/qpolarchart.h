/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
