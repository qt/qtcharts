#include "qpieseries.h"
#include "pieslice.h"
#include <QGraphicsObject>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeries::QPieSeries(QList<qreal> x, QGraphicsObject *parent) :
    QChartSeries(parent),
    m_x(x),
    m_sizeFactor(1.0)
{
    // Create slices
    qreal fullPie = 360;
    qreal total = 0;
    foreach (qreal value, m_x)
        total += value;

    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent);
    Q_ASSERT(parentItem);
    m_chartSize = parentItem->boundingRect();
    qreal angle = 0;
    // TODO: no need to create new slices in case size changed; we should re-use the existing ones
    foreach (qreal value, m_x) {
        qreal span = value / total * fullPie;
        PieSlice *slice = new PieSlice(randomColor(), angle, span, parentItem->boundingRect());
        slice->setParentItem(parentItem);
        m_slices.append(slice);
        angle += span;
    }

    resizeSlices(m_chartSize);
}

QPieSeries::~QPieSeries()
{
    while (m_slices.count())
        delete m_slices.takeLast();
}

void QPieSeries::chartSizeChanged(QRectF chartRect)
{
    // TODO: allow user setting the size?
    // TODO: allow user defining the margins?
    m_chartSize = chartRect;
    resizeSlices(m_chartSize);
}

void QPieSeries::resizeSlices(QRectF rect)
{
    QRectF tempRect = rect;
    if (tempRect.width() < tempRect.height()) {
        tempRect.setWidth(tempRect.width() * m_sizeFactor);
        tempRect.setHeight(tempRect.width());
        tempRect.moveCenter(rect.center());
    } else {
        tempRect.setHeight(tempRect.height() * m_sizeFactor);
        tempRect.setWidth(tempRect.height());
        tempRect.moveCenter(rect.center());
    }

    foreach (PieSlice *slice, m_slices)
        slice->m_rect = tempRect;
}

void QPieSeries::setSizeFactor(qreal factor)
{
    if (factor > 0.0)
        m_sizeFactor = factor;
    resizeSlices(m_chartSize);

    // Initiate update via the parent graphics item
    // TODO: potential issue: what if this function is called from the parent context?
    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent());
    Q_ASSERT(parentItem);
    parentItem->update();
}

QColor QPieSeries::randomColor()
{
    QColor c;
    c.setRed(qrand() % 255);
    c.setGreen(qrand() % 255);
    c.setBlue(qrand() % 255);
    return c;
}


#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
