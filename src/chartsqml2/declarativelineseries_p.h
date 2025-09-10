// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVELINESERIES_H
#define DECLARATIVELINESERIES_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QLineSeries>
#include <private/declarativechartglobal_p.h>
#include <private/declarativexyseries_p.h>
#include <private/declarativeaxes_p.h>

#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeLineSeries : public QLineSeries, public DeclarativeXySeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisAngular READ axisAngular WRITE setAxisAngular NOTIFY axisAngularChanged REVISION(1, 3))
    Q_PROPERTY(QAbstractAxis *axisRadial READ axisRadial WRITE setAxisRadial NOTIFY axisRadialChanged REVISION(1, 3))
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged REVISION(1, 1))
    Q_PROPERTY(Qt::PenStyle style READ style WRITE setStyle NOTIFY styleChanged REVISION(1, 1))
    Q_PROPERTY(Qt::PenCapStyle capStyle READ capStyle WRITE setCapStyle NOTIFY capStyleChanged REVISION(1, 1))
    Q_PROPERTY(QQmlListProperty<QObject> declarativeChildren READ declarativeChildren)
    Q_CLASSINFO("DefaultProperty", "declarativeChildren")
    QML_NAMED_ELEMENT(LineSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeLineSeries(QObject *parent = 0);
    QXYSeries *xySeries() override { return this; }
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QAbstractAxis *axisAngular() { return m_axes->axisX(); }
    void setAxisAngular(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisRadial() { return m_axes->axisY(); }
    void setAxisRadial(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    qreal width() const;
    void setWidth(qreal width);
    Qt::PenStyle style() const;
    void setStyle(Qt::PenStyle style);
    Qt::PenCapStyle capStyle() const;
    void setCapStyle(Qt::PenCapStyle capStyle);
    QQmlListProperty<QObject> declarativeChildren();

public: // from QDeclarativeParserStatus
    void classBegin() override { DeclarativeXySeries::classBegin(); }
    void componentComplete() override { DeclarativeXySeries::componentComplete(); }

public:
    Q_INVOKABLE void append(qreal x, qreal y) { DeclarativeXySeries::append(x, y); }
    Q_INVOKABLE void replace(qreal oldX, qreal oldY, qreal newX, qreal newY) { DeclarativeXySeries::replace(oldX, oldY, newX, newY); }
    Q_REVISION(1, 3) Q_INVOKABLE void replace(int index, qreal newX, qreal newY) { DeclarativeXySeries::replace(index, newX, newY); }
    Q_INVOKABLE void remove(qreal x, qreal y) { DeclarativeXySeries::remove(x, y); }
    Q_REVISION(1, 3) Q_INVOKABLE void remove(int index) { DeclarativeXySeries::remove(index); }
    Q_REVISION(2, 1) Q_INVOKABLE void removePoints(int index, int count) { DeclarativeXySeries::removePoints(index, count); }
    Q_INVOKABLE void insert(int index, qreal x, qreal y) { DeclarativeXySeries::insert(index, x, y); }
    Q_INVOKABLE void clear() { DeclarativeXySeries::clear(); }
    Q_INVOKABLE QPointF at(int index) { return DeclarativeXySeries::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);
    Q_REVISION(1, 3) void axisAngularChanged(QAbstractAxis *axis);
    Q_REVISION(1, 3) void axisRadialChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void widthChanged(qreal width);
    Q_REVISION(1, 1) void styleChanged(Qt::PenStyle style);
    Q_REVISION(1, 1) void capStyleChanged(Qt::PenCapStyle capStyle);

public Q_SLOTS:
    void handleCountChanged(int index);

public:
    static void appendDeclarativeChildren(QQmlListProperty<QObject> *list, QObject *element);

    DeclarativeAxes *m_axes;
};

QT_END_NAMESPACE

#endif // DECLARATIVELINESERIES_H
