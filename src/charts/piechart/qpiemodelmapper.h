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
