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
#include <private/domain_p.h>
#include <qaxis.h>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(Domain*)
Q_DECLARE_METATYPE(QSizeF)

class tst_Domain: public QObject
{
Q_OBJECT

public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private Q_SLOTS:
    void domain();
    void handleAxisRangeXChanged_data();
    void handleAxisRangeXChanged();
    void handleAxisRangeYChanged_data();
    void handleAxisRangeYChanged();
    void isEmpty_data();
    void isEmpty();
    void maxX_data();
    void maxX();
    void maxY_data();
    void maxY();
    void minX_data();
    void minX();
    void minY_data();
    void minY();
    void operatorEquals_data();
    void operatorEquals();
    void setRange_data();
    void setRange();
    void setRangeX_data();
    void setRangeX();
    void setRangeY_data();
    void setRangeY();
    void spanX_data();
    void spanX();
    void spanY_data();
    void spanY();
    void zoom_data();
    void zoom();
    void move_data();
    void move();
    void handleAxisXChanged_data();
    void handleAxisXChanged();
    void handleAxisYChanged_data();
    void handleAxisYChanged();
};

void tst_Domain::initTestCase()
{
}

void tst_Domain::cleanupTestCase()
{
}

void tst_Domain::init()
{
}

void tst_Domain::cleanup()
{
}

void tst_Domain::domain()
{
    Domain domain;

    QCOMPARE(domain.isEmpty(), true);
    QCOMPARE(domain.maxX(), 0.0);
    QCOMPARE(domain.maxY(), 0.0);
    QCOMPARE(domain.minX(), 0.0);
    QCOMPARE(domain.minY(), 0.0);
}

void tst_Domain::handleAxisRangeXChanged_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("-1 1") << -1.0 << 1.0;
    QTest::newRow("0 1") << 0.0 << 1.0;
    QTest::newRow("-1 0") << -1.0 << 0.0;
}

void tst_Domain::handleAxisRangeXChanged()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.handleAxisXChanged(min, max);

    QList<QVariant> arg0 = spy0.first();
    QVERIFY(qFuzzyIsNull(arg0.at(0).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg0.at(1).toReal() - max));

    QList<QVariant> arg1 = spy1.first();
    QVERIFY(qFuzzyIsNull(arg1.at(0).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg1.at(1).toReal() - max));

    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 0);

}

void tst_Domain::handleAxisRangeYChanged_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("-1 1") << -1.0 << 1.0;
    QTest::newRow("0 1") << 0.0 << 1.0;
    QTest::newRow("-1 0") << -1.0 << 0.0;
}

void tst_Domain::handleAxisRangeYChanged()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.handleAxisYChanged(min, max, 5);

    QList<QVariant> arg0 = spy0.first();
    QVERIFY(qFuzzyIsNull(arg0.at(2).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg0.at(3).toReal() - max));

    QList<QVariant> arg1 = spy2.first();
    QVERIFY(qFuzzyIsNull(arg1.at(0).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg1.at(1).toReal() - max));

    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 1);
}

void tst_Domain::isEmpty_data()
{
    QTest::addColumn<qreal>("minX");
    QTest::addColumn<qreal>("maxX");
    QTest::addColumn<qreal>("minY");
    QTest::addColumn<qreal>("maxY");
    QTest::addColumn<bool>("isEmpty");
    QTest::newRow("0 0 0 0") << 0.0 << 0.0 << 0.0 << 0.0 << true;
    QTest::newRow("0 1 0 0") << 0.0 << 1.0 << 0.0 << 0.0 << true;
    QTest::newRow("0 0 0 1") << 0.0 << 1.0 << 0.0 << 0.0 << true;
    QTest::newRow("0 1 0 1") << 0.0 << 1.0 << 0.0 << 1.0 << false;
}

void tst_Domain::isEmpty()
{
    QFETCH(qreal, minX);
    QFETCH(qreal, maxX);
    QFETCH(qreal, minY);
    QFETCH(qreal, maxY);
    QFETCH(bool, isEmpty);

    Domain domain;
    domain.setRange(minX, maxX, minY, maxY);
    QCOMPARE(domain.isEmpty(), isEmpty);
}

void tst_Domain::maxX_data()
{
    QTest::addColumn<qreal>("maxX1");
    QTest::addColumn<qreal>("maxX2");
    QTest::addColumn<int>("count");
    QTest::newRow("1") << 0.0 << 1.0 << 1;
    QTest::newRow("1.0") << 1.0 << 1.0 << 1;
    QTest::newRow("2.0") << 1.0 << 0.0 << 2;
}

void tst_Domain::maxX()
{
    QFETCH(qreal, maxX1);
    QFETCH(qreal, maxX2);
    QFETCH(int, count);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setMaxX(maxX1);
    QCOMPARE(domain.maxX(), maxX1);
    domain.setMaxX(maxX2);
    QCOMPARE(domain.maxX(), maxX2);

    TRY_COMPARE(spy0.count(), count);
    TRY_COMPARE(spy1.count(), count);
    TRY_COMPARE(spy2.count(), 0);

}

