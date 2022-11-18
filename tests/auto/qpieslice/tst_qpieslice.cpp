// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtTest/QtTest>
#include <tst_definitions.h>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>

QT_USE_NAMESPACE

class tst_qpieslice : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void construction();
    void changedSignals();
    void customize();
    void clickedSignal();
    void hoverSignal();
    void pressedSignal();
    void releasedSignal();
    void doubleClickedSignal();

private:
    QList<QPoint> slicePoints(QRectF rect);

private:

};

void tst_qpieslice::initTestCase()
{
}

void tst_qpieslice::cleanupTestCase()
{
    QTest::qWait(1); // Allow final deleteLaters to run
}

void tst_qpieslice::init()
{

}

void tst_qpieslice::cleanup()
{

}

void tst_qpieslice::construction()
{
    // no params
    QPieSlice slice1;
    QCOMPARE(slice1.value(), 0.0);
    QVERIFY(slice1.label().isEmpty());
    QVERIFY(!slice1.isLabelVisible());
    QVERIFY(!slice1.isExploded());
    QCOMPARE(slice1.pen(), QPen());
    QCOMPARE(slice1.brush(), QBrush());
    QCOMPARE(slice1.labelBrush(), QBrush());
    QCOMPARE(slice1.labelFont(), QFont());
    QCOMPARE(slice1.labelArmLengthFactor(), 0.15); // default value
    QCOMPARE(slice1.explodeDistanceFactor(), 0.15); // default value
    QCOMPARE(slice1.percentage(), 0.0);
    QCOMPARE(slice1.startAngle(), 0.0);
    QCOMPARE(slice1.angleSpan(), 0.0);

    // value and label params
    QPieSlice slice2("foobar", 1.0);
    QCOMPARE(slice2.value(), 1.0);
    QCOMPARE(slice2.label(), QString("foobar"));
    QVERIFY(!slice2.isLabelVisible());
    QVERIFY(!slice2.isExploded());
    QCOMPARE(slice2.pen(), QPen());
    QCOMPARE(slice2.brush(), QBrush());
    QCOMPARE(slice2.labelBrush(), QBrush());
    QCOMPARE(slice2.labelFont(), QFont());
    QCOMPARE(slice2.labelArmLengthFactor(), 0.15); // default value
    QCOMPARE(slice2.explodeDistanceFactor(), 0.15); // default value
    QCOMPARE(slice2.percentage(), 0.0);
    QCOMPARE(slice2.startAngle(), 0.0);
    QCOMPARE(slice2.angleSpan(), 0.0);
}

