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
#include <qlineseries.h>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE


Q_DECLARE_METATYPE(QChart*)
Q_DECLARE_METATYPE(QChartView::RubberBands)
Q_DECLARE_METATYPE(Qt::Key)

class tst_QChartView : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private Q_SLOTS:
    void qchartview_data();
    void qchartview();
    void chart_data();
    void chart();
    void rubberBand_data();
    void rubberBand();

private:
    QChartView* m_view;
};

void tst_QChartView::initTestCase()
{
    //test tracks mouse, give a while to user to relese it
    QTest::qWait(1000);
}

void tst_QChartView::cleanupTestCase()
{
}

void tst_QChartView::init()
{
    m_view = new QChartView(new QChart());
    m_view->chart()->legend()->setVisible(false);
}

void tst_QChartView::cleanup()
{
    delete m_view;
    m_view =0;
}

void tst_QChartView::qchartview_data()
{

}

void tst_QChartView::qchartview()
{
    QVERIFY(m_view->chart());
    QCOMPARE(m_view->rubberBand(), QChartView::NoRubberBand);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QChartView::chart_data()
{

    QTest::addColumn<QChart*>("chart");
    QTest::newRow("qchart") << new QChart();
}

void tst_QChartView::chart()
{
    QFETCH(QChart*, chart);
    QChartView* view = new QChartView(chart);
    QCOMPARE(view->chart(), chart);
    delete view;
}

void tst_QChartView::rubberBand_data()
{
    QTest::addColumn<QChartView::RubberBands>("rubberBand");
    QTest::addColumn<int>("Xcount");
    QTest::addColumn<int>("Ycount");

    QTest::addColumn<int>("minX");
    QTest::addColumn<int>("maxX");
    QTest::addColumn<int>("minY");
    QTest::addColumn<int>("maxY");

    QTest::newRow("HorizonalRubberBand") << QChartView::RubberBands(QChartView::HorizonalRubberBand) << 0 << 1 << 20 << 180 << 0<< 200;
    QTest::newRow("VerticalRubberBand") <<  QChartView::RubberBands(QChartView::VerticalRubberBand) << 1 << 0 << 0 << 200 << 20<< 180;
    QTest::newRow("RectangleRubberBand") <<  QChartView::RubberBands(QChartView::RectangleRubberBand) << 1 << 1 <<20 << 180 << 20<< 180;
}

void tst_QChartView::rubberBand()
{
    QFETCH(QChartView::RubberBands, rubberBand);
    QFETCH(int, Xcount);
    QFETCH(int, Ycount);
    QFETCH(int, minX);
    QFETCH(int, maxX);
    QFETCH(int, minY);
    QFETCH(int, maxY);

    m_view->setRubberBand(rubberBand);
    QRectF padding = m_view->chart()->margins();
    QCOMPARE(m_view->rubberBand(), rubberBand);

    QLineSeries* line = new QLineSeries();
    *line << QPointF(0, 0) << QPointF(200, 200);

    m_view->chart()->addSeries(line);
    m_view->resize(200 + padding.left() + padding.right(), 200 +  padding.top()+ padding.bottom());
    m_view->show();

    //this is hack since view does not get events otherwise
    m_view->setMouseTracking(true);

    QAxis* axisY = m_view->chart()->axisY();
    QSignalSpy spy0(axisY, SIGNAL(rangeChanged(qreal,qreal)));
    QAxis* axisX = m_view->chart()->axisX();
    QSignalSpy spy1(axisX, SIGNAL(rangeChanged(qreal,qreal)));

    QTest::qWaitForWindowShown(m_view);
    QTest::mouseMove(m_view->viewport(),  QPoint(minX, minY) + padding.topLeft().toPoint());
    QTest::mousePress(m_view->viewport(), Qt::LeftButton, 0,  QPoint(minX, minY) + padding.topLeft().toPoint());
    QTest::mouseMove(m_view->viewport(), QPoint(maxX, maxY) + padding.topLeft().toPoint());
    QTest::mouseRelease(m_view->viewport(), Qt::LeftButton, 0, QPoint(maxX, maxY)+ padding.topLeft().toPoint());

    QCOMPARE(spy0.count(), Xcount);
    QCOMPARE(spy1.count(), Ycount);

    //this is hack since view does not get events otherwise
    m_view->setMouseTracking(false);

    QVERIFY(axisX->min() - minX < 1);
    QVERIFY(axisX->max() - maxX < 1);
    QVERIFY(axisY->min() - minY < 1);
    QVERIFY(axisY->max() - maxY < 1);
}

QTEST_MAIN(tst_QChartView)
#include "tst_qchartview.moc"

