// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QXYMODELMAPPER_H
#define QXYMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

Q_MOC_INCLUDE(<QtCharts/qxyseries.h>)

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QXYModelMapperPrivate;
class QXYSeries;

class Q_CHARTS_EXPORT QXYModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QXYModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QXYSeries *series() const;
    void setSeries(QXYSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int xSection() const;
    void setXSection(int xSection);

    int ySection() const;
    void setYSection(int ySection);

protected:
    QXYModelMapperPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(QXYModelMapper)
};

QT_END_NAMESPACE

#endif // QXYMODELMAPPER_H