void tst_Domain::maxY_data()
{
    QTest::addColumn<qreal>("maxY1");
    QTest::addColumn<qreal>("maxY2");
    QTest::addColumn<int>("count");
    QTest::newRow("1") << 0.0 << 1.0 << 1;
    QTest::newRow("1.0") << 1.0 << 1.0 << 1;
    QTest::newRow("2.0") << 1.0 << 0.0 << 2;
}

void tst_Domain::maxY()
{
    QFETCH(qreal, maxY1);
    QFETCH(qreal, maxY2);
    QFETCH(int, count);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setMaxY(maxY1);
    QCOMPARE(domain.maxY(), maxY1);
    domain.setMaxY(maxY2);
    QCOMPARE(domain.maxY(), maxY2);

    TRY_COMPARE(spy0.count(), count);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), count);
}

void tst_Domain::minX_data()
{
    QTest::addColumn<qreal>("minX1");
    QTest::addColumn<qreal>("minX2");
    QTest::addColumn<int>("count");
    QTest::newRow("1") << 0.0 << 1.0 << 1;
    QTest::newRow("1.0") << 1.0 << 1.0 << 1;
    QTest::newRow("2.0") << 1.0 << 0.0 << 2;
}

void tst_Domain::minX()
{
    QFETCH(qreal, minX1);
    QFETCH(qreal, minX2);
    QFETCH(int, count);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setMinX(minX1);
    QCOMPARE(domain.minX(), minX1);
    domain.setMinX(minX2);
    QCOMPARE(domain.minX(), minX2);

    TRY_COMPARE(spy0.count(), count);
    TRY_COMPARE(spy1.count(), count);
    TRY_COMPARE(spy2.count(), 0);
}

void tst_Domain::minY_data()
{
    QTest::addColumn<qreal>("minY1");
    QTest::addColumn<qreal>("minY2");
    QTest::addColumn<int>("count");
    QTest::newRow("1") << 0.0 << 1.0 << 1;
    QTest::newRow("1.0") << 1.0 << 1.0 << 1;
    QTest::newRow("2.0") << 1.0 << 0.0 << 2;
}

void tst_Domain::minY()
{
    QFETCH(qreal, minY1);
    QFETCH(qreal, minY2);
    QFETCH(int, count);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setMinY(minY1);
    QCOMPARE(domain.minY(), minY1);
    domain.setMinY(minY2);
    QCOMPARE(domain.minY(), minY2);

    TRY_COMPARE(spy0.count(), count);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), count);
}

void tst_Domain::operatorEquals_data()
{

    QTest::addColumn<Domain*>("domain1");
    QTest::addColumn<Domain*>("domain2");
    QTest::addColumn<bool>("equals");
    QTest::addColumn<bool>("notEquals");
    Domain* a;
    Domain* b;
    a = new Domain();
    a->setRange(0, 100, 0, 100);
    b = new Domain();
    b->setRange(0, 100, 0, 100);
    QTest::newRow("equals") << a << b << true << false;
    a = new Domain();
    a->setRange(0, 100, 0, 100);
    b = new Domain();
    b->setRange(0, 100, 0, 1);
    QTest::newRow("equals") << a << b << false << true;
    a = new Domain();
    a->setRange(0, 100, 0, 100);
    b = new Domain();
    b->setRange(0, 1, 0, 100);
    QTest::newRow("equals") << a << b << false << true;

}

void tst_Domain::operatorEquals()
{
    QFETCH(Domain*, domain1);
    QFETCH(Domain*, domain2);
    QFETCH(bool, equals);
    QFETCH(bool, notEquals);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    QCOMPARE(*domain1==*domain2, equals);
    QCOMPARE(*domain1!=*domain2, notEquals);

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 0);
}

void tst_Domain::setRange_data()
{
    QTest::addColumn<qreal>("minX");
    QTest::addColumn<qreal>("maxX");
    QTest::addColumn<qreal>("minY");
    QTest::addColumn<qreal>("maxY");
    QTest::newRow("1,2,1,2") << 1.0 << 2.0 << 1.0 << 2.0;
    QTest::newRow("1,3,1,3") << 1.0 << 3.0 << 1.0 << 3.0;
    QTest::newRow("-1,5,-2,-1") << -1.0 << 5.0 << -2.0 << -1.0;
}

void tst_Domain::setRange()
{
    QFETCH(qreal, minX);
    QFETCH(qreal, maxX);
    QFETCH(qreal, minY);
    QFETCH(qreal, maxY);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setRange(minX, maxX, minY, maxY);

    QCOMPARE(domain.minX(), minX);
    QCOMPARE(domain.maxX(), maxX);
    QCOMPARE(domain.minY(), minY);
    QCOMPARE(domain.maxY(), maxY);

    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 1);

}

