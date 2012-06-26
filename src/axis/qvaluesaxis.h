/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#ifndef QVALUESAXIS_H
#define QVALUESAXIS_H

#include "qabstractaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QValuesAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QValuesAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(int ticksCount READ ticksCount WRITE setTicksCount)
    Q_PROPERTY(bool niceNumbersEnabled READ niceNumbersEnabled WRITE setNiceNumbersEnabled)
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)

public:
    explicit QValuesAxis(QObject *parent = 0);
    ~QValuesAxis();

protected:
    QValuesAxis(QValuesAxisPrivate &d,QObject *parent = 0);

public:
    AxisType type() const;

    //range handling
    void setMin(qreal min);
    qreal min() const;
    void setMax(qreal max);
    qreal max() const;
    void setRange(qreal min, qreal max);

    //ticks handling
    void setTicksCount(int count);
    int ticksCount() const;

    void setNiceNumbersEnabled(bool enable = true);
    bool niceNumbersEnabled() const;

private:
    //range handling
    void setMin(QVariant min);
    void setMax(QVariant max);
    void setRange(QVariant min, QVariant max);

Q_SIGNALS:
    void minChanged(qreal min);
    void maxChanged(qreal max);
    void rangeChanged(qreal min, qreal max);

private:
    Q_DECLARE_PRIVATE(QValuesAxis)
    Q_DISABLE_COPY(QValuesAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVALUESAXIS_H
