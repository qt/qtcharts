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
#include <qchartaxis.h>
#include <qlineseries.h>
#include <private/chartdataset_p.h>
#include <private/domain_p.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(Domain *)
Q_DECLARE_METATYPE(QChartAxis *)
Q_DECLARE_METATYPE(QAbstractSeries *)
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
	void removeSeries_data();
	void removeSeries();
	void removeAllSeries_data();
	void removeAllSeries();
	void axisY_data();
	void axisY();
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
};

void tst_ChartDataSet::initTestCase()
{
    qRegisterMetaType<Domain*>();
	qRegisterMetaType<QChartAxis*>();
	qRegisterMetaType<QSeries*>();
}

void tst_ChartDataSet::cleanupTestCase()
{
}

void tst_ChartDataSet::init()
{
}

void tst_ChartDataSet::cleanup()
{
}

void tst_ChartDataSet::chartdataset_data()
{
}

void tst_ChartDataSet::chartdataset()
{
	ChartDataSet dataSet;
	QVERIFY2(dataSet.axisX(), "Missing axisX.");
	QVERIFY2(dataSet.axisY(), "Missing axisY.");
	//check if not dangling pointer
	dataSet.axisX()->objectName();
	dataSet.axisY()->objectName();
	QLineSeries* series = new QLineSeries(this);
	QCOMPARE(dataSet.seriesIndex(series),-1);
}

void tst_ChartDataSet::addSeries_data()
{
	QTest::addColumn<QLineSeries*>("series0");
    QTest::addColumn<QChartAxis*>("axis0");
    QTest::addColumn<QLineSeries*>("series1");
    QTest::addColumn<QChartAxis*>("axis1");
    QTest::addColumn<QLineSeries*>("series2");
    QTest::addColumn<QChartAxis*>("axis2");
    QTest::addColumn<int>("axisCount");

    QLineSeries* series0 = new QLineSeries(this);
    QLineSeries* series1 = new QLineSeries(this);
    QLineSeries* series2 = new QLineSeries(this);

    QChartAxis* axis0 = new QChartAxis(this);
    QChartAxis* axis1 = new QChartAxis(this);
    QChartAxis* axis2 = new QChartAxis(this);

	QTest::newRow("default axis Y: series0,series1,series2") << series0 << (QChartAxis*)0 << series1 << (QChartAxis*)0  << series2 << (QChartAxis*)0 << 2;
	QTest::newRow("default axis Y: series0, axis 0: series1,series2") << series0 << (QChartAxis*)0 << series1 << axis0 << series2 << axis0 << 3;
	QTest::newRow("axis0: series0, axis1: series1, axis2: series2") << series0 << axis0 << series1 << axis1 << series2 << axis2 << 4;
}

void tst_ChartDataSet::addSeries()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);

    ChartDataSet dataSet;

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*,Domain*)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QAbstractSeries *,Domain*)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QAbstractSeries *)));

    dataSet.addSeries(series0,axis0);
    dataSet.addSeries(series1,axis1);
    dataSet.addSeries(series2,axis2);

    QCOMPARE(spy0.count(), axisCount);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 3);
    QCOMPARE(spy3.count(), 0);

    if(axis0==0) axis0 = dataSet.axisY();
    if(axis1==0) axis1 = dataSet.axisY();
    if(axis2==0) axis2 = dataSet.axisY();

    QVERIFY(axis0 == dataSet.removeSeries(series0));
    QVERIFY(axis1 == dataSet.removeSeries(series1));
    QVERIFY(axis2 == dataSet.removeSeries(series2));
}

void tst_ChartDataSet::removeSeries_data()
{
    addSeries_data();
}

void tst_ChartDataSet::removeSeries()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);

    ChartDataSet dataSet;

    dataSet.addSeries(series0,axis0);
    dataSet.addSeries(series1,axis1);
    dataSet.addSeries(series2,axis2);

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis *, Domain *)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis *)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QAbstractSeries *)));

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), axisCount);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 3);
}

void tst_ChartDataSet::removeAllSeries_data()
{

}

void tst_ChartDataSet::removeAllSeries()
{
    QLineSeries* series0 = new QLineSeries(this);
    QLineSeries* series1 = new QLineSeries(this);
    QLineSeries* series2 = new QLineSeries(this);

    QChartAxis* axis0 = new QChartAxis(this);
    QChartAxis* axis1 = new QChartAxis(this);
    QChartAxis* axis2 = new QChartAxis(this);


    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis *, Domain *)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis *)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QAbstractSeries *)));

    dataSet.removeAllSeries();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 4);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 3);
}


void tst_ChartDataSet::axisY_data()
{
    QTest::addColumn<QChartAxis*>("axis0");
    QTest::addColumn<QChartAxis*>("axis1");
    QTest::addColumn<QChartAxis*>("axis2");
    QTest::newRow("1 defualt, 2 optional") << (QChartAxis*)0 << new QChartAxis() << new QChartAxis();
    QTest::newRow("3 optional") << new QChartAxis() << new QChartAxis() << new QChartAxis();
}

