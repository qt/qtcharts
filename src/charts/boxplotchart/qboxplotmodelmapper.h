// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBOXPLOTMODELMAPPER_H
#define QBOXPLOTMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

Q_MOC_INCLUDE(<QtCharts/qboxplotseries.h>)

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QBoxPlotModelMapperPrivate;
class QBoxPlotSeries;

class Q_CHARTS_EXPORT QBoxPlotModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QBoxPlotModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QBoxPlotSeries *series() const;
    void setSeries(QBoxPlotSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    int firstBoxSetSection() const;
    void setFirstBoxSetSection(int firstBoxSetSection);

    int lastBoxSetSection() const;
    void setLastBoxSetSection(int lastBoxSetSection);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

protected:
    QBoxPlotModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QBoxPlotModelMapper)
};

QT_END_NAMESPACE

#endif // QBOXPLOTMODELMAPPER_H
