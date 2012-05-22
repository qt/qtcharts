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
    void construction();
    void append();
    void insert();
    void remove();
    void calculatedValues();
    void clickedSignal();
    void hoverSignal();
    void model();
    void modelCustomMap();
    void modelUpdate();

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

void tst_qpieseries::construction()
{
    // verify default values
    QPieSeries s;
    QVERIFY(s.type() == QAbstractSeries::SeriesTypePie);
    QVERIFY(s.count() == 0);
    QVERIFY(s.isEmpty());
    QCOMPARE(s.sum(), 0.0);
    QCOMPARE(s.horizontalPosition(), 0.5);
    QCOMPARE(s.verticalPosition(), 0.5);
    QCOMPARE(s.pieSize(), 0.7);
    QCOMPARE(s.pieStartAngle(), 0.0);
    QCOMPARE(s.pieEndAngle(), 360.0);
}

void tst_qpieseries::append()
{
    QPieSeries s;

    // append pointer
    QPieSlice *slice1 = 0;
    QVERIFY(!s.append(slice1));
    slice1 = new QPieSlice(1, "slice 1");
    QVERIFY(s.append(slice1));
    QVERIFY(!s.append(slice1));
    QCOMPARE(s.count(), 1);

    // append pointer list
    QList<QPieSlice *> list;
    QVERIFY(!s.append(list));
    list << (QPieSlice *) 0;
    QVERIFY(!s.append(list));
    list.clear();
    list << new QPieSlice(2, "slice 2");
    list << new QPieSlice(3, "slice 3");
    QVERIFY(s.append(list));
    QVERIFY(!s.append(list));
    QCOMPARE(s.count(), 3);

    // append operator
    s << new QPieSlice(4, "slice 4");
    s << slice1; // fails because already added
    QCOMPARE(s.count(), 4);

    // append with params
    QPieSlice *slice5 = s.append(5, "slice 5");
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
    slice1 = new QPieSlice(1, "slice 1");
    QVERIFY(!s.insert(-1, slice1));
    QVERIFY(!s.insert(5, slice1));
    QVERIFY(s.insert(0, slice1));
    QVERIFY(!s.insert(0, slice1));
    QCOMPARE(s.count(), 1);

    // add some more slices
    s.append(2, "slice 2");
    s.append(4, "slice 4");
    QCOMPARE(s.count(), 3);

    // insert between slices
    s.insert(2, new QPieSlice(3, "slice 3"));
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
    QPieSlice *slice1 = s.append(1, "slice 1");
    QPieSlice *slice2 = s.append(2, "slice 2");
    QPieSlice *slice3 = s.append(3, "slice 3");
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

    // add a slice
    QPieSlice *slice1 = s.append(1, "slice 1");
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;

    // add some more slices
    QList<QPieSlice *> list;
    list << new QPieSlice(2, "slice 2");
    list << new QPieSlice(3, "slice 3");
    s.append(list);
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;

    // remove a slice
    s.remove(slice1);
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;

    // insert a slice
    s.insert(0, new QPieSlice(1, "Slice 4"));
    verifyCalculatedData(s, &ok);
    if (!ok)
        return;

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
    series->setPieSize(1.0);
    QPieSlice *s1 = series->append(1, "slice 1");
    series->append(2, "slice 2");
    series->append(3, "slice 3");
    QSignalSpy clickSpy1(series, SIGNAL(clicked(QPieSlice*)));

    // add series to the chart
    QChartView view(new QChart());
    view.chart()->legend()->setVisible(false);
    view.resize(200, 200);
    view.chart()->addSeries(series);
    view.show();
    QTest::qWaitForWindowShown(&view);

    // simulate clicks
    // pie rectangle: QRectF(60,60 121x121)
    QTest::mouseClick(view.viewport(), Qt::LeftButton, 0,  QPoint(146, 90)); // inside slice 1
    TRY_COMPARE(clickSpy1.count(), 1);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy1.at(0).at(0)), s1);
}

void tst_qpieseries::hoverSignal()
{
    // create a pie series
    QPieSeries *series = new QPieSeries();
    series->setPieSize(1.0);
    QPieSlice *s1 = series->append(1, "slice 1");
    series->append(2, "slice 2");
    series->append(3, "slice 3");

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

void tst_qpieseries::model()
{
    QSKIP("Needs to be checked again. Model implementation changed", SkipAll);

    QPieSeries *series = new QPieSeries;
    QChart *chart = new QChart;
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart);
    chartView->show();

    QStandardItemModel *stdModel = new QStandardItemModel(0, 2);
    series->setModel(stdModel);

    int rowCount = 3;
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < 2; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            stdModel->setItem(row, column, item);
        }
    }

    // data has been added to the model, but mapper is not set the number of slices should still be 0
    QVERIFY2(series->slices().count() == 0, "Mapper has not been set, so the number of slices should be 0");

    // set the mapper
    QPieModelMapper *mapper = series->modelMapper();//new QPieModelMapper;
    mapper->setMapValues(0);
    mapper->setMapLabels(0);
