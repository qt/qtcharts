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
#include <qlineseries.h>
#include <qxymodelmapper.h>
#include <qchartview.h>
#include <QStandardItemModel>
#include <tst_definitions.h>

Q_DECLARE_METATYPE(QList<QPointF>)

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QLineSeries : public QObject
{
    Q_OBJECT

    public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    private slots:
    void qlineseries_data();
    void qlineseries();
    void append_raw_data();
    void append_raw();
    void append_chart_data();
    void append_chart();
    void append_chart_animation_data();
    void append_chart_animation();
    void chart_append_data();
    void chart_append();
    void count_raw_data();
    void count_raw();
    void oper_data();
    void oper();
    void pen_data();
    void pen();
    void pointsVisible_raw_data();
    void pointsVisible_raw();
    void remove_raw_data();
    void remove_raw();
    void remove_chart_data();
    void remove_chart();
    void remove_chart_animation_data();
    void remove_chart_animation();
    void removeAll_raw_data();
    void removeAll_raw();
    void removeAll_chart_data();
    void removeAll_chart();
    void removeAll_chart_animation_data();
    void removeAll_chart_animation();
    void replace_raw_data();
    void replace_raw();
    void replace_chart_data();
    void replace_chart();
    void replace_chart_animation_data();
    void replace_chart_animation();
    private:
    void append_data();
    void count_data();
    void pointsVisible_data();

    private:
    QChartView* m_view;
    QChart* m_chart;
    QLineSeries* m_series;
};

void tst_QLineSeries::initTestCase()
{
}

void tst_QLineSeries::cleanupTestCase()
{
}

void tst_QLineSeries::init()
{
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
    m_series = new QLineSeries();
}

void tst_QLineSeries::cleanup()
{
    delete m_series;
    delete m_view;
    m_view = 0;
    m_chart = 0;
    m_series = 0;
}

void tst_QLineSeries::qlineseries_data()
{

}

void tst_QLineSeries::qlineseries()
{
    QLineSeries series;

    QCOMPARE(series.count(),0);
    QCOMPARE(series.brush(), QBrush());
    QCOMPARE(series.points(), QList<QPointF>());
    QCOMPARE(series.pen(), QPen());
    QCOMPARE(series.pointsVisible(), false);

    series.append(QList<QPointF>());
    series.append(0.0,0.0);
    series.append(QPointF());

    series.remove(0.0,0.0);
    series.remove(QPointF());
    series.removeAll();

    series.replace(QPointF(),QPointF());
    series.replace(0,0,0,0);
    series.setBrush(QBrush());

//    QCOMPARE(series.setModel((QAbstractItemModel*)0), false);

//    series.setModelMapping(-1, -1, Qt::Orientation(0));

    series.setPen(QPen());
    series.setPointsVisible(false);

    m_chart->addSeries(&series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QLineSeries::append_data()
{
    QTest::addColumn< QList<QPointF> >("points");
    QTest::newRow("0,0 1,1 2,2 3,3") << (QList<QPointF>() << QPointF(0,0) << QPointF(1,1) << QPointF(2,2) << QPointF(3,3));
    QTest::newRow("0,0 -1,-1 -2,-2 -3,-3") << (QList<QPointF>() << QPointF(0,0) << QPointF(-1,-1) << QPointF(-2,-2) << QPointF(-3,-3));
}


void tst_QLineSeries::append_raw_data()
{
    append_data();
}

void tst_QLineSeries::append_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);
}

void tst_QLineSeries::chart_append_data()
{
    append_data();
}

void tst_QLineSeries::chart_append()
{
    append_raw();
    m_chart->addSeries(m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QLineSeries::append_chart_data()
{
    append_data();
}

void tst_QLineSeries::append_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    append_raw();

}

void tst_QLineSeries::append_chart_animation_data()
{
    append_data();
}

void tst_QLineSeries::append_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    append_chart();
}

void tst_QLineSeries::count_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("5") << 5;
    QTest::newRow("10") << 5;
}

void tst_QLineSeries::count_raw_data()
{
    count_data();
}

void tst_QLineSeries::count_raw()
{
    QFETCH(int, count);

    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));

    for(int i=0 ; i< count; ++i)
        m_series->append(i,i);

    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->count(), count);
}

void tst_QLineSeries::oper_data()
{
    append_data();
}

void tst_QLineSeries::oper()
{
    QFETCH(QList<QPointF>, points);
    QLineSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));

    foreach(const QPointF& point,points)
    {
        series<<point;
    }

    QCOMPARE(series.points(), points);
    TRY_COMPARE(spy0.count(), 0);
}


void tst_QLineSeries::pen_data()
{
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QLineSeries::pen()
{
    QFETCH(QPen, pen);
    QLineSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    series.setPen(pen);

    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(series.pen(), pen);

    m_chart->addSeries(&series);

    if(pen!=QPen()) QCOMPARE(series.pen(), pen);

    m_chart->setTheme(QChart::ChartThemeDark);

    QVERIFY(series.pen() != pen);
}

void tst_QLineSeries::pointsVisible_data()
{
    QTest::addColumn<bool>("pointsVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QLineSeries::pointsVisible_raw_data()
{
    pointsVisible_data();
}

void tst_QLineSeries::pointsVisible_raw()
{
    QFETCH(bool, pointsVisible);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->setPointsVisible(pointsVisible);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->pointsVisible(), pointsVisible);
}

void tst_QLineSeries::remove_raw_data()
{
    append_data();
}

void tst_QLineSeries::remove_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);

    foreach(const QPointF& point,points)
        m_series->remove(point);

    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points().count(), 0);
}

void tst_QLineSeries::remove_chart_data()
{
    append_data();
}

void tst_QLineSeries::remove_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    remove_raw();
}

void tst_QLineSeries::remove_chart_animation_data()
{
    append_data();
}

void tst_QLineSeries::remove_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    remove_chart();
}


void tst_QLineSeries::removeAll_raw_data()
{
    append_data();
}

void tst_QLineSeries::removeAll_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);
    m_series->removeAll();
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points().count(), 0);
}

void tst_QLineSeries::removeAll_chart_data()
{
    append_data();
}

void tst_QLineSeries::removeAll_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    removeAll_raw();
}

void tst_QLineSeries::removeAll_chart_animation_data()
{
    append_data();
}

void tst_QLineSeries::removeAll_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    removeAll_chart();
}

void tst_QLineSeries::replace_raw_data()
{
    append_data();
}

void tst_QLineSeries::replace_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);

    foreach(const QPointF& point,points)
       m_series->replace(point.x(),point.y(),point.x(),0);

    QList<QPointF> newPoints = m_series->points();

    QCOMPARE(newPoints.count(), points.count());

    for(int i =0 ; i<points.count() ; ++i) {
        QCOMPARE(points[i].x(), newPoints[i].x());
        QCOMPARE(newPoints[i].y(), 0.0);
    }
}


void tst_QLineSeries::replace_chart_data()
{
    append_data();
}

void tst_QLineSeries::replace_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    replace_raw();
}

void tst_QLineSeries::replace_chart_animation_data()
{
    append_data();
}

void tst_QLineSeries::replace_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    replace_chart();
}

QTEST_MAIN(tst_QLineSeries)

#include "tst_qlineseries.moc"

