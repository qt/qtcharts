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

#ifndef DECLARATIVEBOXPLOT_H
#define DECLARATIVEBOXPLOT_H

#include "qboxset.h"
#include "declarativeaxes.h"
#include "qboxplotseries.h"
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeBoxSet : public QBoxSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit DeclarativeBoxSet(QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);

public: // From QBoxSet
    Q_INVOKABLE void append(qreal value) { QBoxSet::append(value); }
    Q_INVOKABLE void replace(int index, qreal value) { QBoxSet::replace(index, value); }
    Q_INVOKABLE qreal at(int index) { return QBoxSet::at(index); }

Q_SIGNALS:
    void countChanged(int count);

private Q_SLOTS:
    void handleCountChanged(int index, int count);
};

class DeclarativeBoxPlotSeries : public QBoxPlotSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION 1)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION 1)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION 2)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION 2)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeBoxPlotSeries(QDeclarativeItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    Q_REVISION(2) QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    Q_REVISION(2) void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    Q_REVISION(2) QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    Q_REVISION(2) void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QDeclarativeListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBoxSet *at(int index);
    Q_INVOKABLE DeclarativeBoxSet *append(QVariantList values) { return insert(count(), values); }
    Q_INVOKABLE DeclarativeBoxSet *insert(int index, QVariantList values);
    Q_INVOKABLE bool remove(QBoxSet *boxset) { return QBoxPlotSeries::remove(boxset); }
    Q_INVOKABLE void clear() { return QBoxPlotSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    Q_REVISION(1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(2) void axisYRightChanged(QAbstractAxis *axis);

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);

public:
    DeclarativeAxes *m_axes;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBOXPLOT_H
