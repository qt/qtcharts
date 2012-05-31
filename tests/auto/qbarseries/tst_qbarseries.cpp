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
#include <qbarseries.h>
#include <qbarset.h>
#include <qchartview.h>
#include <qchart.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QBarSet*)

class tst_QBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qbarseries_data();
    void qbarseries();
    void type_data();
    void type();
    void append_data();
    void append();
    void remove_data();
    void remove();
    void appendList_data();
    void appendList();
    void removeList_data();
    void removeList();
    void barsetCount_data();
    void barsetCount();
    void barSets_data();
    void barSets();
    void setLabelsVisible_data();
    void setLabelsVisible();
    void mouseclicked_data();
    void mouseclicked();
    void mousehovered_data();
    void mousehovered();

private:
    QBarSeries* m_barseries;
    QBarSeries* m_barseries_with_sets;

    QList<QBarSet*> m_testSets;

};

void tst_QBarSeries::initTestCase()
{
    qRegisterMetaType<QBarSet*>("QBarSet*");
}

void tst_QBarSeries::cleanupTestCase()
{
}

void tst_QBarSeries::init()
{
    m_barseries = new QBarSeries();
    m_barseries_with_sets = new QBarSeries();

    for (int i=0; i<5; i++) {
        m_testSets.append(new QBarSet("testset"));
        m_barseries_with_sets->append(m_testSets.at(i));
    }
}

void tst_QBarSeries::cleanup()
{
    foreach(QBarSet* s, m_testSets) {
        m_barseries_with_sets->remove(s);
        delete s;
    }
    m_testSets.clear();

    delete m_barseries;
    m_barseries = 0;
    delete m_barseries_with_sets;
    m_barseries_with_sets = 0;
}

void tst_QBarSeries::qbarseries_data()
{
}

void tst_QBarSeries::qbarseries()
{
    QBarSeries *barseries = new QBarSeries();
    QVERIFY(barseries != 0);
}

void tst_QBarSeries::type_data()
{

}

void tst_QBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeBar);
}

void tst_QBarSeries::append_data()
{
}

void tst_QBarSeries::append()
{
    QVERIFY(m_barseries->barsetCount() == 0);

    bool ret = false;

    // Try adding barset
    QBarSet *barset = new QBarSet("testset");
    ret = m_barseries->append(barset);

    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == 1);

    // Try adding another set
    QBarSet *barset2 = new QBarSet("testset2");
    ret = m_barseries->append(barset2);

    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == 2);

    // Try adding same set again
    ret = m_barseries->append(barset2);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == 2);

    // Try adding null set
    ret = m_barseries->append(0);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == 2);

}

void tst_QBarSeries::remove_data()
{
}

void tst_QBarSeries::remove()
{
    int count = m_testSets.count();
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try to remove null pointer (should not remove, should not crash)
    bool ret = false;
    ret = m_barseries_with_sets->remove(0);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try to remove invalid pointer (should not remove, should not crash)
    ret = m_barseries_with_sets->remove((QBarSet*) (m_testSets.at(0) + 1) );
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // remove some sets
    ret = m_barseries_with_sets->remove(m_testSets.at(2));
    QVERIFY(ret == true);
    ret = m_barseries_with_sets->remove(m_testSets.at(3));
    QVERIFY(ret == true);
    ret = m_barseries_with_sets->remove(m_testSets.at(4));
    QVERIFY(ret == true);

    QVERIFY(m_barseries_with_sets->barsetCount() == 2);

    QList<QBarSet*> verifysets = m_barseries_with_sets->barSets();

    QVERIFY(verifysets.at(0) == m_testSets.at(0));
    QVERIFY(verifysets.at(1) == m_testSets.at(1));

    // Try removing all sets again (should be ok, even if some sets have already been removed)
    ret = false;
    for (int i=0; i<count; i++) {
        ret |= m_barseries_with_sets->remove(m_testSets.at(i));
    }

    QVERIFY(ret == true);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);
}

void tst_QBarSeries::appendList_data()
{

}

void tst_QBarSeries::appendList()
{
    int count = 5;
    QVERIFY(m_barseries->barsetCount() == 0);

    QList<QBarSet*> sets;
    for (int i=0; i<count; i++) {
        sets.append(new QBarSet("testset"));
    }

    // Append new sets (should succeed, count should match the count of sets)
    bool ret = false;
    ret = m_barseries->append(sets);
    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == count);

    // Append same sets again (should fail, count should remain same)
    ret = m_barseries->append(sets);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == count);

    // Try append empty list (should succeed, but count should remain same)
    QList<QBarSet*> invalidList;
    ret = m_barseries->append(invalidList);
    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == count);

    // Try append list with one new and one existing set (should fail, count remains same)
    invalidList.append(new QBarSet("ok set"));
    invalidList.append(sets.at(0));
    ret = m_barseries->append(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == count);

    // Try append list with null pointers (should fail, count remains same)
    QList<QBarSet*> invalidList2;
    invalidList2.append(0);
    invalidList2.append(0);
    invalidList2.append(0);
    ret = m_barseries->append(invalidList2);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == count);
}

