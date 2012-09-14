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
#ifndef BUILD_PRIVATE_UNIT_TESTS
#include <QtTest/QtTest>

class tst_ChartDataSet: public QObject {

    Q_OBJECT

private Q_SLOTS:
    void skip();

};

void tst_ChartDataSet::skip()
{
#ifdef QT5_QUICK_1
    QSKIP("This test requires the debug version of library");
#else
    QSKIP("This test requires the debug version of library", SkipAll);
#endif
}

QTEST_MAIN(tst_ChartDataSet)
#include "tst_chartdataset.moc"

#else

#include <QtTest/QtTest>
#include <qabstractaxis.h>
#include <qvalueaxis.h>
#include <qbarcategoryaxis.h>
#include <qlineseries.h>
#include <qareaseries.h>
#include <qscatterseries.h>
#include <qsplineseries.h>
#include <qpieseries.h>
#include <qbarseries.h>
#include <qpercentbarseries.h>
#include <qstackedbarseries.h>
#include <private/chartdataset_p.h>
#include <private/domain_p.h>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(Domain *)
Q_DECLARE_METATYPE(QAbstractAxis *)
Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QList<QAbstractSeries *>)
Q_DECLARE_METATYPE(QList<QAbstractAxis *>)
Q_DECLARE_METATYPE(QLineSeries *)

class tst_ChartDataSet: public QObject {

    Q_OBJECT

public Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();
	void init();
	void cleanup();

private Q_SLOTS:
	void chartdataset_data();
	void chartdataset();
	void addSeries_data();
	void addSeries();
    void setAxisX_data();
    void setAxisX();
    void setAxisY_data();
    void setAxisY();
	void removeSeries_data();
	void removeSeries();
	void removeAllSeries_data();
	void removeAllSeries();
    void seriesCount_data();
	void seriesCount();
    void seriesIndex_data();
	void seriesIndex();
	void domain_data();
	void domain();
    void zoomInDomain_data();
	void zoomInDomain();
    void zoomOutDomain_data();
    void zoomOutDomain();
    void scrollDomain_data();
    void scrollDomain();

private:
    ChartDataSet* m_dataset;
};

void tst_ChartDataSet::initTestCase()
{
    qRegisterMetaType<Domain*>();
	qRegisterMetaType<QAbstractAxis*>();
    qRegisterMetaType<QAbstractSeries*>();
}

void tst_ChartDataSet::cleanupTestCase()
{
}

void tst_ChartDataSet::init()
{
    m_dataset = new ChartDataSet();
}


void tst_ChartDataSet::cleanup()
{
    QList<QAbstractSeries*> series = m_dataset->series();
    foreach(QAbstractSeries* serie, series)
    {
        m_dataset->removeSeries(serie);
    }
}

void tst_ChartDataSet::chartdataset_data()
{
}

void tst_ChartDataSet::chartdataset()
{
	QVERIFY(m_dataset->axisX(0) == 0);
	QVERIFY(m_dataset->axisY(0) == 0);
	QLineSeries* series = new QLineSeries(this);
	QCOMPARE(m_dataset->seriesIndex(series),-1);
	QVERIFY(m_dataset->domain(series) == 0);
	QVERIFY(m_dataset->axisX(series) == 0);
	QVERIFY(m_dataset->axisY(series) == 0);
	m_dataset->createDefaultAxes();
}


void tst_ChartDataSet::addSeries_data()
{
	QTest::addColumn<QAbstractSeries*>("series");

    QAbstractSeries* line = new QLineSeries(this);
    QAbstractSeries* area = new QAreaSeries(static_cast<QLineSeries*>(line));
    QAbstractSeries* scatter = new QScatterSeries(this);
    QAbstractSeries* spline = new QSplineSeries(this);
    QAbstractSeries* pie = new QPieSeries(this);
    QAbstractSeries* bar = new QBarSeries(this);
    QAbstractSeries* percent = new QPercentBarSeries(this);
    QAbstractSeries* stacked = new QStackedBarSeries(this);

	QTest::newRow("line") << line;
	QTest::newRow("area") << area;
	QTest::newRow("scatter") << scatter;
	QTest::newRow("spline") << spline;
	QTest::newRow("pie") << pie;
    QTest::newRow("bar") << bar;
	QTest::newRow("percent") << percent;
	QTest::newRow("stacked") << stacked;
}

void tst_ChartDataSet::addSeries()
{

    QFETCH(QAbstractSeries*, series);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis*, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis*)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->addSeries(series);
    m_dataset->createDefaultAxes();
    if(series->type()==QAbstractSeries::SeriesTypePie){
        TRY_COMPARE(spy0.count(), 0);
    }else{
        TRY_COMPARE(spy0.count(), 2);
    }
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 1);
    TRY_COMPARE(spy3.count(), 0);
}


