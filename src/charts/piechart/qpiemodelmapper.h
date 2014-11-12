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

#ifndef QPIEMODELMAPPER_H
#define QPIEMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

class QAbstractItemModel;

QT_CHARTS_BEGIN_NAMESPACE

class QPieModelMapperPrivate;
class QPieSeries;

class QT_CHARTS_EXPORT QPieModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QPieModelMapper(QObject *parent = 0);

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

QT_CHARTS_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
