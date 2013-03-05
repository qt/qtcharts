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
#include <QtTest/QtTest>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include "tst_definitions.h"

class tst_QML : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:
    void checkPlugin_data();
    void checkPlugin();
private:
    QString componentErrors(const QDeclarativeComponent* component) const;
    QString imports();

};

QString tst_QML::componentErrors(const QDeclarativeComponent* component) const
{
    Q_ASSERT(component);

    QStringList errors;

    foreach (QDeclarativeError const& error, component->errors()) {
        errors  << error.toString();
    }

    return errors.join("\n");
}

QString tst_QML::imports()
{
    return "import QtQuick 1.0 \n"
           "import QtCommercial.Chart 1.1 \n";
}


void tst_QML::initTestCase()
{
}

void tst_QML::cleanupTestCase()
{
}

void tst_QML::init()
{

}

void tst_QML::cleanup()
{

}

void tst_QML::checkPlugin_data()
{
    QTest::addColumn<QString>("source");

    QTest::newRow("createChartView") <<  imports() + "ChartView{}";
    QTest::newRow("XYPoint") << imports() + "XYPoint{}";
    QTest::newRow("scatterSeries") <<  imports() + "ScatterSeries{}";
    QTest::newRow("lineSeries") <<  imports() + "LineSeries{}";
    QTest::newRow("splineSeries") <<  imports() + "SplineSeries{}";
    QTest::newRow("areaSeries") <<  imports() + "AreaSeries{}";
    QTest::newRow("barSeries") << imports() + "BarSeries{}";
    QTest::newRow("stackedBarSeries") << imports() + "StackedBarSeries{}";
    QTest::newRow("precentBarSeries") << imports() + "PercentBarSeries{}";
    QTest::newRow("horizonatlBarSeries") << imports() + "HorizontalBarSeries{}";
    QTest::newRow("horizonatlStackedBarSeries") << imports() + "HorizontalStackedBarSeries{}";
    QTest::newRow("horizonatlstackedBarSeries") << imports() + "HorizontalPercentBarSeries{}";
    QTest::newRow("pieSeries") << imports() + "PieSeries{}";
    QTest::newRow("PieSlice") << imports() + "PieSlice{}";
    QTest::newRow("BarSet") << imports() + "BarSet{}";
    QTest::newRow("HXYModelMapper") << imports() + "HXYModelMapper{}";
    QTest::newRow("VXYModelMapper") << imports() + "VXYModelMapper{}";
    QTest::newRow("HPieModelMapper") << imports() + "HPieModelMapper{}";
    QTest::newRow("HPieModelMapper") << imports() + "HPieModelMapper{}";
    QTest::newRow("HBarModelMapper") << imports() + "HBarModelMapper{}";
    QTest::newRow("VBarModelMapper") << imports() + "VBarModelMapper{}";
    QTest::newRow("ValueAxis") << imports() + "ValueAxis{}";
#ifndef QT_ON_ARM
    QTest::newRow("DateTimeAxis") << imports() + "DateTimeAxis{}";
#endif
    QTest::newRow("CategoryAxis") << imports() + "CategoryAxis{}";
    QTest::newRow("CategoryRange") << imports() + "CategoryRange{}";
    QTest::newRow("BarCategoryAxis") << imports() + "BarCategoryAxis{}";
}

void tst_QML::checkPlugin()
{
    QFETCH(QString, source);
    QDeclarativeEngine engine;
    QDeclarativeComponent component(&engine);
    component.setData(source.toLatin1(), QUrl());
    QVERIFY2(!component.isError(), qPrintable(componentErrors(&component)));
    TRY_COMPARE(component.status(), QDeclarativeComponent::Ready);
    QObject *obj = component.create();
    QVERIFY(obj != 0);

    //
    //TODO:
    //  QCOMPARE(obj->property("something").toInt(), 0);

    delete obj;
}

QTEST_MAIN(tst_QML)

#include "tst_qml.moc"

