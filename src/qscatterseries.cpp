#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qchart.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

//#define QSeriesData QList<qreal>

QScatterSeriesPrivate::QScatterSeriesPrivate(QList<qreal> x, QList<qreal> y, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_x(x),
    m_y(y)
{
}

void QScatterSeriesPrivate::resize(QRectF rect, qreal xscale, qreal yscale)
{
    m_scenex.clear();
    m_sceney.clear();

    foreach(qreal x, m_x)
        m_scenex.append(rect.left() + x * xscale);

    foreach(qreal y, m_y)
        m_sceney.append(rect.bottom() - y * yscale);
}

QRectF QScatterSeriesPrivate::boundingRect() const
{
    return QRectF(0, 0, 55, 100);
}

void QScatterSeriesPrivate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = painter->pen();
    QBrush brush = pen.brush();
    // TODO: The opacity should be user definable...
    brush.setColor(QColor(255, 82, 0, 50));
    pen.setBrush(brush);
    pen.setWidth(4);
    painter->setPen(pen);

    // TODO: m_scenex and m_sceny are left empty during construction -> we would need a resize
    // event right after construction or maybe given a size during initialization
    for (int i(0); i < m_scenex.count() && i < m_sceney.count(); i++) {
        if (scene()->width() > m_scenex.at(i) && scene()->height() > m_sceney.at(i))
            //painter->drawArc(m_scenex.at(i), m_sceney.at(i), 2, 2, 0, 5760);
            painter->drawPoint(m_scenex.at(i), m_sceney.at(i));
    }
}

QScatterSeries::QScatterSeries(QList<qreal> x, QList<qreal> y, QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate(x, y, qobject_cast<QGraphicsItem *> (parent)))
{
    connect(parent, SIGNAL(sizeChanged(QRectF, qreal, qreal)), this, SLOT(chartSizeChanged(QRectF, qreal, qreal)));
}

void QScatterSeries::chartSizeChanged(QRectF rect, qreal xscale, qreal yscale)
{
    // Recalculate scatter data point locations on the scene
//    d->transform().reset();
//    d->transform().translate();
    d->resize(rect, xscale, yscale);
}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
