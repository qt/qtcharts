#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qchart.h"
#include <QPainter>
#include <QGraphicsScene>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

//#define QSeriesData QList<qreal>

QScatterSeriesPrivate::QScatterSeriesPrivate(QList<qreal> x, QList<qreal> y, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_x(x),
    m_y(y)
{
}

void QScatterSeriesPrivate::setSize()
{
}

QRectF QScatterSeriesPrivate::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
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
    QTransform transform = painter->transform();

    // TODO: get min and max values of the axes from the QChart (or some dedicated class)
    const qreal xmin = 0.0;
    const qreal xmax = 100.0;
    const qreal xscale = scene()->width() / (xmax - xmin);
    const qreal ymin = 0.0;
    const qreal ymax = 100.0;
    const qreal yscale = scene()->height() / (ymax - ymin);

    for (int i(0); i < m_x.count() && i < m_y.count(); i++) {
        transform.reset();
        transform.translate(m_x.at(i) * xscale, m_y.at(i) * yscale);
        painter->setTransform(transform);
        painter->drawArc(0, 0, 4, 4, 0, 5760);
    }
}

QScatterSeries::QScatterSeries(QList<qreal> x, QList<qreal> y, QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate(x, y, qobject_cast<QGraphicsItem *> (parent)))
{
}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
