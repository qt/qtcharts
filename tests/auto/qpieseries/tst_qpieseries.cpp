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
#include <qchart.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include <qpiemodelmapper.h>
#include <QStandardItemModel>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QPieSlice*)

class tst_qpieseries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void properties();
    void append();
    void insert();
    void remove();
    void calculatedValues();
    void clickedSignal();
    void hoverSignal();

private:
    void verifyCalculatedData(const QPieSeries &series, bool *ok);

private:

};

void tst_qpieseries::initTestCase()
{
    qRegisterMetaType<QPieSlice*>("QPieSlice*");
}

void tst_qpieseries::cleanupTestCase()
{
}

void tst_qpieseries::init()
{

}

void tst_qpieseries::cleanup()
{

}

void tst_qpieseries::properties()
{
    QPieSeries s;

    QSignalSpy countSpy(&s, SIGNAL(countChanged()));
    QSignalSpy sumSpy(&s, SIGNAL(sumChanged()));
    QSignalSpy sizeSpy(&s, SIGNAL(pieSizeChanged()));
    QSignalSpy startAngleSpy(&s, SIGNAL(pieStartAngleChanged()));
    QSignalSpy endAngleSpy(&s, SIGNAL(pieEndAngleChanged()));
    QSignalSpy horPosSpy(&s, SIGNAL(horizontalPositionChanged()));
    QSignalSpy verPosSpy(&s, SIGNAL(verticalPositionChanged()));

    QVERIFY(s.type() == QAbstractSeries::SeriesTypePie);
    QVERIFY(s.count() == 0);
    QVERIFY(s.isEmpty());
    QCOMPARE(s.sum(), 0.0);
    QCOMPARE(s.horizontalPosition(), 0.5);
    QCOMPARE(s.verticalPosition(), 0.5);
    QCOMPARE(s.pieSize(), 0.7);
    QCOMPARE(s.pieStartAngle(), 0.0);
    QCOMPARE(s.pieEndAngle(), 360.0);

    s.append("s1", 1);
    s.append("s2", 1);
    s.append("s3", 1);
    s.insert(1, new QPieSlice("s4", 1));
    s.remove(s.slices().first());
    QCOMPARE(s.count(), 3);
    QCOMPARE(s.sum(), 3.0);
    s.clear();
    QCOMPARE(s.count(), 0);
    QCOMPARE(s.sum(), 0.0);
    QCOMPARE(countSpy.count(), 6);
    QCOMPARE(sumSpy.count(), 6);

    s.setPieSize(-1.0);
    QCOMPARE(s.pieSize(), 0.0);
    s.setPieSize(0.0);
    s.setPieSize(0.9);
    s.setPieSize(2.0);
    QCOMPARE(s.pieSize(), 1.0);
    QCOMPARE(sizeSpy.count(), 3);

    s.setPieStartAngle(0);
    s.setPieStartAngle(-180);
    s.setPieStartAngle(180);
    QCOMPARE(startAngleSpy.count(), 2);

    s.setPieEndAngle(360);
    s.setPieEndAngle(-180);
    s.setPieEndAngle(180);
    QCOMPARE(endAngleSpy.count(), 2);

    s.setHorizontalPosition(0.5);
    s.setHorizontalPosition(-1.0);
    QCOMPARE(s.horizontalPosition(), 0.0);
    s.setHorizontalPosition(1.0);
    s.setHorizontalPosition(2.0);
    QCOMPARE(s.horizontalPosition(), 1.0);
    QCOMPARE(horPosSpy.count(), 2);

    s.setVerticalPosition(0.5);
    s.setVerticalPosition(-1.0);
    QCOMPARE(s.verticalPosition(), 0.0);
    s.setVerticalPosition(1.0);
    s.setVerticalPosition(2.0);
    QCOMPARE(s.verticalPosition(), 1.0);
    QCOMPARE(verPosSpy.count(), 2);
}