void tst_QBarSeries::removeList_data()
{

}

void tst_QBarSeries::removeList()
{
    int count = m_testSets.count();
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try removing empty list of sets (should return false, since no barsets were removed)
    bool ret = false;
    QList<QBarSet*> invalidList;
    ret = m_barseries_with_sets->remove(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Add some null pointers to list
    invalidList.append(0);
    invalidList.append(0);
    invalidList.append(0);

    // Try removing null pointers from list (should return false, should not crash, should not remove anything)
    ret = m_barseries_with_sets->remove(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // remove all sets (should return true, since sets were removed)
    ret = m_barseries_with_sets->remove(m_testSets);
    QVERIFY(ret == true);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);

    // Try removing invalid list again (should return false, since no barsets were removed)
    ret = m_barseries_with_sets->remove(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);

    // remove all sets again (should return false, since barsets were already removed)
    ret = m_barseries_with_sets->remove(m_testSets);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);
}

void tst_QBarSeries::barsetCount_data()
{

}

void tst_QBarSeries::barsetCount()
{
    QVERIFY(m_barseries->barsetCount() == 0);
    QVERIFY(m_barseries_with_sets->barsetCount() == m_testSets.count());
}

void tst_QBarSeries::barSets_data()
{

}

void tst_QBarSeries::barSets()
{
    QVERIFY(m_barseries->barSets().count() == 0);

    QList<QBarSet*> sets = m_barseries_with_sets->barSets();
    QVERIFY(sets.count() == m_testSets.count());

    for (int i=0; i<m_testSets.count(); i++) {
        QVERIFY(sets.at(i) == m_testSets.at(i));
    }
}

void tst_QBarSeries::setLabelsVisible_data()
{

}

void tst_QBarSeries::setLabelsVisible()
{
    // labels should be invisible by default
    QVERIFY(m_barseries->isLabelsVisible() == false);
    QVERIFY(m_barseries_with_sets->isLabelsVisible() == false);

    // turn labels to visible
    m_barseries_with_sets->setLabelsVisible(true);
    // TODO: test the signal
    QVERIFY(m_barseries_with_sets->isLabelsVisible() == true);

    // turn labels to invisible
    m_barseries_with_sets->setLabelsVisible(false);
    // TODO: test the signal
    QVERIFY(m_barseries_with_sets->isLabelsVisible() == false);

    // without parameter, should turn labels to visible
    m_barseries_with_sets->setLabelsVisible();
    // TODO: test the signal
    QVERIFY(m_barseries_with_sets->isLabelsVisible() == true);
}

void tst_QBarSeries::mouseclicked_data()
{

}

void tst_QBarSeries::mouseclicked()
{
    QBarSeries* series = new QBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << QPointF(0,10) << QPointF(1,10) << QPointF(2,10);
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << QPointF(0.3,10) << QPointF(1.3,10) << QPointF(2.3,10);
    series->append(set2);

    QSignalSpy seriesSpy(series,SIGNAL(clicked(QBarSet*,int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

//====================================================================================
// barset 1, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(106,142));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 0);

//====================================================================================
// barset 1, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(199,142));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 1);

//====================================================================================
// barset 1, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(291,142));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 2);

//====================================================================================
// barset 2, category test1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(134,142));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 0);

//====================================================================================
// barset 2, category test2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(227,142));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 1);

//====================================================================================
// barset 2, category test3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, QPoint(319,142));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(1).toInt() == 2);
}

void tst_QBarSeries::mousehovered_data()
{

}

void tst_QBarSeries::mousehovered()
{
    QBarSeries* series = new QBarSeries();
    QStringList categories;
    categories << "test1" << "test2" << "test3";
//    series->setCategories(categories);

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << QPointF(0.1,10) << QPointF(1.1,10) << QPointF(2.1,10);
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << QPointF(0.3,10) << QPointF(1.3,10) << QPointF(2.3,10);
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
    QTest::mouseMove(view.viewport(), QPoint(0, 142));

    QVERIFY(seriesSpy.count() == 0);

//=======================================================================
// move mouse on top of set1
    QTest::mouseMove(view.viewport(), QPoint(106,142));

    QVERIFY(seriesSpy.count() == 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set1);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == true);

//=======================================================================
// move mouse from top of set1 to top of set2
    QTest::mouseMove(view.viewport(), QPoint(134,142));

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
    QTest::mouseMove(view.viewport(), QPoint(134,0));
    QVERIFY(seriesSpy.count() == 1);

    // should leave set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(0)), set2);
    QVERIFY(seriesSpyArg.at(1).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(1).toBool() == false);
}

QTEST_MAIN(tst_QBarSeries)

#include "tst_qbarseries.moc"

