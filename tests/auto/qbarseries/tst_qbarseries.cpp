// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtTest/QtTest>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include "tst_definitions.h"

QT_USE_NAMESPACE

Q_DECLARE_METATYPE(QBarSet*)
Q_DECLARE_METATYPE(QList<QBarSet*>)
Q_DECLARE_METATYPE(QAbstractBarSeries::LabelsPosition)

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
    void take_data();
    void take();
    void appendList_data();
    void appendList();
    void count_data();
    void count();
    void barSets_data();
    void barSets();
    void setLabelsVisible_data();
    void setLabelsVisible();
    void setLabelsFormat();
    void setLabelsPosition();
    void setLabelsAngle();
    void setLabelsPrecision();
    void opacity();
    void mouseclicked_data();
    void mouseclicked();
    void mousehovered_data();
    void mousehovered();
    void clearWithAnimations();
    void destruction();
    void mousePressed();
    void mouseReleased();
    void mouseDoubleClicked();

private:
    QBarSeries* m_barseries;
    QBarSeries* m_barseries_with_sets;

    QList<QBarSet*> m_testSets;

};

void tst_QBarSeries::initTestCase()
{
    qRegisterMetaType<QBarSet*>("QBarSet*");
    qRegisterMetaType<QList<QBarSet*> >("QList<QBarSet*>");
    qRegisterMetaType<QAbstractBarSeries::LabelsPosition>("QAbstractBarSeries::LabelsPosition");
}

void tst_QBarSeries::cleanupTestCase()
{
    QTest::qWait(1); // Allow final deleteLaters to run
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
    foreach (QBarSet* s, m_testSets) {
        m_barseries_with_sets->remove(s);
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
    delete barseries;
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
    QVERIFY(m_barseries->count() == 0);

    bool ret = false;

    // Try adding barset
    QBarSet *barset = new QBarSet("testset");
    ret = m_barseries->append(barset);

    QVERIFY(ret == true);
    QVERIFY(m_barseries->count() == 1);

    // Try adding another set
    QBarSet *barset2 = new QBarSet("testset2");
    ret = m_barseries->append(barset2);

    QVERIFY(ret == true);
    QVERIFY(m_barseries->count() == 2);

    // Try adding same set again
    ret = m_barseries->append(barset2);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->count() == 2);

    // Try adding null set
    ret = m_barseries->append(0);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->count() == 2);

}

void tst_QBarSeries::remove_data()
{
}

void tst_QBarSeries::remove()
{
    int count = m_testSets.size();
    QVERIFY(m_barseries_with_sets->count() == count);

    // Try to remove null pointer (should not remove, should not crash)
    bool ret = false;
    ret = m_barseries_with_sets->remove(0);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->count() == count);

    // Try to remove invalid pointer (should not remove, should not crash)
    ret = m_barseries_with_sets->remove((QBarSet*) (m_testSets.at(0) + 1));
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->count() == count);

    // remove some sets
    ret = m_barseries_with_sets->remove(m_testSets.at(2));
    QVERIFY(ret == true);
    ret = m_barseries_with_sets->remove(m_testSets.at(3));
    QVERIFY(ret == true);
    ret = m_barseries_with_sets->remove(m_testSets.at(4));
    QVERIFY(ret == true);

    QVERIFY(m_barseries_with_sets->count() == 2);

    QList<QBarSet*> verifysets = m_barseries_with_sets->barSets();

    QVERIFY(verifysets.at(0) == m_testSets.at(0));
    QVERIFY(verifysets.at(1) == m_testSets.at(1));

    // Try removing all sets again (should be ok, even if some sets have already been removed)
    ret = false;
    for (int i=0; i<count; i++) {
        ret |= m_barseries_with_sets->remove(m_testSets.at(i));
    }

    QVERIFY(ret == true);
    QVERIFY(m_barseries_with_sets->count() == 0);
}

void tst_QBarSeries::take_data()
{

}

