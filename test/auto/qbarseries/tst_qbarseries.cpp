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
#include <qbarset.h>

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
    QBarSeries* m_barseries;
    QBarSeries* m_barseries_with_sets;

    QList<QBarSet*> m_testSets;

    QBarCategories m_categories;
};

void tst_QBarSeries::initTestCase()
{
}

void tst_QBarSeries::cleanupTestCase()
{
}

void tst_QBarSeries::init()
{
    m_categories << "category0" << "category1" << "category2";
    m_barseries = new QBarSeries();
    m_barseries->setCategories(m_categories);
    m_barseries_with_sets = new QBarSeries();
    m_barseries_with_sets->setCategories(m_categories);

    for (int i=0; i<5; i++) {
        m_testSets.append(new QBarSet("testset"));
        m_barseries_with_sets->appendBarSet(m_testSets.at(i));
    }
}

void tst_QBarSeries::cleanup()
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
    QBarSeries *barseries = new QBarSeries();
    QVERIFY(barseries != 0);
    barseries->setCategories(categories);
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

void tst_QBarSeries::setCategories_data()
{
    QTest::addColumn<QBarCategories> ("categories");
    QBarCategories categories;
    categories << "c1" << "c2" << "c3" << "c4" << "c5" << "c6";
    QTest::newRow("cat") << categories;
}

void tst_QBarSeries::setCategories()
{
    QVERIFY(m_barseries->categories().count() == m_categories.count());

    QFETCH(QBarCategories, categories);
    m_barseries->setCategories(categories);

    QVERIFY(m_barseries->categories().count() == categories.count());
    for (int i=0; i<categories.count(); i++) {
        QVERIFY(m_barseries->categories().at(i).compare(categories.at(i)) == 0);
    }
}

void tst_QBarSeries::appendBarSet_data()
{
}

void tst_QBarSeries::appendBarSet()
{
    QVERIFY(m_barseries->barsetCount() == 0);

    bool ret = false;

    // Try adding barset
    QBarSet *barset = new QBarSet("testset");
    ret = m_barseries->appendBarSet(barset);

    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == 1);

    // Try adding another set
    QBarSet *barset2 = new QBarSet("testset2");
    ret = m_barseries->appendBarSet(barset2);

    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == 2);

    // Try adding same set again
    ret = m_barseries->appendBarSet(barset2);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == 2);

    // Try adding null set
    ret = m_barseries->appendBarSet(0);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == 2);

}

void tst_QBarSeries::removeBarSet_data()
{
}

void tst_QBarSeries::removeBarSet()
{
    int count = m_testSets.count();
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try to remove null pointer (should not remove, should not crash)
    bool ret = false;
    ret = m_barseries_with_sets->removeBarSet(0);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try to remove invalid pointer (should not remove, should not crash)
    ret = m_barseries_with_sets->removeBarSet((QBarSet*) (m_testSets.at(0) + 1) );
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // remove some sets
    ret = m_barseries_with_sets->removeBarSet(m_testSets.at(2));
    QVERIFY(ret == true);
    ret = m_barseries_with_sets->removeBarSet(m_testSets.at(3));
    QVERIFY(ret == true);
    ret = m_barseries_with_sets->removeBarSet(m_testSets.at(4));
    QVERIFY(ret == true);

    QVERIFY(m_barseries_with_sets->barsetCount() == 2);

    QList<QBarSet*> verifysets = m_barseries_with_sets->barSets();

    QVERIFY(verifysets.at(0) == m_testSets.at(0));
    QVERIFY(verifysets.at(1) == m_testSets.at(1));

    // Try removing all sets again (should be ok, even if some sets have already been removed)
    ret = false;
    for (int i=0; i<count; i++) {
        ret |= m_barseries_with_sets->removeBarSet(m_testSets.at(i));
    }

    QVERIFY(ret == true);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);
}

void tst_QBarSeries::appendBarSets_data()
{

}

