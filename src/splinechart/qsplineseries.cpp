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

#include "qsplineseries.h"
#include "qsplineseries_p.h"
#include "splinechartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"

/*!
    \class QSplineSeries
    \brief Series type used to store data needed to draw a spline.

    QSplineSeries stores the data points along with the segment control points needed by QPainterPath to draw spline
    Control points are automatically calculated when data changes. The algorithm computes the points so that the normal spline can be drawn.

    \image examples_splinechart.png

    Creating basic spline chart is simple:
    \code
    QSplineSeries* series = new QSplineSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chart->addSeries(series);
    \endcode
*/

/*!
  \fn QSeriesType QSplineSeries::type() const
  Returns the type of the series
  */

/*!
  \fn QSeriesType QSplineSeries::controlPoint(int index) const
  Returns the control point specified by \a index
  */

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance then the ownerships is transferred.
  */

QSplineSeries::QSplineSeries(QObject *parent) :
    QLineSeries(*new QSplineSeriesPrivate(this),parent)
{
}

QAbstractSeries::QSeriesType QSplineSeries::type() const
{
    return QAbstractSeries::SeriesTypeSpline;
}

QPointF QSplineSeries::controlPoint(int index) const
{
    Q_D(const QSplineSeries);
    return d->m_controlPoints[index];
}

/*!
     Sets the \a modelX to be used as a data source for x coordinate and \a modelY to be used
     as a data source for y coordinate. The \a orientation parameter specifies whether the data
     is in columns or in rows.
     \sa setModel()
 */
void QSplineSeries::setModelMapping(int modelX, int modelY, Qt::Orientation orientation)
{
    Q_D(QSplineSeries);
    QXYSeries::setModelMapping(modelX, modelY, orientation);
    d->calculateControlPoints();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSplineSeriesPrivate::QSplineSeriesPrivate(QSplineSeries* q):QLineSeriesPrivate(q)
{
    QObject::connect(this,SIGNAL(pointAdded(int)), this, SLOT(updateControlPoints()));
    QObject::connect(this,SIGNAL(pointRemoved(int)), this, SLOT(updateControlPoints()));
    QObject::connect(this,SIGNAL(pointReplaced(int)), this, SLOT(updateControlPoints()));
};

/*!
  Calculates control points which are needed by QPainterPath.cubicTo function to draw the cubic Bezier cureve between two points.
  */
void QSplineSeriesPrivate::calculateControlPoints()
{

    Q_Q(QSplineSeries);

    int n = q->count() - 1;

    if (n == 1)
    {
        //for n==1
        m_controlPoints.append(QPointF((2 * q->x(0) + q->x(1)) / 3, (2 * q->y(0) + q->y(1)) / 3));
        m_controlPoints.append(QPointF(2 * m_controlPoints[0].x() - q->x(0), 2 * m_controlPoints[0].y() - q->y(0)));
        return;
    }

    // Calculate first Bezier control points
    // Right hand side vector
    //  Set of equations for P0 to Pn points.
    //
    //  |   2   1   0   0   ... 0   0   0   ... 0   0   0   |   |   P1_1    |   |   P0 + 2 * P1             |
    //  |   1   4   1   0   ... 0   0   0   ... 0   0   0   |   |   P1_2    |   |   4 * P1 + 2 * P2         |
    //  |   0   1   4   1   ... 0   0   0   ... 0   0   0   |   |   P1_3    |   |   4 * P2 + 2 * P3         |
    //  |   .   .   .   .   .   .   .   .   .   .   .   .   |   |   ...     |   |   ...                     |
    //  |   0   0   0   0   ... 1   4   1   ... 0   0   0   | * |   P1_i    | = |   4 * P(i-1) + 2 * Pi     |
    //  |   .   .   .   .   .   .   .   .   .   .   .   .   |   |   ...     |   |   ...                     |
    //  |   0   0   0   0   0   0   0   0   ... 1   4   1   |   |   P1_(n-1)|   |   4 * P(n-2) + 2 * P(n-1) |
    //  |   0   0   0   0   0   0   0   0   ... 0   2   7   |   |   P1_n    |   |   8 * P(n-1) + Pn         |
    //
    QList<qreal> points;

    points.append(q->x(0) + 2 * q->x(1));


    for (int i = 1; i < n - 1; ++i)
        points.append(4 * q->x(i) + 2 * q->x(i + 1));

    points.append((8 * q->x(n - 1) + q->x(n)) / 2.0);

    QList<qreal> xControl = firstControlPoints(points);
    points[0] = q->y(0) + 2 * q->y(1);

    for (int i = 1; i < n - 1; ++i) {
        points[i] = 4 * q->y(i) + 2 * q->y(i + 1);
    }

    points[n - 1] = (8 * q->y(n - 1) + q->y(n)) / 2.0;

    QList<qreal> yControl = firstControlPoints(points);

    for (int i = 0; i < n; ++i) {

        m_controlPoints.append(QPointF(xControl[i], yControl[i]));

        if (i < n - 1)
            m_controlPoints.append(QPointF(2 * q->x(i + 1) - xControl[i + 1], 2 * q->y(i + 1) - yControl[i + 1]));
        else
            m_controlPoints.append(QPointF((q->x(n) + xControl[n - 1]) / 2, (q->y(n) + yControl[n - 1]) / 2));
    }
}

QList<qreal> QSplineSeriesPrivate::firstControlPoints(QList<qreal> list)
{
    QList<qreal> result;
    QList<qreal> temp;

    qreal b = 2.0;
    result.append(list[0] / b);
    temp.append(0);
    for (int i = 1; i < list.size(); i++) {
        temp.append(1 / b);
        b = (i < list.size() - 1 ? 4.0 : 3.5) - temp[i];
        result.append((list[i] - result[i - 1]) / b);
    }
    for (int i = 1; i < list.size(); i++)
        result[list.size() - i - 1] -= temp[list.size() - i] * result[list.size() - i];

    return result;
}

/*!
  Updates the control points, besed on currently avaiable knots.
  */
void QSplineSeriesPrivate::updateControlPoints()
{
    Q_Q(QSplineSeries);
    if (q->count() > 1) {
        m_controlPoints.clear();
        calculateControlPoints();
    }
}

Chart* QSplineSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QSplineSeries);
    SplineChartItem* spline  = new SplineChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(spline);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return spline;
}

#include "moc_qsplineseries.cpp"
#include "moc_qsplineseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