void tst_QBarSeries::take()
{
    int count = m_testSets.size();
    QVERIFY(m_barseries_with_sets->count() == count);

    QSignalSpy countSpy(m_barseries_with_sets,SIGNAL(countChanged()));
    QSignalSpy removedSpy(m_barseries_with_sets,SIGNAL(barsetsRemoved(QList<QBarSet*>)));

    for (int i=0; i<m_testSets.size(); i++) {
        QBarSet* set = m_testSets.at(i);
        bool success = m_barseries_with_sets->take(set);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
        QVERIFY(success);
        TRY_COMPARE(countSpy.size(),1);
        TRY_COMPARE(removedSpy.size(),1);

        QList<QVariant> removedSpyArg = removedSpy.takeFirst();
        QList<QBarSet*> removedSets = qvariant_cast<QList<QBarSet*> > (removedSpyArg.at(0));
        QCOMPARE(removedSets.at(0), m_testSets.at(i));
        countSpy.takeFirst();
    }
}


void tst_QBarSeries::appendList_data()
{

}

void tst_QBarSeries::appendList()
{
    int count = 5;
    QVERIFY(m_barseries->count() == 0);

    QList<QBarSet*> sets;
    for (int i=0; i<count; i++) {
        sets.append(new QBarSet("testset"));
    }

    // Append new sets (should succeed, count should match the count of sets)
    bool ret = false;
    ret = m_barseries->append(sets);
    QVERIFY(ret == true);
    QVERIFY(m_barseries->count() == count);

    // Append same sets again (should fail, count should remain same)
    ret = m_barseries->append(sets);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->count() == count);

    // Try append empty list (should succeed, but count should remain same)
    QList<QBarSet*> invalidList;
    ret = m_barseries->append(invalidList);
    QVERIFY(ret == true);
    QVERIFY(m_barseries->count() == count);

    // Try append list with one new and one existing set (should fail, count remains same)
    invalidList.append(new QBarSet("ok set"));
    invalidList.append(sets.at(0));
    ret = m_barseries->append(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->count() == count);
    delete invalidList.at(0);

    // Try append list with null pointers (should fail, count remains same)
    QList<QBarSet*> invalidList2;
    invalidList2.append(0);
    invalidList2.append(0);
    invalidList2.append(0);
    ret = m_barseries->append(invalidList2);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->count() == count);
}

void tst_QBarSeries::count_data()
{

}

void tst_QBarSeries::count()
{
    QVERIFY(m_barseries->count() == 0);
    QVERIFY(m_barseries_with_sets->count() == m_testSets.size());
}

void tst_QBarSeries::barSets_data()
{

}

