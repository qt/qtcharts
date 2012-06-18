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
#include <qchartview.h>
#include <qchart.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include <qpiemodelmapper.h>
#include <QStandardItemModel>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QPieSlice*)
Q_DECLARE_METATYPE(QList<QPieSlice*>)

class tst_qpieseries : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void properties();
    void append();
    void appendAnimated();
    void insert();
    void insertAnimated();
    void remove();
    void removeAnimated();
    void calculatedValues();
    void clickedSignal();
    void hoverSignal();
    void sliceSeries();

private:
    void verifyCalculatedData(const QPieSeries &series, bool *ok);

private:
    QChartView *m_view;
    QPieSeries *m_series;
};

void tst_qpieseries::initTestCase()
{
    qRegisterMetaType<QPieSlice*>("QPieSlice*");
    qRegisterMetaType<QList<QPieSlice*> >("QList<QPieSlice*>");
}

void tst_qpieseries::cleanupTestCase()
{
}

void tst_qpieseries::init()
{
    m_view = new QChartView();
    m_series = new QPieSeries(m_view);
}

void tst_qpieseries::cleanup()
{
    delete m_view;
    m_view = 0;
    m_series = 0;
}

void tst_qpieseries::properties()
{
    QSignalSpy countSpy(m_series, SIGNAL(countChanged()));
    QSignalSpy sumSpy(m_series, SIGNAL(sumChanged()));

    QVERIFY(m_series->type() == QAbstractSeries::SeriesTypePie);
    QVERIFY(m_series->count() == 0);
    QVERIFY(m_series->isEmpty());
    QCOMPARE(m_series->sum(), 0.0);
    QCOMPARE(m_series->horizontalPosition(), 0.5);
    QCOMPARE(m_series->verticalPosition(), 0.5);
    QCOMPARE(m_series->pieSize(), 0.7);
    QCOMPARE(m_series->pieStartAngle(), 0.0);
    QCOMPARE(m_series->pieEndAngle(), 360.0);

    m_series->append("s1", 1);
    m_series->append("s2", 1);
    m_series->append("s3", 1);
    m_series->insert(1, new QPieSlice("s4", 1));
    m_series->remove(m_series->slices().first());
    QCOMPARE(m_series->count(), 3);
    QCOMPARE(m_series->sum(), 3.0);
    m_series->clear();
    QCOMPARE(m_series->count(), 0);
    QCOMPARE(m_series->sum(), 0.0);
    QCOMPARE(countSpy.count(), 6);
    QCOMPARE(sumSpy.count(), 6);

    m_series->setPieSize(-1.0);
    QCOMPARE(m_series->pieSize(), 0.0);
    m_series->setPieSize(0.0);
    m_series->setPieSize(0.9);
    m_series->setPieSize(2.0);
    QCOMPARE(m_series->pieSize(), 1.0);

    m_series->setPieStartAngle(0);
    m_series->setPieStartAngle(-180);
    m_series->setPieStartAngle(180);
    QCOMPARE(m_series->pieStartAngle(), 180.0);

    m_series->setPieEndAngle(360);
    m_series->setPieEndAngle(-180);
    m_series->setPieEndAngle(180);
    QCOMPARE(m_series->pieEndAngle(), 180.0);

    m_series->setHorizontalPosition(0.5);
    m_series->setHorizontalPosition(-1.0);
    QCOMPARE(m_series->horizontalPosition(), 0.0);
    m_series->setHorizontalPosition(1.0);
    m_series->setHorizontalPosition(2.0);
    QCOMPARE(m_series->horizontalPosition(), 1.0);

    m_series->setVerticalPosition(0.5);
    m_series->setVerticalPosition(-1.0);
    QCOMPARE(m_series->verticalPosition(), 0.0);
    m_series->setVerticalPosition(1.0);
    m_series->setVerticalPosition(2.0);
    QCOMPARE(m_series->verticalPosition(), 1.0);
}

