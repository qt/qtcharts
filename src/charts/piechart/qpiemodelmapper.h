// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QPIEMODELMAPPER_H
#define QPIEMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

Q_MOC_INCLUDE(<QtCharts/qpieseries.h>)

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QPieModelMapperPrivate;
class QPieSeries;

class Q_CHARTS_EXPORT QPieModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QPieModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QPieSeries *series() const;
    void setSeries(QPieSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    int valuesSection() const;
    void setValuesSection(int valuesSection);

    int labelsSection() const;
    void setLabelsSection(int labelsSection);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

protected:
    QPieModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QPieModelMapper)
};

QT_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
