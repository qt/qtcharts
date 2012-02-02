#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qchart.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

//#define QSeriesData QList<qreal>

QScatterSeriesPrivate::QScatterSeriesPrivate(QGraphicsItem *parent) :
    ChartItem(parent),
    m_markerColor(QColor()),
    m_visibleChartArea(),
    m_boundingRect()
{
    if (parent)
        m_boundingRect = parent->boundingRect();
}

void QScatterSeriesPrivate::changeGeometry()
{
    if (m_boundingRect.isValid()) {
        prepareGeometryChange();
        qreal scalex = m_boundingRect.width() / m_visibleChartArea.spanX();
        qreal scaley = m_boundingRect.height() / m_visibleChartArea.spanY();
        m_scenex.clear();
        m_sceney.clear();

        // Convert relative coordinates to absolute pixel coordinates that can be used for drawing
        foreach(qreal x, m_x)
            m_scenex.append(m_boundingRect.left() + x * scalex - m_visibleChartArea.m_minX * scalex);

        foreach(qreal y, m_y)
            m_sceney.append(m_boundingRect.bottom() - y * scaley + m_visibleChartArea.m_minY * scaley);
    }
}

void QScatterSeriesPrivate::setSize(const QSizeF &size)
{
//    m_boundingRect = QRectF(pos().x(), pos().y(), size.width(), size.height());
    m_boundingRect = QRectF(0, 0, size.width(), size.height());
    changeGeometry();
}

void QScatterSeriesPrivate::themeChanged(ChartTheme *theme)
{
    m_theme = theme->themeForSeries();
}

void QScatterSeriesPrivate::setPlotDomain(const PlotDomain& plotDomain)
{
    m_visibleChartArea = plotDomain;
    changeGeometry();
}

QRectF QScatterSeriesPrivate::boundingRect() const
{
    return m_boundingRect;
}

void QScatterSeriesPrivate::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    // TODO: The opacity should be user definable?
    //brush.setColor(QColor(255, 82, 0, 100));
    if (m_markerColor.isValid()) {
        QPen pen = painter->pen();
        QBrush brush = pen.brush();
        brush.setColor(m_markerColor);
        pen.setBrush(brush);
        pen.setWidth(4);
        painter->setPen(pen);
    }
    else
        painter->setPen(m_theme.markerPen);
//        brush.setColor(m_theme..lineColor);

    // TODO: m_scenex and m_sceny are left empty during construction -> we would need a resize
    // event right after construction or maybe given a size during initialization
    for (int i(0); i < m_scenex.count() && i < m_sceney.count(); i++) {
        if (scene()->width() > m_scenex.at(i) && scene()->height() > m_sceney.at(i))
            //painter->drawArc(m_scenex.at(i), m_sceney.at(i), 2, 2, 0, 5760);
            painter->drawPoint(m_scenex.at(i), m_sceney.at(i));
    }
}

QScatterSeries::QScatterSeries(QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate(qobject_cast<QGraphicsItem *> (parent)))
{
}

bool QScatterSeries::setData(QList<qreal> xlist, QList<qreal> ylist)
{
    // TODO: validate data
    d->m_x = xlist;
    d->m_y = ylist;

    // TODO: the following updates the visible chart area setting of the series, we would instead
    // need to update the _chart's_ visible area... this would require a callback or
    // similar to the parenting QChart object...
    foreach (qreal x, d->m_x) {
        d->m_visibleChartArea.m_minX = qMin(d->m_visibleChartArea.m_minX, x);
        d->m_visibleChartArea.m_maxX = qMax(d->m_visibleChartArea.m_maxX, x);
    }
    foreach (qreal y, d->m_y) {
        d->m_visibleChartArea.m_minY = qMin(d->m_visibleChartArea.m_minY, y);
        d->m_visibleChartArea.m_maxY = qMax(d->m_visibleChartArea.m_maxY, y);
    }

    d->changeGeometry();

    return true;
}

void QScatterSeries::setMarkerColor(QColor color)
{
    d->m_markerColor = color;
}

QColor QScatterSeries::markerColor()
{
    return d->m_markerColor;
}

// TODO:
//void QScatterSeries::chartScaleChanged(qreal xscale, qreal yscale)
//{
//    d->rescale(xscale, yscale);
//}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
