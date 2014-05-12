/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "../qxyseries/tst_qxyseries.h"
#include <qsplineseries.h>

Q_DECLARE_METATYPE(QList<QPointF>)

class tst_QSplineSeries : public tst_QXYSeries
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:
    void qsplineseries_data();
    void qsplineseries();
protected:
    void pointsVisible_data();
};

void tst_QSplineSeries::initTestCase()
{
}

void tst_QSplineSeries::cleanupTestCase()
{
}

void tst_QSplineSeries::init()
{
    tst_QXYSeries::init();
    m_series = new QSplineSeries();
}

void tst_QSplineSeries::cleanup()
{
    delete m_series;
    tst_QXYSeries::cleanup();
}

void tst_QSplineSeries::qsplineseries_data()
{

}

void tst_QSplineSeries::qsplineseries()
{
    QSplineSeries series;

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

QTEST_MAIN(tst_QSplineSeries)

#include "tst_qsplineseries.moc"

