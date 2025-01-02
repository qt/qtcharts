// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QCANDLESTICKMODELMAPPER_H
#define QCANDLESTICKMODELMAPPER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

Q_MOC_INCLUDE(<QtCharts/qcandlestickseries.h>)
Q_MOC_INCLUDE(<QtCore/qabstractitemmodel.h>)

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QCandlestickModelMapperPrivate;
class QCandlestickSeries;

class Q_CHARTS_EXPORT QCandlestickModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(QCandlestickSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)

public:
    explicit QCandlestickModelMapper(QObject *parent = nullptr);

    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    void setSeries(QCandlestickSeries *series);
    QCandlestickSeries *series() const;

    virtual Qt::Orientation orientation() const = 0;

Q_SIGNALS:
    void modelReplaced();
    void seriesReplaced();

protected:
    void setTimestamp(int timestamp);
    int timestamp() const;

    void setOpen(int open);
    int open() const;

    void setHigh(int high);
    int high() const;

    void setLow(int low);
    int low() const;

    void setClose(int close);
    int close() const;

    void setFirstSetSection(int firstSetSection);
    int firstSetSection() const;

    void setLastSetSection(int lastSetSection);
    int lastSetSection() const;

protected:
    QCandlestickModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QCandlestickModelMapper)
};

QT_END_NAMESPACE

#endif // QCANDLESTICKMODELMAPPER_H
