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
    QStackedBarSeries* series = new QStackedBarSeries();
    QBarCategories categories;
    categories << "test1" << "test2" << "test3";
    series->setCategories(categories);

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QSignalSpy setSpy1(set1, SIGNAL(clicked(QString)));
    QSignalSpy setSpy2(set2, SIGNAL(clicked(QString)));
    QSignalSpy seriesSpy(series,SIGNAL(clicked(QBarSet*,QString)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

//====================================================================================
// barset 1, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(115,230));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(setSpy1.count(), 1);
    QCOMPARE(setSpy2.count(), 0);
    QCOMPARE(seriesSpy.count(), 1);
    QList<QVariant> setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::String);
    QVERIFY(setSpyArg.at(0).toString().compare(QString("test1")) == 0);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);

//====================================================================================
// barset 1, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(205,230));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(setSpy1.count(), 1);
    QCOMPARE(setSpy2.count(), 0);
    QCOMPARE(seriesSpy.count(), 1);
    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::String);
    QVERIFY(setSpyArg.at(0).toString().compare(QString("test2")) == 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);

//====================================================================================
// barset 1, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(300,230));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(setSpy1.count(), 1);
    QCOMPARE(setSpy2.count(), 0);
    QCOMPARE(seriesSpy.count(), 1);
    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::String);
    QVERIFY(setSpyArg.at(0).toString().compare(QString("test3")) == 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);

//====================================================================================
// barset 2, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(115,140));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(setSpy1.count(), 0);
    QCOMPARE(setSpy2.count(), 1);
    QCOMPARE(seriesSpy.count(), 1);
    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::String);
    QVERIFY(setSpyArg.at(0).toString().compare(QString("test1")) == 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);

//====================================================================================
// barset 2, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(205,140));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(setSpy1.count(), 0);
    QCOMPARE(setSpy2.count(), 1);
    QCOMPARE(seriesSpy.count(), 1);
    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::String);
    QVERIFY(setSpyArg.at(0).toString().compare(QString("test2")) == 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);

//====================================================================================
// barset 2, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(300,140));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(setSpy1.count(), 0);
    QCOMPARE(setSpy2.count(), 1);
    QCOMPARE(seriesSpy.count(), 1);
    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::String);
    QVERIFY(setSpyArg.at(0).toString().compare(QString("test3")) == 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);

//====================================================================================
// no event cases
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(1,1));     // Outside of both sets
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(1,1));    // Right mouse button outside and inside sets
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(115,230)); // barset 1, category test1
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(205,230)); // barset 1, category test2
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(300,230)); // barset 1, category test3
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(115,140)); // barset 2, category test1
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(205,140)); // barset 2, category test2
    QTest::mouseClick(view.viewport(), Qt::RightButton, 0, QPoint(300,140)); // barset 2, category test3

    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
    QCOMPARE(setSpy1.count(), 0);
    QCOMPARE(setSpy2.count(), 0);
    QCOMPARE(seriesSpy.count(), 0);
}

void tst_QStackedBarSeries::mousehovered_data()
{

}

void tst_QStackedBarSeries::mousehovered()
{
    QStackedBarSeries* series = new QStackedBarSeries();
    QBarCategories categories;
    categories << "test1" << "test2" << "test3";
    series->setCategories(categories);

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QSignalSpy setSpy1(set1, SIGNAL(hovered(bool)));
    QSignalSpy setSpy2(set2, SIGNAL(hovered(bool)));
    QSignalSpy seriesSpy(series,SIGNAL(hovered(QBarSet*,bool)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

//=======================================================================
// move mouse to left border
    QTest::mouseMove(view.viewport(), QPoint(0, 230));

    QVERIFY(setSpy1.count() == 0);
    QVERIFY(setSpy2.count() == 0);
    QVERIFY(seriesSpy.count() == 0);

//=======================================================================
// move mouse on top of set1
    QTest::mouseMove(view.viewport(), QPoint(115,230));

    QVERIFY(setSpy1.count() == 1);
    QVERIFY(setSpy2.count() == 0);
    QVERIFY(seriesSpy.count() == 1);

    QList<QVariant> setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(setSpyArg.at(0).toBool() == true);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);

//=======================================================================
// move mouse from top of set1 to top of set2
    QTest::mouseMove(view.viewport(), QPoint(115,140));

    QVERIFY(setSpy1.count() == 1);
    QVERIFY(setSpy2.count() == 1);
    QVERIFY(seriesSpy.count() == 2);

    // should leave set1
    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(setSpyArg.at(0).toBool() == false);

    // should enter set2
    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(setSpyArg.at(0).toBool() == true);

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
    QTest::mouseMove(view.viewport(), QPoint(0,140));

    QVERIFY(setSpy1.count() == 0);
    QVERIFY(setSpy2.count() == 1);
    QVERIFY(seriesSpy.count() == 1);

    // should leave set2 (event via set)
    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(setSpyArg.at(0).toBool() == false);

    // should leave set2 (event via series)
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == false);
}


/*
bool setModel(QAbstractItemModel *model);
void setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
void setModelMappingRange(int first, int count = -1);
*/
QTEST_MAIN(tst_QStackedBarSeries)

#include "tst_qstackedbarseries.moc"

