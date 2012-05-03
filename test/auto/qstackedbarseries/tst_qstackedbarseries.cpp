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
    void setCategories_data();
    void setCategories();
    void appendBarSet_data();
    void appendBarSet();
    void removeBarSet_data();
    void removeBarSet();
    void appendBarSets_data();
    void appendBarSets();
    void removeBarSets_data();
    void removeBarSets();
    void barsetCount_data();
    void barsetCount();
    void categoryCount_data();
    void categoryCount();
    void barSets_data();
    void barSets();
    void categories_data();
    void categories();
    void setLabelsVisible_data();
    void setLabelsVisible();

private:
    QStackedBarSeries* m_barseries;
    QStackedBarSeries* m_barseries_with_sets;

    QList<QBarSet*> m_testSets;

    QBarCategories m_categories;
};

void tst_QStackedBarSeries::initTestCase()
{
}

void tst_QStackedBarSeries::cleanupTestCase()
{
}

void tst_QStackedBarSeries::init()
{
    m_categories << "category0" << "category1" << "category2";
    m_barseries = new QStackedBarSeries();
    m_barseries->setCategories(m_categories);
    m_barseries_with_sets = new QStackedBarSeries();
    m_barseries_with_sets->setCategories(m_categories);

    for (int i=0; i<5; i++) {
        m_testSets.append(new QBarSet("testset"));
        m_barseries_with_sets->appendBarSet(m_testSets.at(i));
    }
}

void tst_QStackedBarSeries::cleanup()
{
    foreach(QBarSet* s, m_testSets) {
        m_barseries_with_sets->removeBarSet(s);
        delete s;
    }
    m_testSets.clear();

    delete m_barseries;
    m_barseries = 0;
    delete m_barseries_with_sets;
    m_barseries_with_sets = 0;
    m_categories.clear();
}

void tst_QStackedBarSeries::qstackedbarseries_data()
{
    QTest::addColumn<QBarCategories> ("categories");
    QBarCategories c;
    c << "category0" << "category1" << "category2";
    QTest::newRow("categories") << c;
}

void tst_QStackedBarSeries::qstackedbarseries()
{
    QFETCH(QBarCategories, categories);
    QStackedBarSeries *barseries = new QStackedBarSeries();
    QVERIFY(barseries != 0);
    barseries->setCategories(categories);
    QBarCategories verifyCategories = barseries->categories();

    QVERIFY(verifyCategories.count() == categories.count());
    for (int i=0; i<categories.count(); i++) {
        QVERIFY(verifyCategories.at(i).compare(categories.at(i)) == 0);
    }
}

void tst_QStackedBarSeries::type_data()
{

}

void tst_QStackedBarSeries::type()
{
    QVERIFY(m_barseries->type() == QAbstractSeries::SeriesTypeStackedBar);
}

void tst_QStackedBarSeries::setCategories_data()
{
    QTest::addColumn<QBarCategories> ("categories");
    QBarCategories categories;
    categories << "c1" << "c2" << "c3" << "c4" << "c5" << "c6";
    QTest::newRow("cat") << categories;
}

void tst_QStackedBarSeries::setCategories()
{
    QVERIFY(m_barseries->categories().count() == m_categories.count());

    QFETCH(QBarCategories, categories);
    m_barseries->setCategories(categories);

    QVERIFY(m_barseries->categories().count() == categories.count());
    for (int i=0; i<categories.count(); i++) {
        QVERIFY(m_barseries->categories().at(i).compare(categories.at(i)) == 0);
    }
}

void tst_QStackedBarSeries::appendBarSet_data()
{
}

void tst_QStackedBarSeries::appendBarSet()
{
    QVERIFY(m_barseries->barsetCount() == 0);

    QBarSet *barset = new QBarSet("testset");
    m_barseries->appendBarSet(barset);

    QVERIFY(m_barseries->barsetCount() == 1);

    QBarSet *barset2 = new QBarSet("testset2");
    m_barseries->appendBarSet(barset2);

    QVERIFY(m_barseries->barsetCount() == 2);
}

void tst_QStackedBarSeries::removeBarSet_data()
{
}

