/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef DECLARATIVEAXES_H
#define DECLARATIVEAXES_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractAxis;

class DeclarativeAxes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)

public:
    explicit DeclarativeAxes(QObject *parent = 0);

    QAbstractAxis *axisX() { return m_axisX; }
    void setAxisX(QAbstractAxis *axis);
    QAbstractAxis *axisY() { return m_axisY; }
    void setAxisY(QAbstractAxis *axis);
    QAbstractAxis *axisXTop() { return m_axisXTop; }
    void setAxisXTop(QAbstractAxis *axis);
    QAbstractAxis *axisYRight() { return m_axisYRight; }
    void setAxisYRight(QAbstractAxis *axis);

public:
    void emitAxisXChanged() { emit axisXChanged(m_axisX); }
    void emitAxisYChanged() { emit axisYChanged(m_axisY); }
    void emitAxisXTopChanged() { emit axisXTopChanged(m_axisXTop); }
    void emitAxisYRightChanged() { emit axisYRightChanged(m_axisYRight); }

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);
    void axisXTopChanged(QAbstractAxis *axis);
    void axisYRightChanged(QAbstractAxis *axis);

private:
    QAbstractAxis *m_axisX;
    QAbstractAxis *m_axisY;
    QAbstractAxis *m_axisXTop;
    QAbstractAxis *m_axisYRight;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVEAXES_H
