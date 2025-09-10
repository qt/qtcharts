// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVBARMODELMAPPER_H
#define QVBARMODELMAPPER_H

#include <QtCharts/QBarModelMapper>
Q_MOC_INCLUDE(<QtCore/qabstractitemmodel.h>)

QT_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QVBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QAbstractBarSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int firstBarSetColumn READ firstBarSetColumn WRITE setFirstBarSetColumn NOTIFY firstBarSetColumnChanged)
    Q_PROPERTY(int lastBarSetColumn READ lastBarSetColumn WRITE setLastBarSetColumn NOTIFY lastBarSetColumnChanged)
    Q_PROPERTY(int firstRow READ firstRow WRITE setFirstRow NOTIFY firstRowChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)

public:
    explicit QVBarModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QAbstractBarSeries *series() const;
    void setSeries(QAbstractBarSeries *series);

    int firstBarSetColumn() const;
    void setFirstBarSetColumn(int firstBarSetColumn);

    int lastBarSetColumn() const;
    void setLastBarSetColumn(int lastBarSetColumn);

    int firstRow() const;
    void setFirstRow(int firstRow);

    int rowCount() const;
    void setRowCount(int rowCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void firstBarSetColumnChanged();
    void lastBarSetColumnChanged();
    void firstRowChanged();
    void rowCountChanged();
};

QT_END_NAMESPACE

#endif // QVBARMODELMAPPER_H
