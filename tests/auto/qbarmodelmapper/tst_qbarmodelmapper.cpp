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
#include <qgroupedbarseries.h>
#include <qbarset.h>
#include <qvbarmodelmapper.h>
#include <qhbarmodelmapper.h>
#include <QStandardItemModel>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_qbarmodelmapper : public QObject
{
    Q_OBJECT
    
    public:
    tst_qbarmodelmapper();
    
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

    private:
    QStandardItemModel *m_model;
    int m_modelRowCount;
    int m_modelColumnCount;

    QGroupedBarSeries *m_series;
    QChart *m_chart;
};

tst_qbarmodelmapper::tst_qbarmodelmapper():
    m_model(0),
    m_modelRowCount(10),
    m_modelColumnCount(8)
{
}

void tst_qbarmodelmapper::init()
{
    //    m_series = new QGroupedBarSeries;
    //    m_chart->addSeries(m_series);
}

void tst_qbarmodelmapper::cleanup()
{
    m_chart->removeSeries(m_series);
    delete m_series;
    m_series = 0;
}

void tst_qbarmodelmapper::initTestCase()
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

void tst_qbarmodelmapper::cleanupTestCase()
{
    m_model->clear();
}

void tst_qbarmodelmapper::verticalMapper_data()
{
    QTest::addColumn<int>("firstBarSetColumn");
    QTest::addColumn<int>("lastBarSetColumn");
    QTest::addColumn<int>("expectedBarSetCount");
    QTest::newRow("lastBarSetColumn greater than firstBarSetColumn") << 0 << 1 << 2;
    QTest::newRow("lastBarSetColumn equal to firstBarSetColumn") << 1 << 1 << 1;
    QTest::newRow("lastBarSetColumn lesser than firstBarSetColumn") << 1 << 0 << 0;
    QTest::newRow("invalid firstBarSetColumn and correct lastBarSetColumn") << -3 << 1 << 0;
    QTest::newRow("firstBarSetColumn beyond the size of model and correct lastBarSetColumn") << m_modelColumnCount << 1 << 0;
    QTest::newRow("firstBarSetColumn beyond the size of model and invalid lastBarSetColumn") << m_modelColumnCount << -1 << 0;
}

void tst_qbarmodelmapper::verticalMapper()
{
    QFETCH(int, firstBarSetColumn);
    QFETCH(int, lastBarSetColumn);
    QFETCH(int, expectedBarSetCount);

    m_series = new QGroupedBarSeries;

    QVBarModelMapper *mapper = new QVBarModelMapper;
    mapper->setFirstBarSetColumn(firstBarSetColumn);
    mapper->setLastBarSetColumn(lastBarSetColumn);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);

    m_chart->addSeries(m_series);

    QCOMPARE(m_series->barsetCount(), expectedBarSetCount);
    QCOMPARE(mapper->firstBarSetColumn(), qMax(-1, firstBarSetColumn));
    QCOMPARE(mapper->lastBarSetColumn(), qMax(-1, lastBarSetColumn));

    delete mapper;
    mapper = 0;
}

void tst_qbarmodelmapper::verticalMapperCustomMapping_data()
{
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("countLimit");
    QTest::addColumn<int>("expectedBarSetCount");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("first: 0, unlimited count") << 0 << -1 << 2 << m_modelRowCount;
    QTest::newRow("first: 3, unlimited count") << 3 << -1 << 2 << m_modelRowCount - 3;
    QTest::newRow("first: 0, count: 5") << 0 << 5 << 2 << qMin(5, m_modelRowCount);
    QTest::newRow("first: 3, count: 5") << 3 << 5 << 2 << qMin(5, m_modelRowCount - 3);
    QTest::newRow("first: +1 greater then the number of rows in the model, unlimited count") << m_modelRowCount + 1 << -1 << 0 << 0;
    QTest::newRow("first: +1 greater then the number of rows in the model, count: 5") << m_modelRowCount + 1 << 5 << 0 << 0;
    QTest::newRow("first: 0, count: +3 greater than the number of rows in the model (should limit to the size of model)") << 0 << m_modelRowCount + 3 << 2 << m_modelRowCount;
    QTest::newRow("first: -3(invalid - should default to 0), unlimited count") << -3 << -1 << 2 << m_modelRowCount;
    QTest::newRow("first: 0, count: -3 (invalid - shlould default to -1)") << 0 << -3 << 2 << m_modelRowCount;
    QTest::newRow("first: -3(invalid - should default to 0), count: -3 (invalid - shlould default to -1)") << -3 << -3 << 2 << m_modelRowCount;
}

void tst_qbarmodelmapper::verticalMapperCustomMapping()
{
    QFETCH(int, first);
    QFETCH(int, countLimit);
    QFETCH(int, expectedBarSetCount);
    QFETCH(int, expectedCount);

    m_series = new QGroupedBarSeries;

    QCOMPARE(m_series->barsetCount(), 0);

    QVBarModelMapper *mapper = new QVBarModelMapper;
    mapper->setFirstBarSetColumn(0);
    mapper->setLastBarSetColumn(1);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);
    mapper->setFirst(first);
    mapper->setCount(countLimit);
    m_chart->addSeries(m_series);

    QCOMPARE(m_series->barsetCount(), expectedBarSetCount);

    if (expectedBarSetCount > 0)
        QCOMPARE(m_series->barSets().first()->count(), expectedCount);

    // change values column mapping to invalid
    mapper->setFirstBarSetColumn(-1);
    mapper->setLastBarSetColumn(1);

    QCOMPARE(m_series->barsetCount(), 0);

    delete mapper;
    mapper = 0;
}

