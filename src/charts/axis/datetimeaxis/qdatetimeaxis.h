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

#ifndef QDATETIMEAXIS_H
#define QDATETIMEAXIS_H

#include <QtCharts/QAbstractAxis>

QT_BEGIN_NAMESPACE
class QDateTime;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE

class QDateTimeAxisPrivate;

class Q_CHARTS_EXPORT QDateTimeAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(int tickCount READ tickCount WRITE setTickCount NOTIFY tickCountChanged)
    Q_PROPERTY(QDateTime min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(QDateTime max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)

public:
    explicit QDateTimeAxis(QObject *parent = nullptr);
    ~QDateTimeAxis();

protected:
    QDateTimeAxis(QDateTimeAxisPrivate &d, QObject *parent = nullptr);

public:
    AxisType type() const;

    //range handling
    void setMin(QDateTime min);
    QDateTime min() const;
    void setMax(QDateTime max);
    QDateTime max() const;
    void setRange(QDateTime min, QDateTime max);

    void setFormat(QString format);
    QString format() const;

    //ticks handling
    void setTickCount(int count);
    int tickCount() const;

Q_SIGNALS:
    void minChanged(QDateTime min);
    void maxChanged(QDateTime max);
    void rangeChanged(QDateTime min, QDateTime max);
    void formatChanged(QString format);
    void tickCountChanged(int tick);

private:
    Q_DECLARE_PRIVATE(QDateTimeAxis)
    Q_DISABLE_COPY(QDateTimeAxis)
};

QT_CHARTS_END_NAMESPACE

#endif // QDATETIMEAXIS_H
