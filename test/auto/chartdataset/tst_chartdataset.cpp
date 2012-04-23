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
#include <qaxis.h>
#include <qlineseries.h>
#include <private/chartdataset_p.h>
#include <private/domain_p.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(Domain *)
Q_DECLARE_METATYPE(QAxis *)
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
private:
    ChartDataSet* m_dataset;
};

void tst_ChartDataSet::initTestCase()
{
    qRegisterMetaType<Domain*>();
	qRegisterMetaType<QAxis*>();
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
	QVERIFY2(m_dataset->axisX(), "Missing axisX.");
	QVERIFY2(m_dataset->axisY(), "Missing axisY.");
	//check if not dangling pointer
	m_dataset->axisX()->objectName();
	m_dataset->axisY()->objectName();
	QLineSeries* series = new QLineSeries(this);
	QCOMPARE(m_dataset->seriesIndex(series),-1);
}

void tst_ChartDataSet::addSeries_data()
{
	QTest::addColumn<QLineSeries*>("series0");
    QTest::addColumn<QAxis*>("axis0");
    QTest::addColumn<QLineSeries*>("series1");
    QTest::addColumn<QAxis*>("axis1");
    QTest::addColumn<QLineSeries*>("series2");
    QTest::addColumn<QAxis*>("axis2");
    QTest::addColumn<int>("axisCount");

    QLineSeries* series0 = new QLineSeries(this);
    QLineSeries* series1 = new QLineSeries(this);
    QLineSeries* series2 = new QLineSeries(this);

    QAxis* axis0 = new QAxis(this);
    QAxis* axis1 = new QAxis(this);
    QAxis* axis2 = new QAxis(this);

	QTest::newRow("default axis Y: series0,series1,series2") << series0 << (QAxis*)0 << series1 << (QAxis*)0  << series2 << (QAxis*)0 << 2;
	QTest::newRow("default axis Y: series0, axis0: series1,series2") << series0 << (QAxis*)0 << series1 << axis0 << series2 << axis0 << 3;
	QTest::newRow("axis0: series0, axis1: series1, axis2: series2") << series0 << axis0 << series1 << axis1 << series2 << axis2 << 4;
}

void tst_ChartDataSet::addSeries()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAxis*,Domain*)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAxis*)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *,Domain*)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->addSeries(series0,axis0);
    m_dataset->addSeries(series1,axis1);
    m_dataset->addSeries(series2,axis2);

    QCOMPARE(spy0.count(), axisCount);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 3);
    QCOMPARE(spy3.count(), 0);

    if(axis0==0) axis0 = m_dataset->axisY();
    if(axis1==0) axis1 = m_dataset->axisY();
    if(axis2==0) axis2 = m_dataset->axisY();

    QVERIFY(axis0 == m_dataset->removeSeries(series0));
    QVERIFY(axis1 == m_dataset->removeSeries(series1));
    QVERIFY(axis2 == m_dataset->removeSeries(series2));
}

void tst_ChartDataSet::removeSeries_data()
{
    addSeries_data();
}

void tst_ChartDataSet::removeSeries()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);

    m_dataset->addSeries(series0,axis0);
    m_dataset->addSeries(series1,axis1);
    m_dataset->addSeries(series2,axis2);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->removeSeries(series0);
    m_dataset->removeSeries(series1);
    m_dataset->removeSeries(series2);

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

    QAxis* axis0 = new QAxis(this);
    QAxis* axis1 = new QAxis(this);
    QAxis* axis2 = new QAxis(this);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    m_dataset->removeAllSeries();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 4);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 3);
}


void tst_ChartDataSet::axisY_data()
{
    QTest::addColumn<QAxis*>("axis0");
    QTest::addColumn<QAxis*>("axis1");
    QTest::addColumn<QAxis*>("axis2");
    QTest::newRow("1 defualt, 2 optional") << (QAxis*)0 << new QAxis() << new QAxis();
    QTest::newRow("3 optional") << new QAxis() << new QAxis() << new QAxis();
}

void tst_ChartDataSet::axisY()
{
    QFETCH(QAxis*, axis0);
    QFETCH(QAxis*, axis1);
    QFETCH(QAxis*, axis2);

    QAxis* defaultAxisY = m_dataset->axisY();

    QVERIFY2(defaultAxisY, "Missing axisY.");

    QLineSeries* series0 = new QLineSeries();
    m_dataset->addSeries(series0,axis0);

    QLineSeries* series1 = new QLineSeries();
    m_dataset->addSeries(series1,axis1);

    QLineSeries* series2 = new QLineSeries();
    m_dataset->addSeries(series2,axis2);

    if(!axis0) axis0=defaultAxisY ;
    if(!axis1) axis1=defaultAxisY ;
    if(!axis2) axis2=defaultAxisY ;

    QVERIFY(m_dataset->axisY(series0) == axis0);
    QVERIFY(m_dataset->axisY(series1) == axis1);
    QVERIFY(m_dataset->axisY(series2) == axis2);

}