//    series->setModelMapper(mapper); // this should cause the Pie to get initialized from the model, since there is now both the model and the mapper defined
    QCOMPARE(series->slices().count(), rowCount);

    // set the mappings to be outside of the model
    mapper->setMapLabels(5);
    mapper->setMapValues(4);
    QCOMPARE(series->slices().count(), 0); // Mappings are invalid, so the number of slices should be 0

    // set back to correct ones
    mapper->setMapValues(0);
    mapper->setMapLabels(0);
    QCOMPARE(series->slices().count(), rowCount);

    // reset the mappings
    mapper->reset();
    QCOMPARE(series->slices().count(), 0); // Mappings have been reset and are invalid, so the number of slices should be 0

    // unset the model and the mapper
    series->setModel(0);
//    series->setModelMapper(0);
    QVERIFY(series->model() == 0); // Model should be unset
//    QVERIFY(series->modelMapper() == 0); // Model mapper should be unset
}

void tst_qpieseries::modelCustomMap()
{
    QSKIP("Needs to be checked again. Model implementation changed", SkipAll);

    int rowCount = 12;
    int columnCount = 3;
    QStandardItemModel *stdModel = new QStandardItemModel(0, 3);
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < 2; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            stdModel->setItem(row, column, item);
        }
    }

    QPieSeries *series = new QPieSeries;
    QChart *chart = new QChart;
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart);
    chartView->show();
    series->setModel(stdModel);

    QPieModelMapper *mapper = series->modelMapper();//new QPieModelMapper;
    mapper->setMapValues(0);
    mapper->setMapLabels(0);
//    series->setModelMapper(mapper);
    QCOMPARE(series->slices().count(), rowCount);

    // lets change the orientation to horizontal
    mapper->setOrientation(Qt::Horizontal);
    QCOMPARE(series->slices().count(), columnCount);

    // change it back to vertical
    mapper->setOrientation(Qt::Vertical);
    QCOMPARE(series->slices().count(), rowCount);

    // lets customize the mapping
    int first = 3;
    mapper->setFirst(first);
    QCOMPARE(series->slices().count(), rowCount - first);
    int count = 7;
    mapper->setCount(count);
    QCOMPARE(series->slices().count(), count);
    first = 9;
    mapper->setFirst(first);
    QCOMPARE(series->slices().count(), qMin(count, rowCount - first));
}

void tst_qpieseries::modelUpdate()
{
    QSKIP("Needs to be checked again. Model implementation changed", SkipAll);

    int rowCount = 12;
    int columnCount = 7;
    QStandardItemModel *stdModel = new QStandardItemModel(rowCount, columnCount);
    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            stdModel->setItem(row, column, item);
        }
    }

    QPieSeries *series = new QPieSeries;
    QChart *chart = new QChart;
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart);
    chartView->show();
    series->setModel(stdModel);

    QPieModelMapper *mapper = series->modelMapper();//new QPieModelMapper;
    mapper->setMapValues(0);
    mapper->setMapLabels(0);
//    series->setModelMapper(mapper);

    stdModel->insertRows(3, 5);
    QCOMPARE(series->slices().count(), rowCount + 5);

    stdModel->removeRows(10, 5);
    QCOMPARE(series->slices().count(), rowCount);

    // limit the number of slices taken from the model to 12
    mapper->setCount(rowCount);
    stdModel->insertRows(3, 5);
    QCOMPARE(series->slices().count(), rowCount);

    stdModel->removeRows(0, 10);
    QCOMPARE(series->slices().count(), rowCount - 5);

    // change the orientation to horizontal
    mapper->setOrientation(Qt::Horizontal);
    QCOMPARE(series->slices().count(), columnCount);

    stdModel->insertColumns(3, 10);
    QCOMPARE(series->slices().count(), rowCount); // count is limited to rowCount (12)

    stdModel->removeColumns(5, 10);
    QCOMPARE(series->slices().count(), columnCount);

}

QTEST_MAIN(tst_qpieseries)

#include "tst_qpieseries.moc"

