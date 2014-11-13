/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

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
    QTest::qWaitForWindowShown(m_view);
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
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(lineSeries);
    view.show();
    QTest::qWaitForWindowShown(&view);

    QSignalSpy seriesSpy(lineSeries, SIGNAL(pressed(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(linePoint);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);
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
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(lineSeries);
    view.show();
    QTest::qWaitForWindowShown(&view);

    QSignalSpy seriesSpy(lineSeries, SIGNAL(released(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(linePoint);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(linePoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(linePoint.y()));
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
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(lineSeries);
    view.show();
    QTest::qWaitForWindowShown(&view);

    QSignalSpy seriesSpy(lineSeries, SIGNAL(doubleClicked(QPointF)));

    QPointF checkPoint = view.chart()->mapToPosition(linePoint);
    // mouseClick needed first to save the position
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, checkPoint.toPoint());
    QTest::mouseDClick(view.viewport(), Qt::LeftButton, 0, checkPoint.toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);
    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    // checkPoint is QPointF and for the mouseClick it it's changed to QPoint
    // this causes small distinction in decimals so we round it before comparing
    QPointF signalPoint = qvariant_cast<QPointF>(seriesSpyArg.at(0));
    QCOMPARE(qRound(signalPoint.x()), qRound(linePoint.x()));
    QCOMPARE(qRound(signalPoint.y()), qRound(linePoint.y()));
}

QTEST_MAIN(tst_QLineSeries)

#include "tst_qlineseries.moc"