void tst_QBarSeries::barSets()
{
    QVERIFY(m_barseries->barSets().size() == 0);

    QList<QBarSet*> sets = m_barseries_with_sets->barSets();
    QVERIFY(sets.size() == m_testSets.size());

    for (int i=0; i<m_testSets.size(); i++) {
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

void tst_QBarSeries::setLabelsFormat()
{
    QSignalSpy labelsFormatSpy(m_barseries, SIGNAL(labelsFormatChanged(QString)));
    QCOMPARE(m_barseries->labelsFormat(), QString());

    QString format("(@value)");
    m_barseries->setLabelsFormat(format);
    TRY_COMPARE(labelsFormatSpy.size(), 1);
    QList<QVariant> arguments = labelsFormatSpy.takeFirst();
    QVERIFY(arguments.at(0).toString() == format);
    QCOMPARE(m_barseries->labelsFormat(), format);

    m_barseries->setLabelsFormat(QString());
    TRY_COMPARE(labelsFormatSpy.size(), 1);
    arguments = labelsFormatSpy.takeFirst();
    QVERIFY(arguments.at(0).toString() == QString());
    QCOMPARE(m_barseries->labelsFormat(), QString());
}

void tst_QBarSeries::setLabelsPosition()
{
    QSignalSpy labelsPositionSpy(m_barseries,
                             SIGNAL(labelsPositionChanged(QAbstractBarSeries::LabelsPosition)));
    QCOMPARE(m_barseries->labelsPosition(), QBarSeries::LabelsCenter);

    m_barseries->setLabelsPosition(QBarSeries::LabelsInsideEnd);
    TRY_COMPARE(labelsPositionSpy.size(), 1);
    QList<QVariant> arguments = labelsPositionSpy.takeFirst();
    QVERIFY(arguments.at(0).value<QAbstractBarSeries::LabelsPosition>()
                == QBarSeries::LabelsInsideEnd);
    QCOMPARE(m_barseries->labelsPosition(), QBarSeries::LabelsInsideEnd);

    m_barseries->setLabelsPosition(QBarSeries::LabelsInsideBase);
    TRY_COMPARE(labelsPositionSpy.size(), 1);
    arguments = labelsPositionSpy.takeFirst();
    QVERIFY(arguments.at(0).value<QAbstractBarSeries::LabelsPosition>()
            == QBarSeries::LabelsInsideBase);
    QCOMPARE(m_barseries->labelsPosition(), QBarSeries::LabelsInsideBase);

    m_barseries->setLabelsPosition(QBarSeries::LabelsOutsideEnd);
    TRY_COMPARE(labelsPositionSpy.size(), 1);
    arguments = labelsPositionSpy.takeFirst();
    QVERIFY(arguments.at(0).value<QAbstractBarSeries::LabelsPosition>()
            == QBarSeries::LabelsOutsideEnd);
    QCOMPARE(m_barseries->labelsPosition(), QBarSeries::LabelsOutsideEnd);

    m_barseries->setLabelsPosition(QBarSeries::LabelsCenter);
    TRY_COMPARE(labelsPositionSpy.size(), 1);
    arguments = labelsPositionSpy.takeFirst();
    QVERIFY(arguments.at(0).value<QAbstractBarSeries::LabelsPosition>()
            == QBarSeries::LabelsCenter);
    QCOMPARE(m_barseries->labelsPosition(), QBarSeries::LabelsCenter);
}

void tst_QBarSeries::setLabelsAngle()
{
    QSignalSpy labelsAngleSpy(m_barseries,
                             SIGNAL(labelsAngleChanged(qreal)));
    QCOMPARE(m_barseries->labelsAngle(), 0.0);

    m_barseries->setLabelsAngle(55.0);
    TRY_COMPARE(labelsAngleSpy.size(), 1);
    QList<QVariant> arguments = labelsAngleSpy.takeFirst();
    QVERIFY(arguments.at(0).value<qreal>() == 55.0);
    QCOMPARE(m_barseries->labelsAngle(), 55.0);
}

void tst_QBarSeries::setLabelsPrecision()
{
    QSignalSpy labelsPrecisionSpy(m_barseries,
                             SIGNAL(labelsPrecisionChanged(int)));
    QCOMPARE(m_barseries->labelsPrecision(), 6);

    m_barseries->setLabelsPrecision(9);
    TRY_COMPARE(labelsPrecisionSpy.size(), 1);
    QList<QVariant> arguments = labelsPrecisionSpy.takeFirst();
    QVERIFY(arguments.at(0).value<int>() == 9);
    QCOMPARE(m_barseries->labelsPrecision(), 9);
}

void tst_QBarSeries::opacity()
{
    QSignalSpy opacitySpy(m_barseries, SIGNAL(opacityChanged()));

    QCOMPARE(m_barseries->opacity(), 1.0);

    m_barseries->setOpacity(0.5);
    QCOMPARE(m_barseries->opacity(), 0.5);
    QCOMPARE(opacitySpy.size(), 1);

    m_barseries->setOpacity(0.0);
    QCOMPARE(m_barseries->opacity(), 0.0);
    QCOMPARE(opacitySpy.size(), 2);

    m_barseries->setOpacity(1.0);
    QCOMPARE(m_barseries->opacity(), 1.0);
    QCOMPARE(opacitySpy.size(), 3);
}

void tst_QBarSeries::mouseclicked_data()
{

}

void tst_QBarSeries::mouseclicked()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QBarSeries* series = new QBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);
    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesSpy(series,SIGNAL(clicked(int,QBarSet*)));
    QSignalSpy setSpy1(set1, SIGNAL(clicked(int)));
    QSignalSpy setSpy2(set2, SIGNAL(clicked(int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 10;  // From 0 to 10 because of maximum value in set is 10
    qreal rangeX = 3; // 3 values per set
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = 0;       // These come from internal domain used by barseries.
    qreal domainMinX = -0.5;    // No access to domain from outside, so use hard coded values.
    qreal rectWidth = (scaleX / setCount) * series->barWidth();

    QList<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal yPos = height + scaleY * domainMinY + plotArea.top();
        for (int set = 0; set < setCount; set++) {
            qreal xPos = (i - domainMinX) * scaleX + plotArea.left();
            xPos -= series->count()*rectWidth/2;
            xPos += set*rectWidth;

            qreal rectHeight = barSets.at(set)->at(i) * scaleY;
            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
            layout.append(rect);
        }
    }

//====================================================================================
// barset 1, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(0).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    QList<QVariant> setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 1, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(2).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 1, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(4).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 2);

//====================================================================================
// barset 2, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(1).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 2, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(3).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 2, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(5).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 2);
}

void tst_QBarSeries::mousehovered_data()
{
    QTest::addColumn<uint>("labelsPosition");
    QTest::addColumn<bool>("labelsVisible");

    QTest::newRow("labelsCenter") << (uint)QAbstractBarSeries::LabelsCenter << true;
    QTest::newRow("labelsInsideEnd") << (uint)QAbstractBarSeries::LabelsInsideEnd << true;
    QTest::newRow("labelsInsideBase") << (uint)QAbstractBarSeries::LabelsInsideBase << true;
    QTest::newRow("labelsOutsideEnd") << (uint)QAbstractBarSeries::LabelsOutsideEnd << true;
    QTest::newRow("noLabelsCenter") << (uint)QAbstractBarSeries::LabelsCenter << false;
}

void tst_QBarSeries::mousehovered()
{
    QFETCH(uint, labelsPosition);
    QFETCH(bool, labelsVisible);
#ifdef Q_OS_ANDROID
    QSKIP("Android emulator doesn't have a mouse enabled");
#endif

    QBarSeries* series = new QBarSeries();
    series->setLabelsVisible(labelsVisible);
    series->setLabelsPosition(static_cast<QAbstractBarSeries::LabelsPosition>(labelsPosition));
    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);
    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesIndexSpy(series, SIGNAL(hovered(bool, int, QBarSet*)));
    QSignalSpy setIndexSpy1(set1, SIGNAL(hovered(bool, int)));
    QSignalSpy setIndexSpy2(set2, SIGNAL(hovered(bool, int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    //this is hack since view does not get events otherwise
    view.setMouseTracking(true);

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 10;  // From 0 to 10 because of maximum value in set is 10
    qreal rangeX = 3;   // 3 values per set
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = 0;       // These come from internal domain used by barseries.
    qreal domainMinX = -0.5;    // No access to domain from outside, so use hard coded values.
    qreal rectWidth = (scaleX / setCount) * series->barWidth();

    QList<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal yPos = height + scaleY * domainMinY + plotArea.top();
        for (int set = 0; set < setCount; set++) {
            qreal xPos = (i - domainMinX) * scaleX + plotArea.left();
            xPos -= series->count()*rectWidth/2;
            xPos += set*rectWidth;

            qreal rectHeight = barSets.at(set)->at(i) * scaleY;
            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
            layout.append(rect);
        }
    }
    // In order to make it feel like a normal user moving the mouse, we hover across from the edge.
    // If we go right to the center, we can hit a label which does not emit hovered then, but that
    // would not be a normal use case.

//=======================================================================
// move mouse to left border
    QTest::mouseMove(view.viewport(), QPoint(0, layout.at(0).center().y()));
    QTest::qWait(5000);
    QCOMPARE(seriesIndexSpy.size(), 0);
    QCOMPARE(setIndexSpy1.size(), 0);
    QCOMPARE(setIndexSpy2.size(), 0);

//=======================================================================
// move mouse to just inside left border to account for labels
    QTest::mouseMove(view.viewport(), QPoint(layout.at(0).x() + 1, layout.at(0).y() + 1));
    QTRY_COMPARE(seriesIndexSpy.size(), 1);
    QTRY_COMPARE(setIndexSpy1.size(), 1);
    QTRY_COMPARE(setIndexSpy2.size(), 0);

    QList<QVariant> seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set1);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == true);

    QList<QVariant> setIndexSpyArg = setIndexSpy1.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == true);

//=======================================================================
// move mouse to center of set1
    QTest::mouseMove(view.viewport(), layout.at(0).center().toPoint());
    QTest::qWait(5000);
    QCOMPARE(seriesIndexSpy.size(), 0);
    QCOMPARE(setIndexSpy1.size(), 0);
    QCOMPARE(setIndexSpy2.size(), 0);

//=======================================================================
// move mouse to bottom of set1
    QTest::mouseMove(view.viewport(), QPoint(layout.at(0).center().x(), layout.at(0).bottom()));
    QTest::qWait(5000);
    QCOMPARE(seriesIndexSpy.size(), 0);
    QCOMPARE(setIndexSpy1.size(), 0);
    QCOMPARE(setIndexSpy2.size(), 0);

//=======================================================================
// move mouse from top of set1 to top of set2
    QTest::mouseMove(view.viewport(), QPoint(layout.at(1).x() + 1, layout.at(1).y() + 1));
    QTRY_COMPARE(seriesIndexSpy.size(), 2);
    QTRY_COMPARE(setIndexSpy1.size(), 1);
    QTRY_COMPARE(setIndexSpy2.size(), 1);

    // should leave set1
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set1);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == false);

    setIndexSpyArg = setIndexSpy1.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == false);

    // should enter set2
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set2);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == true);

    setIndexSpyArg = setIndexSpy2.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == true);

