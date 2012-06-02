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
#include <qpieseries.h>
#include <qvpiemodelmapper.h>
#include <qhpiemodelmapper.h>
#include <QStandardItemModel>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_qpiemodelmapper : public QObject
{
    Q_OBJECT
    
    public:
    tst_qpiemodelmapper();
    
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


    private:
    QStandardItemModel *m_model;
    int m_modelRowCount;
    int m_modelColumnCount;

    QPieSeries *m_series;
    QChart *m_chart;
};

tst_qpiemodelmapper::tst_qpiemodelmapper():
    m_model(0),
    m_modelRowCount(10),
    m_modelColumnCount(8)
{
}

void tst_qpiemodelmapper::init()
{
    m_series = new QPieSeries;
    m_chart->addSeries(m_series);
}

void tst_qpiemodelmapper::cleanup()
{
    m_chart->removeSeries(m_series);
    delete m_series;
    m_series = 0;
}

void tst_qpiemodelmapper::initTestCase()
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

void tst_qpiemodelmapper::cleanupTestCase()
{
    m_model->clear();
}

void tst_qpiemodelmapper::verticalMapper_data()
{
    QTest::addColumn<int>("valuesColumn");
    QTest::addColumn<int>("labelsColumn");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("different values and labels columns") << 0 << 1 << m_modelRowCount;
    QTest::newRow("same values and labels columns") << 1 << 1 << m_modelRowCount;
    QTest::newRow("invalid values column and correct labels column") << -3 << 1 << 0;
    QTest::newRow("values column beyond the size of model and correct labels column") << m_modelColumnCount << 1 << 0;
    QTest::newRow("values column beyond the size of model and invalid labels column") << m_modelColumnCount << -1 << 0;
}

void tst_qpiemodelmapper::verticalMapper()
{
    QFETCH(int, valuesColumn);
    QFETCH(int, labelsColumn);
    QFETCH(int, expectedCount);

    QVPieModelMapper *mapper = new QVPieModelMapper;
    mapper->setValuesColumn(valuesColumn);
    mapper->setLabelsColumn(labelsColumn);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);

    QCOMPARE(m_series->count(), expectedCount);
    QCOMPARE(mapper->valuesColumn(), qMax(-1, valuesColumn));
    QCOMPARE(mapper->labelsColumn(), qMax(-1, labelsColumn));

    delete mapper;
    mapper = 0;
}

void tst_qpiemodelmapper::verticalMapperCustomMapping_data()
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

void tst_qpiemodelmapper::verticalMapperCustomMapping()
{
    QFETCH(int, first);
    QFETCH(int, countLimit);
    QFETCH(int, expectedCount);

    QCOMPARE(m_series->count(), 0);

    QVPieModelMapper *mapper = new QVPieModelMapper;
    mapper->setValuesColumn(0);
    mapper->setLabelsColumn(1);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);
    mapper->setFirst(first);
    mapper->setCount(countLimit);

    QCOMPARE(m_series->count(), expectedCount);

    // change values column mapping to invalid
    mapper->setValuesColumn(-1);
    mapper->setLabelsColumn(1);

    QCOMPARE(m_series->count(), 0);

    delete mapper;
    mapper = 0;
}

void tst_qpiemodelmapper::horizontalMapper_data()
{
    QTest::addColumn<int>("valuesRow");
    QTest::addColumn<int>("labelsRow");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("different values and labels rows") << 0 << 1 << m_modelColumnCount;
    QTest::newRow("same values and labels rows") << 1 << 1 << m_modelColumnCount;
    QTest::newRow("invalid values row and correct labels row") << -3 << 1 << 0;
    QTest::newRow("values row beyond the size of model and correct labels row") << m_modelRowCount << 1 << 0;
    QTest::newRow("values row beyond the size of model and invalid labels row") << m_modelRowCount << -1 << 0;
}

void tst_qpiemodelmapper::horizontalMapper()
{
    QFETCH(int, valuesRow);
    QFETCH(int, labelsRow);
    QFETCH(int, expectedCount);

    QHPieModelMapper *mapper = new QHPieModelMapper;
    mapper->setValuesRow(valuesRow);
    mapper->setLabelsRow(labelsRow);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);

    QCOMPARE(m_series->count(), expectedCount);
    QCOMPARE(mapper->valuesRow(), qMax(-1, valuesRow));
    QCOMPARE(mapper->labelsRow(), qMax(-1, labelsRow));

    delete mapper;
    mapper = 0;
}

void tst_qpiemodelmapper::horizontalMapperCustomMapping_data()
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

void tst_qpiemodelmapper::horizontalMapperCustomMapping()
{
    QFETCH(int, first);
    QFETCH(int, countLimit);
    QFETCH(int, expectedCount);

    QCOMPARE(m_series->count(), 0);

    QHPieModelMapper *mapper = new QHPieModelMapper;
    mapper->setValuesRow(0);
    mapper->setLabelsRow(1);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);
    mapper->setFirst(first);
    mapper->setCount(countLimit);

    QCOMPARE(m_series->count(), expectedCount);

    // change values row mapping to invalid
    mapper->setValuesRow(-1);
    mapper->setLabelsRow(1);

    QCOMPARE(m_series->count(), 0);

    delete mapper;
    mapper = 0;
}

void tst_qpiemodelmapper::seriesUpdated()
{
    QStandardItemModel *otherModel = new QStandardItemModel;
    for (int row = 0; row < m_modelRowCount; ++row) {
        for (int column = 0; column < m_modelColumnCount; column++) {
            QStandardItem *item = new QStandardItem(row * column);
            otherModel->setItem(row, column, item);
        }
    }

    QVPieModelMapper *mapper = new QVPieModelMapper;
    mapper->setValuesColumn(0);
    mapper->setLabelsColumn(1);
    mapper->setModel(otherModel);
    mapper->setSeries(m_series);
    QCOMPARE(m_series->count(), m_modelRowCount);
    QCOMPARE(mapper->count(), -1);

    m_series->append("1000", 1000);
    QCOMPARE(m_series->count(), m_modelRowCount + 1);
    QCOMPARE(mapper->count(), -1); // the value should not change as it indicates 'all' items there are in the model

    m_series->remove(m_series->slices().last());
    QCOMPARE(m_series->count(), m_modelRowCount);
    QCOMPARE(mapper->count(), -1); // the value should not change as it indicates 'all' items there are in the model

    otherModel->clear();
    delete otherModel;
    otherModel = 0;
}

QTEST_MAIN(tst_qpiemodelmapper)

#include "tst_qpiemodelmapper.moc"