void tst_ChartDataSet::setAxisX_data()
{
    QTest::addColumn<QList<QAbstractSeries*> >("seriesList");
    QTest::addColumn<QList<QAbstractAxis*> >("axisList");
    QTest::addColumn<int>("axisCount");

    QAbstractSeries* line = new QLineSeries(this);
    QAbstractSeries* area = new QAreaSeries(static_cast<QLineSeries*>(line));
    QAbstractSeries* scatter = new QScatterSeries(this);
    QAbstractSeries* spline = new QSplineSeries(this);
    /*QAbstractSeries* pie = */new QPieSeries(this);
    /*QAbstractSeries* bar = */new QBarSeries(this);
    /*QAbstractSeries* percent = */new QPercentBarSeries(this);
    /*QAbstractSeries* stacked = */new QStackedBarSeries(this);

    QTest::newRow("line,spline,scatter: axis 0 axis1 axis 2")
        << (QList<QAbstractSeries*>() << line << spline << scatter)
        << (QList<QAbstractAxis*>() << new QValueAxis(this) << new QValueAxis(this) << new QValueAxis(this)) << 3;

    QTest::newRow("area: axis 0") << (QList<QAbstractSeries*>() << area)
        << (QList<QAbstractAxis*>() << new QValueAxis(this)) << 1;

    QList<QAbstractAxis*> axes0;
    axes0 << new QValueAxis(this) << new QValueAxis(this);
    axes0 << axes0.last();
    QTest::newRow("line,spline,scatter: axis 0 axis1 axis 1")
        << (QList<QAbstractSeries*>() << line << spline << scatter)
        << axes0 << 2;
    //TODO: add more test cases
}

void tst_ChartDataSet::setAxisX()
{
    QFETCH(QList<QAbstractSeries*>, seriesList);
    QFETCH(QList<QAbstractAxis*>, axisList);
    QFETCH(int, axisCount);

    Q_ASSERT(seriesList.count() == axisList.count());

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis *,Domain*)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *,Domain*)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    foreach(QAbstractSeries* series, seriesList){
        m_dataset->addSeries(series);
    }

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), seriesList.count());
    TRY_COMPARE(spy3.count(), 0);

    QSignalSpy spy4(m_dataset, SIGNAL(axisAdded(QAbstractAxis*,Domain*)));
    QSignalSpy spy5(m_dataset, SIGNAL(axisRemoved(QAbstractAxis*)));
    QSignalSpy spy6(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *,Domain*)));
    QSignalSpy spy7(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    for(int i=0 ; i < seriesList.count(); i++){
           m_dataset->setAxis(seriesList.at(i),axisList.at(i),Qt::Horizontal);
    }

    TRY_COMPARE(spy4.count(), axisCount);
    TRY_COMPARE(spy5.count(), 0);
    TRY_COMPARE(spy6.count(), 0);
    TRY_COMPARE(spy7.count(), 0);

    for(int i=0 ; i < seriesList.count(); i++){
        QVERIFY(m_dataset->axisX(seriesList.at(i)) == axisList.at(i));
    }
}

void tst_ChartDataSet::setAxisY_data()
{
    setAxisX_data();
}

void tst_ChartDataSet::setAxisY()
{
    QFETCH(QList<QAbstractSeries*>, seriesList);
    QFETCH(QList<QAbstractAxis*>, axisList);
    QFETCH(int, axisCount);

    Q_ASSERT(seriesList.count() == axisList.count());

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis*,Domain*)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis*)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *,Domain*)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    foreach(QAbstractSeries* series, seriesList){
        m_dataset->addSeries(series);
    }

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), seriesList.count());
    TRY_COMPARE(spy3.count(), 0);

    QSignalSpy spy4(m_dataset, SIGNAL(axisAdded(QAbstractAxis*,Domain*)));
    QSignalSpy spy5(m_dataset, SIGNAL(axisRemoved(QAbstractAxis*)));
    QSignalSpy spy6(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *,Domain*)));
    QSignalSpy spy7(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    for(int i=0 ; i < seriesList.count(); i++){
           m_dataset->setAxis(seriesList.at(i),axisList.at(i),Qt::Vertical);
    }

    TRY_COMPARE(spy4.count(), axisCount);
    TRY_COMPARE(spy5.count(), 0);
    TRY_COMPARE(spy6.count(), 0);
    TRY_COMPARE(spy7.count(), 0);

    for(int i=0 ; i < seriesList.count(); i++){
        QVERIFY(m_dataset->axisY(seriesList.at(i)) == axisList.at(i));
    }
}

