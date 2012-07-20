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

#include "../qabstractaxis/tst_qabstractaxis.h"
#include <qbarseries.h>
#include <qbarset.h>
#include <qbarcategoriesaxis.h>

class tst_QBarCategoriesAxis: public tst_QAbstractAxis
{
Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qbarcategoriesaxis_data();
    void qbarcategoriesaxis();

    void append_data();
    void append();
    void at_data();
    void at();
    void categories_data();
    void categories();
    void clear_data();
    void clear();
    void count_data();
    void count();
    void insert_data();
    void insert();
    void max_data();
    void max();
    void min_data();
    void min();
    void remove_data();
    void remove();
    void setCategories_data();
    void setCategories();
    void setMax_data();
    void setMax();
    void setMin_data();
    void setMin();
    void setRange_data();
    void setRange();
    void type_data();
    void type();
    void categoriesChanged_data();
    void categoriesChanged();
    void maxChanged_data();
    void maxChanged();
    void minChanged_data();
    void minChanged();
    void rangeChanged_data();
    void rangeChanged();
private:
    QBarCategoriesAxis* m_baraxis;
    QBarSeries* m_series;
};

void tst_QBarCategoriesAxis::initTestCase()
{
}

void tst_QBarCategoriesAxis::cleanupTestCase()
{
}

void tst_QBarCategoriesAxis::init()
{
    m_baraxis = new QBarCategoriesAxis();
    m_series = new QBarSeries();

    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    m_series->append(set0);
    m_series->append(set1);
    m_series->append(set2);
    m_series->append(set3);
    m_series->append(set4);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";

    m_baraxis->append(categories);

    tst_QAbstractAxis::init(m_baraxis, m_series);
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}

void tst_QBarCategoriesAxis::cleanup()
{
    delete m_series;
    delete m_baraxis;
    m_series = 0;
    m_baraxis = 0;
    tst_QAbstractAxis::cleanup();
}

void tst_QBarCategoriesAxis::qbarcategoriesaxis_data()
{
}

void tst_QBarCategoriesAxis::qbarcategoriesaxis()
{
    qabstractaxis();
    QBarCategoriesAxis axis;
    axis.append(QStringList());
    axis.append(QString());
    QCOMPARE(axis.at(0), QString());
    QStringList test;
    test.append(QString());
    QCOMPARE(axis.categories(),test);
    axis.clear();
    QCOMPARE(axis.count(), 0);
    axis.insert(-1, QString());
    QCOMPARE(axis.max(), QString());
    QCOMPARE(axis.min(), QString());
    axis.remove(QString());
    axis.setCategories(QStringList());
    axis.setMax(QString());
    axis.setMin(QString());
    axis.setRange(QString(), QString());
    QCOMPARE(axis.type(), QAbstractAxis::AxisTypeCategories);
}

void tst_QBarCategoriesAxis::append_data()
{
    QTest::addColumn<QStringList>("categories");
    QTest::newRow("null") << QStringList();
}

