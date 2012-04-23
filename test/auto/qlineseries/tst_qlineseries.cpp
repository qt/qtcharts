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
#include <qlineseries.h>
#include <qchartview.h>
#include <QStandardItemModel>

Q_DECLARE_METATYPE(QList<QPointF>)

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QLineSeries : public QObject
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
    void append_raw_data();
    void append_raw();
    void append_chart_data();
    void append_chart();
    void append_chart_animation_data();
    void append_chart_animation();
    void chart_append_data();
    void chart_append();
    void count_raw_data();
    void count_raw();
    void oper_data();
    void oper();
    void pen_data();
    void pen();
    void pointsVisible_raw_data();
    void pointsVisible_raw();
    void remove_raw_data();
    void remove_raw();
    void remove_chart_data();
    void remove_chart();
    void remove_chart_animation_data();
    void remove_chart_animation();
    void removeAll_data();
    void removeAll();
    void replace_data();
    void replace();
    void setModel_data();
    void setModel();
    void setModelMapping_data();
    void setModelMapping();
    void setModelMappingRange_data();
    void setModelMappingRange();
    void modelUpdated();
    void modelUpdatedCustomMapping();
    private:
    void append_data();
    void count_data();
    void pointsVisible_data();

    private:
    QChartView* m_view;
    QChart* m_chart;
    QLineSeries* m_series;
};

void tst_QLineSeries::initTestCase()
{
}

void tst_QLineSeries::cleanupTestCase()
{
}

void tst_QLineSeries::init()
{
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
    m_series = new QLineSeries();
}

void tst_QLineSeries::cleanup()
{
    delete m_series;
    delete m_view;
    m_view = 0;
    m_chart = 0;
    m_series = 0;
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

    series.append(QList<QPointF>());
    series.append(0.0,0.0);
    series.append(QPointF());

    series.remove(0.0,0.0);
    series.remove(QPointF());
    series.removeAll();

    series.replace(QPointF(),QPointF());
    series.replace(0,0,0,0);
    series.setBrush(QBrush());

    QCOMPARE(series.setModel((QAbstractItemModel*)0), false);

    series.setModelMapping(-1, -1, Qt::Orientation(0));

    series.setPen(QPen());
    series.setPointsVisible(false);

    m_chart->addSeries(&series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QLineSeries::append_data()
{
    QTest::addColumn< QList<QPointF> >("points");
    QTest::newRow("0,0 1,1 2,2 3,3") << (QList<QPointF>() << QPointF(0,0) << QPointF(1,1) << QPointF(2,2) << QPointF(3,3));
    QTest::newRow("0,0 -1,-1 -2,-2 -3,-3") << (QList<QPointF>() << QPointF(0,0) << QPointF(-1,-1) << QPointF(-2,-2) << QPointF(-3,-3));
}


void tst_QLineSeries::append_raw_data()
{
    append_data();
}

void tst_QLineSeries::append_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    QTest::qWait(200);
    m_series->append(points);
    QTest::qWait(200);
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);
}

void tst_QLineSeries::chart_append_data()
{
    append_data();
}

void tst_QLineSeries::chart_append()
{
    append_raw();
    m_chart->addSeries(m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QLineSeries::append_chart_data()
{
    append_data();
}

void tst_QLineSeries::append_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    append_raw();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QLineSeries::append_chart_animation_data()
{
    append_data();
}

void tst_QLineSeries::append_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    append_chart();
}

void tst_QLineSeries::count_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("5") << 5;
    QTest::newRow("10") << 5;
}

void tst_QLineSeries::count_raw_data()
{
    count_data();
}

void tst_QLineSeries::count_raw()
{
    QFETCH(int, count);

    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));

    for(int i=0 ; i< count; ++i)
        m_series->append(i,i);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(m_series->count(), count);
}

void tst_QLineSeries::oper_data()
{
    append_data();
}

void tst_QLineSeries::oper()
{
    QFETCH(QList<QPointF>, points);
    QLineSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));

    foreach(const QPointF& point,points)
    {
        series<<point;
    }

    QCOMPARE(series.points(), points);
    QCOMPARE(spy0.count(), 0);
}


