/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtTest/QtTest>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include "tst_definitions.h"

class tst_quick2 : public QObject
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
    QString componentErrors(const QQmlComponent* component) const;
    QString imports_1_1();
    QString imports_1_3();

};

QString tst_quick2::componentErrors(const QQmlComponent* component) const
{
    Q_ASSERT(component);

    QStringList errors;

    foreach (QQmlError const& error, component->errors()) {
        errors  << error.toString();
    }

    return errors.join("\n");
}

QString tst_quick2::imports_1_1()
{
    return "import QtQuick 2.0 \n"
           "import QtCommercial.Chart 1.1 \n";
}

QString tst_quick2::imports_1_3()
{
    return "import QtQuick 2.0 \n"
           "import QtCommercial.Chart 1.3 \n";
}


void tst_quick2::initTestCase()
{
}

void tst_quick2::cleanupTestCase()
{
}

void tst_quick2::init()
{

}

void tst_quick2::cleanup()
{

}

void tst_quick2::checkPlugin_data()
{
    QTest::addColumn<QString>("source");

    QTest::newRow("createChartView") <<  imports_1_1() + "ChartView{}";
    QTest::newRow("XYPoint") << imports_1_1() + "XYPoint{}";
    QTest::newRow("scatterSeries") <<  imports_1_1() + "ScatterSeries{}";
    QTest::newRow("lineSeries") <<  imports_1_1() + "LineSeries{}";
    QTest::newRow("splineSeries") <<  imports_1_1() + "SplineSeries{}";
    QTest::newRow("areaSeries") <<  imports_1_1() + "AreaSeries{}";
    QTest::newRow("barSeries") << imports_1_1() + "BarSeries{}";
    QTest::newRow("stackedBarSeries") << imports_1_1() + "StackedBarSeries{}";
    QTest::newRow("precentBarSeries") << imports_1_1() + "PercentBarSeries{}";
    QTest::newRow("horizonatlBarSeries") << imports_1_1() + "HorizontalBarSeries{}";
    QTest::newRow("horizonatlStackedBarSeries") << imports_1_1() + "HorizontalStackedBarSeries{}";
    QTest::newRow("horizonatlstackedBarSeries") << imports_1_1() + "HorizontalPercentBarSeries{}";
    QTest::newRow("pieSeries") << imports_1_1() + "PieSeries{}";
    QTest::newRow("PieSlice") << imports_1_1() + "PieSlice{}";
    QTest::newRow("BarSet") << imports_1_1() + "BarSet{}";
    QTest::newRow("HXYModelMapper") << imports_1_1() + "HXYModelMapper{}";
    QTest::newRow("VXYModelMapper") << imports_1_1() + "VXYModelMapper{}";
    QTest::newRow("HPieModelMapper") << imports_1_1() + "HPieModelMapper{}";
    QTest::newRow("HPieModelMapper") << imports_1_1() + "HPieModelMapper{}";
    QTest::newRow("HBarModelMapper") << imports_1_1() + "HBarModelMapper{}";
    QTest::newRow("VBarModelMapper") << imports_1_1() + "VBarModelMapper{}";
    QTest::newRow("ValueAxis") << imports_1_1() + "ValueAxis{}";
#ifndef QT_ON_ARM
    QTest::newRow("DateTimeAxis") << imports_1_1() + "DateTimeAxis{}";
#endif
    QTest::newRow("CategoryAxis") << imports_1_1() + "CategoryAxis{}";
    QTest::newRow("CategoryRange") << imports_1_1() + "CategoryRange{}";
    QTest::newRow("BarCategoryAxis") << imports_1_1() + "BarCategoryAxis{}";

    QTest::newRow("createPolarChartView") <<  imports_1_3() + "PolarChartView{}";
    QTest::newRow("LogValueAxis") <<  imports_1_3() + "LogValueAxis{}";
}

void tst_quick2::checkPlugin()
{
    QFETCH(QString, source);
    QQmlEngine engine;
    engine.addImportPath(QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), QLatin1String("qml")));
    QQmlComponent component(&engine);
    component.setData(source.toLatin1(), QUrl());
    QVERIFY2(!component.isError(), qPrintable(componentErrors(&component)));
    TRY_COMPARE(component.status(), QQmlComponent::Ready);
    QObject *obj = component.create();
    QVERIFY(obj != 0);
    delete obj;
}

QTEST_MAIN(tst_quick2)

#include "tst_quick2.moc"

