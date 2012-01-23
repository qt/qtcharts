#include "qpieseries.h"
#include "pieslice.h"
#include <QGraphicsObject>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeries::QPieSeries(QList<qreal> x, QGraphicsObject *parent) :
    QChartSeries(parent),
    m_x(x)
{
    // Create slices
    qreal fullPie = 360;
    qreal total = 0;
    foreach (qreal value, m_x)
        total += value;

    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent);
    Q_ASSERT(parentItem);
    qreal angle = 0;
    // TODO: no need to create new slices in case size changed; we should re-use the existing ones
    foreach (qreal value, m_x) {
        qreal span = value / total * fullPie;
        PieSlice *slice = new PieSlice(randomColor(), angle, span);
        slice->setParentItem(parentItem);
        m_slices.append(slice);
        angle += span;
    }
}

QPieSeries::~QPieSeries()
{
}

void QPieSeries::chartSizeChanged(QRectF /*rect*/)
{
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