void tst_QLineSeries::pen_data()
{
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QLineSeries::pen()
{
    QFETCH(QPen, pen);
    QLineSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    series.setPen(pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(series.pen(), pen);

    m_chart->addSeries(&series);

    if(pen!=QPen()) QCOMPARE(series.pen(), pen);
}

void tst_QLineSeries::pointsVisible_data()
{
    QTest::addColumn<bool>("pointsVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QLineSeries::pointsVisible_raw_data()
{
    pointsVisible_data();
}

void tst_QLineSeries::pointsVisible_raw()
{
    QFETCH(bool, pointsVisible);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->setPointsVisible(pointsVisible);
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(m_series->pointsVisible(), pointsVisible);
}

void tst_QLineSeries::remove_raw_data()
{
    append_data();
}

void tst_QLineSeries::remove_raw()
{
    QFETCH(QList<QPointF>, points);
    QSignalSpy spy0(m_series, SIGNAL(clicked(QPointF const&)));
    m_series->append(points);
    QTest::qWait(200);
    QCOMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points(), points);

    foreach(const QPointF& point,points)
    {
        m_series->remove(point);
        QTest::qWait(200);
    }

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(m_series->points().count(), 0);
}

void tst_QLineSeries::remove_chart_data()
{
    append_data();
}

void tst_QLineSeries::remove_chart()
{
    m_view->show();
    m_chart->addSeries(m_series);
    remove_raw();
    QTest::qWaitForWindowShown(m_view);
}

void tst_QLineSeries::remove_chart_animation_data()
{
    append_data();
}

void tst_QLineSeries::remove_chart_animation()
{
    m_chart->setAnimationOptions(QChart::AllAnimations);
    remove_chart();
}


void tst_QLineSeries::removeAll_data()
{
    append_data();
}

void tst_QLineSeries::removeAll()
{
#if 0
    QFETCH(int, foo);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.removeAll();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::replace_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::newRow("null") << QPointF();
}

void tst_QLineSeries::replace()
{
#if 0
    QFETCH(QPointF, point);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.replace(point);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::setModel_data()
{
    //    QTest::addColumn<QStandardItemModel *>("model");
    //    QTest::addColumn<QStandardItemModel *>("expected");

    //    QTest::newRow("null") << 0 << 0;
    //    QTest::newRow("QStandardItemModel") << new QStandardItemModel() << new QStandardItemModel();
}

void tst_QLineSeries::setModel()
{
    //    QFETCH(QStandardItemModel *, model);
    //    QFETCH(QStandardItemModel *, expected);

    QLineSeries series;
    series.setModel(0);
    QVERIFY2(series.model() == 0, "Model should be unset");

    QStandardItemModel *stdModel = new QStandardItemModel();
    series.setModel(stdModel);
    QVERIFY2((series.model()) == stdModel, "Model should be stdModel");

    // unset the model
    series.setModel(0);
    QVERIFY2(series.model() == 0, "Model should be unset");

}

Q_DECLARE_METATYPE(Qt::Orientation)
void tst_QLineSeries::setModelMapping_data()
{
    QTest::addColumn<int>("modelX");
    QTest::addColumn<int>("modelY");
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::newRow("different x and y, vertical") << 0 << 1 << Qt::Vertical;
    QTest::newRow("same x and y, vertical") << 0 << 0 << Qt::Vertical;
    QTest::newRow("invalid x, corrent y, vertical") << -1 << 1 << Qt::Vertical;

    QTest::newRow("different x and y, horizontal") << 0 << 1 << Qt::Horizontal;
    QTest::newRow("same x and y, horizontal") << 0 << 0 << Qt::Horizontal;
    QTest::newRow("invalid x, corrent y, horizontal") << -1 << 1 << Qt::Horizontal;
}

void tst_QLineSeries::setModelMapping()
{
    QFETCH(int, modelX);
    QFETCH(int, modelY);
    QFETCH(Qt::Orientation, orientation);

    QLineSeries series;

    // model has not been set so setting mapping should do nothing
    series.setModelMapping(modelX, modelY, orientation);
    QCOMPARE(series.mapX(), -1);
    QCOMPARE(series.mapY(), -1);
    QVERIFY2(series.mapOrientation() == Qt::Vertical, "The orientation by default should be Qt::Vertical");

    // now let us set the model
    series.setModel(new QStandardItemModel());
    series.setModelMapping(modelX, modelY, orientation);
    QCOMPARE(series.mapX(), modelX);
    QCOMPARE(series.mapY(), modelY);
    QVERIFY2(series.mapOrientation() == orientation, "not good");

    // now let us remove the model, the values should go back to default ones.
    series.setModel(0);
    QCOMPARE(series.mapX(), -1);
    QCOMPARE(series.mapY(), -1);
    QVERIFY2(series.mapOrientation() == Qt::Vertical, "The orientation by default should be Qt::Vertical");
}

void tst_QLineSeries::setModelMappingRange_data()
{
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("count");
    QTest::newRow("first: 0, count: unlimited") << 0 << -1;
    QTest::newRow("first: 0, count: 5") << 0 << 5;
    QTest::newRow("first: 3, count: unlimited") << 3 << -1;
    QTest::newRow("first: 3, count: 5") << 3 << 5;
    QTest::newRow("first: -3, count: 5") << -3 << 5;
    QTest::newRow("first: 3, count: -5") << 3 << -5;
    QTest::newRow("first: -3, count: -5") << 3 << -5;
    QTest::newRow("first: -3, count: 0") << -3 << 0;
    QTest::newRow("first: 0, count: -5") << 0 << -5;
    QTest::newRow("first: 0, count: 0") << 0 << 0;
}

void tst_QLineSeries::setModelMappingRange()
{
    QFETCH(int, first);
    QFETCH(int, count);
    QLineSeries series;

    QStandardItemModel *model = new QStandardItemModel(0, 2);
    series.setModel(model);
    series.setModelMapping(0, 1);
    series.setModelMappingRange(first, count);

    QCOMPARE(series.mapFirst(), qMax(first, 0)); // regardles of what value was used to set the range, first should not be less than 0
    QCOMPARE(series.mapCount(), qMax(count, -1)); // regardles of what value was used to set the range, first should not be less than 0
    QVERIFY2(series.count() == 0, "No rows in the model, count should be 0");

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 2; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            model->setItem(row, column, item);
        }
    }
    if (qMax(count, -1) != -1)
        QVERIFY2(series.count() == qMin(model->rowCount() - qMax(first, 0), qMax(count, -1)), "Count should be the number of items in a model after first item, but not more than count and not less than 0");
    else
        QVERIFY2(series.count() == model->rowCount() - qMax(first, 0), "Count should be the number of items in a model after first item, but not less then 0");

    // let's add few more rows to the model
    for (int row = 0; row < 10; ++row) {
        QList<QStandardItem *> newRow;
        for (int column = 0; column < 2; column++) {
            newRow.append(new QStandardItem(row * column));
        }
        model->appendRow(newRow);
    }
    if (qMax(count, -1) != -1)
        QVERIFY2(series.count() == qMin(model->rowCount() - qMax(first, 0), qMax(count, -1)), "Count should be the number of items in a model after first item, but not more than count, but not more than count and not less than 0");
    else
        QVERIFY2(series.count() == model->rowCount() - qMax(first, 0), "Count should be the number of items in a model after first item, but not less then 0");

    // unset the model, values should be default
    series.setModel(0);
    QCOMPARE(series.mapFirst(), 0);
    QCOMPARE(series.mapCount(), -1);
    QVERIFY2(series.count() == 0, "No rows in the model, count should be 0");
}

void tst_QLineSeries::modelUpdated()
{
    QStandardItemModel *model = new QStandardItemModel;
    for (int row = 0; row < 10; ++row) {
        QList<QStandardItem *> newRow;
        for (int column = 0; column < 2; column++) {
            newRow.append(new QStandardItem(row * column));
        }
        model->appendRow(newRow);
    }

    QLineSeries series;
    series.setModel(model);
    series.setModelMapping(0, 1);

    model->setData(model->index(3, 1), 34);
    // check that the update data is correctly taken from the model
    QVERIFY(qFuzzyCompare(series.points().at(3).y(), 34));
}

void tst_QLineSeries::modelUpdatedCustomMapping()
{

    QStandardItemModel *model = new QStandardItemModel;
    for (int row = 0; row < 10; ++row) {
        QList<QStandardItem *> newRow;
        for (int column = 0; column < 2; column++) {
            newRow.append(new QStandardItem(row * column));
        }
        model->appendRow(newRow);
    }

    QLineSeries series;
    series.setModel(model);
    series.setModelMapping(0, 1);
    series.setModelMappingRange(3, 4);

    model->setData(model->index(3, 1), 34);
    QVERIFY(qFuzzyCompare(series.points().at(0).y(), 34));
}

QTEST_MAIN(tst_QLineSeries)

#include "tst_qlineseries.moc"