void tst_qpieseries::append()
{
    m_view->chart()->addSeries(m_series);
    QSignalSpy addedSpy(m_series, SIGNAL(added(QList<QPieSlice*>)));

    // append pointer
    QPieSlice *slice1 = 0;
    QVERIFY(!m_series->append(slice1));
    slice1 = new QPieSlice("slice 1", 1);
    QVERIFY(m_series->append(slice1));
    QVERIFY(!m_series->append(slice1));
    QCOMPARE(m_series->count(), 1);
    QCOMPARE(addedSpy.count(), 1);
    QList<QPieSlice*> added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(0).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice1);

    // try to append same slice to another series
    QPieSeries series2;
    QVERIFY(!series2.append(slice1));

    // append pointer list
    QList<QPieSlice *> list;
    QVERIFY(!m_series->append(list));
    list << (QPieSlice *) 0;
    QVERIFY(!m_series->append(list));
    list.clear();
    list << new QPieSlice("slice 2", 2);
    list << new QPieSlice("slice 3", 3);
    QVERIFY(m_series->append(list));
    QVERIFY(!m_series->append(list));
    QCOMPARE(m_series->count(), 3);
    QCOMPARE(addedSpy.count(), 2);
    added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(1).at(0));
    QCOMPARE(added.count(), 2);
    QCOMPARE(added, list);

    // append operator
    QPieSlice *slice4 = new QPieSlice("slice 4", 4);
    *m_series << slice4;
    *m_series << slice1; // fails because already added
    QCOMPARE(m_series->count(), 4);
    QCOMPARE(addedSpy.count(), 3);
    added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(2).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice4);

    // append with params
    QPieSlice *slice5 = m_series->append("slice 5", 5);
    QVERIFY(slice5 != 0);
    QCOMPARE(slice5->value(), 5.0);
    QCOMPARE(slice5->label(), QString("slice 5"));
    QCOMPARE(m_series->count(), 5);
    QCOMPARE(addedSpy.count(), 4);
    added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(3).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice5);

    // check slices
    QVERIFY(!m_series->isEmpty());
    for (int i=0; i<m_series->count(); i++) {
        QCOMPARE(m_series->slices().at(i)->value(), (qreal) i+1);
        QCOMPARE(m_series->slices().at(i)->label(), QString("slice ") + QString::number(i+1));
    }
}

void tst_qpieseries::appendAnimated()
{
    m_view->chart()->setAnimationOptions(QChart::AllAnimations);
}

void tst_qpieseries::insert()
{
    m_view->chart()->addSeries(m_series);
    QSignalSpy addedSpy(m_series, SIGNAL(added(QList<QPieSlice*>)));

    // insert one slice
    QPieSlice *slice1 = 0;
    QVERIFY(!m_series->insert(0, slice1));
    slice1 = new QPieSlice("slice 1", 1);
    QVERIFY(!m_series->insert(-1, slice1));
    QVERIFY(!m_series->insert(5, slice1));
    QVERIFY(m_series->insert(0, slice1));
    QVERIFY(!m_series->insert(0, slice1));
    QCOMPARE(m_series->count(), 1);
    QCOMPARE(addedSpy.count(), 1);
    QList<QPieSlice*> added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(0).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice1);

    // try to insert same slice to another series
    QPieSeries series2;
    QVERIFY(!series2.insert(0, slice1));

    // add some more slices
    QPieSlice *slice2 = m_series->append("slice 2", 2);
    QPieSlice *slice4 = m_series->append("slice 4", 4);
    QCOMPARE(m_series->count(), 3);
    QCOMPARE(addedSpy.count(), 3);
    added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(1).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice2);
    added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(2).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice4);

    // insert between slices
    QPieSlice *slice3 = new QPieSlice("slice 3", 3);
    m_series->insert(2, slice3);
    QCOMPARE(m_series->count(), 4);
    QCOMPARE(addedSpy.count(), 4);
    added = qvariant_cast<QList<QPieSlice*> >(addedSpy.at(3).at(0));
    QCOMPARE(added.count(), 1);
    QCOMPARE(added.first(), slice3);

    // check slices
    for (int i=0; i<m_series->count(); i++) {
        QCOMPARE(m_series->slices().at(i)->value(), (qreal) i+1);
        QCOMPARE(m_series->slices().at(i)->label(), QString("slice ") + QString::number(i+1));
    }
}

void tst_qpieseries::insertAnimated()
{
    m_view->chart()->setAnimationOptions(QChart::AllAnimations);
}

