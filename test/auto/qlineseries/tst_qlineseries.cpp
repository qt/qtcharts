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
#include <qlineseries.h>
#include <qchartview.h>

Q_DECLARE_METATYPE(QList<QPointF>)

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QLineSeries : public QObject
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

    void append_data();
    void append();
    void brush_data();
    void brush();
    void count_data();
    void count();
    void data_data();
    void data();
    void oper_data();
    void oper();
    void pen_data();
    void pen();
    void pointsVisible_data();
    void pointsVisible();
    void remove_data();
    void remove();
    void removeAll_data();
    void removeAll();
    void replace_data();
    void replace();
    void setBrush_data();
    void setBrush();
    void setModel_data();
    void setModel();
    void setModelMapping_data();
    void setModelMapping();
    void setPen_data();
    void setPen();
    void setPointsVisible_data();
    void setPointsVisible();
    void x_data();
    void x();
    void y_data();
    void y();
    void clicked_data();
    void clicked();
    void selected_data();
    void selected();

private:
    QChartView* m_view;
    QChart* m_chart;
};

void tst_QLineSeries::initTestCase()
{
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
}

void tst_QLineSeries::cleanupTestCase()
{
}

void tst_QLineSeries::init()
{
}

void tst_QLineSeries::cleanup()
{
    delete m_view;
    m_view = 0;
    m_chart = 0;
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

    series.append(QList<QPointF>());
    series.append(0.0,0.0);
    series.append(QPointF());

    series.remove(0.0,0.0);
    series.remove(QPointF());
    series.removeAll();

    series.replace(QPointF(),QPointF());
    series.replace(0,0,0,0);
    series.setBrush(QBrush());

    QCOMPARE(series.setModel((QAbstractItemModel*)0), false);

    series.setModelMapping(-1, -1, Qt::Orientation(0));

    series.setPen(QPen());
    series.setPointsVisible(false);
}

void tst_QLineSeries::append_data()
{
#if 0
    QTest::addColumn<QList<QPointF>>("points");
    QTest::newRow("null") << QList<QPointF>();
#endif
}

// public void append(QList<QPointF> const points)
void tst_QLineSeries::append()
{
#if 0
    QFETCH(QList<QPointF>, points);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.append(points);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QBrush)
void tst_QLineSeries::brush_data()
{
#if 0
    QTest::addColumn<QBrush>("brush");
    QTest::newRow("null") << QBrush();
#endif
}

