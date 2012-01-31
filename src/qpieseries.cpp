#include "qpieseries_p.h"
#include "qpieseries.h"
#include <QGraphicsObject>
#include "pieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeriesPrivate::QPieSeriesPrivate() :
    m_sizeFactor(1.0),
    m_position(QPieSeries::PiePositionMaximized)
{
}

QPieSeriesPrivate::~QPieSeriesPrivate()
{
    while (m_slices.count())
        delete m_slices.takeLast();
}

bool QPieSeriesPrivate::setData(QList<qreal> data)
{
    m_data = data;

    if (m_parentItem) {
        // Create slices
        qreal fullPie = 360;
        qreal total = 0;
        foreach (qreal value, m_data)
            total += value;

        m_chartSize = m_parentItem->boundingRect();
        qreal angle = 0;
        // TODO: no need to create new slices in case size changed; we should re-use the existing ones
        foreach (qreal value, m_data) {
            qreal span = value / total * fullPie;
            PieSlice *slice = new PieSlice(QColor(), angle, span, m_parentItem->boundingRect());
            slice->setParentItem(m_parentItem);
            m_slices.append(slice);
            angle += span;
        }

        setTheme(m_chartTheme);
        resizeSlices(m_chartSize);
    }

    return true;
}

void QPieSeriesPrivate::setPos(const QPointF & pos)
{
    // TODO
}

void QPieSeriesPrivate::resize(const QSize &size)
{
    // TODO: allow user setting the size?
    // TODO: allow user defining the margins?
    m_chartSize = QRect(0, 0, size.width(), size.height());
    resizeSlices(m_chartSize);
}

void QPieSeriesPrivate::setTheme(ChartTheme *theme)
{
    if (theme) {
        m_chartTheme = theme;
        for (int i(0); i < m_slices.count(); i++)
            m_slices.at(i)->m_theme = theme->themeForSeries();
    }
}

void QPieSeriesPrivate::setPlotDomain(const PlotDomain& plotDomain)
{
    // TODO
}

void QPieSeriesPrivate::resizeSlices(QRectF rect)
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

    switch (m_position) {
        case QPieSeries::PiePositionTopLeft: {
            tempRect.setHeight(tempRect.height() / 2);
            tempRect.setWidth(tempRect.height());
            tempRect.moveCenter(QPointF(rect.center().x() / 2, rect.center().y() / 2));
            break;
        }
        case QPieSeries::PiePositionTopRight: {
            tempRect.setHeight(tempRect.height() / 2);
            tempRect.setWidth(tempRect.height());
            tempRect.moveCenter(QPointF((rect.center().x() / 2) * 3, rect.center().y() / 2));
            break;
        }
        case QPieSeries::PiePositionBottomLeft: {
            tempRect.setHeight(tempRect.height() / 2);
            tempRect.setWidth(tempRect.height());
            tempRect.moveCenter(QPointF(rect.center().x() / 2, (rect.center().y() / 2) * 3));
            break;
        }
        case QPieSeries::PiePositionBottomRight: {
            tempRect.setHeight(tempRect.height() / 2);
            tempRect.setWidth(tempRect.height());
            tempRect.moveCenter(QPointF((rect.center().x() / 2) * 3, (rect.center().y() / 2) * 3));
            break;
        }
        default:
            break;
    }

    foreach (PieSlice *slice, m_slices)
        slice->m_rect = tempRect;
}

QPieSeries::QPieSeries(QGraphicsObject *parent) :
    QChartSeries(parent),
    d(new QPieSeriesPrivate())
{
    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent);
    if (parentItem)
        d->m_parentItem = parentItem;
}

QPieSeries::~QPieSeries()
{
    delete d;
}

bool QPieSeries::setData(QList<qreal> data)
{
    return d->setData(data);
}

void QPieSeries::setSliceColor(int index, QColor color)
{
    if (index >= 0 && index < d->m_slices.count())
        d->m_slices.at(index)->m_color = color;
}

QColor QPieSeries::sliceColor(int index)
{
    if (index >= 0 && index < d->m_slices.count())
        return d->m_slices.at(index)->m_color;
    else
        return QColor();
}

int QPieSeries::sliceCount()
{
    return d->m_slices.count();
}

void QPieSeries::setSizeFactor(qreal factor)
{
    if (factor > 0.0)
        d->m_sizeFactor = factor;
    d->resizeSlices(d->m_chartSize);

    // Initiate update via the parent graphics item
    // TODO: potential issue: what if this function is called from the parent context?
    if (d->m_parentItem)
        d->m_parentItem->update();
}

qreal QPieSeries::sizeFactor()
{
    return d->m_sizeFactor;
}

void QPieSeries::setPosition(PiePosition position)
{
    d->m_position = position;
    d->resizeSlices(d->m_chartSize);

    // Initiate update via the parent graphics item
    // TODO: potential issue: what if this function is called from the parent context?
    QGraphicsItem *parentItem = qobject_cast<QGraphicsItem *>(parent());
    Q_ASSERT(parentItem);
    parentItem->update();
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
