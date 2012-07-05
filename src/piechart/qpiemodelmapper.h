/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPIEMODELMAPPER_H
#define QPIEMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieModelMapperPrivate;
class QPieSeries;

class QTCOMMERCIALCHART_EXPORT QPieModelMapper : public QObject
{
    Q_OBJECT

protected:
    explicit QPieModelMapper(QObject *parent = 0);

    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel *model);

    QPieSeries* series() const;
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

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
