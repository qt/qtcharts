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

#include "../qabstractaxis/tst_qabstractaxis.h"
#include "qvaluesaxis.h"
#include <qlineseries.h>

class tst_QValuesAxis: public tst_QAbstractAxis
{
Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qvaluesaxis_data();
    void qvaluesaxis();

    void max_raw_data();
    void max_raw();
    void max_data();
    void max();
    void max_animation_data();
    void max_animation();
    void min_raw_data();
    void min_raw();
    void min_data();
    void min();
    void min_animation_data();
    void min_animation();
    void niceNumbersEnabled_data();
    void niceNumbersEnabled();
    void range_raw_data();
    void range_raw();
    void range_data();
    void range();
    void range_animation_data();
    void range_animation();
    void ticksCount_data();
    void ticksCount();

private:
    QValuesAxis* m_valuesaxis;
    QLineSeries* m_series;
};

void tst_QValuesAxis::initTestCase()
{
}

void tst_QValuesAxis::cleanupTestCase()
{
}

void tst_QValuesAxis::init()
{
    m_valuesaxis = new QValuesAxis();
    tst_QAbstractAxis::init(m_valuesaxis);
    m_series = new QLineSeries();
    *m_series << QPointF(-100, -100) << QPointF(0, 0) << QPointF(100, 100);
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}

void tst_QValuesAxis::cleanup()
{
    delete m_series;
    delete m_valuesaxis;
    m_series = 0;
    m_valuesaxis = 0;
    tst_QAbstractAxis::cleanup();
}

void tst_QValuesAxis::qvaluesaxis_data()
{
}