//=======================================================================
// move mouse from top of set2 to background
    QTest::mouseMove(view.viewport(), QPoint(layout.at(1).center().x(), 0));
    QTRY_COMPARE(seriesIndexSpy.size(), 1);
    QTRY_COMPARE(setIndexSpy1.size(), 0);
    QTRY_COMPARE(setIndexSpy2.size(), 1);

    // should leave set2
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set2);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == false);

    setIndexSpyArg = setIndexSpy2.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == false);

//=======================================================================
// move mouse on top of set1, bar0 to check the index (hover into set1)
    QTest::mouseMove(view.viewport(), QPoint(layout.at(0).x() + 1, layout.at(0).y() + 1));

    QTRY_COMPARE(seriesIndexSpy.size(), 1);
    QTRY_COMPARE(setIndexSpy1.size(), 1);
    QTRY_COMPARE(setIndexSpy2.size(), 0);

    //should enter set1, bar0
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set1);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == true);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 0);

    setIndexSpyArg = setIndexSpy1.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == true);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 0);

//=======================================================================
// move mouse on top of set2, bar0 to check the index (hover out set1,
// hover in set1)
    QTest::mouseMove(view.viewport(), QPoint(layout.at(1).x() + 1, layout.at(1).y() + 1));

    QTRY_COMPARE(seriesIndexSpy.size(), 2);
    QTRY_COMPARE(setIndexSpy1.size(), 1);
    QTRY_COMPARE(setIndexSpy2.size(), 1);

    // should leave set1, bar0
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set1);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == false);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 0);

    setIndexSpyArg = setIndexSpy1.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == false);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 0);

    // should enter set2, bar0
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set2);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == true);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 0);

    setIndexSpyArg = setIndexSpy2.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == true);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 0);