void tst_ChartDataSet::seriesCount_data()
{
    addSeries_data();
}

void tst_ChartDataSet::seriesCount()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    QCOMPARE(m_dataset->seriesCount(series0->type()),3);
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
}

void tst_ChartDataSet::seriesIndex_data()
{
    addSeries_data();
}

void tst_ChartDataSet::seriesIndex()
{
    //TODO: rewrite this series_index_data to match better

    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAxis*,Domain*)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAxis*)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries*,Domain*)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)));

    QCOMPARE(m_dataset->seriesIndex(series0),0);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),2);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);

    m_dataset->removeSeries(series0);
    m_dataset->removeSeries(series1);
    m_dataset->removeSeries(series2);

    QCOMPARE(m_dataset->seriesIndex(series0),-1);
    QCOMPARE(m_dataset->seriesIndex(series1),-1);
    QCOMPARE(m_dataset->seriesIndex(series2),-1);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    QCOMPARE(m_dataset->seriesIndex(series0),0);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),2);

    m_dataset->removeSeries(series1);

    QCOMPARE(m_dataset->seriesIndex(series0),0);
    QCOMPARE(m_dataset->seriesIndex(series1),-1);
    QCOMPARE(m_dataset->seriesIndex(series2),2);

    m_dataset->addSeries(series1, axis1);
    QCOMPARE(m_dataset->seriesIndex(series0),0);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),2);

    m_dataset->removeSeries(series2);
    QCOMPARE(m_dataset->seriesIndex(series0),0);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),-1);

    m_dataset->removeSeries(series0);
    QCOMPARE(m_dataset->seriesIndex(series0),-1);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),-1);

    m_dataset->addSeries(series2);
    QCOMPARE(m_dataset->seriesIndex(series0),-1);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),0);

    m_dataset->addSeries(series0);
    QCOMPARE(m_dataset->seriesIndex(series0),2);
    QCOMPARE(m_dataset->seriesIndex(series1),1);
    QCOMPARE(m_dataset->seriesIndex(series2),0);
}

void tst_ChartDataSet::domain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::domain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    QSignalSpy spy0(m_dataset, SIGNAL(axisAdded(QAxis *, Domain *)));
    QSignalSpy spy1(m_dataset, SIGNAL(axisRemoved(QAxis *)));
    QSignalSpy spy2(m_dataset, SIGNAL(seriesAdded(QAbstractSeries *, Domain *)));
    QSignalSpy spy3(m_dataset, SIGNAL(seriesRemoved(QAbstractSeries *)));

    QVERIFY(m_dataset->domain(axis0)==m_dataset->domain(series0));
    QVERIFY(m_dataset->domain(axis1)==m_dataset->domain(series1));
    QVERIFY(m_dataset->domain(axis2)==m_dataset->domain(series2));
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
}

void tst_ChartDataSet::zoomInDomain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::zoomInDomain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);
    Q_UNUSED(axisCount);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    Domain* domain0 = m_dataset->domain(series0);
    Domain* domain1 = m_dataset->domain(series1);
    Domain* domain2 = m_dataset->domain(series2);

    QSignalSpy spy0(domain0, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(domain1, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy2(domain2, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));

    m_dataset->zoomInDomain(QRect(0,0,100,100),QSize(1000,1000));

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_ChartDataSet::zoomOutDomain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::zoomOutDomain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);

    Q_UNUSED(axisCount);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    Domain* domain0 = m_dataset->domain(series0);
    Domain* domain1 = m_dataset->domain(series1);
    Domain* domain2 = m_dataset->domain(series2);

    QSignalSpy spy0(domain0, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(domain1, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy2(domain2, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));

    m_dataset->zoomOutDomain(QRect(0,0,100,100),QSize(1000,1000));

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

void tst_ChartDataSet::scrollDomain_data()
{
    addSeries_data();
}

void tst_ChartDataSet::scrollDomain()
{
    QFETCH(QLineSeries*, series0);
    QFETCH(QAxis*, axis0);
    QFETCH(QLineSeries*, series1);
    QFETCH(QAxis*, axis1);
    QFETCH(QLineSeries*, series2);
    QFETCH(QAxis*, axis2);
    QFETCH(int, axisCount);

    Q_UNUSED(axisCount);

    m_dataset->addSeries(series0, axis0);
    m_dataset->addSeries(series1, axis1);
    m_dataset->addSeries(series2, axis2);

    Domain* domain0 = m_dataset->domain(series0);
    Domain* domain1 = m_dataset->domain(series1);
    Domain* domain2 = m_dataset->domain(series2);

    QSignalSpy spy0(domain0, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(domain1, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy2(domain2, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));

    m_dataset->scrollDomain(10,10,QSize(1000,1000));

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 1);
}

QTEST_MAIN(tst_ChartDataSet)
#include "tst_chartdataset.moc"