void tst_ChartDataSet::removeSeries_data()
{
    addSeries_data();
}

void tst_ChartDataSet::removeSeries()
{
    QFETCH(QAbstractSeries*, series);

    m_dataset->addSeries(series);
    m_dataset->createDefaultAxes();

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis*, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis*)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->removeSeries(series);

    TRY_COMPARE(spy0.count(), 0);
    if (series->type() == QAbstractSeries::SeriesTypePie) {
        TRY_COMPARE(spy1.count(), 0);
    }
    else {
        TRY_COMPARE(spy1.count(), 2);
    }
    TRY_COMPARE(spy2.count(), 0);
    TRY_COMPARE(spy3.count(), 1);
}

void tst_ChartDataSet::removeAllSeries_data()
{
    QTest::addColumn<QList<QAbstractSeries*> >("seriesList");
    QTest::addColumn<QList<QAbstractAxis*> >("axisList");
    QTest::addColumn<int>("axisCount");

    QTest::newRow("line,spline,scatter: axis 0 axis1 axis 2")
        << (QList<QAbstractSeries*>() << new QLineSeries(this) << new QSplineSeries(this)
            << new QScatterSeries(this))
        << (QList<QAbstractAxis*>() << new QValueAxis(this) << new QValueAxis(this)
            << new QValueAxis(this)) << 3;
    //TODO:
}

void tst_ChartDataSet::removeAllSeries()
{
    QFETCH(QList<QAbstractSeries*>, seriesList);
    QFETCH(QList<QAbstractAxis*>, axisList);
    QFETCH(int, axisCount);

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->addSeries(series);
    }

    for (int i = 0; i < seriesList.count(); i++) {
        m_dataset->setAxis(seriesList.at(i), axisList.at(i),Qt::Horizontal);
    }

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->removeAllSeries();

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), axisCount);
    TRY_COMPARE(spy2.count(), 0);
    TRY_COMPARE(spy3.count(), seriesList.count());
}


void tst_ChartDataSet::seriesCount_data()
{
    QTest::addColumn<QList<QAbstractSeries*> >("seriesList");
    QTest::addColumn<int>("seriesCount");

    QTest::newRow("line,line, line, spline  3") << (QList<QAbstractSeries*>() <<  new QLineSeries(this) <<  new QLineSeries(this) <<  new QLineSeries(this) << new QSplineSeries(this) ) << 3;
    QTest::newRow("scatter,scatter, line, line  2") << (QList<QAbstractSeries*>() <<  new QScatterSeries(this) <<  new QScatterSeries(this) << new QLineSeries(this) << new QLineSeries(this) ) << 2;
}

void tst_ChartDataSet::seriesCount()
{
    QFETCH(QList<QAbstractSeries*>, seriesList);
    QFETCH(int, seriesCount);

    foreach(QAbstractSeries* series, seriesList){
          m_dataset->addSeries(series);
    }

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    QCOMPARE(m_dataset->seriesCount(seriesList.at(0)->type()),seriesCount);
    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 0);
    TRY_COMPARE(spy3.count(), 0);
}

void tst_ChartDataSet::seriesIndex_data()
{
    QTest::addColumn<QList<QAbstractSeries*> >("seriesList");

    QTest::newRow("line,line, line, spline") << (QList<QAbstractSeries*>() <<  new QLineSeries(this) <<  new QLineSeries(this) <<  new QLineSeries(this) << new QSplineSeries(this) );
    QTest::newRow("scatter,scatter, line, line") << (QList<QAbstractSeries*>() <<  new QScatterSeries(this) <<  new QScatterSeries(this) << new QLineSeries(this) << new QLineSeries(this) );
}

