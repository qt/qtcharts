#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QScatterSeriesPrivate::QScatterSeriesPrivate() :
    m_data(QList<QPointF>())
{
}

QScatterSeries::QScatterSeries(QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate())
{
}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

// TODO: change to list of QPointFs?
bool QScatterSeries::setData(QList<qreal> xlist, QList<qreal> ylist)
{
    d->m_data.clear();
    // TODO: validate data
    for (int i(0); i < xlist.count() && i < ylist.count(); i++) {
        d->m_data.append(QPointF(xlist[i], ylist[i]));
    }


    // TODO: the following updates the visible chart area setting of the series, we would instead
    // need to update the _chart's_ visible area... this would require a callback or
    // similar to the parenting QChart object...
//    foreach (qreal x, d->m_x) {
//        d->m_visibleChartArea.m_minX = qMin(d->m_visibleChartArea.m_minX, x);
//        d->m_visibleChartArea.m_maxX = qMax(d->m_visibleChartArea.m_maxX, x);
//    }
//    foreach (qreal y, d->m_y) {
//        d->m_visibleChartArea.m_minY = qMin(d->m_visibleChartArea.m_minY, y);
//        d->m_visibleChartArea.m_maxY = qMax(d->m_visibleChartArea.m_maxY, y);
//    }
//    d->changeGeometry();

    emit changed();
    return true;
}

QList<QPointF> QScatterSeries::data()
{
    return d->m_data;
}

void QScatterSeries::setMarkerColor(QColor color)
{
    // TODO:
//    d->m_markerColor = color;
}

QColor QScatterSeries::markerColor()
{
    // TODO:
//    return d->m_markerColor;
    return QColor();
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
