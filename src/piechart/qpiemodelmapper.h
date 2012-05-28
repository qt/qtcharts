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
    Q_PROPERTY(QPieSeries *series READ series WRITE setSeries)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel)
    Q_PROPERTY(int first READ first WRITE setFirst)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_ENUMS(Qt::Orientation)

protected:
    QPieModelMapper(QObject *parent = 0);

public:
    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel *model);

    QPieSeries* series() const;
    void setSeries(QPieSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    void reset();

protected:
    int valuesIndex() const;
    void setValuesIndex(int valuesIndex);

    int labelsIndex() const;
    void setLabelsIndex(int labelsIndex);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

protected:
    QPieModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QPieModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