void tst_ChartDataSet::seriesIndex()
{

    QFETCH(QList<QAbstractSeries*>, seriesList);

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->addSeries(series);
    }

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis *,Domain*)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries*,Domain*)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)));

    for (int i = 0; i < seriesList.count(); i++) {
        QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
    }

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 0);
    TRY_COMPARE(spy3.count(), 0);

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->removeSeries(series);
    }

    for (int i = 0; i < seriesList.count(); i++) {
        QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), -1);
    }

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->addSeries(series);
    }

    for (int i = 0; i < seriesList.count(); i++) {
        QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
    }

    m_dataset->removeSeries(seriesList.at(1));

    for (int i = 0; i < seriesList.count(); i++) {
        if (i != 1)
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
        else
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), -1);
    }

    m_dataset->addSeries(seriesList.at(1));

    for (int i = 0; i < seriesList.count(); i++) {
        QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
    }

    m_dataset->removeSeries(seriesList.at(2));

    for (int i = 0; i < seriesList.count(); i++) {
        if (i != 2)
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
        else
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), -1);
    }

    m_dataset->removeSeries(seriesList.at(0));

    for (int i = 0; i < seriesList.count(); i++) {
        if (i != 2 && i != 0)
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
        else
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), -1);
    }

    m_dataset->addSeries(seriesList.at(2));
    m_dataset->addSeries(seriesList.at(0));

    for (int i = 0; i < seriesList.count(); i++) {
        if (i == 2)
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), 0);
        else if (i == 0)
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), 2);
        else
            QCOMPARE(m_dataset->seriesIndex(seriesList.at(i)), i);
    }

}

void tst_ChartDataSet::domain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::domain()
{
    QFETCH(QAbstractSeries*, series);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAbstractAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAbstractAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->addSeries(series);
    QVERIFY(m_dataset->domain(series));


    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 1);

    QList<QVariant> arguments = spy2.takeFirst();
    Domain *domain = (Domain *) arguments.at(1).value<Domain *>();
    QVERIFY(m_dataset->domain(series) == domain);

    TRY_COMPARE(spy3.count(), 0);

}

void tst_ChartDataSet::zoomInDomain_data()
{
    QTest::addColumn<bool >("sameAxis");
    QTest::addColumn<QList<QAbstractSeries*> >("seriesList");
    QTest::newRow("sameAxis: line,line, line, spline") << true << (QList<QAbstractSeries*>() <<  new QLineSeries(this) <<  new QLineSeries(this) <<  new QLineSeries(this) << new QSplineSeries(this) );
    QTest::newRow("separeateAxis: line,line, line, spline") << false << (QList<QAbstractSeries*>() <<  new QLineSeries(this) <<  new QLineSeries(this) <<  new QLineSeries(this) << new QSplineSeries(this) );
}

void tst_ChartDataSet::zoomInDomain()
{
    QFETCH(bool, sameAxis);
    QFETCH(QList<QAbstractSeries*>, seriesList);

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->addSeries(series);
    }

    if(sameAxis) m_dataset->createDefaultAxes();

    QList<QSignalSpy*> spyList;

    foreach(QAbstractSeries* series, seriesList) {
        spyList << new QSignalSpy(m_dataset->domain(series),SIGNAL(updated()));
    }

    m_dataset->zoomInDomain(QRect(0, 0, 100, 100), QSize(1000, 1000));

    foreach(QSignalSpy* spy, spyList) {
        TRY_COMPARE(spy->count(), 1);
    }

    qDeleteAll(spyList);
}



void tst_ChartDataSet::zoomOutDomain_data()
{
    zoomInDomain_data();
}

void tst_ChartDataSet::zoomOutDomain()
{
    QFETCH(bool, sameAxis);
    QFETCH(QList<QAbstractSeries*>, seriesList);

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->addSeries(series);
    }

    if (sameAxis)
        m_dataset->createDefaultAxes();

    QList<QSignalSpy*> spyList;

    foreach(QAbstractSeries* series, seriesList) {
        spyList << new QSignalSpy(m_dataset->domain(series), SIGNAL(updated()));
    }

    m_dataset->zoomOutDomain(QRect(0, 0, 100, 100), QSize(1000, 1000));

    foreach(QSignalSpy* spy, spyList) {
        TRY_COMPARE(spy->count(), 1);
    }

    qDeleteAll (spyList);
}

void tst_ChartDataSet::scrollDomain_data()
{
    zoomInDomain_data();
}

void tst_ChartDataSet::scrollDomain()
{
    QFETCH(bool, sameAxis);
    QFETCH(QList<QAbstractSeries*>, seriesList);

    foreach(QAbstractSeries* series, seriesList) {
        m_dataset->addSeries(series);
    }

    if (sameAxis)
        m_dataset->createDefaultAxes();

    QList<QSignalSpy*> spyList;

    foreach(QAbstractSeries* series, seriesList) {
        spyList
            << new QSignalSpy(m_dataset->domain(series),
                SIGNAL(updated()));
    }

    m_dataset->scrollDomain(10, 10, QSize(1000, 1000));

    foreach(QSignalSpy* spy, spyList) {
        TRY_COMPARE(spy->count(), 1);
    }

    qDeleteAll(spyList);
}

QTEST_MAIN(tst_ChartDataSet)
#include "tst_chartdataset.moc"
#endif
