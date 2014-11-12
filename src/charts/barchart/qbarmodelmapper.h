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

#ifndef QBARMODELMAPPER_H
#define QBARMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

class QAbstractItemModel;

QT_CHARTS_BEGIN_NAMESPACE

class QBarModelMapperPrivate;
class QAbstractBarSeries;

class QT_CHARTS_EXPORT QBarModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QBarModelMapper(QObject *parent = 0);

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

QT_CHARTS_END_NAMESPACE

#endif // QBARMODELMAPPER_H
