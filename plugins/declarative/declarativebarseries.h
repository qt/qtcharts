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

#ifndef DECLARATIVEBARSERIES_H
#define DECLARATIVEBARSERIES_H

#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qhorizontalbarseries.h"
#include "qhorizontalstackedbarseries.h"
#include "qhorizontalpercentbarseries.h"
#include "qbarset.h"
#include "declarativeaxes.h"
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativeBarSet : public QBarSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged REVISION 1)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit DeclarativeBarSet(QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);
    qreal borderWidth() const;
    void setBorderWidth(qreal borderWidth);

public: // From QBarSet
    Q_INVOKABLE void append(qreal value) { QBarSet::append(value); }
    Q_INVOKABLE void remove(const int index, const int count = 1) { QBarSet::remove(index, count); }
    Q_INVOKABLE void replace(int index, qreal value) { QBarSet::replace(index, value); }
    Q_INVOKABLE qreal at(int index) { return QBarSet::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    Q_REVISION(1) void borderWidthChanged(qreal width);

private Q_SLOTS:
    void handleCountChanged(int index, int count);
};

class DeclarativeBarSeries : public QBarSeries, public QDeclarativeParserStatus
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
    explicit DeclarativeBarSeries(QDeclarativeItem *parent = 0);
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
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QBarSeries::clear(); }

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

class DeclarativeStackedBarSeries : public QStackedBarSeries, public QDeclarativeParserStatus
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
    explicit DeclarativeStackedBarSeries(QDeclarativeItem *parent = 0);
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
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QStackedBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QStackedBarSeries::clear(); }

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

class DeclarativePercentBarSeries : public QPercentBarSeries, public QDeclarativeParserStatus
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
    explicit DeclarativePercentBarSeries(QDeclarativeItem *parent = 0);
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
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QPercentBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QPercentBarSeries::clear(); }

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

class DeclarativeHorizontalBarSeries : public QHorizontalBarSeries, public QDeclarativeParserStatus
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
    explicit DeclarativeHorizontalBarSeries(QDeclarativeItem *parent = 0);
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
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QHorizontalBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QHorizontalBarSeries::clear(); }

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

class DeclarativeHorizontalStackedBarSeries : public QHorizontalStackedBarSeries, public QDeclarativeParserStatus
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
    explicit DeclarativeHorizontalStackedBarSeries(QDeclarativeItem *parent = 0);
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
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QHorizontalStackedBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QHorizontalStackedBarSeries::clear(); }

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

class DeclarativeHorizontalPercentBarSeries : public QHorizontalPercentBarSeries, public QDeclarativeParserStatus
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
    explicit DeclarativeHorizontalPercentBarSeries(QDeclarativeItem *parent = 0);
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
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QHorizontalPercentBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QHorizontalPercentBarSeries::clear(); }

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

#endif // DECLARATIVEBARSERIES_H
