#include "qpieseries.h"
#include "pieslice.h"
#include <QGraphicsObject>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeries::QPieSeries(QList<qreal> x, QGraphicsObject *parent) :
    QChartSeries(parent),
    m_x(x)
{
}

QPieSeries::~QPieSeries()
{
}

void QPieSeries::chartSizeChanged(QRectF rect, qreal xscale, qreal yscale)
{
    qreal fullPie = 360;
    qreal total = 0;
    foreach (qreal value, m_x)
        total += value;

    // We must have a parent for the graphics items we create
    // TODO: maybe QChartSeries needs to be a QGraphicsObject to make this clear for the users?
    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent());
    Q_ASSERT(parentItem);
    qreal angle = 0;
    foreach (qreal value, m_x) {
        qreal span = value / total * fullPie;
        PieSlice *slice = new PieSlice(randomColor(), angle, span);
        slice->setParentItem(parentItem);
        m_slices.append(slice);
        angle += span;
    }
}

QColor QPieSeries::randomColor()
{
    QColor c;
    c.setRed(qrand() % 255);
    c.setGreen(qrand() % 255);
    c.setBlue(qrand() % 255);
    return c;
}

void QPieSeries::setData(QList<int> data)
{
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
