/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef QDATETIMEAXIS_H
#define QDATETIMEAXIS_H

#include <QtCharts/QAbstractAxis>

class QDateTime;

QT_CHARTS_BEGIN_NAMESPACE

class QDateTimeAxisPrivate;

class QT_CHARTS_EXPORT QDateTimeAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(int tickCount READ tickCount WRITE setTickCount NOTIFY tickCountChanged)
    Q_PROPERTY(QDateTime min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(QDateTime max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)

public:
    explicit QDateTimeAxis(QObject *parent = 0);
    ~QDateTimeAxis();

protected:
    QDateTimeAxis(QDateTimeAxisPrivate &d, QObject *parent = 0);

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
