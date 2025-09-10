// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVCANDLESTICKMODELMAPPER_H
#define QVCANDLESTICKMODELMAPPER_H

#include <QtCharts/QCandlestickModelMapper>

QT_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QVCandlestickModelMapper : public QCandlestickModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int timestampRow READ timestampRow WRITE setTimestampRow NOTIFY timestampRowChanged)
    Q_PROPERTY(int openRow READ openRow WRITE setOpenRow NOTIFY openRowChanged)
    Q_PROPERTY(int highRow READ highRow WRITE setHighRow NOTIFY highRowChanged)
    Q_PROPERTY(int lowRow READ lowRow WRITE setLowRow NOTIFY lowRowChanged)
    Q_PROPERTY(int closeRow READ closeRow WRITE setCloseRow NOTIFY closeRowChanged)
    Q_PROPERTY(int firstSetColumn READ firstSetColumn WRITE setFirstSetColumn NOTIFY firstSetColumnChanged)
    Q_PROPERTY(int lastSetColumn READ lastSetColumn WRITE setLastSetColumn NOTIFY lastSetColumnChanged)

public:
    explicit QVCandlestickModelMapper(QObject *parent = nullptr);

    Qt::Orientation orientation() const override;

    void setTimestampRow(int timestampRow);
    int timestampRow() const;

    void setOpenRow(int openRow);
    int openRow() const;

    void setHighRow(int highRow);
    int highRow() const;

    void setLowRow(int lowRow);
    int lowRow() const;

    void setCloseRow(int closeRow);
    int closeRow() const;

    void setFirstSetColumn(int firstSetColumn);
    int firstSetColumn() const;

    void setLastSetColumn(int lastSetColumn);
    int lastSetColumn() const;

Q_SIGNALS:
    void timestampRowChanged();
    void openRowChanged();
    void highRowChanged();
    void lowRowChanged();
    void closeRowChanged();
    void firstSetColumnChanged();
    void lastSetColumnChanged();
};

QT_END_NAMESPACE

#endif // QVCANDLESTICKMODELMAPPER_H