void tst_qpieseries::remove()
{
    m_view->chart()->addSeries(m_series);
    QSignalSpy removedSpy(m_series, SIGNAL(removed(QList<QPieSlice*>)));

    // add some slices
    QPieSlice *slice1 = m_series->append("slice 1", 1);
    QPieSlice *slice2 = m_series->append("slice 2", 2);
    QPieSlice *slice3 = m_series->append("slice 3", 3);
    QSignalSpy spy1(slice1, SIGNAL(destroyed()));
    QSignalSpy spy2(slice2, SIGNAL(destroyed()));
    QSignalSpy spy3(slice3, SIGNAL(destroyed()));
    QCOMPARE(m_series->count(), 3);

    // null pointer remove
    QVERIFY(!m_series->remove(0));

    // remove first
    QVERIFY(m_series->remove(slice1));
    QVERIFY(!m_series->remove(slice1));
    QCOMPARE(m_series->count(), 2);
    QCOMPARE(m_series->slices().at(0)->label(), slice2->label());
    QCOMPARE(removedSpy.count(), 1);
    QList<QPieSlice*> removed = qvariant_cast<QList<QPieSlice*> >(removedSpy.at(0).at(0));
    QCOMPARE(removed.count(), 1);
    QCOMPARE(removed.first(), slice1);

    // remove all
    m_series->clear();
    QVERIFY(m_series->isEmpty());
    QVERIFY(m_series->slices().isEmpty());
    QCOMPARE(m_series->count(), 0);
    QCOMPARE(removedSpy.count(), 2);
    removed = qvariant_cast<QList<QPieSlice*> >(removedSpy.at(1).at(0));
    QCOMPARE(removed.count(), 2);
    QCOMPARE(removed.first(), slice2);
    QCOMPARE(removed.last(), slice3);

    // check that slices were actually destroyed
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 1);
    TRY_COMPARE(spy3.count(), 1);
}

void tst_qpieseries::removeAnimated()
{
    m_view->chart()->setAnimationOptions(QChart::AllAnimations);
}

void tst_qpieseries::calculatedValues()
{
    m_view->chart()->addSeries(m_series);

    QPieSlice *slice1 = new QPieSlice("slice 1", 1);
    QSignalSpy percentageSpy(slice1, SIGNAL(percentageChanged()));
    QSignalSpy startAngleSpy(slice1, SIGNAL(startAngleChanged()));
    QSignalSpy angleSpanSpy(slice1, SIGNAL(angleSpanChanged()));

    // add a slice
    m_series->append(slice1);
    bool ok;
    verifyCalculatedData(*m_series, &ok);
    if (!ok)
        return;
    QCOMPARE(percentageSpy.count(), 1);
    QCOMPARE(startAngleSpy.count(), 0);
    QCOMPARE(angleSpanSpy.count(), 1);

    // add some more slices
    QList<QPieSlice *> list;
    list << new QPieSlice("slice 2", 2);
    list << new QPieSlice("slice 3", 3);
    m_series->append(list);
    verifyCalculatedData(*m_series, &ok);
    if (!ok)
        return;
    QCOMPARE(percentageSpy.count(), 2);
    QCOMPARE(startAngleSpy.count(), 0);
    QCOMPARE(angleSpanSpy.count(), 2);

    // remove a slice
    m_series->remove(list.first()); // remove slice 2
    verifyCalculatedData(*m_series, &ok);
    if (!ok)
        return;
    QCOMPARE(percentageSpy.count(), 3);
    QCOMPARE(startAngleSpy.count(), 0);
    QCOMPARE(angleSpanSpy.count(), 3);

    // insert a slice
    m_series->insert(0, new QPieSlice("Slice 4", 4));
    verifyCalculatedData(*m_series, &ok);
    if (!ok)
        return;
    QCOMPARE(percentageSpy.count(), 4);
    QCOMPARE(startAngleSpy.count(), 1);
    QCOMPARE(angleSpanSpy.count(), 4);

    // modify pie angles
    m_series->setPieStartAngle(-90);
    m_series->setPieEndAngle(90);
    verifyCalculatedData(*m_series, &ok);
    if (!ok)
        return;
    QCOMPARE(percentageSpy.count(), 4);
    QCOMPARE(startAngleSpy.count(), 3);
    QCOMPARE(angleSpanSpy.count(), 6);

    // clear all
    m_series->clear();
    verifyCalculatedData(*m_series, &ok);
    if (!ok)
        return;
    QCOMPARE(percentageSpy.count(), 4);
    QCOMPARE(startAngleSpy.count(), 3);
    QCOMPARE(angleSpanSpy.count(), 6);
}