void tst_Domain::setRangeX_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("-1 1") << -1.0 << 1.0;
    QTest::newRow("0 1") << 0.0 << 1.0;
    QTest::newRow("-1 0") << -1.0 << 0.0;
}

void tst_Domain::setRangeX()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setRangeX(min, max);

    QList<QVariant> arg0 = spy0.first();
    QVERIFY(qFuzzyIsNull(arg0.at(0).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg0.at(1).toReal() - max));

    QList<QVariant> arg1 = spy1.first();
    QVERIFY(qFuzzyIsNull(arg1.at(0).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg1.at(1).toReal() - max));

    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 0);
}

void tst_Domain::setRangeY_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::newRow("-1 1") << -1.0 << 1.0;
    QTest::newRow("0 1") << 0.0 << 1.0;
    QTest::newRow("-1 0") << -1.0 << 0.0;
}

void tst_Domain::setRangeY()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);

    Domain domain;

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.setRangeY(min, max);

    QList<QVariant> arg0 = spy0.first();
    QVERIFY(qFuzzyIsNull(arg0.at(2).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg0.at(3).toReal() - max));

    QList<QVariant> arg1 = spy2.first();
    QVERIFY(qFuzzyIsNull(arg1.at(0).toReal() - min));
    QVERIFY(qFuzzyIsNull(arg1.at(1).toReal() - max));

    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 1);
}

void tst_Domain::spanX_data()
{
    QTest::addColumn<qreal>("minX");
    QTest::addColumn<qreal>("maxX");
    QTest::addColumn<qreal>("spanX");
    QTest::newRow("1 2 1") << 1.0 << 2.0 << 1.0;
    QTest::newRow("0 2 2") << 1.0 << 2.0 << 1.0;
}

void tst_Domain::spanX()
{
    QFETCH(qreal, minX);
    QFETCH(qreal, maxX);
    QFETCH(qreal, spanX);

    Domain domain;

    domain.setRangeX(minX, maxX);

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    QCOMPARE(domain.spanX(), spanX);

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 0);
}

void tst_Domain::spanY_data()
{
    QTest::addColumn<qreal>("minY");
    QTest::addColumn<qreal>("maxY");
    QTest::addColumn<qreal>("spanY");
    QTest::newRow("1 2 1") << 1.0 << 2.0 << 1.0;
    QTest::newRow("0 2 2") << 1.0 << 2.0 << 1.0;
}

void tst_Domain::spanY()
{
    QFETCH(qreal, minY);
    QFETCH(qreal, maxY);
    QFETCH(qreal, spanY);

    Domain domain;

    domain.setRangeY(minY, maxY);

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    QCOMPARE(domain.spanY(), spanY);

    TRY_COMPARE(spy0.count(), 0);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 0);
}

void tst_Domain::zoom_data()
{
    QTest::addColumn<QRectF>("rect0");
    QTest::addColumn<QSizeF>("size0");
    QTest::addColumn<QRectF>("rect1");
    QTest::addColumn<QSizeF>("size1");
    QTest::addColumn<QRectF>("rect2");
    QTest::addColumn<QSizeF>("size2");
    QTest::newRow("first") << QRectF(10, 10, 100, 100) << QSizeF(1000, 1000)
        << QRectF(20, 20, 100, 100) << QSizeF(1000, 1000) << QRectF(50, 50, 100, 100)
        << QSizeF(1000, 1000);
    QTest::newRow("scound") << QRectF(10, 10, 50, 50) << QSizeF(1000, 1000)
        << QRectF(20, 20, 100, 100) << QSizeF(1000, 1000) << QRectF(50, 50, 100, 100)
        << QSizeF(1000, 1000);
    QTest::newRow("third") << QRectF(10, 10, 10, 10) << QSizeF(100, 100) << QRectF(20, 20, 20, 20)
        << QSizeF(100, 100) << QRectF(50, 50, 50, 50) << QSizeF(100, 100);
}

void tst_Domain::zoom()
{
    QFETCH(QRectF, rect0);
    QFETCH(QSizeF, size0);
    QFETCH(QRectF, rect1);
    QFETCH(QSizeF, size1);
    QFETCH(QRectF, rect2);
    QFETCH(QSizeF, size2);

    Domain domain;

    domain.setRange(0, 1000, 0, 1000);

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    Domain domain0;
    domain0.setRange(domain.minX(), domain.maxX(), domain.minY(), domain.maxY());
    domain.zoomIn(rect0, size0);
    Domain domain1;
    domain1.setRange(domain.minX(), domain.maxX(), domain.minY(), domain.maxY());
    domain.zoomIn(rect1, size1);
    Domain domain2;
    domain2.setRange(domain.minX(), domain.maxX(), domain.minY(), domain.maxY());
    domain.zoomIn(rect2, size2);
    domain.zoomOut(rect2, size2);
    QCOMPARE(domain == domain2, true);
    domain.zoomOut(rect1, size1);
    QCOMPARE(domain == domain1, true);
    domain.zoomOut(rect0, size0);
    QCOMPARE(domain == domain0, true);
    TRY_COMPARE(spy0.count(), 6);
    TRY_COMPARE(spy1.count(), 6);
    TRY_COMPARE(spy2.count(), 6);
}

