#include <QtTest/QtTest>
#include <qchartaxis.h>
#include <qchartseries.h>
#include <qlinechartseries.h>
#include <private/chartdataset_p.h>
#include <private/domain_p.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(Domain)
Q_DECLARE_METATYPE(QChartAxis*)
Q_DECLARE_METATYPE(QChartSeries*)
Q_DECLARE_METATYPE(QLineChartSeries*)

class tst_ChartDataSet: public QObject {
Q_OBJECT

public slots:
	void initTestCase();
	void cleanupTestCase();
	void init();
	void cleanup();

private slots:
	void chartdataset_data();
	void chartdataset();

	void addDomain_data();
	void addDomain();
	void addSeries_data();
	void addSeries();
	void axisY_data();
	void axisY();
	void clearDomains_data();
	void clearDomains();
	void domain_data();
	void domain();
	void nextpreviousDomain_data();
	void nextpreviousDomain();
	void removeSeries_data();
	void removeSeries();
	void removeAllSeries_data();
	void removeAllSeries();
};

void tst_ChartDataSet::initTestCase()
{
	qRegisterMetaType<Domain>("Domain");
	qRegisterMetaType<QChartAxis*>();
	qRegisterMetaType<QChartSeries*>();
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
	QVERIFY(dataSet.domain(dataSet.axisX())==Domain());
	QVERIFY(dataSet.domain(dataSet.axisY())==Domain());
	QCOMPARE(dataSet.domainIndex(), 0);
}

void tst_ChartDataSet::addDomain_data()
{
	QTest::addColumn<QRectF>("rect");
	QTest::addColumn<QRectF>("viewport");
	QTest::newRow("400x400,1000x1000") << QRectF(200, 200, 600, 600)
			<< QRectF(0, 0, 1000, 1000);
	QTest::newRow("600x600,1000x1000") << QRectF(100, 100, 700, 700)
			<< QRectF(0, 0, 1000, 1000);
	QTest::newRow("200x200,1000x1000") << QRectF(400, 400, 600, 600)
			<< QRectF(0, 0, 1000, 1000);
}