void tst_qpieseries::append()
{
    QPieSeries s;

    // append pointer
    QPieSlice *slice1 = 0;
    QVERIFY(!s.append(slice1));
    slice1 = new QPieSlice("slice 1", 1);
    QVERIFY(s.append(slice1));
    QVERIFY(!s.append(slice1));
    QCOMPARE(s.count(), 1);

    // append pointer list
    QList<QPieSlice *> list;
    QVERIFY(!s.append(list));
    list << (QPieSlice *) 0;
    QVERIFY(!s.append(list));
    list.clear();
    list << new QPieSlice("slice 2", 2);
    list << new QPieSlice("slice 3", 3);
    QVERIFY(s.append(list));
    QVERIFY(!s.append(list));
    QCOMPARE(s.count(), 3);

    // append operator
    s << new QPieSlice("slice 4", 4);
    s << slice1; // fails because already added
    QCOMPARE(s.count(), 4);

    // append with params
    QPieSlice *slice5 = s.append("slice 5", 5);
    QVERIFY(slice5 != 0);
    QCOMPARE(slice5->value(), 5.0);
    QCOMPARE(slice5->label(), QString("slice 5"));
    QCOMPARE(s.count(), 5);

    // check slices
    QVERIFY(!s.isEmpty());
    for (int i=0; i<s.count(); i++) {
        QCOMPARE(s.slices().at(i)->value(), (qreal) i+1);
        QCOMPARE(s.slices().at(i)->label(), QString("slice ") + QString::number(i+1));
    }
}

void tst_qpieseries::insert()
{
    QPieSeries s;

    // insert one slice
    QPieSlice *slice1 = 0;
    QVERIFY(!s.insert(0, slice1));
    slice1 = new QPieSlice("slice 1", 1);
    QVERIFY(!s.insert(-1, slice1));
    QVERIFY(!s.insert(5, slice1));
    QVERIFY(s.insert(0, slice1));
    QVERIFY(!s.insert(0, slice1));
    QCOMPARE(s.count(), 1);

    // add some more slices
    s.append("slice 2", 2);
    s.append("slice 4", 4);
    QCOMPARE(s.count(), 3);

    // insert between slices
    s.insert(2, new QPieSlice("slice 3", 3));
    QCOMPARE(s.count(), 4);

    // check slices
    for (int i=0; i<s.count(); i++) {
        QCOMPARE(s.slices().at(i)->value(), (qreal) i+1);
        QCOMPARE(s.slices().at(i)->label(), QString("slice ") + QString::number(i+1));
    }
}

void tst_qpieseries::remove()
{
    QPieSeries s;

    // add some slices
    QPieSlice *slice1 = s.append("slice 1", 1);
    QPieSlice *slice2 = s.append("slice 2", 2);
    QPieSlice *slice3 = s.append("slice 3", 3);
    QSignalSpy spy1(slice1, SIGNAL(destroyed()));
    QSignalSpy spy2(slice2, SIGNAL(destroyed()));
    QSignalSpy spy3(slice3, SIGNAL(destroyed()));
    QCOMPARE(s.count(), 3);

    // null pointer remove
    QVERIFY(!s.remove(0));

    // remove first
    QVERIFY(s.remove(slice1));
    QVERIFY(!s.remove(slice1));
    QCOMPARE(s.count(), 2);
    QCOMPARE(s.slices().at(0)->label(), slice2->label());

    // remove all
    s.clear();
    QVERIFY(s.isEmpty());
    QVERIFY(s.slices().isEmpty());
    QCOMPARE(s.count(), 0);

    // check that slices were actually destroyed
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 1);
    TRY_COMPARE(spy3.count(), 1);
}

void tst_qpieseries::calculatedValues()
{
    bool ok;
    QPieSeries s;

    QPieSlice *slice1 = new QPieSlice("slice 1", 1);
    QSignalSpy calculatedDataSpy(slice1, SIGNAL(calculatedDataChanged()));

    // add a slice
    s.append(slice1);
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;
    QCOMPARE(calculatedDataSpy.count(), 1);

    // add some more slices
    QList<QPieSlice *> list;
    list << new QPieSlice("slice 2", 2);
    list << new QPieSlice("slice 3", 3);
    s.append(list);
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;
    QCOMPARE(calculatedDataSpy.count(), 2);

    // remove a slice
    s.remove(list.first()); // remove slice 2
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;
    QCOMPARE(calculatedDataSpy.count(), 3);

    // insert a slice
    s.insert(0, new QPieSlice("Slice 4", 4));
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;
    QCOMPARE(calculatedDataSpy.count(), 4);

    // modify pie angles
    s.setPieStartAngle(-90);
    s.setPieEndAngle(90);
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;
    QCOMPARE(calculatedDataSpy.count(), 6);

    // clear all
    s.clear();
    verifyCalculatedData(s, &ok);
}

