// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVXYMODELMAPPER_H
#define QVXYMODELMAPPER_H

#include <QtCharts/QXYModelMapper>

Q_MOC_INCLUDE(<QtCharts/qxyseries.h>)
Q_MOC_INCLUDE(<QtCore/qabstractitemmodel.h>)

QT_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QVXYModelMapper : public QXYModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QXYSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int xColumn READ xColumn WRITE setXColumn NOTIFY xColumnChanged)
    Q_PROPERTY(int yColumn READ yColumn WRITE setYColumn NOTIFY yColumnChanged)
    Q_PROPERTY(int firstRow READ firstRow WRITE setFirstRow NOTIFY firstRowChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY rowCountChanged)

public:
    explicit QVXYModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QXYSeries *series() const;
    void setSeries(QXYSeries *series);

    int xColumn() const;
    void setXColumn(int xColumn);

    int yColumn() const;
    void setYColumn(int yColumn);

    int firstRow() const;
    void setFirstRow(int firstRow);

    int rowCount() const;
    void setRowCount(int rowCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void xColumnChanged();
    void yColumnChanged();
    void firstRowChanged();
    void rowCountChanged();
};

QT_END_NAMESPACE

#endif // QVXYMODELMAPPER_H
