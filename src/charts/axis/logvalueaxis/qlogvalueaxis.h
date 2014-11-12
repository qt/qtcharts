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

#ifndef QLOGVALUEAXIS_H
#define QLOGVALUEAXIS_H

#include <QtCharts/QAbstractAxis>

class QDateTime;

QT_CHARTS_BEGIN_NAMESPACE

class QLogValueAxisPrivate;

class QT_CHARTS_EXPORT QLogValueAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString labelFormat READ labelFormat WRITE setLabelFormat NOTIFY labelFormatChanged)
    Q_PROPERTY(qreal base READ base WRITE setBase NOTIFY baseChanged)

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
    void labelFormatChanged(const QString &format);
    void baseChanged(qreal base);

private:
    Q_DECLARE_PRIVATE(QLogValueAxis)
    Q_DISABLE_COPY(QLogValueAxis)
};

QT_CHARTS_END_NAMESPACE

#endif // QLOGVALUEAXIS_H
