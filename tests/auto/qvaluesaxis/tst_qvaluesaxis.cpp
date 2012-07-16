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

class tst_QValuesAxis : public tst_QAbstractAxis
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

    void max_data();
    void max();
    void min_data();
    void min();
    void niceNumbersEnabled_data();
    void niceNumbersEnabled();
    void setNiceNumbersEnabled_data();
    void setNiceNumbersEnabled();
    void setRange_data();
    void setRange();
    void setTicksCount_data();
    void setTicksCount();
    void ticksCount_data();
    void ticksCount();
    void type_data();
    void type();
    void maxChanged_data();
    void maxChanged();
    void minChanged_data();
    void minChanged();
    void rangeChanged_data();
    void rangeChanged();

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
    *m_series << QPointF(-100,-100) << QPointF(0,0) << QPointF(100,100);
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}

void tst_QValuesAxis::cleanup()
{
    delete m_series;
    delete m_valuesaxis;
    m_series = 0;
    m_valuesaxis = 0 ;
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

    m_chart->setAxisX(m_valuesaxis,m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    QVERIFY(!qFuzzyIsNull(m_valuesaxis->max()));
    QVERIFY(!qFuzzyIsNull(m_valuesaxis->min()));
    QCOMPARE(m_valuesaxis->niceNumbersEnabled(), false);
    QCOMPARE(m_valuesaxis->ticksCount(), 5);
}

void tst_QValuesAxis::max_data()
{
    QTest::addColumn<qreal>("max");
    QTest::newRow("null") << 0.0;
}

// public qreal max() const
void tst_QValuesAxis::max()
{
#if 0
    QFETCH(qreal, max);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    QCOMPARE(axis.max(), max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::min_data()
{
    QTest::addColumn<qreal>("min");
    QTest::newRow("null") << 0.0;
}

// public qreal min() const
void tst_QValuesAxis::min()
{
#if 0
    QFETCH(qreal, min);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    QCOMPARE(axis.min(), min);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::niceNumbersEnabled_data()
{
    QTest::addColumn<bool>("niceNumbersEnabled");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool niceNumbersEnabled() const
void tst_QValuesAxis::niceNumbersEnabled()
{
#if 0
    QFETCH(bool, niceNumbersEnabled);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    QCOMPARE(axis.niceNumbersEnabled(), niceNumbersEnabled);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}


void tst_QValuesAxis::setNiceNumbersEnabled_data()
{
    QTest::addColumn<bool>("enable");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setNiceNumbersEnabled(bool enable = true)
void tst_QValuesAxis::setNiceNumbersEnabled()
{
#if 0
    QFETCH(bool, enable);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    axis.setNiceNumbersEnabled(enable);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::setRange_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("null") << 0.0 << 0.0;
}

// public void setRange(qreal min, qreal max)
void tst_QValuesAxis::setRange()
{
#if 0
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    axis.setRange(min, max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::setTicksCount_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void setTicksCount(int count)
void tst_QValuesAxis::setTicksCount()
{
#if 0
    QFETCH(int, count);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    axis.setTicksCount(count);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::ticksCount_data()
{
    QTest::addColumn<int>("ticksCount");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public int ticksCount() const
void tst_QValuesAxis::ticksCount()
{
#if 0
    QFETCH(int, ticksCount);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    QCOMPARE(axis.ticksCount(), ticksCount);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QAbstractAxis::AxisType)
void tst_QValuesAxis::type_data()
{
#if 0
    QTest::addColumn<AxisType>("type");
    QTest::newRow("null") << AxisType();
#endif
}

// public AxisType type() const
void tst_QValuesAxis::type()
{
#if 0
    QFETCH(AxisType, type);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    QCOMPARE(axis.type(), type);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::maxChanged_data()
{
    QTest::addColumn<qreal>("max");
    QTest::newRow("null") << 0.0;
}

// protected void maxChanged(qreal max)
void tst_QValuesAxis::maxChanged()
{
#if 0
    QFETCH(qreal, max);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    axis.call_maxChanged(max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::minChanged_data()
{
    QTest::addColumn<qreal>("min");
    QTest::newRow("null") << 0.0;
}

// protected void minChanged(qreal min)
void tst_QValuesAxis::minChanged()
{
#if 0
    QFETCH(qreal, min);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    axis.call_minChanged(min);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QValuesAxis::rangeChanged_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("null") << 0.0 << 0.0;
}

// protected void rangeChanged(qreal min, qreal max)
void tst_QValuesAxis::rangeChanged()
{
#if 0
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    SubQValuesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(maxChanged(qreal)));
    QSignalSpy spy1(&axis, SIGNAL(minChanged(qreal)));
    QSignalSpy spy2(&axis, SIGNAL(rangeChanged(qreal, qreal)));

    axis.call_rangeChanged(min, max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

QTEST_MAIN(tst_QValuesAxis)
#include "tst_qvaluesaxis.moc"

