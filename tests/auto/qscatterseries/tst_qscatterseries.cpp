// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "../qxyseries/tst_qxyseries.h"
#include <QtCharts/QScatterSeries>

Q_DECLARE_METATYPE(QList<QPointF>)

class tst_QScatterSeries : public tst_QXYSeries
{
    Q_OBJECT

public slots:
    void initTestCase() override;
    void cleanupTestCase() override;
    void init() override;
    void cleanup() override;
private slots:
    void qscatterseries_data();
    void qscatterseries();
    void scatterChangedSignals();
    void pressedSignal();
    void releasedSignal();
    void doubleClickedSignal();

protected:
    void pointsVisible_data();
};

void tst_QScatterSeries::initTestCase()
{
}

void tst_QScatterSeries::cleanupTestCase()
{
    QTest::qWait(1); // Allow final deleteLaters to run
}

void tst_QScatterSeries::init()
{
    tst_QXYSeries::init();
    m_series = new QScatterSeries();
}

void tst_QScatterSeries::cleanup()
{
    delete m_series;
    tst_QXYSeries::cleanup();
}

void tst_QScatterSeries::qscatterseries_data()
{

}

void tst_QScatterSeries::qscatterseries()
{
    QScatterSeries series;

    QCOMPARE(series.count(),0);
    QCOMPARE(series.brush(), QBrush());
    QCOMPARE(series.points(), QList<QPointF>());
    QCOMPARE(series.pen(), QPen());
    QCOMPARE(series.pointsVisible(), true);

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
    series.setPointsVisible(true);

    m_chart->addSeries(&series);
    m_view->show();
    QVERIFY(QTest::qWaitForWindowExposed(m_view));
}

void tst_QScatterSeries::scatterChangedSignals()
{
    QScatterSeries *series = qobject_cast<QScatterSeries *>(m_series);
    QVERIFY(series);

    QSignalSpy colorSpy(series, SIGNAL(colorChanged(QColor)));
    QSignalSpy borderColorSpy(series, SIGNAL(borderColorChanged(QColor)));

    // Color
    series->setColor(QColor("blueviolet"));
    TRY_COMPARE(colorSpy.size(), 1);

    // Border color
    series->setBorderColor(QColor("burlywood"));
    TRY_COMPARE(borderColorSpy.size(), 1);

    // Pen
    QPen p = series->pen();
    p.setColor("lightpink");
    series->setPen(p);
    TRY_COMPARE(borderColorSpy.size(), 2);

    // Brush
    QBrush b = series->brush();
    b.setColor("lime");
    series->setBrush(b);
    TRY_COMPARE(colorSpy.size(), 2);
}

void tst_QScatterSeries::pressedSignal()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QPointF scatterPoint(4, 12);
    QScatterSeries *scatterSeries = new QScatterSeries();
    scatterSeries->append(QPointF(2, 1));
    scatterSeries->append(scatterPoint);
    scatterSeries->append(QPointF(6, 12));

    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(scatterSeries);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    QSignalSpy seriesSpy(scatterSeries, SIGNAL(pressed(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(scatterPoint);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(scatterPoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(scatterPoint.y()));
}

void tst_QScatterSeries::releasedSignal()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QPointF scatterPoint(4, 12);
    QScatterSeries *scatterSeries = new QScatterSeries();
    scatterSeries->append(QPointF(2, 1));
    scatterSeries->append(scatterPoint);
    scatterSeries->append(QPointF(6, 12));

    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(scatterSeries);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    QSignalSpy seriesSpy(scatterSeries, SIGNAL(released(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(scatterPoint);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(scatterPoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(scatterPoint.y()));
}

void tst_QScatterSeries::doubleClickedSignal()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QPointF scatterPoint(4, 12);
    QScatterSeries *scatterSeries = new QScatterSeries();
    scatterSeries->append(QPointF(2, 1));
    scatterSeries->append(scatterPoint);
    scatterSeries->append(QPointF(6, 12));

    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(scatterSeries);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    QSignalSpy seriesSpy(scatterSeries, SIGNAL(doubleClicked(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(scatterPoint);
    QTest::mouseDClick(view.viewport(), Qt::LeftButton, {}, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.size(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(scatterPoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(scatterPoint.y()));
}

QTEST_MAIN(tst_QScatterSeries)

#include "tst_qscatterseries.moc"

