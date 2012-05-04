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
#include <qstackedbarseries.h>
#include <qbarset.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QStackedBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qstackedbarseries_data();
    void qstackedbarseries();
    void type_data();
    void type();

private:
    QStackedBarSeries* m_barseries;
};

void tst_QStackedBarSeries::initTestCase()
{
}

void tst_QStackedBarSeries::cleanupTestCase()
{
}

void tst_QStackedBarSeries::init()
{
    m_barseries = new QStackedBarSeries();
}

void tst_QStackedBarSeries::cleanup()
{
    delete m_barseries;
    m_barseries = 0;
}

void tst_QStackedBarSeries::qstackedbarseries_data()
{
}

void tst_QStackedBarSeries::qstackedbarseries()
{
    QStackedBarSeries *barseries = new QStackedBarSeries();
    QVERIFY(barseries != 0);
}

void tst_QStackedBarSeries::type_data()
{

}

void tst_QStackedBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeStackedBar);
}

/*
bool setModel(QAbstractItemModel *model);
void setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
void setModelMappingRange(int first, int count = -1);
*/
QTEST_MAIN(tst_QStackedBarSeries)

#include "tst_qstackedbarseries.moc"

