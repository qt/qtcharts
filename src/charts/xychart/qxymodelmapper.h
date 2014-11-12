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

#ifndef QXYMODELMAPPER_H
#define QXYMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

class QAbstractItemModel;

QT_CHARTS_BEGIN_NAMESPACE

class QXYModelMapperPrivate;
class QXYSeries;

class QT_CHARTS_EXPORT QXYModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QXYModelMapper(QObject *parent = 0);

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

QT_CHARTS_END_NAMESPACE

#endif // QXYMODELMAPPER_H
