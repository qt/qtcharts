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

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <qchart.h>
#include <qchartview.h>
#include <qxyseries.h>
#include <qlineseries.h>
#include <qvxymodelmapper.h>
#include <qhxymodelmapper.h>
#include <QStandardItemModel>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_qxymodelmapper : public QObject
{
    Q_OBJECT
    
public:
    tst_qxymodelmapper();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void verticalMapper_data();
    void verticalMapper();
    void verticalMapperCustomMapping_data();
    void verticalMapperCustomMapping();
    void horizontalMapper_data();
    void horizontalMapper();
    void horizontalMapperCustomMapping_data();
    void horizontalMapperCustomMapping();
    void seriesUpdated();
    void modelUpdated();

private:
    QStandardItemModel *m_model;
    int m_modelRowCount;
    int m_modelColumnCount;

    QXYSeries *m_series;
    QChart *m_chart;
};

tst_qxymodelmapper::tst_qxymodelmapper():
    m_model(0),
    m_modelRowCount(10),
    m_modelColumnCount(8)
{
}

void tst_qxymodelmapper::init()
{
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
}

void tst_qxymodelmapper::cleanup()
{
    m_chart->removeSeries(m_series);
    delete m_series;
    m_series = 0;
}

void tst_qxymodelmapper::initTestCase()
{
    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->show();

    m_model = new QStandardItemModel(this);
    for (int row = 0; row < m_modelRowCount; ++row) {
        for (int column = 0; column < m_modelColumnCount; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            m_model->setItem(row, column, item);
        }
    }
}

void tst_qxymodelmapper::cleanupTestCase()
{
    m_model->clear();
}

void tst_qxymodelmapper::verticalMapper_data()
{
    QTest::addColumn<int>("xColumn");
    QTest::addColumn<int>("yColumn");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("different x and y columns") << 0 << 1 << m_modelRowCount;
    QTest::newRow("same x and y columns") << 1 << 1 << m_modelRowCount;
    QTest::newRow("invalid x column and correct y column") << -3 << 1 << 0;
    QTest::newRow("x column beyond the size of model and correct y column") << m_modelColumnCount << 1 << 0;
    QTest::newRow("x column beyond the size of model and invalid y column") << m_modelColumnCount << -1 << 0;
}

void tst_qxymodelmapper::verticalMapper()
{
    QFETCH(int, xColumn);
    QFETCH(int, yColumn);
    QFETCH(int, expectedCount);

    QVXYModelMapper *mapper = new QVXYModelMapper;
    QVERIFY(mapper->model() == 0);

    mapper->setXColumn(xColumn);
    mapper->setYColumn(yColumn);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);

    QCOMPARE(m_series->count(), expectedCount);
    QCOMPARE(mapper->xColumn(), qMax(-1, xColumn));
    QCOMPARE(mapper->yColumn(), qMax(-1, yColumn));

    delete mapper;
    mapper = 0;
}

void tst_qxymodelmapper::verticalMapperCustomMapping_data()
{
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("countLimit");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("first: 0, unlimited count") << 0 << -1 << m_modelRowCount;
    QTest::newRow("first: 3, unlimited count") << 3 << -1 << m_modelRowCount - 3;
    QTest::newRow("first: 0, count: 5") << 0 << 5 << qMin(5, m_modelRowCount);
    QTest::newRow("first: 3, count: 5") << 3 << 5 << qMin(5, m_modelRowCount - 3);
    QTest::newRow("first: +1 greater then the number of rows in the model, unlimited count") << m_modelRowCount + 1 << -1 << 0;
    QTest::newRow("first: +1 greater then the number of rows in the model, count: 5") << m_modelRowCount + 1 << 5 << 0;
    QTest::newRow("first: 0, count: +3 greater than the number of rows in the model (should limit to the size of model)") << 0 << m_modelRowCount + 3 << m_modelRowCount;
    QTest::newRow("first: -3(invalid - should default to 0), unlimited count") << -3 << -1 << m_modelRowCount;
    QTest::newRow("first: 0, count: -3 (invalid - shlould default to -1)") << 0 << -3 << m_modelRowCount;
    QTest::newRow("first: -3(invalid - should default to 0), count: -3 (invalid - shlould default to -1)") << -3 << -3 << m_modelRowCount;

}

void tst_qxymodelmapper::verticalMapperCustomMapping()
{
    QFETCH(int, first);
    QFETCH(int, countLimit);
    QFETCH(int, expectedCount);

    QCOMPARE(m_series->count(), 0);

    QVXYModelMapper *mapper = new QVXYModelMapper;
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);
    mapper->setFirst(first);
    mapper->setCount(countLimit);

    QCOMPARE(m_series->count(), expectedCount);

    // change values column mapping to invalid
    mapper->setXColumn(-1);
    mapper->setYColumn(1);

    QCOMPARE(m_series->count(), 0);

    delete mapper;
    mapper = 0;
}

