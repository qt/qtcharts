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
#include "qintervalsaxis.h"
#include <qlineseries.h>

class tst_QIntervalsAxis: public tst_QAbstractAxis
{
Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qintervalsaxis_data();
    void qintervalsaxis();

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
    void range_raw_data();
    void range_raw();
    void range_data();
    void range();
    void range_animation_data();
    void range_animation();

    void interval_data();
    void interval();

private:
    QIntervalsAxis* m_intervalsaxis;
    QLineSeries* m_series;
};

void tst_QIntervalsAxis::initTestCase()
{
}

void tst_QIntervalsAxis::cleanupTestCase()
{
}

void tst_QIntervalsAxis::init()
{
    m_intervalsaxis = new QIntervalsAxis();
    m_series = new QLineSeries();
    *m_series << QPointF(-100, -100) << QPointF(0, 0) << QPointF(100, 100);
    tst_QAbstractAxis::init(m_intervalsaxis, m_series);
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}

void tst_QIntervalsAxis::cleanup()
{
    delete m_series;
    delete m_intervalsaxis;
    m_series = 0;
    m_intervalsaxis = 0;
    tst_QAbstractAxis::cleanup();
}

void tst_QIntervalsAxis::qintervalsaxis_data()
{
}

void tst_QIntervalsAxis::qintervalsaxis()
{
    qabstractaxis();

    QVERIFY(qFuzzyIsNull(m_intervalsaxis->max()));
    QVERIFY(qFuzzyIsNull(m_intervalsaxis->min()));
    QCOMPARE(m_intervalsaxis->type(), QAbstractAxis::AxisTypeIntervals);

    m_chart->setAxisX(m_intervalsaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QVERIFY(!qFuzzyIsNull(m_intervalsaxis->max()));
    QVERIFY(!qFuzzyIsNull(m_intervalsaxis->min()));
}

void tst_QIntervalsAxis::max_raw_data()
{
    QTest::addColumn<qreal>("max");
    QTest::newRow("1.0") << 1.0;
    QTest::newRow("50.0") << 50.0;
    QTest::newRow("101.0") << 101.0;
}

void tst_QIntervalsAxis::max_raw()
{
    QFETCH(qreal, max);

    QSignalSpy spy0(m_intervalsaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_intervalsaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_intervalsaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_intervalsaxis->setMax(max);
    QVERIFY2(qFuzzyIsNull(m_intervalsaxis->max() - max), "Not equal");

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);
}

void tst_QIntervalsAxis::max_data()
{
    max_raw_data();
}

void tst_QIntervalsAxis::max()
{
    m_chart->setAxisX(m_intervalsaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    max_raw();
}

void tst_QIntervalsAxis::max_animation_data()
{
    max_data();
}

void tst_QIntervalsAxis::max_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    max();
}

void tst_QIntervalsAxis::min_raw_data()
{
    QTest::addColumn<qreal>("min");
    QTest::newRow("-1.0") << -1.0;
    QTest::newRow("-50.0") << -50.0;
    QTest::newRow("-101.0") << -101.0;
}

void tst_QIntervalsAxis::min_raw()
{
    QFETCH(qreal, min);

    QSignalSpy spy0(m_intervalsaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_intervalsaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_intervalsaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_intervalsaxis->setMin(min);
    QVERIFY2(qFuzzyIsNull(m_intervalsaxis->min() - min), "Not equal");

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_QIntervalsAxis::min_data()
{
    min_raw_data();
}

void tst_QIntervalsAxis::min()
{
    m_chart->setAxisX(m_intervalsaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    min_raw();
}

void tst_QIntervalsAxis::min_animation_data()
{
    min_data();
}

void tst_QIntervalsAxis::min_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    min();
}

void tst_QIntervalsAxis::range_raw_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("1.0 - 101.0") << -1.0 << 101.0;
    QTest::newRow("25.0 - 75.0") << 25.0 << 75.0;
    QTest::newRow("101.0") << 40.0 << 60.0;
}

void tst_QIntervalsAxis::range_raw()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    QSignalSpy spy0(m_intervalsaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_intervalsaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_intervalsaxis, SIGNAL(rangeChanged(qreal, qreal)));

    m_intervalsaxis->setRange(min, max);
    QVERIFY2(qFuzzyIsNull(m_intervalsaxis->min() - min), "Min not equal");
    QVERIFY2(qFuzzyIsNull(m_intervalsaxis->max() - max), "Max not equal");

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_QIntervalsAxis::range_data()
{
    range_raw_data();
}

void tst_QIntervalsAxis::range()
{
    m_chart->setAxisX(m_intervalsaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    range_raw();
}

void tst_QIntervalsAxis::range_animation_data()
{
    range_data();
}

void tst_QIntervalsAxis::range_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    range();
}

void tst_QIntervalsAxis::interval_data()
{
    //
}

void tst_QIntervalsAxis::interval()
{
    // append one correct interval
    m_intervalsaxis->append("first", (qreal)45);
    QCOMPARE(m_intervalsaxis->intervalMin("first"), (qreal)0);
    QCOMPARE(m_intervalsaxis->intervalMax("first"), (qreal)45);

    // append one more correct interval
    m_intervalsaxis->append("second", (qreal)75);
    QCOMPARE(m_intervalsaxis->intervalMin("second"), (qreal)45);
    QCOMPARE(m_intervalsaxis->intervalMax("second"), (qreal)75);

    // append one incorrect interval
    m_intervalsaxis->append("third", (qreal)15);
    QCOMPARE(m_intervalsaxis->count(), 2);
    QCOMPARE(m_intervalsaxis->intervalMax(m_intervalsaxis->intervalsLabels().last()), (qreal)75);
//    QCOMPARE(intervalMax("first"), (qreal)75);

    // append one more correct interval
    m_intervalsaxis->append("third", (qreal)100);
    QCOMPARE(m_intervalsaxis->count(), 3);
    QCOMPARE(m_intervalsaxis->intervalMin("third"), (qreal)75);
    QCOMPARE(m_intervalsaxis->intervalMax("third"), (qreal)100);

    // remove one interval
    m_intervalsaxis->remove("first");
    QCOMPARE(m_intervalsaxis->count(), 2);
    QCOMPARE(m_intervalsaxis->intervalMin("second"), (qreal)0); // second interval should extend to firstInterval minimum
    QCOMPARE(m_intervalsaxis->intervalMax("second"), (qreal)75);

    // remove one interval
    m_intervalsaxis->replace("second", "replaced");
    QCOMPARE(m_intervalsaxis->count(), 2);
    QCOMPARE(m_intervalsaxis->intervalMin("replaced"), (qreal)0); // second interval should extend to firstInterval minimum
    QCOMPARE(m_intervalsaxis->intervalMax("replaced"), (qreal)75);
}

QTEST_MAIN(tst_QIntervalsAxis)
#include "tst_qintervalsaxis.moc"

