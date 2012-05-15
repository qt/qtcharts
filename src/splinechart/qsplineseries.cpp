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
#include <QAbstractItemModel>

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

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance then the ownerships is transferred.
  */

QSplineSeries::QSplineSeries(QObject *parent) :
    QLineSeries(*new QSplineSeriesPrivate(this),parent)
{
}

QSplineSeries::~QSplineSeries()
{
    Q_D(QSplineSeries);
    if(d->m_dataset){
        d->m_dataset->removeSeries(this);
    }
}

QAbstractSeries::SeriesType QSplineSeries::type() const
{
    return QAbstractSeries::SeriesTypeSpline;
}

void QSplineSeries::setModel(QAbstractItemModel *model)
{
    Q_D(QSplineSeries);
    QXYSeries::setModel(model);
    if (d->m_model && d->m_mapper)
        d->updateControlPoints();
}

void QSplineSeries::setModelMapper(QXYModelMapper *mapper)
{
    Q_D(QSplineSeries);
    QXYSeries::setModelMapper(mapper);
    if (d->m_model && d->m_mapper)
        d->updateControlPoints();
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

    const QList<QPointF>& points = q->points();

    int n = points.count() - 1;

    if (n == 1)
    {
        //for n==1
        m_controlPoints[0].setX((2 * points[0].x() + points[1].x()) / 3);
        m_controlPoints[0].setY((2 * points[0].y() + points[1].y()) / 3);
        m_controlPoints[1].setX(2 * m_controlPoints[0].x() - points[0].x());
        m_controlPoints[1].setY(2 * m_controlPoints[0].y() - points[0].y());
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
    QVector<qreal> vector;
    vector.resize(n);

    vector[0] = points[0].x() + 2 * points[1].x();


    for (int i = 1; i < n - 1; ++i){
        vector[i] = 4 * points[i].x() + 2 * points[i + 1].x();
    }

    vector[n - 1] = (8 * points[n-1].x() + points[n].x()) / 2.0;

    QVector<qreal> xControl = firstControlPoints(vector);

    vector[0] = points[0].y() + 2 * points[1].y();

    for (int i = 1; i < n - 1; ++i) {
        vector[i] = 4 * points[i].y() + 2 * points[i + 1].y();
    }

    vector[n - 1] = (8 * points[n-1].y() + points[n].y()) / 2.0;

    QVector<qreal> yControl = firstControlPoints(vector);

    for (int i = 0,j =0; i < n; ++i, ++j) {

        m_controlPoints[j].setX(xControl[i]);
        m_controlPoints[j].setY(yControl[i]);

        j++;

        if (i < n - 1){
            m_controlPoints[j].setX(2 * points[i+1].x() - xControl[i + 1]);
            m_controlPoints[j].setY(2 * points[i+1].y() - yControl[i + 1]);
        }else{
            m_controlPoints[j].setX((points[n].x() + xControl[n - 1]) / 2);
            m_controlPoints[j].setY((points[n].y() + yControl[n - 1]) / 2);
        }
    }
}

QVector<qreal> QSplineSeriesPrivate::firstControlPoints(const QVector<qreal>& vector)
{
    QVector<qreal> result;

    int count = vector.count();
    result.resize(count);
    result[0] = vector[0] / 2.0;

    QVector<qreal> temp;
    temp.resize(count);
    temp[0] = 0;

    qreal b = 2.0;

    for (int i = 1; i < count; i++) {
        temp[i] = 1 / b;
        b = (i < count - 1 ? 4.0 : 3.5) - temp[i];
        result[i]=(vector[i] - result[i - 1]) / b;
    }
    for (int i = 1; i < count; i++)
        result[count - i - 1] -= temp[count - i] * result[count - i];

    return result;
}

QPointF QSplineSeriesPrivate::controlPoint(int index) const
{
    //    Q_D(const QSplineSeries);
    //    return d->m_controlPoints[index];
    return m_controlPoints[index];
}

/*!
  Updates the control points, besed on currently avaiable knots.
  */
void QSplineSeriesPrivate::updateControlPoints()
{
    Q_Q(QSplineSeries);
    if (q->count() > 1) {
        m_controlPoints.resize(2*q->count()-2);
        calculateControlPoints();
    }
}

void QSplineSeriesPrivate::mappingUpdated()
{
    updateControlPoints();
    emit updated();
}

void QSplineSeriesPrivate::modelRowsAdded(QModelIndex parent, int start, int end)
{
    updateControlPoints();
    QXYSeriesPrivate::modelRowsAdded(parent, start, end);
}

void QSplineSeriesPrivate::modelRowsRemoved(QModelIndex parent, int start, int end)
{
    updateControlPoints();
    QXYSeriesPrivate::modelRowsRemoved(parent, start, end);
}

void QSplineSeriesPrivate::modelColumnsAdded(QModelIndex parent, int start, int end)
{
    updateControlPoints();
    QXYSeriesPrivate::modelColumnsAdded(parent, start, end);
}

void QSplineSeriesPrivate::modelColumnsRemoved(QModelIndex parent, int start, int end)
{
    updateControlPoints();
    QXYSeriesPrivate::modelColumnsRemoved(parent, start, end);
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