void tst_qpieseries::verifyCalculatedData(const QPieSeries &series, bool *ok)
{
    *ok = false;

    qreal sum = 0;
    foreach (const QPieSlice *slice, series.slices())
        sum += slice->value();
    QCOMPARE(series.sum(), sum);

    qreal startAngle = series.pieStartAngle();
    qreal pieAngleSpan = series.pieEndAngle() - series.pieStartAngle();
    foreach (const QPieSlice *slice, series.slices()) {
        qreal ratio = slice->value() / sum;
        qreal sliceSpan = pieAngleSpan * ratio;
        QCOMPARE(slice->startAngle(), startAngle);
        QCOMPARE(slice->endAngle(), startAngle + sliceSpan);
        QCOMPARE(slice->percentage(), ratio);
        startAngle += sliceSpan;
    }

    if (!series.isEmpty())
        QCOMPARE(series.slices().last()->endAngle(), series.pieEndAngle());

    *ok = true;
}


void tst_qpieseries::clickedSignal()
{
    // create a pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *s1 = series->append("slice 1", 1);
    QPieSlice *s2 = series->append("slice 2", 1);
    QPieSlice *s3 = series->append("slice 3", 1);
    QPieSlice *s4 = series->append("slice 4", 1);
    QSignalSpy clickSpy(series, SIGNAL(clicked(QPieSlice*)));

    // add series to the chart
    QChartView view(new QChart());
    view.chart()->legend()->setVisible(false);
    view.resize(200, 200);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    // if you devide the chart in four equal tiles these
    // are the center points of those tiles
    QPoint p1(90.25, 90);
    QPoint p2(150, 90);
    QPoint p3(90, 150);
    QPoint p4(150, 150);

    QPoint center(120, 120);

    series->setPieSize(1.0);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 5); // all hit
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(0).at(0)), s4);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(1).at(0)), s1);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(2).at(0)), s3);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(3).at(0)), s2);
    clickSpy.clear();

    series->setPieSize(0.5);
    series->setVerticalPosition(0.25);
    series->setHorizontalPosition(0.25);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p1); // hits
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();

    series->setVerticalPosition(0.25);
    series->setHorizontalPosition(0.75);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p2); // hits
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();

    series->setVerticalPosition(0.75);
    series->setHorizontalPosition(0.25);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p3); // hits
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();

    series->setVerticalPosition(0.75);
    series->setHorizontalPosition(0.75);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, p4); // hits
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();
}

void tst_qpieseries::hoverSignal()
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

    // move inside the slice
    // pie rectangle: QRectF(60,60 121x121)
    QSignalSpy hoverSpy(series, SIGNAL(hovered(QPieSlice*,bool)));
    QTest::mouseMove(view.viewport(), QPoint(139, 85));
    TRY_COMPARE(hoverSpy.count(), 1);
    QCOMPARE(qvariant_cast<QPieSlice*>(hoverSpy.at(0).at(0)), s1);
    QCOMPARE(qvariant_cast<bool>(hoverSpy.at(0).at(1)), true);

    // move outside the slice
    QTest::mouseMove(view.viewport(), QPoint(200, 0));
    TRY_COMPARE(hoverSpy.count(), 2);
    QCOMPARE(qvariant_cast<QPieSlice*>(hoverSpy.at(1).at(0)), s1);
    QCOMPARE(qvariant_cast<bool>(hoverSpy.at(1).at(1)), false);
}

QTEST_MAIN(tst_qpieseries)

#include "tst_qpieseries.moc"