void tst_Domain::move_data()
{
    QTest::addColumn<int>("dx");
    QTest::addColumn<int>("dy");
    QTest::addColumn<QSizeF>("size");
    QTest::newRow("dx 100, dy 0, size 1000x1000") << 100 << 0 << QSizeF(1000, 1000);
    QTest::newRow("dx 0,  dy 100, size 1000x1000") << 0 << 100 << QSizeF(1000, 1000);
    QTest::newRow("dx -100, dy 0, size 1000x1000") << -100 << 0 << QSizeF(1000, 1000);
    QTest::newRow("dx 0, dy -100, size 1000x1000") << 0 << -100 << QSizeF(1000, 1000);
    QTest::newRow("dx 100, dy 100, size 1000x1000") << 100 << 100 << QSizeF(1000, 1000);
    QTest::newRow("dx 100, dy 50, size 1000x1000") << 100 << 50 << QSizeF(1000, 1000);
}

void tst_Domain::move()
{
    QFETCH(int, dx);
    QFETCH(int, dy);
    QFETCH(QSizeF, size);
    Domain domain;

    domain.setRange(0, size.width(), 0, size.height());

    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.move(dx, dy, size);

    Domain result;
    result.setRange(dx, size.width() + dx, dy, size.height() + dy);

    QCOMPARE(domain == result, true);
    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), (dx != 0 ? 1 : 0));
    TRY_COMPARE(spy2.count(), (dy != 0 ? 1 : 0));
}

void tst_Domain::handleAxisXChanged_data()
{
    QTest::addColumn<qreal>("min");
    QTest::addColumn<qreal>("max");
    QTest::addColumn<int>("tickCount");
    QTest::addColumn<bool>("niceNumbers");
    QTest::addColumn<qreal>("resultMin");
    QTest::addColumn<qreal>("resultMax");
    QTest::addColumn<int>("resultTickCount");
    QTest::newRow("0,100,5,false") << 0.0 << 100.0 << 5 << false << 0.0 << 100.0 << 5;
    QTest::newRow("0,100,5,true") << 0.0 << 100.0 << 5 << true << 0.0 << 100.0 << 6;
    QTest::newRow("0.1,99,5,true") << 0.1 << 99.0 << 5 << true << 0.0 << 100.0 << 6;
    QTest::newRow("5,93.5,true") << 5.0 << 93.5 << 5 << true << 0.0 << 100.0 << 6;
}

void tst_Domain::handleAxisXChanged()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);
    QFETCH(int, tickCount);
    QFETCH(bool, niceNumbers);
    QFETCH(qreal, resultMin);
    QFETCH(qreal, resultMax);
    QFETCH(int, resultTickCount);

    Domain domain;
    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.handleAxisXChanged(min, max, tickCount, niceNumbers);

    QCOMPARE(resultMin, domain.minX());
    QCOMPARE(resultMax, domain.maxX());
    QCOMPARE(resultTickCount, domain.tickXCount());
    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 1);
    TRY_COMPARE(spy2.count(), 0);

}

void tst_Domain::handleAxisYChanged_data()
{
    handleAxisXChanged_data();
}

void tst_Domain::handleAxisYChanged()
{
    QFETCH(qreal, min);
    QFETCH(qreal, max);
    QFETCH(int, tickCount);
    QFETCH(bool, niceNumbers);
    QFETCH(qreal, resultMin);
    QFETCH(qreal, resultMax);
    QFETCH(int, resultTickCount);

    Domain domain;
    QSignalSpy spy0(&domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)));
    QSignalSpy spy1(&domain, SIGNAL(rangeXChanged(qreal,qreal,int)));
    QSignalSpy spy2(&domain, SIGNAL(rangeYChanged(qreal,qreal,int)));

    domain.handleAxisYChanged(min, max, tickCount, niceNumbers);

    QCOMPARE(resultMin, domain.minY());
    QCOMPARE(resultMax, domain.maxY());
    QCOMPARE(resultTickCount, domain.tickYCount());
    TRY_COMPARE(spy0.count(), 1);
    TRY_COMPARE(spy1.count(), 0);
    TRY_COMPARE(spy2.count(), 1);
}

QTEST_MAIN(tst_Domain)
#include "tst_domain.moc"

