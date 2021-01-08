/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef QVBARMODELMAPPER_H
#define QVBARMODELMAPPER_H

#include <QtCharts/QBarModelMapper>

QT_CHARTS_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QVBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QAbstractBarSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
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

QT_CHARTS_END_NAMESPACE

#endif // QVBARMODELMAPPER_H
