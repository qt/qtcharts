/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef QVPIEMODELMAPPER_H
#define QVPIEMODELMAPPER_H

#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QPieSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int valuesColumn READ valuesColumn WRITE setValuesColumn NOTIFY valuesColumnChanged)
    Q_PROPERTY(int labelsColumn READ labelsColumn WRITE setLabelsColumn NOTIFY labelsColumnChanged)
    Q_PROPERTY(int firstRow READ firstRow WRITE setFirstRow NOTIFY firstRowChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)

public:
    explicit QVPieModelMapper(QObject *parent = 0);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QPieSeries *series() const;
    void setSeries(QPieSeries *series);

    int valuesColumn() const;
    void setValuesColumn(int valuesColumn);

    int labelsColumn() const;
    void setLabelsColumn(int labelsColumn);

    int firstRow() const;
    void setFirstRow(int firstRow);

    int rowCount() const;
    void setRowCount(int rowCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void valuesColumnChanged();
    void labelsColumnChanged();
    void firstRowChanged();
    void rowCountChanged();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVPIEMODELMAPPER_H
