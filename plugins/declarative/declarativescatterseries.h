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

#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qscatterseries.h"
#include "declarativexyseries.h"
#include "declarativeaxes.h"
#include "shared_defines.h"

#ifdef CHARTS_FOR_QUICK2
#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>
#else
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative/QDeclarativeParserStatus>
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeScatterSeries : public QScatterSeries, public DeclarativeXySeries, public QDECLARATIVE_PARSER_STATUS
{
    Q_OBJECT
#ifdef CHARTS_FOR_QUICK2
    Q_INTERFACES(QQmlParserStatus)
#else
    Q_INTERFACES(QDeclarativeParserStatus)
#endif
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION 1)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION 1)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION 2)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION 2)
    Q_PROPERTY(QAbstractAxis *axisAngular READ axisAngular WRITE setAxisAngular NOTIFY axisAngularChanged REVISION 3)
    Q_PROPERTY(QAbstractAxis *axisRadial READ axisRadial WRITE setAxisRadial NOTIFY axisRadialChanged REVISION 3)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged REVISION 1)
#ifdef CHARTS_FOR_QUICK2
    Q_PROPERTY(QQmlListProperty<QObject> declarativeChildren READ declarativeChildren)
#else
    Q_PROPERTY(QDeclarativeListProperty<QObject> declarativeChildren READ declarativeChildren)
#endif
    Q_CLASSINFO("DefaultProperty", "declarativeChildren")

public:
    explicit DeclarativeScatterSeries(QObject *parent = 0);
    QXYSeries *xySeries() { return this; }
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    Q_REVISION(2) QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    Q_REVISION(2) void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    Q_REVISION(2) QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    Q_REVISION(2) void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    Q_REVISION(3) QAbstractAxis *axisAngular() { return m_axes->axisX(); }
    Q_REVISION(3) void setAxisAngular(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    Q_REVISION(3) QAbstractAxis *axisRadial() { return m_axes->axisY(); }
    Q_REVISION(3) void setAxisRadial(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    qreal borderWidth() const;
    void setBorderWidth(qreal borderWidth);
    QDECLARATIVE_LIST_PROPERTY<QObject> declarativeChildren();

public: // from QDeclarativeParserStatus
    void classBegin() { DeclarativeXySeries::classBegin(); }
    void componentComplete() { DeclarativeXySeries::componentComplete(); }

public:
    Q_INVOKABLE void append(qreal x, qreal y) { DeclarativeXySeries::append(x, y); }
    Q_INVOKABLE void replace(qreal oldX, qreal oldY, qreal newX, qreal newY) { DeclarativeXySeries::replace(oldX, oldY, newX, newY); }
    Q_REVISION(3) Q_INVOKABLE void replace(int index, qreal newX, qreal newY) { DeclarativeXySeries::replace(index, newX, newY); }
    Q_INVOKABLE void remove(qreal x, qreal y) { DeclarativeXySeries::remove(x, y); }
    Q_REVISION(3) Q_INVOKABLE void remove(int index) { DeclarativeXySeries::remove(index); }
    Q_INVOKABLE void insert(int index, qreal x, qreal y) { DeclarativeXySeries::insert(index, x, y); }
    Q_INVOKABLE void clear() { DeclarativeXySeries::clear(); }
    Q_INVOKABLE QPointF at(int index) { return DeclarativeXySeries::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    Q_REVISION(1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1) void borderWidthChanged(qreal width);
    Q_REVISION(2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(2) void axisYRightChanged(QAbstractAxis *axis);
    Q_REVISION(3) void axisAngularChanged(QAbstractAxis *axis);
    Q_REVISION(3) void axisRadialChanged(QAbstractAxis *axis);

public Q_SLOTS:
    static void appendDeclarativeChildren(QDECLARATIVE_LIST_PROPERTY<QObject> *list, QObject *element);
    void handleCountChanged(int index);

public:
    DeclarativeAxes *m_axes;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
