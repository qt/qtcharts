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
#include <tst_definitions.h>
#include <qchartview.h>
#include <qchart.h>
#include <qpieslice.h>
#include <qpieseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

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
    void mouseClick();
    void mouseHover();

private:


private:

};

void tst_qpieslice::initTestCase()
{
}

void tst_qpieslice::cleanupTestCase()
{
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
    QSignalSpy explodedSpy(&slice, SIGNAL(explodedChanged()));
    QSignalSpy penSpy(&slice, SIGNAL(penChanged()));
    QSignalSpy brushSpy(&slice, SIGNAL(brushChanged()));
    QSignalSpy labelBrushSpy(&slice, SIGNAL(labelBrushChanged()));
    QSignalSpy labelFontSpy(&slice, SIGNAL(labelFontChanged()));
    QSignalSpy labelPositionSpy(&slice, SIGNAL(labelPositionChanged()));
    QSignalSpy labelArmLengthFactorSpy(&slice, SIGNAL(labelArmLengthFactorChanged()));
    QSignalSpy explodeDistanceFactorSpy(&slice, SIGNAL(explodeDistanceFactorChanged()));
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
    slice.setLabelPosition(QPieSlice::LabelInside);
    slice.setLabelPosition(QPieSlice::LabelInside);
    slice.setLabelArmLengthFactor(0.1);
    slice.setLabelArmLengthFactor(0.1);
    slice.setExplodeDistanceFactor(0.1);
    slice.setExplodeDistanceFactor(0.1);

    TRY_COMPARE(valueSpy.count(), 1);
    TRY_COMPARE(labelSpy.count(), 1);
    TRY_COMPARE(explodedSpy.count(), 1);
    TRY_COMPARE(penSpy.count(), 2);
    TRY_COMPARE(brushSpy.count(), 1);
    TRY_COMPARE(labelBrushSpy.count(), 1);
    TRY_COMPARE(labelFontSpy.count(), 1);
    TRY_COMPARE(labelPositionSpy.count(), 1);
    TRY_COMPARE(labelArmLengthFactorSpy.count(), 1);
    TRY_COMPARE(explodeDistanceFactorSpy.count(), 1);
    TRY_COMPARE(colorSpy.count(), 1);
    TRY_COMPARE(borderColorSpy.count(), 1);
    TRY_COMPARE(borderWidthSpy.count(), 1);
    TRY_COMPARE(labelColorSpy.count(), 1);
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
    QTest::qWaitForWindowShown(&view);
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
    series->insert(0, new QPieSlice("slice 5", 5));
    QCOMPARE(s1->pen(), p1);
    QCOMPARE(s1->brush(), b1);
    QCOMPARE(s1->labelBrush(), b1);
    QCOMPARE(s1->labelFont(), f1);

    // change theme
    // theme will overwrite customizations
    view.chart()->setTheme(QChart::ChartThemeHighContrast);
    QVERIFY(s1->pen() != p1);
    QVERIFY(s1->brush() != b1);
    QVERIFY(s1->labelBrush() != b1);
    QVERIFY(s1->labelFont() != f1);
}

void tst_qpieslice::mouseClick()
{
    // create a pie series
    QPieSeries *series = new QPieSeries();
    series->setPieSize(1.0);
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 2);
    QPieSlice *s3 = series->append("slice 3", 3);
    QSignalSpy clickSpy1(s1, SIGNAL(clicked()));
    QSignalSpy clickSpy2(s2, SIGNAL(clicked()));
    QSignalSpy clickSpy3(s3, SIGNAL(clicked()));

    // add series to the chart
    QChartView view(new QChart());
    view.chart()->legend()->setVisible(false);
    view.resize(200, 200);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    // simulate clicks
    // pie rectangle: QRectF(60,60 121x121)
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0,  QPoint(139, 85)); // inside slice 1
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0,  QPoint(146, 136)); // inside slice 2
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0,  QPoint(91, 119)); // inside slice 3
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0,  QPoint(70, 70)); // inside pie rectangle but not inside a slice
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0,  QPoint(170, 170)); // inside pie rectangle but not inside a slice
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
    QCOMPARE(clickSpy1.count(), 1);
    QCOMPARE(clickSpy2.count(), 1);
    QCOMPARE(clickSpy3.count(), 1);
}

void tst_qpieslice::mouseHover()
{
    // create a pie series
    QPieSeries *series = new QPieSeries();
    series->setPieSize(1.0);
    QPieSlice *s1 = series->append("slice 1", 1);
    series->append("slice 2", 2);
    series->append("slice 3", 3);

    // add series to the chart
    QChartView view(new QChart());
    view.chart()->legend()->setVisible(false);
    view.resize(200, 200);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    // first move to right top corner
    QTest::mouseMove(view.viewport(), QPoint(200, 0));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    // move inside slice rectangle but NOT the actual slice
    // pie rectangle: QRectF(60,60 121x121)
    QSignalSpy hoverSpy(s1, SIGNAL(hovered(bool)));
    QTest::mouseMove(view.viewport(), QPoint(170, 70));
    TRY_COMPARE(hoverSpy.count(), 0);

    // move inside the slice
    QTest::mouseMove(view.viewport(), QPoint(139, 85));
    TRY_COMPARE(hoverSpy.count(), 1);
    QCOMPARE(qvariant_cast<bool>(hoverSpy.at(0).at(0)), true);

    // move outside the slice
    QTest::mouseMove(view.viewport(), QPoint(200, 0));
    TRY_COMPARE(hoverSpy.count(), 2);
    QCOMPARE(qvariant_cast<bool>(hoverSpy.at(1).at(0)), false);
}

QTEST_MAIN(tst_qpieslice)

#include "tst_qpieslice.moc"

