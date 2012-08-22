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

#ifndef DECLARATIVELINESERIES_H
#define DECLARATIVELINESERIES_H

#include "qlineseries.h"
#include "declarativexyseries.h"
#include <QDeclarativeListProperty>
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeLineSeries : public QLineSeries, public DeclarativeXySeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QDeclarativeListProperty<QObject> declarativeChildren READ declarativeChildren)
    Q_CLASSINFO("DefaultProperty", "declarativeChildren")

public:
    explicit DeclarativeLineSeries(QObject *parent = 0);
    QXYSeries *xySeries() { return this; }
    QAbstractAxis *axisX() { return m_axisX; }
    void setAxisX(QAbstractAxis *axis) { m_axisX = axis; emit axisXChanged(axis); }
    QAbstractAxis *axisY() { return m_axisY; }
    void setAxisY(QAbstractAxis *axis) { m_axisY = axis; emit axisYChanged(axis); }
    QDeclarativeListProperty<QObject> declarativeChildren();

public: // from QDeclarativeParserStatus
    void classBegin() { DeclarativeXySeries::classBegin(); }
    void componentComplete() { DeclarativeXySeries::componentComplete(); }

public:
    Q_INVOKABLE void append(qreal x, qreal y) { DeclarativeXySeries::append(x, y); }
    Q_INVOKABLE void replace(qreal oldX, qreal oldY, qreal newX, qreal newY) { DeclarativeXySeries::replace(oldX, oldY, newX, newY); }
    Q_INVOKABLE void remove(qreal x, qreal y) { DeclarativeXySeries::remove(x, y); }
    Q_INVOKABLE void insert(int index, qreal x, qreal y) { DeclarativeXySeries::insert(index, x, y); }
    Q_INVOKABLE void clear() { DeclarativeXySeries::clear(); }
    Q_INVOKABLE QPointF at(int index) { return DeclarativeXySeries::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);

public Q_SLOTS:
    static void appendDeclarativeChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
    void handleCountChanged(int index);

private:
    QAbstractAxis *m_axisX;
    QAbstractAxis *m_axisY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVELINESERIES_H
