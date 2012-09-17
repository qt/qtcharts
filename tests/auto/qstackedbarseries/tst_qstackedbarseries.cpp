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

#include <QtTest/QtTest>
#include <qstackedbarseries.h>
#include <qbarset.h>
#include <qchartview.h>
#include <qchart.h>
#include "tst_definitions.h"

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QBarSet*)

class tst_QStackedBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qstackedbarseries_data();
    void qstackedbarseries();
    void type_data();
    void type();
    void mouseclicked_data();
    void mouseclicked();
    void mousehovered_data();
    void mousehovered();

private:
    QStackedBarSeries* m_barseries;
};

void tst_QStackedBarSeries::initTestCase()
{
    qRegisterMetaType<QBarSet*>("QBarSet*");
}

void tst_QStackedBarSeries::cleanupTestCase()
{
}

void tst_QStackedBarSeries::init()
{
    m_barseries = new QStackedBarSeries();
}

void tst_QStackedBarSeries::cleanup()
{
    delete m_barseries;
    m_barseries = 0;
}

void tst_QStackedBarSeries::qstackedbarseries_data()
{
}

void tst_QStackedBarSeries::qstackedbarseries()
{
    QStackedBarSeries *barseries = new QStackedBarSeries();
    QVERIFY(barseries != 0);
}

void tst_QStackedBarSeries::type_data()
{

}

void tst_QStackedBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeStackedBar);
}

void tst_QStackedBarSeries::mouseclicked_data()
{

}

void tst_QStackedBarSeries::mouseclicked()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QStackedBarSeries* series = new QStackedBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QSignalSpy seriesSpy(series,SIGNAL(clicked(int, QBarSet*)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

//====================================================================================
// barset 1, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(86,211));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 1, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(200,211));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 1, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(314,211));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

//====================================================================================
// barset 2, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(86,90));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 2, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(200,90));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 2, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(314,90));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);
}

void tst_QStackedBarSeries::mousehovered_data()
{

}

void tst_QStackedBarSeries::mousehovered()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QStackedBarSeries* series = new QStackedBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QSignalSpy seriesSpy(series,SIGNAL(hovered(bool, QBarSet*)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    //this is hack since view does not get events otherwise
    view.setMouseTracking(true);

//=======================================================================
// move mouse to left border
    QTest::mouseMove(view.viewport(), QPoint(0, 211));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 10000);
    TRY_COMPARE(seriesSpy.count(), 0);

//=======================================================================
// move mouse on top of set1
    QTest::mouseMove(view.viewport(), QPoint(86,211));
    TRY_COMPARE(seriesSpy.count(), 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == true);

//=======================================================================
// move mouse from top of set1 to top of set2
    QTest::mouseMove(view.viewport(), QPoint(86,90));
    TRY_COMPARE(seriesSpy.count(), 2);

    // should leave set1
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == false);

    // should enter set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == true);

//=======================================================================
// move mouse from top of set2 to background
    QTest::mouseMove(view.viewport(), QPoint(86,0));
    TRY_COMPARE(seriesSpy.count(), 1);

    // should leave set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == false);
}

QTEST_MAIN(tst_QStackedBarSeries)

#include "tst_qstackedbarseries.moc"

