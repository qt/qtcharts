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

#include "../qxyseries/tst_qxyseries.h"
#include <qscatterseries.h>

Q_DECLARE_METATYPE(QList<QPointF>)

class tst_QScatterSeries : public tst_QXYSeries
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:
    void qscatterseries_data();
    void qscatterseries();
protected:
    void pointsVisible_data();
};

void tst_QScatterSeries::initTestCase()
{
}

void tst_QScatterSeries::cleanupTestCase()
{
}

void tst_QScatterSeries::init()
{
    tst_QXYSeries::init();
    m_series = new QScatterSeries();
}

void tst_QScatterSeries::cleanup()
{
    delete m_series;
    tst_QXYSeries::cleanup();
}

void tst_QScatterSeries::qscatterseries_data()
{

}

void tst_QScatterSeries::qscatterseries()
{
    QScatterSeries series;

    QCOMPARE(series.count(),0);
    QCOMPARE(series.brush(), QBrush());
    QCOMPARE(series.points(), QList<QPointF>());
    QCOMPARE(series.pen(), QPen());
    QCOMPARE(series.pointsVisible(), false);

    series.append(QList<QPointF>());
    series.append(0.0,0.0);
    series.append(QPointF());

    series.remove(0.0,0.0);
    series.remove(QPointF());
    series.clear();

    series.replace(QPointF(),QPointF());
    series.replace(0,0,0,0);
    series.setBrush(QBrush());

    series.setPen(QPen());
    series.setPointsVisible(false);

    m_chart->addSeries(&series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

QTEST_MAIN(tst_QScatterSeries)

#include "tst_qscatterseries.moc"

