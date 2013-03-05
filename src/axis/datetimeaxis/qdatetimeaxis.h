/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDATETIMEAXIS_H
#define QDATETIMEAXIS_H

#include "qabstractaxis.h"

class QDateTime;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QDateTimeAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QDateTimeAxis : public QAbstractAxis
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

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QDATETIMEAXIS_H
