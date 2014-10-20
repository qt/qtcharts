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
#include <QtCharts/QLineSeries>


Q_DECLARE_METATYPE(QList<QPointF>)

class tst_QLineSeries : public tst_QXYSeries
{
    Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:
    void qlineseries_data();
    void qlineseries();
protected:
    void pointsVisible_data();
};

void tst_QLineSeries::initTestCase()
{
}

void tst_QLineSeries::cleanupTestCase()
{
}

void tst_QLineSeries::init()
{
    tst_QXYSeries::init();
    m_series = new QLineSeries();
}

void tst_QLineSeries::cleanup()
{
    delete m_series;
    m_series=0;
    tst_QXYSeries::cleanup();
}

void tst_QLineSeries::qlineseries_data()
{

}

void tst_QLineSeries::qlineseries()
{
    QLineSeries series;

    QCOMPARE(series.count(),0);
    QCOMPARE(series.brush(), QBrush());
    QCOMPARE(series.points(), QList<QPointF>());
    QCOMPARE(series.pen(), QPen());
    QCOMPARE(series.pointsVisible(), false);
    QCOMPARE(series.pointLabelsVisible(), false);
    QCOMPARE(series.pointLabelsFormat(), QLatin1String("@xPoint, @yPoint"));

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

    series.setPointLabelsVisible(false);
    series.setPointLabelsFormat(QString());

    m_chart->addSeries(&series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
}

QTEST_MAIN(tst_QLineSeries)

#include "tst_qlineseries.moc"

