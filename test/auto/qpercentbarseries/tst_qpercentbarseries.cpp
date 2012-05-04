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
#include <qpercentbarseries.h>
#include <qbarset.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QPercentBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qpercentbarseries_data();
    void qpercentbarseries();
    void type_data();
    void type();

private:
    QPercentBarSeries* m_barseries;
};

void tst_QPercentBarSeries::initTestCase()
{
}

void tst_QPercentBarSeries::cleanupTestCase()
{
}

void tst_QPercentBarSeries::init()
{
    m_barseries = new QPercentBarSeries();
}

void tst_QPercentBarSeries::cleanup()
{
    delete m_barseries;
    m_barseries = 0;
}

void tst_QPercentBarSeries::qpercentbarseries_data()
{
}

void tst_QPercentBarSeries::qpercentbarseries()
{
    QPercentBarSeries *barseries = new QPercentBarSeries();
    QVERIFY(barseries != 0);
}

void tst_QPercentBarSeries::type_data()
{

}

void tst_QPercentBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypePercentBar);
}


/*
bool setModel(QAbstractItemModel *model);
void setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
void setModelMappingRange(int first, int count = -1);
*/
QTEST_MAIN(tst_QPercentBarSeries)

#include "tst_qpercentbarseries.moc"