void tst_qpieslice::changedSignals()
{
    QPieSlice slice;

    QSignalSpy valueSpy(&slice, SIGNAL(valueChanged()));
    QSignalSpy labelSpy(&slice, SIGNAL(labelChanged()));
    QSignalSpy penSpy(&slice, SIGNAL(penChanged()));
    QSignalSpy brushSpy(&slice, SIGNAL(brushChanged()));
    QSignalSpy labelBrushSpy(&slice, SIGNAL(labelBrushChanged()));
    QSignalSpy labelFontSpy(&slice, SIGNAL(labelFontChanged()));
    QSignalSpy colorSpy(&slice, SIGNAL(colorChanged()));
    QSignalSpy borderColorSpy(&slice, SIGNAL(borderColorChanged()));
    QSignalSpy borderWidthSpy(&slice, SIGNAL(borderWidthChanged()));
    QSignalSpy labelColorSpy(&slice, SIGNAL(labelColorChanged()));

    // percentageChanged(), startAngleChanged() and angleSpanChanged() signals tested at tst_qpieseries::calculatedValues()

    // set everything twice to see we do not get unnecessary signals
    slice.setValue(1.0);
    slice.setValue(-1.0);
    QCOMPARE(slice.value(), 1.0);
    slice.setLabel("foobar");
    slice.setLabel("foobar");
    slice.setLabelVisible();
    slice.setLabelVisible();
    slice.setExploded();
    slice.setExploded();
    slice.setPen(QPen(Qt::red));
    slice.setPen(QPen(QBrush(Qt::red), 3));
    slice.setBrush(QBrush(Qt::red));
    slice.setBrush(QBrush(Qt::red));
    slice.setLabelBrush(QBrush(Qt::green));
    slice.setLabelBrush(QBrush(Qt::green));
    slice.setLabelFont(QFont("Tahoma"));
    slice.setLabelFont(QFont("Tahoma"));
    slice.setLabelPosition(QPieSlice::LabelInsideHorizontal);
    slice.setLabelPosition(QPieSlice::LabelInsideHorizontal);
    slice.setLabelArmLengthFactor(0.1);
    slice.setLabelArmLengthFactor(0.1);
    slice.setExplodeDistanceFactor(0.1);
    slice.setExplodeDistanceFactor(0.1);

    TRY_COMPARE(valueSpy.size(), 1);
    TRY_COMPARE(labelSpy.size(), 1);
    TRY_COMPARE(penSpy.size(), 2);
    TRY_COMPARE(brushSpy.size(), 1);
    TRY_COMPARE(labelBrushSpy.size(), 1);
    TRY_COMPARE(labelFontSpy.size(), 1);
    TRY_COMPARE(colorSpy.size(), 1);
    TRY_COMPARE(borderColorSpy.size(), 1);
    TRY_COMPARE(borderWidthSpy.size(), 1);
    TRY_COMPARE(labelColorSpy.size(), 1);
}

void tst_qpieslice::customize()
{
    // create a pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 2);
    series->append("slice 3", 3);

    // customize a slice
    QPen p1(Qt::red);
    s1->setPen(p1);
    QBrush b1(Qt::red);
    s1->setBrush(b1);
    s1->setLabelBrush(b1);
    QFont f1("Consolas");
    s1->setLabelFont(f1);

    // add series to the chart
    QChartView view(new QChart());
    view.resize(200, 200);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));
    //QTest::qWait(1000);

    // check that customizations persist
    QCOMPARE(s1->pen(), p1);
    QCOMPARE(s1->brush(), b1);
    QCOMPARE(s1->labelBrush(), b1);
    QCOMPARE(s1->labelFont(), f1);

    // remove a slice
    series->remove(s2);
    QCOMPARE(s1->pen(), p1);
    QCOMPARE(s1->brush(), b1);
    QCOMPARE(s1->labelBrush(), b1);
    QCOMPARE(s1->labelFont(), f1);

    // add a slice
    series->append("slice 4", 4);
    QCOMPARE(s1->pen(), p1);
    QCOMPARE(s1->brush(), b1);
    QCOMPARE(s1->labelBrush(), b1);
    QCOMPARE(s1->labelFont(), f1);

    // insert a slice
    series->insert(0, new QPieSlice("slice 0", 5));
    QCOMPARE(s1->pen(), p1);
    QCOMPARE(s1->brush(), b1);
    QCOMPARE(s1->labelBrush(), b1);
    QCOMPARE(s1->labelFont(), f1);

    // QTBUG-62082, verify correct insertion at 0.
    const QStringList expectedLabels{"slice 0", "slice 1", "slice 3", "slice 4"};
    const auto legendMarkers = view.chart()->legend()->markers();
    const int legendMarkersSize = legendMarkers.size();
    QCOMPARE(legendMarkersSize, expectedLabels.size());
    for (int m = 0; m < legendMarkersSize; ++m)
        QCOMPARE(legendMarkers.at(m)->label(), expectedLabels.at(m));

    // change theme
    // theme will overwrite customizations
    view.chart()->setTheme(QChart::ChartThemeHighContrast);
    QVERIFY(s1->pen() != p1);
    QVERIFY(s1->brush() != b1);
    QVERIFY(s1->labelBrush() != b1);
    QVERIFY(s1->labelFont() != f1);
}

