// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBARMODELMAPPER_H
#define QBARMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

Q_MOC_INCLUDE(<QtCharts/qabstractbarseries.h>)
Q_MOC_INCLUDE(<QtCharts/qvbarmodelmapper.h>)

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QBarModelMapperPrivate;
class QAbstractBarSeries;

class Q_CHARTS_EXPORT QBarModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QBarModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QAbstractBarSeries *series() const;
    void setSeries(QAbstractBarSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    int firstBarSetSection() const;
    void setFirstBarSetSection(int firstBarSetSection);

    int lastBarSetSection() const;
    void setLastBarSetSection(int lastBarSetSection);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

protected:
    QBarModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QBarModelMapper)
};

QT_END_NAMESPACE

#endif // QBARMODELMAPPER_H
