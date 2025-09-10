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

#ifndef DECLARATIVEBARSERIES_H
#define DECLARATIVEBARSERIES_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QHorizontalPercentBarSeries>
#include <QtCharts/QBarSet>
#include <private/declarativechartglobal_p.h>
#include <private/declarativeaxes_p.h>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE

class QChart;

class Q_CHARTSQML_EXPORT DeclarativeBarSet : public QBarSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged REVISION(1, 1))
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION(1, 4))
    QML_NAMED_ELEMENT(BarSet)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeBarSet(QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);
    qreal borderWidth() const;
    void setBorderWidth(qreal borderWidth);
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

public: // From QBarSet
    Q_INVOKABLE void append(qreal value) { QBarSet::append(value); }
    Q_INVOKABLE void remove(const int index, const int count = 1) { QBarSet::remove(index, count); }
    Q_INVOKABLE void replace(int index, qreal value) { QBarSet::replace(index, value); }
    Q_INVOKABLE qreal at(int index) { return QBarSet::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    Q_REVISION(1, 1) void borderWidthChanged(qreal width);
    Q_REVISION(1, 4) void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleCountChanged(int index, int count);
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class Q_CHARTSQML_EXPORT DeclarativeBarSeries : public QBarSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(BarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeBarSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);

public:
    // TODO: This method is used from classes that don't inherit DeclarativeBarSeries
    //       Its implementation is empty. None of this makes any sense.
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

    DeclarativeAxes *m_axes;
};

class Q_CHARTSQML_EXPORT DeclarativeStackedBarSeries : public QStackedBarSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(StackedBarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeStackedBarSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QStackedBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QStackedBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);

private:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

public:
    DeclarativeAxes *m_axes;
};

class Q_CHARTSQML_EXPORT DeclarativePercentBarSeries : public QPercentBarSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(PercentBarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativePercentBarSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QPercentBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QPercentBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);

private:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

public:
    DeclarativeAxes *m_axes;
};

class Q_CHARTSQML_EXPORT DeclarativeHorizontalBarSeries : public QHorizontalBarSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(HorizontalBarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeHorizontalBarSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QHorizontalBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QHorizontalBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);

private:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

public:
    DeclarativeAxes *m_axes;
};

class Q_CHARTSQML_EXPORT DeclarativeHorizontalStackedBarSeries : public QHorizontalStackedBarSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(HorizontalStackedBarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeHorizontalStackedBarSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QHorizontalStackedBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QHorizontalStackedBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);

private:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

public:
    DeclarativeAxes *m_axes;
};

class Q_CHARTSQML_EXPORT DeclarativeHorizontalPercentBarSeries : public QHorizontalPercentBarSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(HorizontalPercentBarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeHorizontalPercentBarSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();

public:
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QHorizontalPercentBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QHorizontalPercentBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);

private:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

public:
    DeclarativeAxes *m_axes;
};

QT_END_NAMESPACE

#endif // DECLARATIVEBARSERIES_H
