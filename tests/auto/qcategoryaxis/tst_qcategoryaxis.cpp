/****************************************************************************
 **
 ** Copyright (C) 2014 Digia Plc
 ** All rights reserved.
 ** For any questions to Digia, please use contact form at http://qt.io
 **
 ** This file is part of the Qt Charts module.
 **
 ** Licensees holding valid commercial license for Qt may use this file in
 ** accordance with the Qt License Agreement provided with the Software
 ** or, alternatively, in accordance with the terms contained in a written
 ** agreement between you and Digia.
 **
 ** If you have questions regarding the use of this file, please use
 ** contact form at http://qt.io
 **
 ****************************************************************************/

#include "../qabstractaxis/tst_qabstractaxis.h"
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QLineSeries>

class tst_QCategoryAxis: public tst_QAbstractAxis
{
Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qcategoryaxis_data();
    void qcategoryaxis();

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
    QCategoryAxis* m_categoryaxis;
    QLineSeries* m_series;
};

void tst_QCategoryAxis::initTestCase()
{
}

void tst_QCategoryAxis::cleanupTestCase()
{
    QTest::qWait(1); // Allow final deleteLaters to run
}

void tst_QCategoryAxis::init()
{
    m_categoryaxis = new QCategoryAxis();
    m_series = new QLineSeries();
    *m_series << QPointF(-100, -100) << QPointF(0, 0) << QPointF(100, 100);
    tst_QAbstractAxis::init(m_categoryaxis, m_series);
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}

void tst_QCategoryAxis::cleanup()
{
    delete m_series;
    delete m_categoryaxis;
    m_series = 0;
    m_categoryaxis = 0;
    tst_QAbstractAxis::cleanup();
}

void tst_QCategoryAxis::qcategoryaxis_data()
{
}

void tst_QCategoryAxis::qcategoryaxis()
{
    qabstractaxis();

    QVERIFY(qFuzzyCompare(m_categoryaxis->max(), 0));
    QVERIFY(qFuzzyCompare(m_categoryaxis->min(), 0));
    QCOMPARE(m_categoryaxis->type(), QAbstractAxis::AxisTypeCategory);

    m_chart->setAxisX(m_categoryaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QVERIFY(!qFuzzyCompare(m_categoryaxis->max(), 0));
    QVERIFY(!qFuzzyCompare(m_categoryaxis->min(), 0));
}

void tst_QCategoryAxis::max_raw_data()
{
    QTest::addColumn<qreal>("max");
    QTest::newRow("1.0") << (qreal)1.0;
    QTest::newRow("50.0") << (qreal)50.0;
    QTest::newRow("101.0") << (qreal)101.0;
}

void tst_QCategoryAxis::max_raw()
{
    QFETCH(qreal, max);

    QSignalSpy spy0(m_categoryaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_categoryaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_categoryaxis, SIGNAL(rangeChanged(qreal,qreal)));

    m_categoryaxis->setMax(max);
    QVERIFY2(qFuzzyCompare(m_categoryaxis->max(), max), "Not equal");

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);
}

void tst_QCategoryAxis::max_data()
{
    max_raw_data();
}

void tst_QCategoryAxis::max()
{
    m_chart->setAxisX(m_categoryaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    max_raw();
}

void tst_QCategoryAxis::max_animation_data()
{
    max_data();
}

void tst_QCategoryAxis::max_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    max();
}

void tst_QCategoryAxis::min_raw_data()
{
    QTest::addColumn<qreal>("min");
    QTest::newRow("-1.0") << (qreal)-1.0;
    QTest::newRow("-50.0") << (qreal)-50.0;
    QTest::newRow("-101.0") << (qreal)-101.0;
}

