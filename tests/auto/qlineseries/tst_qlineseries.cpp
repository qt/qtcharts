// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "../qxyseries/tst_qxyseries.h"
#include <QtCharts/QLineSeries>

Q_DECLARE_METATYPE(QList<QPointF>)

class tst_QLineSeries : public tst_QXYSeries
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
    void pressedSignal();
    void releasedSignal();
    void doubleClickedSignal();
    void insert();
protected:
    void pointsVisible_data();
};

void tst_QLineSeries::initTestCase()
{
}

void tst_QLineSeries::cleanupTestCase()
{
    QTest::qWait(1); // Allow final deleteLaters to run
}

void tst_QLineSeries::init()
{
    tst_QXYSeries::init();
    m_series = new QLineSeries();
}

void tst_QLineSeries::cleanup()
{
    delete m_series;
    m_series=0;
    tst_QXYSeries::cleanup();
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
    QCOMPARE(series.pointLabelsVisible(), false);
    QCOMPARE(series.pointLabelsFormat(), QLatin1String("@xPoint, @yPoint"));
    QCOMPARE(series.pointLabelsClipping(), true);

    series.append(QList<QPointF>());
    series.append(0.0,0.0);
    series.append(QPointF());

    series.remove(0.0,0.0);
    series.remove(QPointF());
    series.clear();

    series.replace(QPointF(),QPointF());
    series.replace(0,0,0,0);
    series.setBrush(QBrush());

    series.setPen(QPen());
    series.setPointsVisible(false);

    series.setPointLabelsVisible(false);
    series.setPointLabelsFormat(QString());

    m_chart->addSeries(&series);
    m_view->show();
    QVERIFY(QTest::qWaitForWindowExposed(m_view));
}

void tst_QLineSeries::pressedSignal()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QPointF linePoint(4, 12);
    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->append(QPointF(2, 1));
    lineSeries->append(linePoint);
    lineSeries->append(QPointF(6, 12));

    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(lineSeries);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    QSignalSpy seriesSpy(lineSeries, SIGNAL(pressed(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(linePoint);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(linePoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(linePoint.y()));
}

void tst_QLineSeries::releasedSignal()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QPointF linePoint(4, 12);
    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->append(QPointF(2, 20));
    lineSeries->append(linePoint);
    lineSeries->append(QPointF(6, 12));

    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(lineSeries);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    QSignalSpy seriesSpy(lineSeries, SIGNAL(released(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(linePoint);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(linePoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(linePoint.y()));
}

void tst_QLineSeries::insert()
{
    QLineSeries lineSeries;
    QSignalSpy insertSpy(&lineSeries, &QXYSeries::pointAdded);
    lineSeries.insert(0, QPoint(3, 3));
    QCOMPARE(insertSpy.size(), 1);
    QVariantList arguments = insertSpy.takeFirst();
    QCOMPARE(arguments.first().toInt(), 0);
    lineSeries.insert(0, QPoint(1, 1));
    arguments = insertSpy.takeFirst();
    QCOMPARE(arguments.first().toInt(), 0);
    lineSeries.insert(1, QPoint(2, 2));
    arguments = insertSpy.takeFirst();
    QCOMPARE(arguments.first().toInt(), 1);
    lineSeries.insert(42, QPoint(0, 0));
    arguments = insertSpy.takeFirst();
    QCOMPARE(arguments.first().toInt(), 3);
    lineSeries.insert(-42, QPoint(0, 0));
    arguments = insertSpy.takeFirst();
    QCOMPARE(arguments.first().toInt(), 0);
}

void tst_QLineSeries::doubleClickedSignal()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QPointF linePoint(4, 12);
    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->append(QPointF(2, 20));
    lineSeries->append(linePoint);
    lineSeries->append(QPointF(6, 12));

    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(lineSeries);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    QSignalSpy seriesSpy(lineSeries, SIGNAL(doubleClicked(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(linePoint);
    // mouseClick needed first to save the position
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QTest::mouseDClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(linePoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(linePoint.y()));
}

QTEST_MAIN(tst_QLineSeries)

#include "tst_qlineseries.moc"

