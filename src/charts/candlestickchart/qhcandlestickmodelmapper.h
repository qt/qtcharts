// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QHCANDLESTICKMODELMAPPER_H
#define QHCANDLESTICKMODELMAPPER_H

#include <QtCharts/QCandlestickModelMapper>

QT_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class Q_CHARTS_EXPORT QHCandlestickModelMapper : public QCandlestickModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int timestampColumn READ timestampColumn WRITE setTimestampColumn NOTIFY timestampColumnChanged)
    Q_PROPERTY(int openColumn READ openColumn WRITE setOpenColumn NOTIFY openColumnChanged)
    Q_PROPERTY(int highColumn READ highColumn WRITE setHighColumn NOTIFY highColumnChanged)
    Q_PROPERTY(int lowColumn READ lowColumn WRITE setLowColumn NOTIFY lowColumnChanged)
    Q_PROPERTY(int closeColumn READ closeColumn WRITE setCloseColumn NOTIFY closeColumnChanged)
    Q_PROPERTY(int firstSetRow READ firstSetRow WRITE setFirstSetRow NOTIFY firstSetRowChanged)
    Q_PROPERTY(int lastSetRow READ lastSetRow WRITE setLastSetRow NOTIFY lastSetRowChanged)

public:
    explicit QHCandlestickModelMapper(QObject *parent = nullptr);

    Qt::Orientation orientation() const override;

    void setTimestampColumn(int timestampColumn);
    int timestampColumn() const;

    void setOpenColumn(int openColumn);
    int openColumn() const;

    void setHighColumn(int highColumn);
    int highColumn() const;

    void setLowColumn(int lowColumn);
    int lowColumn() const;

    void setCloseColumn(int closeColumn);
    int closeColumn() const;

    void setFirstSetRow(int firstSetRow);
    int firstSetRow() const;

    void setLastSetRow(int lastSetRow);
    int lastSetRow() const;

Q_SIGNALS:
    void timestampColumnChanged();
    void openColumnChanged();
    void highColumnChanged();
    void lowColumnChanged();
    void closeColumnChanged();
    void firstSetRowChanged();
    void lastSetRowChanged();
};

QT_END_NAMESPACE

#endif // QHCANDLESTICKMODELMAPPER_H