void tst_qxymodelmapper::horizontalMapper_data()
{
    QTest::addColumn<int>("xRow");
    QTest::addColumn<int>("yRow");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("different x and y rows") << 0 << 1 << m_modelColumnCount;
    QTest::newRow("same x and y rows") << 1 << 1 << m_modelColumnCount;
    QTest::newRow("invalid x row and correct y row") << -3 << 1 << 0;
    QTest::newRow("x row beyond the size of model and correct y row") << m_modelRowCount << 1 << 0;
    QTest::newRow("x row beyond the size of model and invalid y row") << m_modelRowCount << -1 << 0;
}

void tst_qxymodelmapper::horizontalMapper()
{
    QFETCH(int, xRow);
    QFETCH(int, yRow);
    QFETCH(int, expectedCount);

    QHXYModelMapper *mapper = new QHXYModelMapper;
    mapper->setXRow(xRow);
    mapper->setYRow(yRow);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);

    QCOMPARE(m_series->count(), expectedCount);
    QCOMPARE(mapper->xRow(), qMax(-1, xRow));
    QCOMPARE(mapper->yRow(), qMax(-1, yRow));

    delete mapper;
    mapper = 0;
}

void tst_qxymodelmapper::horizontalMapperCustomMapping_data()
{
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("countLimit");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("first: 0, unlimited count") << 0 << -1 << m_modelColumnCount;
    QTest::newRow("first: 3, unlimited count") << 3 << -1 << m_modelColumnCount - 3;
    QTest::newRow("first: 0, count: 5") << 0 << 5 << qMin(5, m_modelColumnCount);
    QTest::newRow("first: 3, count: 5") << 3 << 5 << qMin(5, m_modelColumnCount - 3);
    QTest::newRow("first: +1 greater then the number of columns in the model, unlimited count") << m_modelColumnCount + 1 << -1 << 0;
    QTest::newRow("first: +1 greater then the number of columns in the model, count: 5") << m_modelColumnCount + 1 << 5 << 0;
    QTest::newRow("first: 0, count: +3 greater than the number of columns in the model (should limit to the size of model)") << 0 << m_modelColumnCount + 3 << m_modelColumnCount;
    QTest::newRow("first: -3(invalid - should default to 0), unlimited count") << -3 << -1 << m_modelColumnCount;
    QTest::newRow("first: 0, count: -3 (invalid - shlould default to -1)") << 0 << -3 << m_modelColumnCount;
    QTest::newRow("first: -3(invalid - should default to 0), count: -3 (invalid - shlould default to -1)") << -3 << -3 << m_modelColumnCount;
}

void tst_qxymodelmapper::horizontalMapperCustomMapping()
{
    QFETCH(int, first);
    QFETCH(int, countLimit);
    QFETCH(int, expectedCount);

    QCOMPARE(m_series->count(), 0);

    QHXYModelMapper *mapper = new QHXYModelMapper;
    mapper->setXRow(0);
    mapper->setYRow(1);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);
    mapper->setFirst(first);
    mapper->setCount(countLimit);

    QCOMPARE(m_series->count(), expectedCount);

    // change values row mapping to invalid
    mapper->setXRow(-1);
    mapper->setYRow(1);

    QCOMPARE(m_series->count(), 0);

    delete mapper;
    mapper = 0;
}

void tst_qxymodelmapper::seriesUpdated()
{
    QStandardItemModel *otherModel = new QStandardItemModel;
    for (int row = 0; row < m_modelRowCount; ++row) {
        for (int column = 0; column < m_modelColumnCount; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            otherModel->setItem(row, column, item);
        }
    }

    QVXYModelMapper *mapper = new QVXYModelMapper;
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setModel(otherModel);
    mapper->setSeries(m_series);
    QCOMPARE(m_series->count(), m_modelRowCount);
    QCOMPARE(mapper->count(), -1);

    m_series->append(QPointF(100, 100));
    QCOMPARE(m_series->count(), m_modelRowCount + 1);
    QCOMPARE(mapper->count(), -1); // the value should not change as it indicates 'all' items there are in the model

    m_series->remove(m_series->points().last());
    QCOMPARE(m_series->count(), m_modelRowCount);
    QCOMPARE(mapper->count(), -1); // the value should not change as it indicates 'all' items there are in the model

    delete mapper;
    mapper = 0;

    otherModel->clear();
    delete otherModel;
    otherModel = 0;
}

void tst_qxymodelmapper::modelUpdated()
{
    QStandardItemModel *otherModel = new QStandardItemModel;
    for (int row = 0; row < m_modelRowCount; ++row) {
        for (int column = 0; column < m_modelColumnCount; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            otherModel->setItem(row, column, item);
        }
    }

    QVXYModelMapper *mapper = new QVXYModelMapper;
    QVERIFY(mapper->model() == 0);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setModel(otherModel);
    mapper->setSeries(m_series);
    QCOMPARE(m_series->count(), m_modelRowCount);

    QVERIFY(mapper->model() != 0);

    if (otherModel->insertRows(3, 4))
        QCOMPARE(m_series->count(), m_modelRowCount + 4);

    if (otherModel->removeRows(1, 5))
        QCOMPARE(m_series->count(), m_modelRowCount - 1);

    delete mapper;
    mapper = 0;

    otherModel->clear();
    delete otherModel;
    otherModel = 0;
}

QTEST_MAIN(tst_qxymodelmapper)

#include "tst_qxymodelmapper.moc"