void tst_QBarSeries::appendBarSets()
{
    int count = 5;
    QVERIFY(m_barseries->barsetCount() == 0);

    QList<QBarSet*> sets;
    for (int i=0; i<count; i++) {
        sets.append(new QBarSet("testset"));
    }

    // Append new sets (should succeed, count should match the count of sets)
    bool ret = false;
    ret = m_barseries->appendBarSets(sets);
    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == count);

    // Append same sets again (should fail, count should remain same)
    ret = m_barseries->appendBarSets(sets);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == count);

    // Try append empty list (should succeed, but count should remain same)
    QList<QBarSet*> invalidList;
    ret = m_barseries->appendBarSets(invalidList);
    QVERIFY(ret == true);
    QVERIFY(m_barseries->barsetCount() == count);

    // Try append list with one new and one existing set (should fail, count remains same)
    invalidList.append(new QBarSet("ok set"));
    invalidList.append(sets.at(0));
    ret = m_barseries->appendBarSets(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == count);

    // Try append list with null pointers (should fail, count remains same)
    QList<QBarSet*> invalidList2;
    invalidList2.append(0);
    invalidList2.append(0);
    invalidList2.append(0);
    ret = m_barseries->appendBarSets(invalidList2);
    QVERIFY(ret == false);
    QVERIFY(m_barseries->barsetCount() == count);
}

void tst_QBarSeries::removeBarSets_data()
{

}

void tst_QBarSeries::removeBarSets()
{
    int count = m_testSets.count();
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Try removing empty list of sets (should return false, since no barsets were removed)
    bool ret = false;
    QList<QBarSet*> invalidList;
    ret = m_barseries_with_sets->removeBarSets(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // Add some null pointers to list
    invalidList.append(0);
    invalidList.append(0);
    invalidList.append(0);

    // Try removing null pointers from list (should return false, should not crash, should not remove anything)
    ret = m_barseries_with_sets->removeBarSets(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == count);

    // remove all sets (should return true, since sets were removed)
    ret = m_barseries_with_sets->removeBarSets(m_testSets);
    QVERIFY(ret == true);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);

    // Try removing invalid list again (should return false, since no barsets were removed)
    ret = m_barseries_with_sets->removeBarSets(invalidList);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);

    // remove all sets again (should return false, since barsets were already removed)
    ret = m_barseries_with_sets->removeBarSets(m_testSets);
    QVERIFY(ret == false);
    QVERIFY(m_barseries_with_sets->barsetCount() == 0);
}

void tst_QBarSeries::barsetCount_data()
{

}

void tst_QBarSeries::barsetCount()
{
    QVERIFY(m_barseries->barsetCount() == 0);
    QVERIFY(m_barseries_with_sets->barsetCount() == m_testSets.count());
}

void tst_QBarSeries::categoryCount_data()
{

}

void tst_QBarSeries::categoryCount()
{
    QVERIFY(m_barseries->categoryCount() == m_categories.count());
    QVERIFY(m_barseries_with_sets->categoryCount() == m_categories.count());
}

void tst_QBarSeries::barSets_data()
{

}

void tst_QBarSeries::barSets()
{
    QVERIFY(m_barseries->barSets().count() == 0);

    QList<QBarSet*> sets = m_barseries_with_sets->barSets();
    QVERIFY(sets.count() == m_testSets.count());

    for (int i=0; i<m_testSets.count(); i++) {
        QVERIFY(sets.at(i) == m_testSets.at(i));
    }
}

void tst_QBarSeries::categories_data()
{

}

void tst_QBarSeries::categories()
{
    QBarCategories categories = m_barseries->categories();

    QVERIFY(categories.count() == m_categories.count());
    for (int i=0; i<m_categories.count(); i++) {
        QVERIFY(categories.at(i).compare(m_categories.at(i)) == 0);
    }
}

void tst_QBarSeries::setLabelsVisible_data()
{

}

void tst_QBarSeries::setLabelsVisible()
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
QTEST_MAIN(tst_QBarSeries)

#include "tst_qbarseries.moc"