void tst_ChartDataSet::axisY()
{
    QFETCH(QChartAxis*, axis0);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QChartAxis*, axis2);

    ChartDataSet dataSet;

    QChartAxis* defaultAxisY = dataSet.axisY();

    QVERIFY2(defaultAxisY, "Missing axisY.");

    QLineSeries* series0 = new QLineSeries();
    dataSet.addSeries(series0,axis0);

    QLineSeries* series1 = new QLineSeries();
    dataSet.addSeries(series1,axis1);

    QLineSeries* series2 = new QLineSeries();
    dataSet.addSeries(series2,axis2);

    if(!axis0) axis0=defaultAxisY ;
    if(!axis1) axis1=defaultAxisY ;
    if(!axis2) axis2=defaultAxisY ;

    QVERIFY(dataSet.axisY(series0) == axis0);
    QVERIFY(dataSet.axisY(series1) == axis1);
    QVERIFY(dataSet.axisY(series2) == axis2);

}

void tst_ChartDataSet::seriesCount_data()
{
    addSeries_data();
}

void tst_ChartDataSet::seriesCount()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis *, Domain *)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis *)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QAbstractSeries *)));

    QCOMPARE(dataSet.seriesCount(series0->type()),3);
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);
}

void tst_ChartDataSet::seriesIndex_data()
{
    addSeries_data();
}

void tst_ChartDataSet::seriesIndex()
{
    //TODO: rewrite this series_index_data to match better

    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*,Domain*)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QSeries*,Domain*)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QSeries*)));

    QCOMPARE(dataSet.seriesIndex(series0),0);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),2);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);

    QCOMPARE(dataSet.seriesIndex(series0),-1);
    QCOMPARE(dataSet.seriesIndex(series1),-1);
    QCOMPARE(dataSet.seriesIndex(series2),-1);

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    QCOMPARE(dataSet.seriesIndex(series0),0);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),2);

    dataSet.removeSeries(series1);

    QCOMPARE(dataSet.seriesIndex(series0),0);
    QCOMPARE(dataSet.seriesIndex(series1),-1);
    QCOMPARE(dataSet.seriesIndex(series2),2);

    dataSet.addSeries(series1, axis1);
    QCOMPARE(dataSet.seriesIndex(series0),0);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),2);

    dataSet.removeSeries(series2);
    QCOMPARE(dataSet.seriesIndex(series0),0);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),-1);

    dataSet.removeSeries(series0);
    QCOMPARE(dataSet.seriesIndex(series0),-1);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),-1);

    dataSet.addSeries(series2);
    QCOMPARE(dataSet.seriesIndex(series0),-1);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),0);

    dataSet.addSeries(series0);
    QCOMPARE(dataSet.seriesIndex(series0),2);
    QCOMPARE(dataSet.seriesIndex(series1),1);
    QCOMPARE(dataSet.seriesIndex(series2),0);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);

}

void tst_ChartDataSet::domain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::domain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis *, Domain *)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis *)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QAbstractSeries *)));

    QVERIFY(dataSet.domain(axis0)==dataSet.domain(series0));
    QVERIFY(dataSet.domain(axis1)==dataSet.domain(series1));
    QVERIFY(dataSet.domain(axis2)==dataSet.domain(series2));
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);
}

void tst_ChartDataSet::zoomInDomain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::zoomInDomain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);

    Q_UNUSED(axisCount);
    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    Domain* domain0 = dataSet.domain(series0);
    Domain* domain1 = dataSet.domain(series1);
    Domain* domain2 = dataSet.domain(series2);

    QSignalSpy spy0(domain0, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(domain1, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy2(domain2, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));

    dataSet.zoomInDomain(QRect(0,0,100,100),QSize(1000,1000));

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);
}

void tst_ChartDataSet::zoomOutDomain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::zoomOutDomain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);

    Q_UNUSED(axisCount);

    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    Domain* domain0 = dataSet.domain(series0);
    Domain* domain1 = dataSet.domain(series1);
    Domain* domain2 = dataSet.domain(series2);

    QSignalSpy spy0(domain0, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(domain1, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy2(domain2, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));

    dataSet.zoomOutDomain(QRect(0,0,100,100),QSize(1000,1000));

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);
}

void tst_ChartDataSet::scrollDomain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::scrollDomain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QChartAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QChartAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QChartAxis*, axis2);
    QFETCH(int, axisCount);

    Q_UNUSED(axisCount);

    ChartDataSet dataSet;

    dataSet.addSeries(series0, axis0);
    dataSet.addSeries(series1, axis1);
    dataSet.addSeries(series2, axis2);

    Domain* domain0 = dataSet.domain(series0);
    Domain* domain1 = dataSet.domain(series1);
    Domain* domain2 = dataSet.domain(series2);

    QSignalSpy spy0(domain0, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(domain1, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy2(domain2, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));

    dataSet.scrollDomain(10,10,QSize(1000,1000));

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);

    dataSet.removeSeries(series0);
    dataSet.removeSeries(series1);
    dataSet.removeSeries(series2);
}

QTEST_MAIN(tst_ChartDataSet)
#include "tst_chartdataset.moc"