void tst_ChartDataSet::addDomain()
{
	QFETCH(QRectF, rect);
	QFETCH(QRectF, viewport);

	ChartDataSet dataSet;

	Domain domain1(0, 1000, 0, 1000);
	QLineChartSeries series;
	series.add(0, 0);
	series.add(1000, 1000);

	dataSet.addSeries(&series);

	QCOMPARE(dataSet.domainIndex(), 0);

	QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
	QSignalSpy spy1(&dataSet,
			SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
	QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
	QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
	QSignalSpy spy4(&dataSet,
			SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
	QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

	Domain domain2 = dataSet.domain(dataSet.axisY());
	QVERIFY(domain1 == domain2);

	dataSet.addDomain(rect, viewport);
	QCOMPARE(dataSet.domainIndex(), 1);
	Domain domain3 = dataSet.domain(dataSet.axisY());
	Domain domain4 = domain1.subDomain(rect, viewport.width(),
			viewport.height());
	QVERIFY(domain3 == domain4);

	QCOMPARE(spy0.count(), 0);
	QCOMPARE(spy1.count(), 2);
	QCOMPARE(spy2.count(), 0);
	QCOMPARE(spy3.count(), 0);
	QCOMPARE(spy4.count(), 1);
	QCOMPARE(spy5.count(), 0);
}

void tst_ChartDataSet::addSeries_data()
{
	QTest::addColumn<int>("seriesCount");
	QTest::addColumn<int>("axisYCount");
	QTest::newRow("2 series, default axis") << 2 << 0;
	QTest::newRow("2 series, 2 new axis") << 2 << 2;
	QTest::newRow("2 series, 1 new axis") << 2 << 2;
	QTest::newRow("3 series, 3 new axis") << 3 << 3;
	QTest::newRow("3 series, 2 new axis") << 3 << 2;
	QTest::newRow("3 series, 1 new axis") << 3 << 1;
}

void tst_ChartDataSet::addSeries()
{
	QFETCH(int, seriesCount);
	QFETCH(int, axisYCount);

	ChartDataSet dataSet;

	QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
	QSignalSpy spy1(&dataSet,
			SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
	QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
	QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
	QSignalSpy spy4(&dataSet,
			SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
	QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

	QList<QChartAxis*> axisList;

	for (int i = 0; i < axisYCount; i++) {
		QChartAxis* axis = new QChartAxis();
		axisList << axis;
	}

	QList<QChartAxis*>::iterator iterator = axisList.begin();

	for (int i = 0; i < seriesCount; i++) {
		QChartAxis* axisY = 0;
		QLineChartSeries* series = new QLineChartSeries();
		if (iterator != axisList.end()) {
			axisY = *iterator;
			iterator++;
		} else if (axisList.count() > 0) {
			iterator--;
			axisY = *iterator;
			iterator++;
		}
		dataSet.addSeries(series, axisY);
	}

	//default axis
	if (axisYCount == 0)
		axisYCount+=2;
	else
	    axisYCount++;

	QCOMPARE(spy0.count(), axisYCount);
	QCOMPARE(spy1.count(), seriesCount*2);
	QCOMPARE(spy2.count(), 0);
	QCOMPARE(spy3.count(), seriesCount);
	QCOMPARE(spy4.count(), seriesCount);
	QCOMPARE(spy5.count(), 0);

	QCOMPARE(dataSet.domainIndex(), 0);
}

void tst_ChartDataSet::axisY_data()
{
	QTest::addColumn<QChartAxis*>("axisY");
	QTest::newRow("axisY1") << new QChartAxis();
	QTest::newRow("axisY2") << new QChartAxis();
}

void tst_ChartDataSet::axisY()
{
	QFETCH(QChartAxis*, axisY);

	ChartDataSet dataSet;

	QChartAxis* defaultAxisY = dataSet.axisY();

	QVERIFY2(defaultAxisY, "Missing axisY.");

	QLineChartSeries* series1 = new QLineChartSeries();
	dataSet.addSeries(series1);

	QLineChartSeries* series2 = new QLineChartSeries();
	dataSet.addSeries(series2, axisY);

	QVERIFY(dataSet.axisY(series1) == defaultAxisY);
	QVERIFY(dataSet.axisY(series2) == axisY);


}

void tst_ChartDataSet::clearDomains_data()
{
	QTest::addColumn<int>("indexCount");
	QTest::newRow("0") << 0;
	QTest::newRow("1") << 1;
	QTest::newRow("5") << 2;
	QTest::newRow("8") << 3;
}

void tst_ChartDataSet::clearDomains()
{
	QFETCH(int, indexCount);

	Domain domain1(0, 100, 0, 100);
	QLineChartSeries* series = new QLineChartSeries();
	series->add(0, 0);
	series->add(100, 100);

	ChartDataSet dataSet;

	QCOMPARE(dataSet.domainIndex(), 0);

	dataSet.addSeries(series);

	Domain domain2 = dataSet.domain(dataSet.axisY());

	QVERIFY(domain2 == domain1);

	QList<Domain> domains;

	domains << domain1;

	for (int i = 0; i < indexCount; i++) {
		dataSet.addDomain(QRect(0, 0, 10, 10), QRect(0, 0, 100, 100));
		domains << dataSet.domain(dataSet.axisY());
	}

	QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
	QSignalSpy spy1(&dataSet,
			SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
	QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
	QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
	QSignalSpy spy4(&dataSet,
			SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
	QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

	dataSet.clearDomains(indexCount);

	QCOMPARE(dataSet.domainIndex(), indexCount);

	domain2 = dataSet.domain(dataSet.axisY());

	QVERIFY(domain2 == domains.at(indexCount));

	QCOMPARE(spy0.count(), 0);
	QCOMPARE(spy1.count(), 0);
	QCOMPARE(spy2.count(), 0);
	QCOMPARE(spy3.count(), 0);
	QCOMPARE(spy4.count(), 0);
	QCOMPARE(spy5.count(), 0);
}

void tst_ChartDataSet::domain_data()
{
	QTest::addColumn<Domain>("domain1");
	QTest::addColumn<Domain>("domain2");
	QTest::addColumn<Domain>("domain3");
	QTest::addColumn<Domain>("domain");
	QTest::newRow("Domain(0,10,0,10)") << Domain(0, 10, 0, 10)
			<< Domain(0, 5, 0, 5) << Domain(0, 3, 0, 3) << Domain(0, 10, 0, 10);
	QTest::newRow("Domain(-1,11,0,11)") << Domain(-1, 10, 0, 10)
			<< Domain(0, 11, 0, 11) << Domain(0, 3, 0, 3)
			<< Domain(-1, 11, 0, 11);
	QTest::newRow("Domain(-5,5,1,8)") << Domain(-5, 0, 1, 1)
			<< Domain(0, 5, 0, 8) << Domain(1, 2, 1, 2) << Domain(-5, 5, 0, 8);
}

void tst_ChartDataSet::domain()
{
	QFETCH(Domain, domain1);
	QFETCH(Domain, domain2);
	QFETCH(Domain, domain3);
	QFETCH(Domain, domain);

	ChartDataSet dataSet;
	QLineChartSeries* series1 = new QLineChartSeries();
	series1->add(domain1.m_minX, domain1.m_minY);
	series1->add(domain1.m_maxX, domain1.m_maxY);
	QLineChartSeries* series2 = new QLineChartSeries();
	series2->add(domain2.m_minX, domain2.m_minY);
	series2->add(domain2.m_maxX, domain2.m_maxY);
	QLineChartSeries* series3 = new QLineChartSeries();
	series3->add(domain3.m_minX, domain3.m_minY);
	series3->add(domain3.m_maxX, domain3.m_maxY);

	QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
	QSignalSpy spy1(&dataSet,
			SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
	QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
	QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
	QSignalSpy spy4(&dataSet,
			SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
	QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

	dataSet.addSeries(series1);
	dataSet.addSeries(series2);
	dataSet.addSeries(series3);

	QCOMPARE(dataSet.domainIndex(), 0);
	QVERIFY2(dataSet.domain(dataSet.axisY()) == domain, "Domain not equal");

	QCOMPARE(spy0.count(), 2);
	QCOMPARE(spy1.count(), 6);
	QCOMPARE(spy2.count(), 0);
	QCOMPARE(spy3.count(), 3);
	QCOMPARE(spy4.count(), 3);
	QCOMPARE(spy5.count(), 0);
}

void tst_ChartDataSet::nextpreviousDomain_data()
{
	QTest::addColumn<QRectF>("rect");
	QTest::addColumn<QRectF>("viewport");
	QTest::newRow("400x400,1000x1000") << QRectF(200, 200, 600, 600)
			<< QRectF(0, 0, 1000, 1000);
	QTest::newRow("600x600,1000x1000") << QRectF(100, 100, 700, 700)
			<< QRectF(0, 0, 1000, 1000);
	QTest::newRow("200x200,1000x1000") << QRectF(400, 400, 600, 600)
			<< QRectF(0, 0, 1000, 1000);
}

void tst_ChartDataSet::nextpreviousDomain()
{

	QFETCH(QRectF, rect);
	QFETCH(QRectF, viewport);

	ChartDataSet dataSet;

	Domain domain1(0, 1000, 0, 1000);
	QLineChartSeries* series = new QLineChartSeries();
	series->add(0, 0);
	series->add(1000, 1000);

	dataSet.addSeries(series);

	QCOMPARE(dataSet.domainIndex(), 0);

	Domain domain2 = dataSet.domain(dataSet.axisY());
	QVERIFY(domain1 == domain2);

	dataSet.addDomain(rect, viewport);
	QCOMPARE(dataSet.domainIndex(), 1);
	Domain domain3 = dataSet.domain(dataSet.axisY());
	Domain domain4 = domain1.subDomain(rect, viewport.width(),
			viewport.height());
	QVERIFY(domain3 == domain4);

	dataSet.addDomain(rect, viewport);
	QCOMPARE(dataSet.domainIndex(), 2);
	Domain domain5 = dataSet.domain(dataSet.axisY());
	Domain domain6 = domain3.subDomain(rect, viewport.width(),
			viewport.height());
	QVERIFY(domain5 == domain6);

	dataSet.addDomain(rect, viewport);
	QCOMPARE(dataSet.domainIndex(), 3);
	Domain domain7 = dataSet.domain(dataSet.axisY());
	Domain domain8 = domain5.subDomain(rect, viewport.width(),
			viewport.height());
	QVERIFY(domain7 == domain8);

	QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
	QSignalSpy spy1(&dataSet,
			SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
	QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
	QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
	QSignalSpy spy4(&dataSet,
			SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
	QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

	Domain domain;

	bool previous = dataSet.previousDomain();
	QCOMPARE(previous, true);
	QCOMPARE(dataSet.domainIndex(), 2);
	domain = dataSet.domain(dataSet.axisY());
	QVERIFY(domain == domain5);
	previous = dataSet.previousDomain();
	QCOMPARE(previous, true);
	QCOMPARE(dataSet.domainIndex(), 1);
	domain = dataSet.domain(dataSet.axisY());
	QVERIFY(domain == domain3);
	previous = dataSet.previousDomain();
	QCOMPARE(previous, true);
	QCOMPARE(dataSet.domainIndex(), 0);
	domain = dataSet.domain(dataSet.axisY());
	QVERIFY(domain == domain1);
	previous = dataSet.previousDomain();
	QCOMPARE(previous, false);
	QCOMPARE(dataSet.domainIndex(), 0);
	domain = dataSet.domain(dataSet.axisY());
	QVERIFY(domain == domain1);

	bool next = dataSet.nextDomain();
	QCOMPARE(next, true);
	QCOMPARE(dataSet.domainIndex(),1);
	next = dataSet.nextDomain();
	QCOMPARE(next, true);
	QCOMPARE(dataSet.domainIndex(),2);
	next = dataSet.nextDomain();
	QCOMPARE(next, true);
	QCOMPARE(dataSet.domainIndex(),3);
	next = dataSet.nextDomain();
	QCOMPARE(next, false);
	QCOMPARE(dataSet.domainIndex(),3);


	QCOMPARE(spy0.count(), 0);
	QCOMPARE(spy1.count(), 12);
	QCOMPARE(spy2.count(), 0);
	QCOMPARE(spy3.count(), 0);
	QCOMPARE(spy4.count(), 6);
	QCOMPARE(spy5.count(), 0);
}

void tst_ChartDataSet::removeSeries_data()
{
	QTest::addColumn<int>("seriesCount");
	QTest::addColumn<int>("axisYCount");
	QTest::newRow("2 series, default axis") << 2 << 0;
	QTest::newRow("2 series, 2 new axis") << 2 << 2;
	QTest::newRow("2 series, 1 new axis") << 2 << 2;
	QTest::newRow("3 series, 3 new axis") << 3 << 3;
	QTest::newRow("3 series, 2 new axis") << 3 << 2;
	QTest::newRow("3 series, 1 new axis") << 3 << 1;
}

void tst_ChartDataSet::removeSeries()
{
	QFETCH(int, seriesCount);
	QFETCH(int, axisYCount);

	ChartDataSet dataSet;

	QList<QChartAxis*> axisList;
	QList<QChartSeries*> seriesList;

	for (int i = 0; i < axisYCount; i++) {
		QChartAxis* axis = new QChartAxis();
		axisList << axis;
	}

	QList<QChartAxis*>::iterator iterator = axisList.begin();

	for (int i = 0; i < seriesCount; i++) {
		QChartAxis* axisY = 0;
		QLineChartSeries* series = new QLineChartSeries();
		if (iterator != axisList.end()) {
			axisY = *iterator;
			iterator++;
		} else if (axisList.count() > 0) {
			iterator--;
			axisY = *iterator;
			iterator++;
		}
		dataSet.addSeries(series, axisY);
		seriesList << series;
	}

	QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
	QSignalSpy spy1(&dataSet,
			SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
	QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
	QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
	QSignalSpy spy4(&dataSet,
			SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
	QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

	for (int i = 0; i < seriesCount; i++) {
		dataSet.removeSeries(seriesList.at(i));
	}

    //default axis
    if (axisYCount == 0)
        axisYCount++;

	QCOMPARE(spy0.count(), 0);
	QCOMPARE(spy1.count(), 0);
	QCOMPARE(spy2.count(), axisYCount);
	QCOMPARE(spy3.count(), 0);
	QCOMPARE(spy4.count(), 0);
	QCOMPARE(spy5.count(), seriesCount);

	QCOMPARE(dataSet.domainIndex(), 0);

	qDeleteAll(seriesList);
}

void tst_ChartDataSet::removeAllSeries_data()
{
    QTest::addColumn<int>("seriesCount");
    QTest::addColumn<int>("axisYCount");
    QTest::newRow("2 series, default axis") << 2 << 0;
    QTest::newRow("2 series, 2 new axis") << 2 << 2;
    QTest::newRow("2 series, 1 new axis") << 2 << 2;
    QTest::newRow("3 series, 3 new axis") << 3 << 3;
    QTest::newRow("3 series, 2 new axis") << 3 << 2;
    QTest::newRow("3 series, 1 new axis") << 3 << 1;
}

void tst_ChartDataSet::removeAllSeries()
{
    QFETCH(int, seriesCount);
    QFETCH(int, axisYCount);

    ChartDataSet dataSet;

    QList<QChartAxis*> axisList;

    for (int i = 0; i < axisYCount; i++) {
        QChartAxis* axis = new QChartAxis();
        axisList << axis;
    }

    QList<QChartAxis*>::iterator iterator = axisList.begin();

    for (int i = 0; i < seriesCount; i++) {
        QChartAxis* axisY = 0;
        QLineChartSeries* series = new QLineChartSeries();
        if (iterator != axisList.end()) {
            axisY = *iterator;
            iterator++;
        } else if (axisList.count() > 0) {
            iterator--;
            axisY = *iterator;
            iterator++;
        }
        dataSet.addSeries(series, axisY);
    }

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisLabelsChanged(QChartAxis*, QStringList const&)));
    QSignalSpy spy2(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesAdded(QChartSeries*)));
    QSignalSpy spy4(&dataSet, SIGNAL(seriesDomainChanged(QChartSeries*, Domain const&)));
    QSignalSpy spy5(&dataSet, SIGNAL(seriesRemoved(QChartSeries*)));

    dataSet.removeAllSeries();
    //default axis
    if (axisYCount == 0)
        axisYCount++;

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), axisYCount);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), seriesCount);

    QCOMPARE(dataSet.domainIndex(), 0);
}


QTEST_MAIN(tst_ChartDataSet)
#include "tst_chartdataset.moc"