//=======================================================================
// move mouse on top of set1, bar1 to check the index (hover out set 2,
// hover in set1)
    QTest::mouseMove(view.viewport(), QPoint(layout.at(2).x() + 1, layout.at(2).y() + 1));

    QTRY_COMPARE(seriesIndexSpy.size(), 2);
    QTRY_COMPARE(setIndexSpy1.size(), 1);
    QTRY_COMPARE(setIndexSpy2.size(), 1);

    // should leave set2, bar0
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set2);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == false);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 0);

    setIndexSpyArg = setIndexSpy2.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == false);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 0);

    // should enter set1, bar1
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set1);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == true);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 1);

    setIndexSpyArg = setIndexSpy1.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == true);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 1);

//=======================================================================
// move mouse on top of view between set1 and set2 to check the index
// (hover out set1)
    QTest::mouseMove(view.viewport(), QPoint((layout.at(2).right() + layout.at(3).left()) / 2, 0));

    QTRY_COMPARE(seriesIndexSpy.size(), 1);
    QTRY_COMPARE(setIndexSpy1.size(), 1);
    QTRY_COMPARE(setIndexSpy2.size(), 0);

    // should leave set1, bar1
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set1);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == false);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 1);

    setIndexSpyArg = setIndexSpy1.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == false);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 1);

