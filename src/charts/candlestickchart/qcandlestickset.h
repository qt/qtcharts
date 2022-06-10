// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QCANDLESTICKSET_H
#define QCANDLESTICKSET_H

#include <QtCharts/qchartglobal.h>
#include <QtGui/qbrush.h>
#include <QtGui/qpen.h>
#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE

class QCandlestickSetPrivate;

class Q_CHARTS_EXPORT QCandlestickSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(qreal open READ open WRITE setOpen NOTIFY openChanged)
    Q_PROPERTY(qreal high READ high WRITE setHigh NOTIFY highChanged)
    Q_PROPERTY(qreal low READ low WRITE setLow NOTIFY lowChanged)
    Q_PROPERTY(qreal close READ close WRITE setClose NOTIFY closeChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)

public:
    explicit QCandlestickSet(qreal timestamp = 0.0, QObject *parent = nullptr);
    explicit QCandlestickSet(qreal open, qreal high, qreal low, qreal close, qreal timestamp = 0.0,
                             QObject *parent = nullptr);
    virtual ~QCandlestickSet();

    void setTimestamp(qreal timestamp);
    qreal timestamp() const;

    void setOpen(qreal open);
    qreal open() const;

    void setHigh(qreal high);
    qreal high() const;

    void setLow(qreal low);
    qreal low() const;

    void setClose(qreal close);
    qreal close() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setPen(const QPen &pen);
    QPen pen() const;

Q_SIGNALS:
    void clicked();
    void hovered(bool status);
    void pressed();
    void released();
    void doubleClicked();
    void timestampChanged();
    void openChanged();
    void highChanged();
    void lowChanged();
    void closeChanged();
    void brushChanged();
    void penChanged();

private:
    QScopedPointer<QCandlestickSetPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QCandlestickSet)
    Q_DISABLE_COPY(QCandlestickSet)
    friend class QCandlestickSeriesPrivate;
};

QT_END_NAMESPACE

#endif // QCANDLESTICKSET_H