void tst_QCategoryAxis::min_raw()
{
    QFETCH(qreal, min);

    QSignalSpy spy0(m_categoryaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_categoryaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_categoryaxis, SIGNAL(rangeChanged(qreal,qreal)));

    m_categoryaxis->setMin(min);
    QVERIFY2(qFuzzyCompare(m_categoryaxis->min(), min), "Not equal");

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_QCategoryAxis::min_data()
{
    min_raw_data();
}

void tst_QCategoryAxis::min()
{
    m_chart->setAxisX(m_categoryaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    min_raw();
}

void tst_QCategoryAxis::min_animation_data()
{
    min_data();
}

void tst_QCategoryAxis::min_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    min();
}

void tst_QCategoryAxis::range_raw_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("1.0 - 101.0") << (qreal)-1.0 << (qreal)101.0;
    QTest::newRow("25.0 - 75.0") << (qreal)25.0 << (qreal)75.0;
    QTest::newRow("101.0") << (qreal)40.0 << (qreal)60.0;
    QTest::newRow("-35.0 - 0.0") << (qreal)-35.0 << (qreal)10.0;
    QTest::newRow("-35.0 - 0.0") << (qreal)-35.0 << (qreal)-15.0;
    QTest::newRow("0.0 - 0.0") << (qreal)-0.1 << (qreal)0.1;
}

void tst_QCategoryAxis::range_raw()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    QSignalSpy spy0(m_categoryaxis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(m_categoryaxis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(m_categoryaxis, SIGNAL(rangeChanged(qreal,qreal)));

    m_categoryaxis->setRange(min, max);
    QVERIFY2(qFuzzyCompare(m_categoryaxis->min(), min), "Min not equal");
    QVERIFY2(qFuzzyCompare(m_categoryaxis->max(), max), "Max not equal");

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_QCategoryAxis::range_data()
{
    range_raw_data();
}

void tst_QCategoryAxis::range()
{
    m_chart->setAxisX(m_categoryaxis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    range_raw();
}

void tst_QCategoryAxis::range_animation_data()
{
    range_data();
}

void tst_QCategoryAxis::range_animation()
{
    m_chart->setAnimationOptions(QChart::GridAxisAnimations);
    range();
}

void tst_QCategoryAxis::interval_data()
{
    //
}

void tst_QCategoryAxis::interval()
{
    // append one correct interval
    m_categoryaxis->append("first", (qreal)45);
    QCOMPARE(m_categoryaxis->startValue("first"), (qreal)0);
    QCOMPARE(m_categoryaxis->endValue("first"), (qreal)45);

    // append one more correct interval
    m_categoryaxis->append("second", (qreal)75);
    QCOMPARE(m_categoryaxis->startValue("second"), (qreal)45);
    QCOMPARE(m_categoryaxis->endValue("second"), (qreal)75);

    // append one incorrect interval
    m_categoryaxis->append("third", (qreal)15);
    QCOMPARE(m_categoryaxis->count(), 2);
    QCOMPARE(m_categoryaxis->endValue(m_categoryaxis->categoriesLabels().last()), (qreal)75);
//    QCOMPARE(intervalMax("first"), (qreal)75);

    // append one more correct interval
    m_categoryaxis->append("third", (qreal)100);
    QCOMPARE(m_categoryaxis->count(), 3);
    QCOMPARE(m_categoryaxis->startValue("third"), (qreal)75);
    QCOMPARE(m_categoryaxis->endValue("third"), (qreal)100);

    // remove one interval
    m_categoryaxis->remove("first");
    QCOMPARE(m_categoryaxis->count(), 2);
    QCOMPARE(m_categoryaxis->startValue("second"), (qreal)0); // second interval should extend to firstInterval minimum
    QCOMPARE(m_categoryaxis->endValue("second"), (qreal)75);

    // remove one interval
    m_categoryaxis->replaceLabel("second", "replaced");
    QCOMPARE(m_categoryaxis->count(), 2);
    QCOMPARE(m_categoryaxis->startValue("replaced"), (qreal)0); // second interval should extend to firstInterval minimum
    QCOMPARE(m_categoryaxis->endValue("replaced"), (qreal)75);
}

QTEST_MAIN(tst_QCategoryAxis)
#include "tst_qcategoryaxis.moc"

