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
#include <qbarset.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QBarSet : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qbarset_data();
    void qbarset();
    void name_data();
    void name();
    void append_data();
    void append();
    void appendOperator_data();
    void appendOperator();
    void insert_data();
    void insert();
    void remove_data();
    void remove();
    void replace_data();
    void replace();
    void at_data();
    void at();
    void atOperator_data();
    void atOperator();
    void count_data();
    void count();
    void sum_data();
    void sum();

private:

private:
    QBarSet* m_barset;
};

void tst_QBarSet::initTestCase()
{
}

void tst_QBarSet::cleanupTestCase()
{
}

void tst_QBarSet::init()
{
     m_barset = new QBarSet(QString("Name"));
}

void tst_QBarSet::cleanup()
{
    delete m_barset;
    m_barset = 0;
}

void tst_QBarSet::qbarset_data()
{
}

void tst_QBarSet::qbarset()
{
    QBarSet barset(QString("Name"));
    QCOMPARE(barset.name(), QString("Name"));
    QCOMPARE(barset.count(), 0);
    QVERIFY(qFuzzyIsNull(barset.sum()));
}

void tst_QBarSet::name_data()
{
    QTest::addColumn<QString> ("names");
    QTest::newRow("name0, name1") << QString("name0") << QString("name1");
}

void tst_QBarSet::name()
{
    QFETCH(QString, names);

    m_barset->setName(names);
    QCOMPARE(m_barset->name(), names);
}

void tst_QBarSet::append_data()
{
//    QTest::addColumn<QList<qreal> >("values");
//    QTest::newRow("0.0 1.0 2.0 3.0 4.0") << (QList<qreal>(0.0) << qreal(1.0) << qreal(2.0) << qreal(3.0) << qreal(4.0));
    QTest::addColumn<int> ("count");
    QTest::newRow("0 1 2 3 4") << 0 << 1 << 2 << 3 << 4;
}

void tst_QBarSet::append()
{
    QFETCH(int, count);

    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    qreal sum(0.0);
    qreal value(0.0);

    for (int i=0; i<count; i++) {
        m_barset->append(value);
        QCOMPARE(m_barset->at(i), value);
        sum += value;
        value += 1.0;
    }

    QCOMPARE(m_barset->count(), count);
    QVERIFY(qFuzzyCompare(m_barset->sum(), sum));
}

void tst_QBarSet::appendOperator_data()
{
    append_data();
}

void tst_QBarSet::appendOperator()
{
    QFETCH(int, count);

    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    qreal sum(0.0);
    qreal value(0.0);

    for (int i=0; i<count; i++) {
        *m_barset << value;
        QCOMPARE(m_barset->at(i), value);
        sum += value;
        value += 1.0;
    }

    QCOMPARE(m_barset->count(), count);
    QVERIFY(qFuzzyCompare(m_barset->sum(), sum));
}

void tst_QBarSet::insert_data()
{
    // TODO?
}

void tst_QBarSet::insert()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->insert(0, 1.0);       // 1.0
    QCOMPARE(m_barset->at(0), 1.0);
    QCOMPARE(m_barset->count(), 1);
    QCOMPARE(m_barset->sum(), 1.0);

    m_barset->insert(0, 2.0);       // 2.0 1.0
    QCOMPARE(m_barset->at(0), 2.0);
    QCOMPARE(m_barset->at(1), 1.0);
    QCOMPARE(m_barset->count(), 2);
    QCOMPARE(m_barset->sum(), 3.0);

    m_barset->insert(1, 3.0);       // 2.0 3.0 1.0
    QCOMPARE(m_barset->at(1), 3.0);
    QCOMPARE(m_barset->at(0), 2.0);
    QCOMPARE(m_barset->at(2), 1.0);
    QCOMPARE(m_barset->count(), 3);
    QCOMPARE(m_barset->sum(), 6.0);
}

void tst_QBarSet::remove_data()
{
    // TODO?
}

void tst_QBarSet::remove()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->count(), 4);
    QCOMPARE(m_barset->sum(), 10.0);

    m_barset->remove(2);                // 1.0 2.0 4.0
    QCOMPARE(m_barset->at(0), 1.0);
    QCOMPARE(m_barset->at(1), 2.0);
    QCOMPARE(m_barset->at(2), 4.0);
    QCOMPARE(m_barset->count(), 3);
    QCOMPARE(m_barset->sum(), 7.0);

    m_barset->remove(0);                // 2.0 4.0
    QCOMPARE(m_barset->at(0), 2.0);
    QCOMPARE(m_barset->at(1), 4.0);
    QCOMPARE(m_barset->count(), 2);
    QCOMPARE(m_barset->sum(), 6.0);
}

void tst_QBarSet::replace_data()
{

}

void tst_QBarSet::replace()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->count(), 4);
    QCOMPARE(m_barset->sum(), 10.0);

    m_barset->replace(0, 5.0);          // 5.0 2.0 3.0 4.0
    QCOMPARE(m_barset->count(), 4);
    QCOMPARE(m_barset->sum(), 14.0);
    QCOMPARE(m_barset->at(0), 5.0);

    m_barset->replace(3, 6.0);
    QCOMPARE(m_barset->count(), 4);     // 5.0 2.0 3.0 6.0
    QCOMPARE(m_barset->sum(), 16.0);
    QCOMPARE(m_barset->at(0), 5.0);
    QCOMPARE(m_barset->at(1), 2.0);
    QCOMPARE(m_barset->at(2), 3.0);
    QCOMPARE(m_barset->at(3), 6.0);
}

void tst_QBarSet::at_data()
{

}

void tst_QBarSet::at()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->at(0), 1.0);
    QCOMPARE(m_barset->at(1), 2.0);
    QCOMPARE(m_barset->at(2), 3.0);
    QCOMPARE(m_barset->at(3), 4.0);
}

void tst_QBarSet::atOperator_data()
{

}

void tst_QBarSet::atOperator()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    m_barset->append(2.0);
    m_barset->append(3.0);
    m_barset->append(4.0);

    QCOMPARE(m_barset->operator [](0), 1.0);
    QCOMPARE(m_barset->operator [](1), 2.0);
    QCOMPARE(m_barset->operator [](2), 3.0);
    QCOMPARE(m_barset->operator [](3), 4.0);
}

void tst_QBarSet::count_data()
{

}

void tst_QBarSet::count()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    QCOMPARE(m_barset->count(),1);
    m_barset->append(2.0);
    QCOMPARE(m_barset->count(),2);
    m_barset->append(3.0);
    QCOMPARE(m_barset->count(),3);
    m_barset->append(4.0);
    QCOMPARE(m_barset->count(),4);
}

void tst_QBarSet::sum_data()
{

}

void tst_QBarSet::sum()
{
    QCOMPARE(m_barset->count(), 0);
    QVERIFY(qFuzzyIsNull(m_barset->sum()));

    m_barset->append(1.0);
    QCOMPARE(m_barset->sum(),1.0);
    m_barset->append(2.0);
    QCOMPARE(m_barset->sum(),3.0);
    m_barset->append(3.0);
    QCOMPARE(m_barset->sum(),6.0);
    m_barset->append(4.0);
    QCOMPARE(m_barset->sum(),10.0);
}


QTEST_MAIN(tst_QBarSet)

#include "tst_qbarset.moc"