// public void append(QStringList const& categories)
void tst_QBarCategoriesAxis::append()
{
#if 0
    QFETCH(QStringList, categories);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.append(categories);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::at_data()
{
    QTest::addColumn<int>("index");
    QTest::addColumn<QString>("at");
    QTest::newRow("null") << 0 << QString();
}

// public QString at(int index) const
void tst_QBarCategoriesAxis::at()
{
#if 0
    QFETCH(int, index);
    QFETCH(QString, at);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    QCOMPARE(axis.at(index), at);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::categories_data()
{
    QTest::addColumn<QStringList>("categories");
    QTest::newRow("null") << QStringList();
}

// public QStringList categories()
void tst_QBarCategoriesAxis::categories()
{
#if 0
    QFETCH(QStringList, categories);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    QCOMPARE(axis.categories(), categories);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::clear_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void clear()
void tst_QBarCategoriesAxis::clear()
{
#if 0
    QFETCH(int, foo);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.clear();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::count_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public int count() const
void tst_QBarCategoriesAxis::count()
{
#if 0
    QFETCH(int, count);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    QCOMPARE(axis.count(), count);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::insert_data()
{
    QTest::addColumn<int>("index");
    QTest::addColumn<QString>("category");
    QTest::newRow("null") << 0 << QString();
}

// public void insert(int index, QString const& category)
void tst_QBarCategoriesAxis::insert()
{
#if 0
    QFETCH(int, index);
    QFETCH(QString, category);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.insert(index, category);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::max_data()
{
    QTest::addColumn<QString>("max");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public QString max() const
void tst_QBarCategoriesAxis::max()
{
#if 0
    QFETCH(QString, max);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    QCOMPARE(axis.max(), max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::min_data()
{
    QTest::addColumn<QString>("min");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public QString min() const
void tst_QBarCategoriesAxis::min()
{
#if 0
    QFETCH(QString, min);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    QCOMPARE(axis.min(), min);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::remove_data()
{
    QTest::addColumn<QString>("category");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public void remove(QString const& category)
void tst_QBarCategoriesAxis::remove()
{
#if 0
    QFETCH(QString, category);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.remove(category);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::setCategories_data()
{
    QTest::addColumn<QStringList>("categories");
    QTest::newRow("null") << QStringList();
}

// public void setCategories(QStringList const& categories)
void tst_QBarCategoriesAxis::setCategories()
{
#if 0
    QFETCH(QStringList, categories);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.setCategories(categories);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::setMax_data()
{
    QTest::addColumn<QString>("maxCategory");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public void setMax(QString const& maxCategory)
void tst_QBarCategoriesAxis::setMax()
{
#if 0
    QFETCH(QString, maxCategory);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.setMax(maxCategory);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::setMin_data()
{
    QTest::addColumn<QString>("minCategory");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// public void setMin(QString const& minCategory)
void tst_QBarCategoriesAxis::setMin()
{
#if 0
    QFETCH(QString, minCategory);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.setMin(minCategory);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::setRange_data()
{
    QTest::addColumn<QString>("minCategory");
    QTest::addColumn<QString>("maxCategory");
    QTest::newRow("null") << QString() << QString();
}

// public void setRange(QString const& minCategory, QString const& maxCategory)
void tst_QBarCategoriesAxis::setRange()
{
#if 0
    QFETCH(QString, minCategory);
    QFETCH(QString, maxCategory);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.setRange(minCategory, maxCategory);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::type_data()
{
#if 0
    QTest::addColumn<AxisType>("type");
    QTest::newRow("null") << AxisType();
#endif
}

// public AxisType type() const
void tst_QBarCategoriesAxis::type()
{
#if 0
    QFETCH(AxisType, type);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    QCOMPARE(axis.type(), type);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::categoriesChanged_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// protected void categoriesChanged()
void tst_QBarCategoriesAxis::categoriesChanged()
{
#if 0
    QFETCH(int, foo);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.call_categoriesChanged();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::maxChanged_data()
{
    QTest::addColumn<QString>("max");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// protected void maxChanged(QString const& max)
void tst_QBarCategoriesAxis::maxChanged()
{
#if 0
    QFETCH(QString, max);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.call_maxChanged(max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::minChanged_data()
{
    QTest::addColumn<QString>("min");
    QTest::newRow("null") << QString();
    QTest::newRow("foo") << QString("foo");
}

// protected void minChanged(QString const& min)
void tst_QBarCategoriesAxis::minChanged()
{
#if 0
    QFETCH(QString, min);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.call_minChanged(min);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QBarCategoriesAxis::rangeChanged_data()
{
    QTest::addColumn<QString>("min");
    QTest::addColumn<QString>("max");
    QTest::newRow("null") << QString() << QString();
}

// protected void rangeChanged(QString const& min, QString const& max)
void tst_QBarCategoriesAxis::rangeChanged()
{
#if 0
    QFETCH(QString, min);
    QFETCH(QString, max);

    SubQBarCategoriesAxis axis;

    QSignalSpy spy0(&axis, SIGNAL(categoriesChanged()));
    QSignalSpy spy1(&axis, SIGNAL(maxChanged(QString const&)));
    QSignalSpy spy2(&axis, SIGNAL(minChanged(QString const&)));
    QSignalSpy spy3(&axis, SIGNAL(rangeChanged(QString const&, QString const&)));

    axis.call_rangeChanged(min, max);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

QTEST_MAIN(tst_QBarCategoriesAxis)
#include "tst_qbarcategoriesaxis.moc"