// public QBrush brush() const
void tst_QLineSeries::brush()
{
#if 0
    QFETCH(QBrush, brush);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.brush(), brush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::count_data()
{
    QTest::addColumn<int>("count");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public int count() const
void tst_QLineSeries::count()
{
#if 0
    QFETCH(int, count);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.count(), count);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::data_data()
{
#if 0
    QTest::addColumn<QList<QPointF>>("data");
    QTest::newRow("null") << QList<QPointF>();
#endif
}

// public QList<QPointF> data()
void tst_QLineSeries::data()
{
#if 0
    QFETCH(QList<QPointF>, data);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.data(), data);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::oper_data()
{
#if 0
    QTest::addColumn<QList<QPointF>>("points");
    QTest::addColumn<QXYSeries&>("operator<<");
    QTest::newRow("null") << QList<QPointF>() << QXYSeries&();
#endif
}

// public QXYSeries& operator<<(QList<QPointF> const points)
void tst_QLineSeries::oper()
{
#if 0
    QFETCH(QList<QPointF>, points);
    QFETCH(QXYSeries&, operator<<);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.operator<<(points), operator<<);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(QPen)
void tst_QLineSeries::pen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public QPen pen() const
void tst_QLineSeries::pen()
{
#if 0
    QFETCH(QPen, pen);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.pen(), pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::pointsVisible_data()
{
    QTest::addColumn<bool>("pointsVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public bool pointsVisible() const
void tst_QLineSeries::pointsVisible()
{
#if 0
    QFETCH(bool, pointsVisible);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.pointsVisible(), pointsVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::remove_data()
{
    QTest::addColumn<qreal>("x");
    QTest::addColumn<qreal>("y");
    QTest::newRow("null") << 0.0 << 0.0;
}

// public void remove(qreal x, qreal y)
void tst_QLineSeries::remove()
{
#if 0
    QFETCH(qreal, x);
    QFETCH(qreal, y);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.remove(x, y);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::removeAll_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// public void removeAll()
void tst_QLineSeries::removeAll()
{
#if 0
    QFETCH(int, foo);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.removeAll();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::replace_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::newRow("null") << QPointF();
}

// public void replace(QPointF const& point)
void tst_QLineSeries::replace()
{
#if 0
    QFETCH(QPointF, point);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.replace(point);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::setBrush_data()
{
#if 0
    QTest::addColumn<QBrush>("brush");
    QTest::newRow("null") << QBrush();
#endif
}

// public void setBrush(QBrush const& brush)
void tst_QLineSeries::setBrush()
{
#if 0
    QFETCH(QBrush, brush);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.setBrush(brush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::setModel_data()
{
    QTest::addColumn<int>("modelCount");
    QTest::addColumn<bool>("setModel");
    QTest::newRow("null") << 0 << false;
}

// public bool setModel(QAbstractItemModel* model)
void tst_QLineSeries::setModel()
{
#if 0
    QFETCH(int, modelCount);
    QFETCH(bool, setModel);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.setModel(model), setModel);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

Q_DECLARE_METATYPE(Qt::Orientation)
void tst_QLineSeries::setModelMapping_data()
{
#if 0
    QTest::addColumn<int>("modelX");
    QTest::addColumn<int>("modelY");
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::newRow("null") << 0 << 0 << Qt::Orientation();
#endif
}

// public void setModelMapping(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical)
void tst_QLineSeries::setModelMapping()
{
#if 0
    QFETCH(int, modelX);
    QFETCH(int, modelY);
    QFETCH(Qt::Orientation, orientation);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.setModelMapping(modelX, modelY, orientation);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::setPen_data()
{
#if 0
    QTest::addColumn<QPen>("pen");
    QTest::newRow("null") << QPen();
#endif
}

// public void setPen(QPen const& pen)
void tst_QLineSeries::setPen()
{
#if 0
    QFETCH(QPen, pen);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.setPen(pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::setPointsVisible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

// public void setPointsVisible(bool visible = true)
void tst_QLineSeries::setPointsVisible()
{
#if 0
    QFETCH(bool, visible);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.setPointsVisible(visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::x_data()
{
    QTest::addColumn<int>("pos");
    QTest::addColumn<qreal>("x");
    QTest::newRow("null") << 0 << 0.0;
}

// public qreal x(int pos) const
void tst_QLineSeries::x()
{
#if 0
    QFETCH(int, pos);
    QFETCH(qreal, x);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.x(pos), x);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::y_data()
{
    QTest::addColumn<int>("pos");
    QTest::addColumn<qreal>("y");
    QTest::newRow("null") << 0 << 0.0;
}

// public qreal y(int pos) const
void tst_QLineSeries::y()
{
#if 0
    QFETCH(int, pos);
    QFETCH(qreal, y);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    QCOMPARE(series.y(pos), y);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::clicked_data()
{
    QTest::addColumn<QPointF>("point");
    QTest::newRow("null") << QPointF();
}

// protected void clicked(QPointF const& point)
void tst_QLineSeries::clicked()
{
#if 0
    QFETCH(QPointF, point);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.call_clicked(point);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QLineSeries::selected_data()
{
    QTest::addColumn<int>("foo");
    QTest::newRow("0") << 0;
    QTest::newRow("-1") << -1;
}

// protected void selected()
void tst_QLineSeries::selected()
{
#if 0
    QFETCH(int, foo);

    SubQXYSeries series;

    QSignalSpy spy0(&series, SIGNAL(clicked(QPointF const&)));
    QSignalSpy spy1(&series, SIGNAL(selected()));

    series.call_selected();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

QTEST_MAIN(tst_QLineSeries)

#include "tst_qlineseries.moc"