//=======================================================================
// move mouse on top of set2, bar1 to check the index (hover in set2)
    QTest::mouseMove(view.viewport(), QPoint(layout.at(3).x() + 1, layout.at(3).y() + 1));

    QTRY_COMPARE(seriesIndexSpy.size(), 1);
    QTRY_COMPARE(setIndexSpy1.size(), 0);
    QTRY_COMPARE(setIndexSpy2.size(), 1);

    // should enter set2, bar1
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set2);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == true);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 1);

    setIndexSpyArg = setIndexSpy2.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == true);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 1);

//=======================================================================
// move mouse on top of the view between bar1 and bar2 to check the index
//(hover out set2)
    QTest::mouseMove(view.viewport(), QPoint((layout.at(3).right() + layout.at(3).left()) / 2, 0));

    QTRY_COMPARE(seriesIndexSpy.size(), 1);
    QTRY_COMPARE(setIndexSpy1.size(), 0);
    QTRY_COMPARE(setIndexSpy2.size(), 1);

    // should leave set2, bar1
    seriesIndexSpyArg = seriesIndexSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesIndexSpyArg.at(2)), set2);
    QVERIFY(seriesIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(seriesIndexSpyArg.at(0).toBool() == false);
    QVERIFY(seriesIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(seriesIndexSpyArg.at(1).toInt() == 1);

    setIndexSpyArg = setIndexSpy2.takeFirst();
    QVERIFY(setIndexSpyArg.at(0).metaType().id() == QMetaType::Bool);
    QVERIFY(setIndexSpyArg.at(0).toBool() == false);
    QVERIFY(setIndexSpyArg.at(1).metaType().id() == QMetaType::Int);
    QVERIFY(setIndexSpyArg.at(1).toInt() == 1);
}

void tst_QBarSeries::clearWithAnimations()
{
    QBarSeries* series = new QBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->setAnimationOptions(QChart::SeriesAnimations);
    view.chart()->addSeries(series);
    view.show();

    series->clear();
}

void tst_QBarSeries::destruction()
{
    // add a barset
    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("testset");
    QSignalSpy spy1(set, SIGNAL(destroyed()));
    series->append(set);

    // delete the series
    delete series;

    // check that series deletes the set
    QCOMPARE(spy1.size(), 1);
}

void tst_QBarSeries::mousePressed()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QBarSeries* series = new QBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);
    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesSpy(series,SIGNAL(pressed(int,QBarSet*)));
    QSignalSpy setSpy1(set1, SIGNAL(pressed(int)));
    QSignalSpy setSpy2(set2, SIGNAL(pressed(int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 10;  // From 0 to 10 because of maximum value in set is 10
    qreal rangeX = 3; // 3 values per set
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = 0;       // These come from internal domain used by barseries.
    qreal domainMinX = -0.5;    // No access to domain from outside, so use hard coded values.
    qreal rectWidth = (scaleX / setCount) * series->barWidth();

    QList<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal yPos = height + scaleY * domainMinY + plotArea.top();
        for (int set = 0; set < setCount; set++) {
            qreal xPos = (i - domainMinX) * scaleX + plotArea.left();
            xPos -= series->count()*rectWidth/2;
            xPos += set*rectWidth;

            qreal rectHeight = barSets.at(set)->at(i) * scaleY;
            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
            layout.append(rect);
        }
    }

//====================================================================================
// barset 1, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(0).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    QList<QVariant> setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 1, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(2).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 1, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(4).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 2);

//====================================================================================
// barset 2, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(1).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 2, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(3).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 2, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(5).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 2);
}

void tst_QBarSeries::mouseReleased()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QBarSeries* series = new QBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);
    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesSpy(series,SIGNAL(released(int,QBarSet*)));
    QSignalSpy setSpy1(set1, SIGNAL(released(int)));
    QSignalSpy setSpy2(set2, SIGNAL(released(int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 10;  // From 0 to 10 because of maximum value in set is 10
    qreal rangeX = 3; // 3 values per set
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = 0;       // These come from internal domain used by barseries.
    qreal domainMinX = -0.5;    // No access to domain from outside, so use hard coded values.
    qreal rectWidth = (scaleX / setCount) * series->barWidth();

    QList<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal yPos = height + scaleY * domainMinY + plotArea.top();
        for (int set = 0; set < setCount; set++) {
            qreal xPos = (i - domainMinX) * scaleX + plotArea.left();
            xPos -= series->count()*rectWidth/2;
            xPos += set*rectWidth;

            qreal rectHeight = barSets.at(set)->at(i) * scaleY;
            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
            layout.append(rect);
        }
    }

//====================================================================================
// barset 1, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(0).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    QList<QVariant> setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 1, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(2).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 1, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(4).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

    setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 2);

//====================================================================================
// barset 2, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(1).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 2, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(3).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 2, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, layout.at(5).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 0);
    QCOMPARE(setSpy2.size(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

    setSpyArg = setSpy2.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 2);
}

void tst_QBarSeries::mouseDoubleClicked()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QBarSeries* series = new QBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);
    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesSpy(series,SIGNAL(doubleClicked(int,QBarSet*)));
    QSignalSpy setSpy1(set1, SIGNAL(doubleClicked(int)));
    QSignalSpy setSpy2(set2, SIGNAL(doubleClicked(int)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 10;  // From 0 to 10 because of maximum value in set is 10
    qreal rangeX = 3; // 3 values per set
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = 0;       // These come from internal domain used by barseries.
    qreal domainMinX = -0.5;    // No access to domain from outside, so use hard coded values.
    qreal rectWidth = (scaleX / setCount) * series->barWidth();

    QList<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal yPos = height + scaleY * domainMinY + plotArea.top();
        for (int set = 0; set < setCount; set++) {
            qreal xPos = (i - domainMinX) * scaleX + plotArea.left();
            xPos -= series->count()*rectWidth/2;
            xPos += set*rectWidth;

            qreal rectHeight = barSets.at(set)->at(i) * scaleY;
            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
            layout.append(rect);
        }
    }

    // barset 1, bar 0
    QTest::mouseDClick(view.viewport(), Qt::LeftButton, {}, layout.at(0).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QCOMPARE(setSpy1.size(), 1);
    QCOMPARE(setSpy2.size(), 0);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

    QList<QVariant> setSpyArg = setSpy1.takeFirst();
    QVERIFY(setSpyArg.at(0).metaType().id() == QMetaType::Int);
    QVERIFY(setSpyArg.at(0).toInt() == 0);
}

QTEST_MAIN(tst_QBarSeries)

#include "tst_qbarseries.moc"

