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

#include "tst_qxyseries.h"

Q_DECLARE_METATYPE(QList<QPointF>)

void tst_QXYSeries::initTestCase()
{
}

void tst_QXYSeries::cleanupTestCase()
{
}

void tst_QXYSeries::init()
{
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
}

void tst_QXYSeries::cleanup()
{
    delete m_view;
    m_view = 0;
    m_chart = 0;
    m_series = 0;
}

void tst_QXYSeries::seriesName()
{
    QSignalSpy nameSpy(m_series, SIGNAL(nameChanged()));
    QCOMPARE(m_series->name(), QString());
    m_series->setName("seriesname");
    QCOMPARE(m_series->name(), QString("seriesname"));
    TRY_COMPARE(nameSpy.count(), 1);
}

void tst_QXYSeries::seriesVisible()
{
    QSignalSpy visibleSpy(m_series, SIGNAL(visibleChanged()));
    QCOMPARE(m_series->isVisible(), true);
    m_series->setVisible(false);
    QCOMPARE(m_series->isVisible(), false);
    m_series->setVisible(true);
    TRY_COMPARE(visibleSpy.count(), 2);
}

void tst_QXYSeries::append_data()
{
    QTest::addColumn< QList<QPointF> >("points");
    QTest::newRow("0,0 1,1 2,2 3,3") << (QList<QPointF>() << QPointF(0,0) << QPointF(1,1) << QPointF(2,2) << QPointF(3,3));
    QTest::newRow("0,0 -1,-1 -2,-2 -3,-3") << (QList<QPointF>() << QPointF(0,0) << QPointF(-1,-1) << QPointF(-2,-2) << QPointF(-3,-3));
}


void tst_QXYSeries::append_raw_data()
{
    append_data();
}

void tst_QXYSeries::append_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy addedSpy(m_series, SIGNAL(pointAdded(int)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(addedSpy.count(), points.count());
    QCOMPARE(m_series->points(), points);
}

void tst_QXYSeries::chart_append_data()
{
    append_data();
}

void tst_QXYSeries::chart_append()
{
    append_raw();
    m_chart->addSeries(m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QXYSeries::append_chart_data()
{
    append_data();
}

void tst_QXYSeries::append_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    append_raw();

}

void tst_QXYSeries::append_chart_animation_data()
{
    append_data();
}

void tst_QXYSeries::append_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    append_chart();
}

void tst_QXYSeries::count_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("5") << 5;
    QTest::newRow("10") << 5;
}

void tst_QXYSeries::count_raw_data()
{
    count_data();
}

void tst_QXYSeries::count_raw()
{
    QFETCH(int, count);

    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));

    for(int i=0 ; i< count; ++i)
        m_series->append(i,i);

    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->count(), count);
}

void tst_QXYSeries::remove_raw_data()
{
    append_data();
}

void tst_QXYSeries::remove_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);

    foreach(const QPointF& point,points)
        m_series->remove(point);

    QCOMPARE(m_series->points().count(), 0);
    TRY_COMPARE(spy0.count(), 0);

    m_series->append(points);
    QCOMPARE(m_series->points(), points);

    //reverse order
    for(int i = points.count()-1 ; i>=0; i--){
        m_series->remove(points[i]);
    }
    QCOMPARE(m_series->points().count(), 0);
}

void tst_QXYSeries::remove_chart_data()
{
    append_data();
}

void tst_QXYSeries::remove_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    remove_raw();
}

void tst_QXYSeries::remove_chart_animation_data()
{
    append_data();
}

void tst_QXYSeries::remove_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    remove_chart();
}


void tst_QXYSeries::clear_raw_data()
{
    append_data();
}

void tst_QXYSeries::clear_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);
    m_series->clear();
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points().count(), 0);
}

void tst_QXYSeries::clear_chart_data()
{
    append_data();
}

void tst_QXYSeries::clear_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    clear_raw();
}

void tst_QXYSeries::clear_chart_animation_data()
{
    append_data();
}

void tst_QXYSeries::clear_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    clear_chart();
}

void tst_QXYSeries::replace_raw_data()
{
    append_data();
}

void tst_QXYSeries::replace_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy replacedSpy(m_series, SIGNAL(pointReplaced(int)));
    m_series->append(points);
    TRY_COMPARE(replacedSpy.count(), 0);
    QCOMPARE(m_series->points(), points);

    foreach(const QPointF& point, points)
       m_series->replace(point.x(),point.y(),point.x(),0);
    TRY_COMPARE(replacedSpy.count(), points.count());

    // Replace a point that does not exist
    m_series->replace(-123, 999, 0, 0);
    TRY_COMPARE(replacedSpy.count(), points.count());

    QList<QPointF> newPoints = m_series->points();

    QCOMPARE(newPoints.count(), points.count());

    for(int i =0 ; i<points.count() ; ++i) {
        QCOMPARE(points[i].x(), newPoints[i].x());
        QCOMPARE(newPoints[i].y(), 0.0);
    }
}


void tst_QXYSeries::replace_chart_data()
{
    append_data();
}

void tst_QXYSeries::replace_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    QTest::qWaitForWindowShown(m_view);
    replace_raw();
}

void tst_QXYSeries::replace_chart_animation_data()
{
    append_data();
}

void tst_QXYSeries::replace_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    replace_chart();
}

void tst_QXYSeries::insert_data()
{
    append_data();
}

void tst_QXYSeries::insert()
{
    QFETCH(QList<QPointF>, points);
    m_series->append(points);

    QSignalSpy addedSpy(m_series, SIGNAL(pointAdded(int)));

    m_series->insert(0, QPointF(5, 5));
    TRY_COMPARE(addedSpy.count(), 1);
    QCOMPARE(m_series->points().count(), points.count() + 1);

    m_series->insert(m_series->count(), QPointF(6, 6));
    TRY_COMPARE(addedSpy.count(), 2);
    QCOMPARE(m_series->points().count(), points.count() + 2);
}

void tst_QXYSeries::oper_data()
{
    append_data();
}

void tst_QXYSeries::oper()
{
    QFETCH(QList<QPointF>, points);

    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));

    foreach(const QPointF& point,points)
    {
        *m_series<<point;
    }

    QCOMPARE(m_series->points(), points);
    TRY_COMPARE(spy0.count(), 0);
}


void tst_QXYSeries::pen_data()
{
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QXYSeries::pen()
{
    QFETCH(QPen, pen);

    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->setPen(pen);

    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->pen(), pen);

    m_chart->addSeries(m_series);

    if (pen != QPen())
        QCOMPARE(m_series->pen(), pen);

    m_chart->setTheme(QChart::ChartThemeDark);

    // setting a theme will overwrite all customizations
    if (pen != QPen())
        QVERIFY(m_series->pen() != pen);
}

void tst_QXYSeries::pointsVisible_data()
{
    QTest::addColumn<bool>("pointsVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QXYSeries::pointsVisible_raw_data()
{
    pointsVisible_data();
}

void tst_QXYSeries::pointsVisible_raw()
{
    QFETCH(bool, pointsVisible);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->setPointsVisible(pointsVisible);
    TRY_COMPARE(spy0.count(), 0);
    QCOMPARE(m_series->pointsVisible(), pointsVisible);
}

void tst_QXYSeries::changedSignals()
{
    QSignalSpy visibleSpy(m_series, SIGNAL(visibleChanged()));

    m_series->setVisible(false);
    m_series->setVisible(false);
    TRY_COMPARE(visibleSpy.count(), 1);
    m_series->setVisible(true);
    TRY_COMPARE(visibleSpy.count(), 2);
}

