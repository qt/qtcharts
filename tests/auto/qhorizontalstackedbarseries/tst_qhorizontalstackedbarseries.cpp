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
#include <qhorizontalstackedbarseries.h>
#include <qbarset.h>
#include <qchartview.h>
#include <qchart.h>
#include "tst_definitions.h"

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QBarSet*)

class tst_QHorizontalStackedBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qhorizontalstackedbarseries_data();
    void qhorizontalstackedbarseries();
    void type_data();
    void type();
    void mouseclicked_data();
    void mouseclicked();
    void mousehovered_data();
    void mousehovered();

private:
    QHorizontalStackedBarSeries* m_barseries;
};

void tst_QHorizontalStackedBarSeries::initTestCase()
{
    qRegisterMetaType<QBarSet*>("QBarSet*");
}

void tst_QHorizontalStackedBarSeries::cleanupTestCase()
{
}

void tst_QHorizontalStackedBarSeries::init()
{
    m_barseries = new QHorizontalStackedBarSeries();
}

void tst_QHorizontalStackedBarSeries::cleanup()
{
    delete m_barseries;
    m_barseries = 0;
}

void tst_QHorizontalStackedBarSeries::qhorizontalstackedbarseries_data()
{
}

void tst_QHorizontalStackedBarSeries::qhorizontalstackedbarseries()
{
    QHorizontalStackedBarSeries *barseries = new QHorizontalStackedBarSeries();
    QVERIFY(barseries != 0);
}

void tst_QHorizontalStackedBarSeries::type_data()
{

}

void tst_QHorizontalStackedBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeHorizontalStackedBar);
}

void tst_QHorizontalStackedBarSeries::mouseclicked_data()
{

}

void tst_QHorizontalStackedBarSeries::mouseclicked()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesSpy(series,SIGNAL(clicked(int,QBarSet*)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 3;   // 3 values per set
    qreal rangeX = 20;  // From 0 to 20 because bars are stacked (this should be height of highest stack)
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = -0.5;    // These come from internal domain used by barseries.
    qreal domainMinX = 0;       // No access to domain from outside, so use hard coded values.
    qreal rectHeight = scaleY * series->barWidth(); // On horizontal chart barWidth of the barseries means height of the rect.

    QVector<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal xMax = -scaleX * domainMinX + plotArea.left();
        qreal xMin = -scaleX * domainMinX + plotArea.left();
        for (int set = 0; set < setCount; set++) {
            qreal yPos = (domainMinY +0.5 -i) * scaleY + plotArea.bottom() - rectHeight/2;
            qreal rectWidth = barSets.at(set)->at(i) * scaleX;
            if (rectWidth > 0) {
                QRectF rect(xMax, yPos - rectHeight, rectWidth, rectHeight);
                layout.append(rect);
                xMax += rectWidth;
            } else {
                QRectF rect(xMin, yPos - rectHeight, rectWidth, rectHeight);
                layout.append(rect);
                xMin += rectWidth;
            }
        }
    }

//====================================================================================
// barset 1, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, layout.at(0).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 1, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, layout.at(2).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 1, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, layout.at(4).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);

//====================================================================================
// barset 2, bar 0
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, layout.at(1).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 0);

//====================================================================================
// barset 2, bar 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, layout.at(3).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 1);

//====================================================================================
// barset 2, bar 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, layout.at(5).center().toPoint());
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    QCOMPARE(seriesSpy.count(), 1);

    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Int);
    QVERIFY(seriesSpyArg.at(0).toInt() == 2);
}

void tst_QHorizontalStackedBarSeries::mousehovered_data()
{

}

void tst_QHorizontalStackedBarSeries::mousehovered()
{
    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();

    QBarSet* set1 = new QBarSet(QString("set 1"));
    *set1 << 10 << 10 << 10;
    series->append(set1);

    QBarSet* set2 = new QBarSet(QString("set 2"));
    *set2 << 10 << 10 << 10;
    series->append(set2);

    QList<QBarSet*> barSets = series->barSets();

    QSignalSpy seriesSpy(series,SIGNAL(hovered(bool,QBarSet*)));

    QChartView view(new QChart());
    view.resize(400,300);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    //this is hack since view does not get events otherwise
    view.setMouseTracking(true);

    // Calculate expected layout for bars
    QRectF plotArea = view.chart()->plotArea();
    qreal width = plotArea.width();
    qreal height = plotArea.height();
    qreal rangeY = 3;   // 3 values per set
    qreal rangeX = 20;  // From 0 to 20 because bars are stacked (this should be height of highest stack)
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);

    qreal setCount = series->count();
    qreal domainMinY = -0.5;    // These come from internal domain used by barseries.
    qreal domainMinX = 0;       // No access to domain from outside, so use hard coded values.
    qreal rectHeight = scaleY * series->barWidth(); // On horizontal chart barWidth of the barseries means height of the rect.

    QVector<QRectF> layout;

    // 3 = count of values in set
    // Note that rects in this vector will be interleaved (set1 bar0, set2 bar0, set1 bar1, set2 bar1, etc.)
    for (int i = 0; i < 3; i++) {
        qreal xMax = -scaleX * domainMinX + plotArea.left();
        qreal xMin = -scaleX * domainMinX + plotArea.left();
        for (int set = 0; set < setCount; set++) {
            qreal yPos = (domainMinY +0.5 -i) * scaleY + plotArea.bottom() - rectHeight/2;
            qreal rectWidth = barSets.at(set)->at(i) * scaleX;
            if (rectWidth > 0) {
                QRectF rect(xMax, yPos - rectHeight, rectWidth, rectHeight);
                layout.append(rect);
                xMax += rectWidth;
            } else {
                QRectF rect(xMin, yPos - rectHeight, rectWidth, rectHeight);
                layout.append(rect);
                xMin += rectWidth;
            }
        }
    }

//=======================================================================
// move mouse to left border
    QTest::mouseMove(view.viewport(), QPoint(0, layout.at(4).center().y()));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 10000);
    TRY_COMPARE(seriesSpy.count(), 0);

//=======================================================================
// move mouse on top of set1
    QTest::mouseMove(view.viewport(), layout.at(4).center().toPoint());
    TRY_COMPARE(seriesSpy.count(), 1);

    QList<QVariant> seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == true);

//=======================================================================
// move mouse from top of set1 to top of set2
    QTest::mouseMove(view.viewport(), layout.at(5).center().toPoint());
    TRY_COMPARE(seriesSpy.count(), 2);

    // should leave set1
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set1);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == false);

    // should enter set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == true);

//=======================================================================
// move mouse from top of set2 to background
    QTest::mouseMove(view.viewport(), QPoint(layout.at(5).center().y(), 0));
    TRY_COMPARE(seriesSpy.count(), 1);

    // should leave set2
    seriesSpyArg = seriesSpy.takeFirst();
    QCOMPARE(qvariant_cast<QBarSet*>(seriesSpyArg.at(1)), set2);
    QVERIFY(seriesSpyArg.at(0).type() == QVariant::Bool);
    QVERIFY(seriesSpyArg.at(0).toBool() == false);
}

QTEST_MAIN(tst_QHorizontalStackedBarSeries)

#include "tst_qhorizontalstackedbarseries.moc"

