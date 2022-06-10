// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVPIEMODELMAPPER_H
#define QVPIEMODELMAPPER_H

#include <QtCharts/QPieModelMapper>

Q_MOC_INCLUDE(<QtCharts/qpieseries.h>)
Q_MOC_INCLUDE(<QtCore/qabstractitemmodel.h>)

QT_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QVPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QPieSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int valuesColumn READ valuesColumn WRITE setValuesColumn NOTIFY valuesColumnChanged)
    Q_PROPERTY(int labelsColumn READ labelsColumn WRITE setLabelsColumn NOTIFY labelsColumnChanged)
    Q_PROPERTY(int firstRow READ firstRow WRITE setFirstRow NOTIFY firstRowChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)

public:
    explicit QVPieModelMapper(QObject *parent = nullptr);

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

QT_END_NAMESPACE

#endif // QVPIEMODELMAPPER_H