void tst_QStackedBarSeries::removeBarSet()
{
    int count = m_testSets.count();
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // remove some sets
    m_barseries_with_sets->removeBarSet(m_testSets.at(2));
    m_barseries_with_sets->removeBarSet(m_testSets.at(3));
    m_barseries_with_sets->removeBarSet(m_testSets.at(4));

    QVERIFY(m_barseries_with_sets->barsetCount() == 2);

    QList<QBarSet*> verifysets = m_barseries_with_sets->barSets();

    QVERIFY(verifysets.at(0) == m_testSets.at(0));
    QVERIFY(verifysets.at(1) == m_testSets.at(1));

    // Try removing all sets again
    for (int i=0; i<count; i++) {
        m_barseries_with_sets->removeBarSet(m_testSets.at(i));
    }

    QVERIFY(m_barseries_with_sets->barsetCount() == 0);
}

void tst_QStackedBarSeries::appendBarSets_data()
{

}

void tst_QStackedBarSeries::appendBarSets()
{
    int count = 5;
    QVERIFY(m_barseries->barsetCount() == 0);

    QList<QBarSet*> sets;
    for (int i=0; i<count; i++) {
        sets.append(new QBarSet("testset"));
    }

    m_barseries->appendBarSets(sets);
    QVERIFY(m_barseries->barsetCount() == count);
}

void tst_QStackedBarSeries::removeBarSets_data()
{

}

void tst_QStackedBarSeries::removeBarSets()
{
    int count = m_testSets.count();
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try removing empty list of sets
    QList<QBarSet*> empty;
    m_barseries_with_sets->removeBarSets(empty);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // remove all sets
    m_barseries_with_sets->removeBarSets(m_testSets);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);

    // Try removing empty list again
    m_barseries_with_sets->removeBarSets(empty);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);

    // remove all sets again
    m_barseries_with_sets->removeBarSets(m_testSets);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);
}

void tst_QStackedBarSeries::barsetCount_data()
{

}

void tst_QStackedBarSeries::barsetCount()
{
    QVERIFY(m_barseries->barsetCount() == 0);
    QVERIFY(m_barseries_with_sets->barsetCount() == m_testSets.count());
}

void tst_QStackedBarSeries::categoryCount_data()
{

}

void tst_QStackedBarSeries::categoryCount()
{
    QVERIFY(m_barseries->categoryCount() == m_categories.count());
    QVERIFY(m_barseries_with_sets->categoryCount() == m_categories.count());
}

void tst_QStackedBarSeries::barSets_data()
{

}

void tst_QStackedBarSeries::barSets()
{
    QVERIFY(m_barseries->barSets().count() == 0);

    QList<QBarSet*> sets = m_barseries_with_sets->barSets();
    QVERIFY(sets.count() == m_testSets.count());

    for (int i=0; i<m_testSets.count(); i++) {
        QVERIFY(sets.at(i) == m_testSets.at(i));
    }
}

void tst_QStackedBarSeries::categories_data()
{

}

void tst_QStackedBarSeries::categories()
{
    QBarCategories categories = m_barseries->categories();

    QVERIFY(categories.count() == m_categories.count());
    for (int i=0; i<m_categories.count(); i++) {
        QVERIFY(categories.at(i).compare(m_categories.at(i)) == 0);
    }
}

void tst_QStackedBarSeries::setLabelsVisible_data()
{

}

void tst_QStackedBarSeries::setLabelsVisible()
{
    foreach (QBarSet* s, m_testSets) {
        QVERIFY(s->labelsVisible() == false);
    }

    m_barseries_with_sets->setLabelsVisible(true);
    foreach (QBarSet* s, m_testSets) {
        QVERIFY(s->labelsVisible() == true);
    }

    m_barseries_with_sets->setLabelsVisible(false);
    foreach (QBarSet* s, m_testSets) {
        QVERIFY(s->labelsVisible() == false);
    }
}

/*
bool setModel(QAbstractItemModel *model);
void setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
void setModelMappingRange(int first, int count = -1);
*/
QTEST_MAIN(tst_QStackedBarSeries)

#include "tst_qstackedbarseries.moc"