void tst_qpieseries::verifyCalculatedData(const QPieSeries &series, bool *ok)
{
    *ok = false;

    qreal sum = 0;
    foreach (const QPieSlice *slice, series.slices())
        sum += slice->value();
    QCOMPARE(series.sum(), sum);

    qreal startAngle = series.pieStartAngle();
    qreal pieAngleSpan = series.pieEndAngle() - series.pieStartAngle();
    foreach (const QPieSlice *slice, series.slices()) {
        qreal ratio = slice->value() / sum;
        qreal sliceSpan = pieAngleSpan * ratio;
        QCOMPARE(slice->startAngle(), startAngle);
        QCOMPARE(slice->angleSpan(), sliceSpan);
        QCOMPARE(slice->percentage(), ratio);
        startAngle += sliceSpan;
    }

    if (!series.isEmpty())
        QCOMPARE(series.slices().last()->startAngle() + series.slices().last()->angleSpan(), series.pieEndAngle());

    *ok = true;
}


void tst_qpieseries::clickedSignal()
{
    // add some slices
    QPieSlice *s1 = m_series->append("slice 1", 1);
    QPieSlice *s2 = m_series->append("slice 2", 1);
    QPieSlice *s3 = m_series->append("slice 3", 1);
    QPieSlice *s4 = m_series->append("slice 4", 1);
    QSignalSpy clickSpy(m_series, SIGNAL(clicked(QPieSlice*)));

    // add series to the chart
    m_view->chart()->legend()->setVisible(false);
    m_view->resize(200, 200);
    m_view->chart()->addSeries(m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    // if you devide the chart in four equal tiles these
    // are the center points of those tiles
    QPoint p1(90.25, 90);
    QPoint p2(150, 90);
    QPoint p3(90, 150);
    QPoint p4(150, 150);

    QPoint center(120, 120);

    m_series->setPieSize(1.0);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 5); // all hit
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(0).at(0)), s4);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(1).at(0)), s1);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(2).at(0)), s3);
    QCOMPARE(qvariant_cast<QPieSlice*>(clickSpy.at(3).at(0)), s2);
    clickSpy.clear();

    m_series->setPieSize(0.5);
    m_series->setVerticalPosition(0.25);
    m_series->setHorizontalPosition(0.25);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p1); // hits
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();

    m_series->setVerticalPosition(0.25);
    m_series->setHorizontalPosition(0.75);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p2); // hits
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();

    m_series->setVerticalPosition(0.75);
    m_series->setHorizontalPosition(0.25);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p3); // hits
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p4);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();

    m_series->setVerticalPosition(0.75);
    m_series->setHorizontalPosition(0.75);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p1);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p2);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p3);
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, p4); // hits
    QTest::mouseClick(m_view->viewport(), Qt::LeftButton, 0, center);
    TRY_COMPARE(clickSpy.count(), 1);
    clickSpy.clear();
}

void tst_qpieseries::hoverSignal()
{
    // add some slices
    m_series->setPieSize(1.0);
    QPieSlice *s1 = m_series->append("slice 1", 1);
    m_series->append("slice 2", 2);
    m_series->append("slice 3", 3);

    // add series to the chart
    m_view->chart()->legend()->setVisible(false);
    m_view->resize(200, 200);
    m_view->chart()->addSeries(m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);

    // first move to right top corner
    QTest::mouseMove(m_view->viewport(), QPoint(200, 0));
    QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    // move inside the slice
    // pie rectangle: QRectF(60,60 121x121)
    QSignalSpy hoverSpy(m_series, SIGNAL(hovered(QPieSlice*,bool)));
    QTest::mouseMove(m_view->viewport(), QPoint(139, 85));
    TRY_COMPARE(hoverSpy.count(), 1);
    QCOMPARE(qvariant_cast<QPieSlice*>(hoverSpy.at(0).at(0)), s1);
    QCOMPARE(qvariant_cast<bool>(hoverSpy.at(0).at(1)), true);

    // move outside the slice
    QTest::mouseMove(m_view->viewport(), QPoint(200, 0));
    TRY_COMPARE(hoverSpy.count(), 2);
    QCOMPARE(qvariant_cast<QPieSlice*>(hoverSpy.at(1).at(0)), s1);
    QCOMPARE(qvariant_cast<bool>(hoverSpy.at(1).at(1)), false);
}

void tst_qpieseries::sliceSeries()
{
    QPieSlice *slice = new QPieSlice();
    QVERIFY(!slice->series());
    delete slice;

    slice = new QPieSlice(m_series);
    QVERIFY(!slice->series());

    m_series->append(slice);
    QCOMPARE(slice->series(), m_series);

    slice = new QPieSlice();
    m_series->insert(0, slice);
    QCOMPARE(slice->series(), m_series);
}

QTEST_MAIN(tst_qpieseries)

#include "tst_qpieseries.moc"

