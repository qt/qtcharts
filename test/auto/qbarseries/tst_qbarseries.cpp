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
#include <qbarseries.h>
#include <qbarset>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QBarSeries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qbarseries_data();
    void qbarseries();
    void type_data();
    void type();
    void appendBarSet_data();
    void appendBarSet();

private:
    QBarSeries* m_barseries;
};

void tst_QBarSeries::initTestCase()
{
}

void tst_QBarSeries::cleanupTestCase()
{
}

void tst_QBarSeries::init()
{
    QBarCategories categories;
    categories << "category0" << "category1" << "category2";
    m_barseries = new QBarSeries(categories);
}

void tst_QBarSeries::cleanup()
{
    delete m_barseries;
    m_barseries = 0;
}

void tst_QBarSeries::qbarseries_data()
{
    QTest::addColumn<QBarCategories> ("categories");
    QBarCategories c;
    c << "category0" << "category1" << "category2";
    QTest::newRow("categories") << c;
}

void tst_QBarSeries::qbarseries()
{
    QFETCH(QBarCategories, categories);
    QBarSeries *barseries = new QBarSeries(categories);
    QVERIFY(barseries != 0);
    QBarCategories verifyCategories = barseries->categories();

    QVERIFY(verifyCategories.count() == categories.count());
    for (int i=0; i<categories.count(); i++) {
        QVERIFY(verifyCategories.at(i).compare(categories.at(i)) == 0);
    }
}

void tst_QBarSeries::type_data()
{

}

void tst_QBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeBar);
}

void tst_QBarSeries::appendBarSet_data()
{
}

void tst_QBarSeries::appendBarSet()
{
    QVERIFY(m_barseries->barsetCount() == 0);

    QBarSet *barset = new QBarSet("testset");
    m_barseries->appendBarSet(barset);

    QVERIFY(m_barseries->barsetCount() == 1);
}

/*
void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
void appendBarSets(QList<QBarSet* > sets);
void removeBarSets(QList<QBarSet* > sets);
int barsetCount() const;
int categoryCount() const;
QList<QBarSet*> barSets() const;
QBarCategories categories() const;

void setLabelsVisible(bool visible = true);

bool setModel(QAbstractItemModel *model);
void setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
void setModelMappingRange(int first, int count = -1);
*/
QTEST_MAIN(tst_QBarSeries)

#include "tst_qbarseries.moc"