void tst_qbarmodelmapper::horizontalMapper_data()
{
    QTest::addColumn<int>("firstBarSetRow");
    QTest::addColumn<int>("lastBarSetRow");
    QTest::addColumn<int>("expectedBarSetCount");
    QTest::newRow("lastBarSetRow greater than firstBarSetRow") << 0 << 1 << 2;
    QTest::newRow("lastBarSetRow equal to firstBarSetRow") << 1 << 1 << 1;
    QTest::newRow("lastBarSetRow lesser than firstBarSetRow") << 1 << 0 << 0;
    QTest::newRow("invalid firstBarSetRow and correct lastBarSetRow") << -3 << 1 << 0;
    QTest::newRow("firstBarSetRow beyond the size of model and correct lastBarSetRow") << m_modelRowCount << 1 << 0;
    QTest::newRow("firstBarSetRow beyond the size of model and invalid lastBarSetRow") << m_modelRowCount << -1 << 0;
}

void tst_qbarmodelmapper::horizontalMapper()
{
    QFETCH(int, firstBarSetRow);
    QFETCH(int, lastBarSetRow);
    QFETCH(int, expectedBarSetCount);

    m_series = new QGroupedBarSeries;

    QHBarModelMapper *mapper = new QHBarModelMapper;
    mapper->setFirstBarSetRow(firstBarSetRow);
    mapper->setLastBarSetRow(lastBarSetRow);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);

    m_chart->addSeries(m_series);

    QCOMPARE(m_series->barsetCount(), expectedBarSetCount);
    QCOMPARE(mapper->firstBarSetRow(), qMax(-1, firstBarSetRow));
    QCOMPARE(mapper->lastBarSetRow(), qMax(-1, lastBarSetRow));

    delete mapper;
    mapper = 0;
}

void tst_qbarmodelmapper::horizontalMapperCustomMapping_data()
{
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("countLimit");
    QTest::addColumn<int>("expectedBarSetCount");
    QTest::addColumn<int>("expectedCount");
    QTest::newRow("first: 0, unlimited count") << 0 << -1 << 2 << m_modelColumnCount;
    QTest::newRow("first: 3, unlimited count") << 3 << -1 << 2 << m_modelColumnCount - 3;
    QTest::newRow("first: 0, count: 5") << 0 << 5 << 2 << qMin(5, m_modelColumnCount);
    QTest::newRow("first: 3, count: 5") << 3 << 5 << 2 << qMin(5, m_modelColumnCount - 3);
    QTest::newRow("first: +1 greater then the number of rows in the model, unlimited count") << m_modelColumnCount + 1 << -1 << 0 << 0;
    QTest::newRow("first: +1 greater then the number of rows in the model, count: 5") << m_modelColumnCount + 1 << 5 << 0 << 0;
    QTest::newRow("first: 0, count: +3 greater than the number of rows in the model (should limit to the size of model)") << 0 << m_modelColumnCount + 3 << 2 << m_modelColumnCount;
    QTest::newRow("first: -3(invalid - should default to 0), unlimited count") << -3 << -1 << 2 << m_modelColumnCount;
    QTest::newRow("first: 0, count: -3 (invalid - shlould default to -1)") << 0 << -3 << 2 << m_modelColumnCount;
    QTest::newRow("first: -3(invalid - should default to 0), count: -3 (invalid - shlould default to -1)") << -3 << -3 << 2 << m_modelColumnCount;
}

void tst_qbarmodelmapper::horizontalMapperCustomMapping()
{
    QFETCH(int, first);
    QFETCH(int, countLimit);
    QFETCH(int, expectedBarSetCount);
    QFETCH(int, expectedCount);

    m_series = new QGroupedBarSeries;

    QCOMPARE(m_series->barsetCount(), 0);

    QHBarModelMapper *mapper = new QHBarModelMapper;
    mapper->setFirstBarSetRow(0);
    mapper->setLastBarSetRow(1);
    mapper->setModel(m_model);
    mapper->setSeries(m_series);
    mapper->setFirst(first);
    mapper->setCount(countLimit);
    m_chart->addSeries(m_series);

    QCOMPARE(m_series->barsetCount(), expectedBarSetCount);

    if (expectedBarSetCount > 0)
        QCOMPARE(m_series->barSets().first()->count(), expectedCount);

    // change values column mapping to invalid
    mapper->setFirstBarSetRow(-1);
    mapper->setLastBarSetRow(1);

    QCOMPARE(m_series->barsetCount(), 0);

    delete mapper;
    mapper = 0;
}

QTEST_MAIN(tst_qbarmodelmapper)

#include "tst_qbarmodelmapper.moc"
