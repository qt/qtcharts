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

void QSplineSeries::setModelMappingRange(int first, int count)
{
    Q_D(QSplineSeries);
    QLineSeries::setModelMappingRange(first, count);
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
  \internal
  Calculates control points which are needed by QPainterPath.cubicTo function to draw the cubic Bezier cureve between two points.
  */
void QSplineSeriesPrivate::calculateControlPoints()
{

    Q_Q(QSplineSeries);
    // Based on http://www.codeproject.com/Articles/31859/Draw-a-Smooth-Curve-through-a-Set-of-2D-Points-wit
    // CPOL License

    int n = q->count() - 1;
    if (n == 1)
    { // Special case: Bezier curve should be a straight line.
        //            firstControlPoints = new Point[1];
        // 3P1 = 2P0 + P3
        m_controlPoints.append(QPointF((2 * q->x(0) + q->x(1)) / 3, (2 * q->y(0) + q->y(1)) / 3));

        // P2 = 2P1  P0
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
    QList<qreal> rhs;
    rhs.append(q->x(0) + 2 * q->x(1));

    // Set right hand side X values
    for (int i = 1; i < n - 1; ++i)
        rhs.append(4 * q->x(i) + 2 * q->x(i + 1));

    rhs.append((8 * q->x(n - 1) + q->x(n)) / 2.0);
    // Get first control points X-values
    QList<qreal> xControl = getFirstControlPoints(rhs);
    rhs[0] = q->y(0) + 2 * q->y(1);

    // Set right hand side Y values
    for (int i = 1; i < n - 1; ++i)
        rhs[i] = 4 * q->y(i) + 2 * q->y(i + 1);

    rhs[n - 1] = (8 * q->y(n - 1) + q->y(n)) / 2.0;
    // Get first control points Y-values
    QList<qreal> yControl = getFirstControlPoints(rhs);

    // Fill output arrays.
    for (int i = 0; i < n; ++i) {
        // First control point
        m_controlPoints.append(QPointF(xControl[i], yControl[i]));
        // Second control point
        if (i < n - 1)
            m_controlPoints.append(QPointF(2 * q->x(i + 1) - xControl[i + 1], 2 * q->y(i + 1) - yControl[i + 1]));
        else
            m_controlPoints.append(QPointF((q->x(n) + xControl[n - 1]) / 2, (q->y(n) + yControl[n - 1]) / 2));
    }
}

/*!
  \internal
  */
QList<qreal> QSplineSeriesPrivate::getFirstControlPoints(QList<qreal> rhs)
{
    QList<qreal> x; // Solution vector.
    QList<qreal> tmp; // Temp workspace.

    qreal b = 2.0;
    x.append(rhs[0] / b);
    tmp.append(0);
    for (int i = 1; i < rhs.size(); i++) {
        // Decomposition and forward substitution.
        tmp.append(1 / b);
        b = (i < rhs.size() - 1 ? 4.0 : 3.5) - tmp[i];
        x.append((rhs[i] - x[i - 1]) / b);
    }
    for (int i = 1; i < rhs.size(); i++)
        x[rhs.size() - i - 1] -= tmp[rhs.size() - i] * x[rhs.size() - i]; // Backsubstitution.

    return x;
}

/*!
  \internal
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

/*//!
     \fn bool QSplineSeries::setModel(QAbstractItemModel *model)
     Sets the \a model to be used as a data source
     \sa setModelMapping(), setModelMappingRange()
 */
//bool QSplineSeries::setModel(QAbstractItemModel* model)
//{
//    QXYSeries::setModel(model);
////    calculateControlPoints();
//    return true;
//}

/*//!
     \fn bool QSplineSeries::setModelMapping(int modelX, int modelY, Qt::Orientation orientation)
     Sets the \a modelX to be used as a data source for x coordinate and \a modelY to be used
     as a data source for y coordinate. The \a orientation parameter specifies whether the data
     is in columns or in rows.
 */
//void QSplineSeries::setModelMapping(int modelX, int modelY, Qt::Orientation orientation)
//{
//    QLineSeries::setModelMapping(modelX, modelY, orientation);
////    calculateControlPoints();
//}

/*!
     \fn bool QSplineSeries::setModelMappingRange(int first, int count)
     Allows limiting the model mapping.
     Parameter \a first specifies which element of the model should be used as a first one of the series.
     Parameter \a count specifies how many elements should be mapped. If count is not specified (defaults to -1)
     then all the items following \a first item in a model are used.
     \sa setModel(), setModelMapping()
 */

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
