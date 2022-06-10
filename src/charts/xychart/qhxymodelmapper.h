// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QHXYMODELMAPPER_H
#define QHXYMODELMAPPER_H

#include <QtCharts/QXYModelMapper>

Q_MOC_INCLUDE(<QtCharts/qxyseries.h>)
Q_MOC_INCLUDE(<QtCore/qabstractitemmodel.h>)

QT_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QHXYModelMapper : public QXYModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QXYSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int xRow READ xRow WRITE setXRow NOTIFY xRowChanged)
    Q_PROPERTY(int yRow READ yRow WRITE setYRow NOTIFY yRowChanged)
    Q_PROPERTY(int firstColumn READ firstColumn WRITE setFirstColumn NOTIFY firstColumnChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)

public:
    explicit QHXYModelMapper(QObject *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QXYSeries *series() const;
    void setSeries(QXYSeries *series);

    int xRow() const;
    void setXRow(int xRow);

    int yRow() const;
    void setYRow(int yRow);

    int firstColumn() const;
    void setFirstColumn(int firstColumn);

    int columnCount() const;
    void setColumnCount(int columnCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void xRowChanged();
    void yRowChanged();
    void firstColumnChanged();
    void columnCountChanged();
};

QT_END_NAMESPACE

#endif // QHXYMODELMAPPER_H
