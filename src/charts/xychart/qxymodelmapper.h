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
