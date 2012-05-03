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
#include <qpieseries.h>
#include <qpieslice.h>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_qpieseries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void construction();
    void append();
    void insert();
    void remove();
    //void calculatedValues();
    //void themes();
    //void clickedSignal();
    //void hoverSignal();

private:


private:

};

void tst_qpieseries::initTestCase()
{
}

void tst_qpieseries::cleanupTestCase()
{
}

void tst_qpieseries::init()
{

}

void tst_qpieseries::cleanup()
{

}

void tst_qpieseries::construction()
{
    // verify default values
    QPieSeries s;
    QVERIFY(s.type() == QAbstractSeries::SeriesTypePie);
    QVERIFY(s.count() == 0);
    QVERIFY(s.isEmpty());
    QVERIFY(qFuzzyIsNull(s.sum()));
    QVERIFY(qFuzzyCompare(s.horizontalPosition(), 0.5));
    QVERIFY(qFuzzyCompare(s.verticalPosition(), 0.5));
    QVERIFY(qFuzzyCompare(s.pieSize(), 0.7));
    QVERIFY(qFuzzyIsNull(s.pieStartAngle()));
    QVERIFY(qFuzzyCompare(s.pieEndAngle(), 360));
}

void tst_qpieseries::append()
{
    QPieSeries s;

    // append pointer
    QPieSlice *slice1 = 0;
    QVERIFY(!s.append(slice1));
    slice1 = new QPieSlice(1, "slice 1");
    QVERIFY(s.append(slice1));
    QVERIFY(!s.append(slice1));
    QCOMPARE(s.count(), 1);

    // append pointer list
    QList<QPieSlice *> list;
    QVERIFY(!s.append(list));
    list << (QPieSlice *) 0;
    QVERIFY(!s.append(list));
    list.clear();
    list << new QPieSlice(2, "slice 2");
    list << new QPieSlice(3, "slice 3");
    QVERIFY(s.append(list));
    QVERIFY(!s.append(list));
    QCOMPARE(s.count(), 3);

    // append operator
    s << new QPieSlice(4, "slice 4");
    s << slice1; // fails because already added
    QCOMPARE(s.count(), 4);

    // append with params
    QPieSlice *slice5 = s.append(5, "slice 5");
    QVERIFY(slice5 != 0);
    QVERIFY(qFuzzyCompare(slice5->value(), 5.0));
    QCOMPARE(slice5->label(), QString("slice 5"));
    QCOMPARE(s.count(), 5);

    // check slices
    QVERIFY(!s.isEmpty());
    for (int i=0; i<s.count(); i++) {
        QVERIFY(qFuzzyCompare(s.slices().at(i)->value(), (qreal) i+1));
        QCOMPARE(s.slices().at(i)->label(), QString("slice ") + QString::number(i+1));
    }
}

void tst_qpieseries::insert()
{
    QPieSeries s;

    // insert one slice
    QPieSlice *slice1 = 0;
    QVERIFY(!s.insert(0, slice1));
    slice1 = new QPieSlice(1, "slice 1");
    QVERIFY(!s.insert(-1, slice1));
    QVERIFY(!s.insert(5, slice1));
    QVERIFY(s.insert(0, slice1));
    QVERIFY(!s.insert(0, slice1));
    QCOMPARE(s.count(), 1);

    // add some more slices
    s.append(2, "slice 2");
    s.append(4, "slice 4");
    QCOMPARE(s.count(), 3);

    // insert between slices
    s.insert(2, new QPieSlice(3, "slice 3"));
    QCOMPARE(s.count(), 4);

    // check slices
    for (int i=0; i<s.count(); i++) {
        QVERIFY(qFuzzyCompare(s.slices().at(i)->value(), (qreal) i+1));
        QCOMPARE(s.slices().at(i)->label(), QString("slice ") + QString::number(i+1));
    }
}

void tst_qpieseries::remove()
{
    QPieSeries s;

    // add some slices
    QPieSlice *slice1 = s.append(1, "slice 1");
    QPieSlice *slice2 = s.append(2, "slice 2");
    QPieSlice *slice3 = s.append(3, "slice 3");
    QSignalSpy spy1(slice1, SIGNAL(destroyed()));
    QSignalSpy spy2(slice2, SIGNAL(destroyed()));
    QSignalSpy spy3(slice3, SIGNAL(destroyed()));
    QCOMPARE(s.count(), 3);

    // null pointer remove
    QVERIFY(!s.remove(0));

    // remove first
    QVERIFY(s.remove(slice1));
    QVERIFY(!s.remove(slice1));
    QCOMPARE(s.count(), 2);
    QCOMPARE(s.slices().at(0)->label(), slice2->label());

    // remove all
    s.clear();
    QVERIFY(s.isEmpty());
    QVERIFY(s.slices().isEmpty());
    QCOMPARE(s.count(), 0);

    // check that slices were actually destroyed
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 1);
    TRY_COMPARE(spy3.count(), 1);
}

/*
void tst_qpieseries::calculatedValues()
{

}

void tst_qpieseries::themes()
{

}

void tst_qpieseries::clickedSignal()
{

}

void tst_qpieseries::hoverSignal()
{

}
*/

QTEST_MAIN(tst_qpieseries)

#include "tst_qpieseries.moc"

