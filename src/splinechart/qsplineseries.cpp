#include "qsplineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QSplineSeries::QSplineSeries(QObject *parent) :
    QChartSeries(parent)
{
}

QSplineSeries& QSplineSeries::operator << (const QPointF &value)
{
//    d->m_data.append(value);
    m_data.append(value);
//    emit changed();
    return *this;
}

void QSplineSeries::addData(QPointF value)
{
    m_data.append(value);
}

void QSplineSeries::calculateControlPoints()
{

    // Based on http://www.codeproject.com/Articles/31859/Draw-a-Smooth-Curve-through-a-Set-of-2D-Points-wit
    // CPOL Licence

    int n = m_data.size() - 1;
    if (n == 1)
    { // Special case: Bezier curve should be a straight line.
        //            firstControlPoints = new Point[1];
        // 3P1 = 2P0 + P3
        m_controlPoints.append(QPointF((2 * m_data[0].x() + m_data[1].x()) / 3, (2 * m_data[0].y() + m_data[1].y()) / 3));

        // P2 = 2P1  P0
        m_controlPoints.append(QPointF(2 * m_controlPoints[0].x() - m_data[0].x(), 2 * m_controlPoints[0].y() - m_data[0].y()));
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
    rhs.append(m_data[0].x() + 2 * m_data[1].x());

    // Set right hand side X values
    for (int i = 1; i < m_data.size() - 1; ++i)
        rhs.append(4 * m_data[i].x() + 2 * m_data[i + 1].x());

    rhs.append((8 * m_data[n - 1].x() + m_data[n].x()) / 2.0);
    // Get first control points X-values
    QList<qreal> x = getFirstControlPoints(rhs);
    rhs[0] = m_data[0].y() + 2 * m_data[1].y();

    // Set right hand side Y values
    for (int i = 1; i < m_data.size() - 1; ++i)
        rhs[i] = 4 * m_data[i].y() + 2 * m_data[i + 1].y();

    rhs[n - 1] = (8 * m_data[n - 1].y() + m_data[n].y()) / 2.0;
    // Get first control points Y-values
    QList<qreal> y = getFirstControlPoints(rhs);

    // Fill output arrays.
    //        firstControlPoints = new Point[n];
    //        secondControlPoints = new Point[n];
    for (int i = 0; i < m_data.size(); ++i)
    {
        // First control point
        m_controlPoints.append(QPointF(x[i], y[i]));
        // Second control point
        if (i < n - 1)
            m_controlPoints.append(QPointF(2 * m_data[i + 1].x() - x[i + 1], 2 * m_data[i + 1].y() - y[i + 1]));
        else
            m_controlPoints.append(QPointF((m_data[n].x() + x[n - 1]) / 2, (m_data[n].y() + y[n - 1]) / 2));
    }
}

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
#include "moc_qsplineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
