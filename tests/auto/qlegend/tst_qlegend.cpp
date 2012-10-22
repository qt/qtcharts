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
#include <qchartview.h>
#include <qlegend.h>
#include <qpieseries.h>
#include <qpielegendmarker.h>
#include <qareaseries.h>
#include <qarealegendmarker.h>
#include <qlineseries.h>
#include <qxylegendmarker.h>
#include <qbarseries.h>
#include <qbarset.h>
#include <qbarlegendmarker.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QLegend : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qlegend();
    void qpieLegendMarker();
    void qareaLegendMarker();
    void qxyLegendMarker();
    void qbarLegendMarker();

private:

    QChart *m_chart;
    
};

void tst_QLegend::initTestCase()
{
}

void tst_QLegend::cleanupTestCase()
{
}

void tst_QLegend::init()
{
    m_chart = new QChart();
}

void tst_QLegend::cleanup()
{
    delete m_chart;
    m_chart = 0;
}

void tst_QLegend::qlegend()
{
    QVERIFY(m_chart);

    QLegend *legend = m_chart->legend();
    QVERIFY(legend);

    QList<QLegendMarker*> markers = legend->markers();
    QVERIFY(markers.count() == 0);
}

void tst_QLegend::qpieLegendMarker()
{
    QVERIFY(m_chart);
    QLegend *legend = m_chart->legend();

    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = new QPieSlice(QString("s1"), 111.0);
    series->append(s1);
    m_chart->addSeries(series);

    // Should have one marker
    QList<QLegendMarker*> markers = legend->markers();
    QVERIFY(markers.count() == 1);
    QLegendMarker *m = markers.at(0);

    // Should be piemarker
    QVERIFY(m->type() == QLegendMarker::LegendMarkerTypePie);

    // Related series and slice must match
    QPieLegendMarker *pm = qobject_cast<QPieLegendMarker *> (m);
    QVERIFY(pm);
    QVERIFY(pm->series() == series);
    QVERIFY(pm->slice() == s1);

    // Add another slice
    QPieSlice *s2 = new QPieSlice(QString("s2"), 111.0);
    series->append(s2);

    markers = legend->markers();
    QVERIFY(markers.count() == 2);
    m = markers.at(1);

    QVERIFY(m->type() == QLegendMarker::LegendMarkerTypePie);

    // Related series and slice must match
    pm = qobject_cast<QPieLegendMarker *> (m);
    QVERIFY(pm);
    QVERIFY(pm->series() == series);
    QVERIFY(pm->slice() == s2);
}

void tst_QLegend::qareaLegendMarker()
{
    QVERIFY(m_chart);
    QLegend *legend = m_chart->legend();
    QAreaSeries *series = new QAreaSeries();

    QLineSeries *upper = new QLineSeries();
    QLineSeries *lower = new QLineSeries();

    upper->append(1,1);
    lower->append(1,0);

    series->setUpperSeries(upper);
    series->setLowerSeries(lower);

    m_chart->addSeries(series);

    // Should have one marker
    QList<QLegendMarker *> markers = legend->markers();
    QVERIFY(markers.count() == 1);
    QLegendMarker *m = markers.at(0);

    QVERIFY(m->series() == series);
    QVERIFY(m->type() == QLegendMarker::LegendMarkerTypeArea);

    QAreaLegendMarker *pm = qobject_cast<QAreaLegendMarker *> (m);
    QVERIFY(pm);
    QVERIFY(pm->series() == series);
}

void tst_QLegend::qxyLegendMarker()
{
    QVERIFY(m_chart);
    QLegend *legend = m_chart->legend();

    QLineSeries *series = new QLineSeries();
    m_chart->addSeries(series);

    // Should have one marker
    QList<QLegendMarker *> markers = legend->markers();
    QVERIFY(markers.count() == 1);
    QLegendMarker *m = markers.at(0);

    QVERIFY(m->series() == series);
    QVERIFY(m->type() == QLegendMarker::LegendMarkerTypeXY);

    QXYLegendMarker *pm = qobject_cast<QXYLegendMarker *> (m);
    QVERIFY(pm);
    QVERIFY(pm->series() == series);
}

void tst_QLegend::qbarLegendMarker()
{
    QVERIFY(m_chart);
    QLegend *legend = m_chart->legend();

    QBarSeries *series = new QBarSeries();
    QBarSet *set0 = new QBarSet(QString("set0"));
    series->append(set0);
    m_chart->addSeries(series);

    // Should have one marker
    QList<QLegendMarker *> markers = legend->markers();
    QVERIFY(markers.count() == 1);
    QLegendMarker *m = markers.at(0);

    QVERIFY(m->series() == series);
    QVERIFY(m->type() == QLegendMarker::LegendMarkerTypeBar);

    QBarLegendMarker *pm = qobject_cast<QBarLegendMarker *> (m);
    QVERIFY(pm);
    QVERIFY(pm->series() == series);
    QVERIFY(pm->barset() == set0);

    // Add another barset
    QBarSet *set1 = new QBarSet(QString("set0"));
    series->append(set1);

    markers = legend->markers();
    QVERIFY(markers.count() == 2);
    m = markers.at(1);

    QVERIFY(m->series() == series);
    QVERIFY(m->type() == QLegendMarker::LegendMarkerTypeBar);

    pm = qobject_cast<QBarLegendMarker *> (m);
    QVERIFY(pm);
    QVERIFY(pm->series() == series);
    QVERIFY(pm->barset() == set1);
}

QTEST_MAIN(tst_QLegend)

#include "tst_qlegend.moc"

