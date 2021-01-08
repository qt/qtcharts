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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVEAXES_H
#define DECLARATIVEAXES_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>
#include <private/declarativechartglobal_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractAxis;

class Q_QMLCHARTS_PRIVATE_EXPORT DeclarativeAxes : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)

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