void tst_qpieslice::clickedSignal()
{
    // NOTE:
    // This test is the same as tst_qpieseries::clickedSignal()
    // Just for different signals.

    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    // create a pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 1);
    QPieSlice *s3 = series->append("slice 3", 1);
    QPieSlice *s4 = series->append("slice 4", 1);
    QSignalSpy clickSpy1(s1, SIGNAL(clicked()));
    QSignalSpy clickSpy2(s2, SIGNAL(clicked()));
    QSignalSpy clickSpy3(s3, SIGNAL(clicked()));
    QSignalSpy clickSpy4(s4, SIGNAL(clicked()));

    // add series to the chart
    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // simulate clicks
    series->setPieSize(1.0);
    QRectF pieRect = view.chart()->plotArea();
    QList<QPoint> points = slicePoints(pieRect);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(0));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(1));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(2));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(3));
    QCOMPARE(clickSpy1.size(), 1);
    QCOMPARE(clickSpy2.size(), 1);
    QCOMPARE(clickSpy3.size(), 1);
    QCOMPARE(clickSpy4.size(), 1);
}

void tst_qpieslice::hoverSignal()
{
    // NOTE:
    // This test is the same as tst_qpieseries::hoverSignal()
    // Just for different signals.

    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();
    SKIP_IF_FLAKY_MOUSE_MOVE();

    // add some slices
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 1);
    QPieSlice *s3 = series->append("slice 3", 1);
    QPieSlice *s4 = series->append("slice 4", 1);

    // add series to the chart
    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // try to ensure focus
    view.activateWindow();
    QVERIFY(QTest::qWaitForWindowActive(&view));
    view.setFocus();
    QApplication::processEvents();
    QVERIFY(view.isActiveWindow());
    QVERIFY(view.hasFocus());

    // move inside the slices
    series->setPieSize(1.0);
    QRectF pieRect = view.chart()->plotArea();
    QList<QPoint> points = slicePoints(pieRect);
    QTest::mouseMove(view.viewport(), pieRect.topRight().toPoint(), 100);
    QSignalSpy hoverSpy1(s1, SIGNAL(hovered(bool)));
    QSignalSpy hoverSpy2(s2, SIGNAL(hovered(bool)));
    QSignalSpy hoverSpy3(s3, SIGNAL(hovered(bool)));
    QSignalSpy hoverSpy4(s4, SIGNAL(hovered(bool)));
    QTest::mouseMove(view.viewport(), points.at(0), 100);
    QTest::mouseMove(view.viewport(), points.at(1), 100);
    QTest::mouseMove(view.viewport(), points.at(2), 100);
    QTest::mouseMove(view.viewport(), points.at(3), 100);
    QTest::mouseMove(view.viewport(), pieRect.topLeft().toPoint(), 100);
    // Final hoverevent can take few milliseconds to appear in some environments, so wait a bit
    QTest::qWait(100);

    // check
    QCOMPARE(hoverSpy1.size(), 2);
    QCOMPARE(qvariant_cast<bool>(hoverSpy1.at(0).at(0)), true);
    QCOMPARE(qvariant_cast<bool>(hoverSpy1.at(1).at(0)), false);
    QCOMPARE(hoverSpy2.size(), 2);
    QCOMPARE(qvariant_cast<bool>(hoverSpy2.at(0).at(0)), true);
    QCOMPARE(qvariant_cast<bool>(hoverSpy2.at(1).at(0)), false);
    QCOMPARE(hoverSpy3.size(), 2);
    QCOMPARE(qvariant_cast<bool>(hoverSpy3.at(0).at(0)), true);
    QCOMPARE(qvariant_cast<bool>(hoverSpy3.at(1).at(0)), false);
    QCOMPARE(hoverSpy4.size(), 2);
    QCOMPARE(qvariant_cast<bool>(hoverSpy4.at(0).at(0)), true);
    QCOMPARE(qvariant_cast<bool>(hoverSpy4.at(1).at(0)), false);
}

