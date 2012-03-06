#include "qsplineseries.h"

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
    When series object is added to QChartView or QChart instance then the ownerships is transfered.
  */

QSplineSeries::QSplineSeries(QObject *parent) :
    QLineSeries(parent)
{
    connect(this,SIGNAL(pointAdded(int)), this, SLOT(updateControlPoints()));
    connect(this,SIGNAL(pointRemoved(int)), this, SLOT(updateControlPoints()));
    connect(this,SIGNAL(pointReplaced(int)), this, SLOT(updateControlPoints()));
}

/*!
  \internal
  Calculates control points which are needed by QPainterPath.cubicTo function to draw the cubic Bezier cureve between two points.
  */
void QSplineSeries::calculateControlPoints()
{

    // Based on http://www.codeproject.com/Articles/31859/Draw-a-Smooth-Curve-through-a-Set-of-2D-Points-wit
    // CPOL License

    int n = m_x.size() - 1;
    if (n == 1)
    { // Special case: Bezier curve should be a straight line.
        //            firstControlPoints = new Point[1];
        // 3P1 = 2P0 + P3
        m_controlPoints.append(QPointF((2 * m_x[0] + m_x[1]) / 3, (2 * m_y[0] + m_y[1]) / 3));

        // P2 = 2P1  P0
        m_controlPoints.append(QPointF(2 * m_controlPoints[0].x() - m_x[0], 2 * m_controlPoints[0].y() - m_y[0]));
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
    rhs.append(m_x[0] + 2 * m_x[1]);

    // Set right hand side X values
    for (int i = 1; i < n - 1; ++i)
        rhs.append(4 * m_x[i] + 2 * m_x[i + 1]);

    rhs.append((8 * m_x[n - 1] + m_x[n]) / 2.0);
    // Get first control points X-values
    QList<qreal> x = getFirstControlPoints(rhs);
    rhs[0] = m_y[0] + 2 * m_y[1];

    // Set right hand side Y values
    for (int i = 1; i < n - 1; ++i)
        rhs[i] = 4 * m_y[i] + 2 * m_y[i + 1];

    rhs[n - 1] = (8 * m_y[n - 1] + m_y[n]) / 2.0;
    // Get first control points Y-values
    QList<qreal> y = getFirstControlPoints(rhs);

    // Fill output arrays.
    for (int i = 0; i < n; ++i)
    {
        // First control point
        m_controlPoints.append(QPointF(x[i], y[i]));
        // Second control point
        if (i < n - 1)
            m_controlPoints.append(QPointF(2 * m_x[i + 1] - x[i + 1], 2 * m_y[i + 1] - y[i + 1]));
        else
            m_controlPoints.append(QPointF((m_x[n] + x[n - 1]) / 2, (m_y[n] + y[n - 1]) / 2));
    }
}

/*!
  \internal
  */
QList<qreal> QSplineSeries::getFirstControlPoints(QList<qreal> rhs)
{
    QList<qreal> x; // Solution vector.
    QList<qreal> tmp; // Temp workspace.

    qreal b = 2.0;
    x.append(rhs[0] / b);
    tmp.append(0);
    for (int i = 1; i < rhs.size(); i++) // Decomposition and forward substitution.
    {
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
void QSplineSeries::updateControlPoints()
{
    if(m_x.size() > 1)
    {
        m_controlPoints.clear();
        calculateControlPoints();
    }
}

#include "moc_qsplineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
