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
    m_visibleChartArea()
{
}

void QScatterSeriesPrivate::resize(QRectF rect)
{
    qreal scalex = rect.width() / m_visibleChartArea.spanX();
    qreal scaley = rect.height() / m_visibleChartArea.spanY();

    m_scenex.clear();
    m_sceney.clear();

    // Convert relative coordinates to absolute pixel coordinates that can be used for drawing
    foreach(qreal x, m_x)
        m_scenex.append(rect.left() + x * scalex - m_visibleChartArea.m_minX * scalex);

    foreach(qreal y, m_y)
        m_sceney.append(rect.bottom() - y * scaley - m_visibleChartArea.m_minY * scaley);
}

void QScatterSeriesPrivate::setSize(const QSize &size)
{
    QGraphicsItem *parent = this->parentItem();
    if (parent)
        resize(QRectF(parent->pos(), size));
}

void QScatterSeriesPrivate::themeChanged(ChartTheme *theme)
{
    m_theme = theme->themeForSeries();
}

void QScatterSeriesPrivate::setPlotDomain(const PlotDomain& plotDomain)
{
    m_visibleChartArea = plotDomain;
    resize(parentItem()->boundingRect());
}

QRectF QScatterSeriesPrivate::boundingRect() const
{
    return QRectF(0, 0, 55, 100);
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

bool QScatterSeries::setData(QList<qreal> x, QList<qreal> y)
{
    // TODO: validate data
    d->m_x = x;
    d->m_y = y;
    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent());
    Q_ASSERT(parentItem);
//    d->setPos(parentItem->pos());
//    d->setSize(parentItem->boundingRect().size().toSize());
    d->resize(parentItem->boundingRect());
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
