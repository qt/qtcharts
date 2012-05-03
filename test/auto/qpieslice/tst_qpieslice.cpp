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
#include <qpieslice.h>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_qpieslice : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void construction();
    void changedSignals();

private:


private:

};

void tst_qpieslice::initTestCase()
{
}

void tst_qpieslice::cleanupTestCase()
{
}

void tst_qpieslice::init()
{

}

void tst_qpieslice::cleanup()
{

}

void tst_qpieslice::construction()
{
    // no params
    QPieSlice slice1;
    QVERIFY(qFuzzyIsNull(slice1.value()));
    QVERIFY(slice1.label().isEmpty());
    QVERIFY(!slice1.isLabelVisible());
    QVERIFY(!slice1.isExploded());
    QCOMPARE(slice1.pen(), QPen());
    QCOMPARE(slice1.brush(), QBrush());
    QCOMPARE(slice1.labelPen(), QPen());
    QCOMPARE(slice1.labelFont(), QFont());
    QVERIFY(qFuzzyCompare(slice1.labelArmLengthFactor(), 0.15)); // default value
    QVERIFY(qFuzzyCompare(slice1.explodeDistanceFactor(), 0.15)); // default value
    QVERIFY(qFuzzyIsNull(slice1.percentage()));
    QVERIFY(qFuzzyIsNull(slice1.startAngle()));
    QVERIFY(qFuzzyIsNull(slice1.endAngle()));

    // value and label params
    QPieSlice slice2(1.0, "foobar");
    QVERIFY(qFuzzyCompare(slice2.value(), 1.0));
    QCOMPARE(slice2.label(), QString("foobar"));
    QVERIFY(!slice2.isLabelVisible());
    QVERIFY(!slice2.isExploded());
    QCOMPARE(slice2.pen(), QPen());
    QCOMPARE(slice2.brush(), QBrush());
    QCOMPARE(slice2.labelPen(), QPen());
    QCOMPARE(slice2.labelFont(), QFont());
    QVERIFY(qFuzzyCompare(slice2.labelArmLengthFactor(), 0.15)); // default value
    QVERIFY(qFuzzyCompare(slice2.explodeDistanceFactor(), 0.15)); // default value
    QVERIFY(qFuzzyIsNull(slice2.percentage()));
    QVERIFY(qFuzzyIsNull(slice2.startAngle()));
    QVERIFY(qFuzzyIsNull(slice2.endAngle()));
}

void tst_qpieslice::changedSignals()
{
    // set everything twice to see we do not get unnecessary signals
    QPieSlice slice;
    QSignalSpy spy(&slice, SIGNAL(changed())); // TODO: this will be changed to something more refined
    slice.setValue(1);
    slice.setValue(1);
    slice.setLabel("foobar");
    slice.setLabel("foobar");
    slice.setLabelVisible();
    slice.setLabelVisible();
    slice.setExploded();
    slice.setExploded();
    slice.setPen(QPen(Qt::red));
    slice.setPen(QPen(Qt::red));
    slice.setBrush(QBrush(Qt::red));
    slice.setBrush(QBrush(Qt::red));
    slice.setLabelPen(QPen(Qt::green));
    slice.setLabelPen(QPen(Qt::green));
    slice.setLabelFont(QFont("Tahoma"));
    slice.setLabelFont(QFont("Tahoma"));
    slice.setLabelArmLengthFactor(0.1);
    slice.setLabelArmLengthFactor(0.1);
    slice.setExplodeDistanceFactor(0.1);
    slice.setExplodeDistanceFactor(0.1);
    TRY_COMPARE(spy.count(), 10);
}

QTEST_MAIN(tst_qpieslice)

#include "tst_qpieslice.moc"