QList<QPoint> tst_qpieslice::slicePoints(QRectF rect)
{
    qreal x1 = rect.topLeft().x() + (rect.width() / 4);
    qreal x2 = rect.topLeft().x() + (rect.width() / 4) * 3;
    qreal y1 = rect.topLeft().y() + (rect.height() / 4);
    qreal y2 = rect.topLeft().y() + (rect.height() / 4) * 3;
    QList<QPoint> points;
    points << QPoint(x2, y1);
    points << QPoint(x2, y2);
    points << QPoint(x1, y2);
    points << QPoint(x1, y1);
    return points;
}

void tst_qpieslice::pressedSignal()
{
    // NOTE:
    // This test is the same as tst_qpieseries::pressedSignal()
    // Just for different signals.

    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    // create a pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 1);
    QPieSlice *s3 = series->append("slice 3", 1);
    QPieSlice *s4 = series->append("slice 4", 1);
    QSignalSpy clickSpy1(s1, SIGNAL(pressed()));
    QSignalSpy clickSpy2(s2, SIGNAL(pressed()));
    QSignalSpy clickSpy3(s3, SIGNAL(pressed()));
    QSignalSpy clickSpy4(s4, SIGNAL(pressed()));

    // add series to the chart
    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // simulate clicks
    series->setPieSize(1.0);
    QRectF pieRect = view.chart()->plotArea();
    QList<QPoint> points = slicePoints(pieRect);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(0));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(1));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(2));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(3));
    QCOMPARE(clickSpy1.size(), 1);
    QCOMPARE(clickSpy2.size(), 1);
    QCOMPARE(clickSpy3.size(), 1);
    QCOMPARE(clickSpy4.size(), 1);
}

void tst_qpieslice::releasedSignal()
{
    // NOTE:
    // This test is the same as tst_qpieseries::releasedSignal()
    // Just for different signals.

    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    // create a pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 1);
    QPieSlice *s3 = series->append("slice 3", 1);
    QPieSlice *s4 = series->append("slice 4", 1);
    QSignalSpy clickSpy1(s1, SIGNAL(released()));
    QSignalSpy clickSpy2(s2, SIGNAL(released()));
    QSignalSpy clickSpy3(s3, SIGNAL(released()));
    QSignalSpy clickSpy4(s4, SIGNAL(released()));

    // add series to the chart
    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // simulate clicks
    series->setPieSize(1.0);
    QRectF pieRect = view.chart()->plotArea();
    QList<QPoint> points = slicePoints(pieRect);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(0));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(1));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(2));
    QTest::mouseClick(view.viewport(), Qt::LeftButton, {}, points.at(3));
    QCOMPARE(clickSpy1.size(), 1);
    QCOMPARE(clickSpy2.size(), 1);
    QCOMPARE(clickSpy3.size(), 1);
    QCOMPARE(clickSpy4.size(), 1);
}

void tst_qpieslice::doubleClickedSignal()
{
    // NOTE:
    // This test is the same as tst_qpieseries::doubleClickedSignal()
    // Just for different signals.

    SKIP_IF_CANNOT_TEST_MOUSE_EVENTS();

    // create a pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QSignalSpy clickSpy1(s1, SIGNAL(doubleClicked()));

    // add series to the chart
    QChartView view;
    view.resize(200, 200);
    view.chart()->legend()->setVisible(false);
    view.chart()->addSeries(series);
    view.show();
    QVERIFY(QTest::qWaitForWindowExposed(&view));

    // simulate clicks
    series->setPieSize(1.0);
    QRectF pieRect = view.chart()->plotArea();
    QList<QPoint> points = slicePoints(pieRect);
    QTest::mouseDClick(view.viewport(), Qt::LeftButton, {}, points.at(0));
    QCOMPARE(clickSpy1.size(), 1);
}

QTEST_MAIN(tst_qpieslice)

#include "tst_qpieslice.moc"