void tst_QValuesAxis::qvaluesaxis()
{
    qabstractaxis();

    QVERIFY(qFuzzyIsNull(m_valuesaxis->max()));
    QVERIFY(qFuzzyIsNull(m_valuesaxis->min()));
    QCOMPARE(m_valuesaxis->niceNumbersEnabled(), false);
    QCOMPARE(m_valuesaxis->ticksCount(), 5);
    QCOMPARE(m_valuesaxis->type(), QAbstractAxis::AxisTypeValues);

    m_chart->setAxisX(m_valuesaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QVERIFY(!qFuzzyIsNull(m_valuesaxis->max()));
    QVERIFY(!qFuzzyIsNull(m_valuesaxis->min()));
    QCOMPARE(m_valuesaxis->niceNumbersEnabled(), false);
    QCOMPARE(m_valuesaxis->ticksCount(), 5);
}

void tst_QValuesAxis::max_raw_data()
{
    QTest::addColumn<qreal>("max");
    QTest::newRow("1.0") << 1.0;
    QTest::newRow("50.0") << 50.0;
    QTest::newRow("101.0") << 101.0;
}

void tst_QValuesAxis::max_raw()
{
    QFETCH(qreal, max);

    QSignalSpy spy0(m_valuesaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_valuesaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_valuesaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_valuesaxis->setMax(max);
    QVERIFY2(qFuzzyIsNull(m_valuesaxis->max() - max), "Not equal");

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);

}

void tst_QValuesAxis::max_data()
{
    max_raw_data();
}

void tst_QValuesAxis::max()
{
    m_chart->setAxisX(m_valuesaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    max_raw();
}

void tst_QValuesAxis::max_animation_data()
{
    max_data();
}

void tst_QValuesAxis::max_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    max();
}

void tst_QValuesAxis::min_raw_data()
{
    QTest::addColumn<qreal>("min");
    QTest::newRow("-1.0") << -1.0;
    QTest::newRow("-50.0") << -50.0;
    QTest::newRow("-101.0") << -101.0;
}

void tst_QValuesAxis::min_raw()
{
    QFETCH(qreal, min);

    QSignalSpy spy0(m_valuesaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_valuesaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_valuesaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_valuesaxis->setMin(min);
    QVERIFY2(qFuzzyIsNull(m_valuesaxis->min() - min), "Not equal");

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_QValuesAxis::min_data()
{
    min_raw_data();
}

void tst_QValuesAxis::min()
{
    m_chart->setAxisX(m_valuesaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    min_raw();
}

void tst_QValuesAxis::min_animation_data()
{
    min_data();
}

void tst_QValuesAxis::min_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    min();
}

void tst_QValuesAxis::niceNumbersEnabled_data()
{
    QTest::addColumn<bool>("niceNumbersEnabled");
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::addColumn<int>("ticks");
    QTest::addColumn<qreal>("expectedMin");
    QTest::addColumn<qreal>("expectedMax");
    QTest::addColumn<int>("expectedTicks");
    QTest::newRow("true 0.1 , 99.0 , 5") << true << 0.1 << 99.0 << 5 << 0.0 << 100.0 << 6;
    QTest::newRow("true 1 , 10.0 , 5") << true << 1.0 << 10.0 << 5 << 0.0 << 10.0 << 6;
    QTest::newRow("true 0.1 , 6.6 , 5") << true << 0.1 << 6.6 << 5 << 0.0 << 8.0 << 5;
    QTest::newRow("false 0.1 , 6.6 , 5") << false << 0.1 << 6.6 << 5 << 0.1 << 6.6 << 5;
    QTest::newRow("true 0.1, 99, 5") << true << 0.1 << 99.0 << 5 << 0.0 << 100.0 << 6;
    QTest::newRow("true 5, 93.5 , 5") << true << 5.0 << 93.5 << 5 << 0.0 << 100.0 << 6;
}

void tst_QValuesAxis::niceNumbersEnabled()
{
    QFETCH(bool, niceNumbersEnabled);
    QFETCH(qreal, min);
    QFETCH(qreal, max);
    QFETCH(int, ticks);
    QFETCH(qreal, expectedMin);
    QFETCH(qreal, expectedMax);
    QFETCH(int, expectedTicks);

    QSignalSpy spy0(m_valuesaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_valuesaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_valuesaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_valuesaxis->setNiceNumbersEnabled(niceNumbersEnabled);
    QCOMPARE(m_valuesaxis->niceNumbersEnabled(), niceNumbersEnabled);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);

    m_valuesaxis->setTicksCount(ticks);
    m_valuesaxis->setRange(min, max);
    QVERIFY2(qFuzzyIsNull(m_valuesaxis->min() - expectedMin), "Min not equal");
    QVERIFY2(qFuzzyIsNull(m_valuesaxis->max() - expectedMax), "Max not equal");
    QCOMPARE(m_valuesaxis->ticksCount(), expectedTicks);

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);

}

void tst_QValuesAxis::range_raw_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("1.0 - 101.0") << -1.0 << 101.0;
    QTest::newRow("25.0 - 75.0") << 25.0 << 75.0;
    QTest::newRow("101.0") << 40.0 << 60.0;
}

void tst_QValuesAxis::range_raw()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    QSignalSpy spy0(m_valuesaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_valuesaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_valuesaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_valuesaxis->setRange(min, max);
    QVERIFY2(qFuzzyIsNull(m_valuesaxis->min() - min), "Min not equal");
    QVERIFY2(qFuzzyIsNull(m_valuesaxis->max() - max), "Max not equal");

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_QValuesAxis::range_data()
{
    range_raw_data();
}

void tst_QValuesAxis::range()
{
    m_chart->setAxisX(m_valuesaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    range_raw();
}

void tst_QValuesAxis::range_animation_data()
{
    range_data();
}

void tst_QValuesAxis::range_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    range();
}

void tst_QValuesAxis::ticksCount_data()
{
    QTest::addColumn<int>("ticksCount");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("0") << 2;
    QTest::newRow("1") << 2;
    QTest::newRow("2") << 2;
    QTest::newRow("3") << 3;
    QTest::newRow("-1") << 2;
}

void tst_QValuesAxis::ticksCount()
{
    QFETCH(int, ticksCount);

    QSignalSpy spy0(m_valuesaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_valuesaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_valuesaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_valuesaxis->setTicksCount(ticksCount);
    QCOMPARE(m_valuesaxis->ticksCount(), ticksCount);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);

    m_chart->setAxisX(m_valuesaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QCOMPARE(m_valuesaxis->ticksCount(), ticksCount);
}

QTEST_MAIN(tst_QValuesAxis)
#include "tst_qvaluesaxis.moc"

