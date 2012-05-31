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
#include <qgroupedbarseries.h>
#include <qbarset.h>
#include <qchartview.h>
#include <qchart.h>
#include <QBarModelMapper>
#include <QStandardItemModel>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QBarSet*)

class tst_QGroupedBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qgroupedbarseries_data();
    void qgroupedbarseries();
    void type_data();
    void type();
    void mouseclicked_data();
    void mouseclicked();
    void mousehovered_data();
    void mousehovered();

private:
    QGroupedBarSeries* m_barseries;
};

void tst_QGroupedBarSeries::initTestCase()
{
    qRegisterMetaType<QBarSet*>("QBarSet*");
}

void tst_QGroupedBarSeries::cleanupTestCase()
{
}

void tst_QGroupedBarSeries::init()
{
    m_barseries = new QGroupedBarSeries();
}

void tst_QGroupedBarSeries::cleanup()
{
    delete m_barseries;
    m_barseries = 0;
}

void tst_QGroupedBarSeries::qgroupedbarseries_data()
{
}

void tst_QGroupedBarSeries::qgroupedbarseries()
{
    QGroupedBarSeries *barseries = new QGroupedBarSeries();
    QVERIFY(barseries != 0);
}

void tst_QGroupedBarSeries::type_data()
{

}

void tst_QGroupedBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeGroupedBar);
}

void tst_QGroupedBarSeries::mouseclicked_data()
{

}

void tst_QGroupedBarSeries::mouseclicked()
{
    QGroupedBarSeries* series = new QGroupedBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QSignalSpy seriesSpy(series,SIGNAL(clicked(QBarSet*,int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

//====================================================================================
// barset 1, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(95,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 0);

//====================================================================================
// barset 1, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(187,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 1);

//====================================================================================
// barset 1, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(280,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 2);

//====================================================================================
// barset 2, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(118,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 0);

//====================================================================================
// barset 2, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(210,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 1);

//====================================================================================
// barset 2, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(303,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 2);
}

void tst_QGroupedBarSeries::mousehovered_data()
{

}

void tst_QGroupedBarSeries::mousehovered()
{
    QGroupedBarSeries* series = new QGroupedBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QSignalSpy seriesSpy(series,SIGNAL(hovered(QBarSet*,bool)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    //this is hack since view does not get events otherwise
    view.setMouseTracking(true);

//=======================================================================
// move mouse to left border
    qDebug() << "move mouse to left border";
    QTest::mouseMove(view.viewport(), QPoint(0, 143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QVERIFY(seriesSpy.count() == 0);

//=======================================================================
// move mouse on top of set1
    qDebug() << "move mouse on top of set1";
    QTest::mouseMove(view.viewport(), QPoint(95,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 10000);

    QVERIFY(seriesSpy.count() == 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == true);

//=======================================================================
// move mouse from top of set1 to top of set2
    qDebug() << "move mouse from top of set1 to top of set2";
    QTest::mouseMove(view.viewport(), QPoint(118,143));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 10000);

    QVERIFY(seriesSpy.count() == 2);

    // should leave set1
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == false);

    // should enter set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == true);

//=======================================================================
// move mouse from top of set2 to background
    qDebug() << "move mouse from top of set2 to background";

    QTest::mouseMove(view.viewport(), QPoint(118,0));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 10000);

    QVERIFY(seriesSpy.count() == 1);

    // should leave set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == false);
}

QTEST_MAIN(tst_QGroupedBarSeries)

#include "tst_qgroupedbarseries.moc"

