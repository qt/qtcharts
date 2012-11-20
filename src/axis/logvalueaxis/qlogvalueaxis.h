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

#ifndef QLOGVALUEAXIS_H
#define QLOGVALUEAXIS_H

#include "qabstractaxis.h"

class QDateTime;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLogValueAxisPrivate;

class QTCOMMERCIALCHART_EXPORT QLogValueAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString labelFormat READ labelFormat WRITE setLabelFormat)

public:
    explicit QLogValueAxis(QObject *parent = 0);
    ~QLogValueAxis();

protected:
    QLogValueAxis(QLogValueAxisPrivate &d, QObject *parent = 0);

public:
    AxisType type() const;

    //range handling
    void setMin(qreal min);
    qreal min() const;
    void setMax(qreal max);
    qreal max() const;
    void setRange(qreal min, qreal max);

    void setLabelFormat(const QString &format);
    QString labelFormat() const;

    void setBase(qreal base);
    qreal base() const;

Q_SIGNALS:
    void minChanged(qreal min);
    void maxChanged(qreal max);
    void rangeChanged(qreal min, qreal max);

private:
    Q_DECLARE_PRIVATE(QLogValueAxis)
    Q_DISABLE_COPY(QLogValueAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLOGVALUEAXIS_H
