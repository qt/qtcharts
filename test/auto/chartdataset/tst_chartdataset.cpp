#include <QtTest/QtTest>
#include <qchartaxis.h>
#include <qlineseries.h>
#include <private/chartdataset_p.h>
#include <private/domain_p.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(Domain*)
Q_DECLARE_METATYPE(QChartAxis*)
Q_DECLARE_METATYPE(QSeries*)
Q_DECLARE_METATYPE(QLineSeries*)

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

	void addSeries_data();
	void addSeries();
	void removeSeries_data();
	void removeSeries();
	void removeAllSeries_data();
	void removeAllSeries();
	void axisY_data();
	void axisY();

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
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QSeries*,Domain*)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QSeries*)));

    dataSet.addSeries(series0,axis0);
    dataSet.addSeries(series1,axis1);
    dataSet.addSeries(series2,axis2);

    QCOMPARE(spy0.count(), axisCount);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 3);
    QCOMPARE(spy3.count(), 0);

}

void tst_ChartDataSet::removeSeries_data()
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

    QTest::newRow("default axis Y: series0,series1,series2") << series0 << (QChartAxis*) 0
        << series1 << (QChartAxis*) 0 << series2 << (QChartAxis*) 0 << 2;
    QTest::newRow("default axis Y: series0, axis 0: series1,series2") << series0 << (QChartAxis*) 0
        << series1 << axis0 << series2 << axis0 << 3;
    QTest::newRow("axis0: series0, axis1: series1, axis2: series2") << series0 << axis0 << series1
        << axis1 << series2 << axis2 << 4;
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

    QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*,Domain*)));
    QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
    QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QSeries*,Domain*)));
    QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QSeries*)));

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

    QTest::newRow("default axis Y: series0,series1,series2") << series0 << (QChartAxis*) 0
        << series1 << (QChartAxis*) 0 << series2 << (QChartAxis*) 0 << 2;
    QTest::newRow("default axis Y: series0, axis 0: series1,series2") << series0 << (QChartAxis*) 0
        << series1 << axis0 << series2 << axis0 << 3;
    QTest::newRow("axis0: series0, axis1: series1, axis2: series2") << series0 << axis0 << series1
        << axis1 << series2 << axis2 << 4;
}

void tst_ChartDataSet::removeAllSeries()
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

      QSignalSpy spy0(&dataSet, SIGNAL(axisAdded(QChartAxis*,Domain*)));
      QSignalSpy spy1(&dataSet, SIGNAL(axisRemoved(QChartAxis*)));
      QSignalSpy spy2(&dataSet, SIGNAL(seriesAdded(QSeries*,Domain*)));
      QSignalSpy spy3(&dataSet, SIGNAL(seriesRemoved(QSeries*)));

      dataSet.removeAllSeries();

      QCOMPARE(spy0.count(), 0);
      QCOMPARE(spy1.count(), axisCount);
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

QTEST_MAIN(tst_ChartDataSet)
#include "tst_chartdataset.moc"

