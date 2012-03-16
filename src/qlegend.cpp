#include "qchartglobal.h"
#include "qlegend.h"
#include "qseries.h"
#include "legendmarker_p.h"
#include "qxyseries.h"
#include "qlineseries.h"
#include "qareaseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qbarset.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QPen>

#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QLegend::QLegend(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mPos(0,0)
    ,mSize(0,0)
    ,mMinimumSize(50,20)                // TODO: magic numbers
    ,mMaximumSize(150,100)
    ,mBackgroundBrush(Qt::darkGray)     // TODO: from theme?
    ,mPreferredLayout(QLegend::PreferredLayoutVertical)
{
//    setVisible(false);
    setZValue(ChartPresenter::LegendZValue);
}

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setOpacity(0.5);
    painter->setBrush(mBackgroundBrush);
    painter->drawRect(boundingRect());
}

QRectF QLegend::boundingRect() const
{
    return QRectF(mPos,mSize);
}

void QLegend::setBackgroundBrush(const QBrush& brush)
{
    mBackgroundBrush = brush;
}

QBrush QLegend::backgroundBrush() const
{
    return mBackgroundBrush;
}

void QLegend::setPreferredLayout(QLegend::PreferredLayout preferred)
{
    mPreferredLayout = preferred;
    layoutChanged();
}

QSizeF QLegend::maximumSize() const
{
    return mMaximumSize;
}

void QLegend::setMaximumSize(const QSizeF size)
{
    mMaximumSize = size;
}

void QLegend::setSize(const QSizeF size)
{
    mSize = size;
    if (mSize.width() > mMaximumSize.width()) {
        mSize.setWidth(mMaximumSize.width());
    }
    if (mSize.height() > mMaximumSize.height()) {
        mSize.setHeight(mMaximumSize.height());
    }
}

void QLegend::setPos(const QPointF &pos)
{
    mPos = pos;
}

void QLegend::handleSeriesAdded(QSeries* series, Domain* domain)
{
    Q_UNUSED(domain)

    mSeriesList.append(series);
    createMarkers(series);
    layoutChanged();
}

void QLegend::handleSeriesRemoved(QSeries* series)
{
    if (series->type() == QSeries::SeriesTypeArea)
    {
        // This is special case. Area series has upper and lower series, which each have markers
        QAreaSeries* s = static_cast<QAreaSeries*> (series);
        deleteMarkers(s->upperSeries());
        deleteMarkers(s->lowerSeries());
    } else {
        deleteMarkers(series);
    }

    mSeriesList.removeOne(series);
    layoutChanged();
}

void QLegend::createMarkers(QSeries *series)
{
    switch (series->type())
    {
    case QSeries::SeriesTypeLine: {
        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        appendMarkers(lineSeries);
        break;
    }
    case QSeries::SeriesTypeArea: {
        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        appendMarkers(areaSeries->upperSeries());
        if(areaSeries->lowerSeries())
        appendMarkers(areaSeries->lowerSeries());
        break;
    }

    case QSeries::SeriesTypeBar: {
        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        appendMarkers(barSeries);
        break;
    }

    case QSeries::SeriesTypeStackedBar: {
        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        appendMarkers(stackedBarSeries);
        break;
    }

    case QSeries::SeriesTypePercentBar: {
        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        appendMarkers(percentBarSeries);
        break;
    }

    case QSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
        appendMarkers(scatterSeries);
        break;
    }

    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        appendMarkers(pieSeries);
        break;
    }

    case QSeries::SeriesTypeSpline: {
        QSplineSeries* splineSeries = static_cast<QSplineSeries*>(series);
        appendMarkers(splineSeries);
        break;
    }
    default: {
        qDebug()<< "QLegend::createMarkers" << series->type() << "not implemented.";
        break;
    }
    }
}

void QLegend::appendMarkers(QXYSeries* series)
{
    LegendMarker* marker = new LegendMarker(series,this);
    marker->setName(series->name());
    marker->setBrush(series->brush());
    connect(marker,SIGNAL(clicked(QSeries*,Qt::MouseButton)),this,SIGNAL(clicked(QSeries*,Qt::MouseButton)));
    mMarkers.append(marker);
    childItems().append(marker);
}

void QLegend::appendMarkers(QBarSeries *series)
{
    foreach(QBarSet* s, series->barSets()) {
        LegendMarker* marker = new LegendMarker(series,s,this);
        marker->setName(s->name());
        marker->setBrush(s->brush());
        connect(marker,SIGNAL(clicked(QBarSet*,Qt::MouseButton)),this,SIGNAL(clicked(QBarSet*,Qt::MouseButton)));
        connect(s,SIGNAL(changed()),marker,SLOT(changed()));
        mMarkers.append(marker);
        childItems().append(marker);
    }
}

void QLegend::appendMarkers(QPieSeries *series)
{
    foreach(QPieSlice* s, series->slices()) {
        LegendMarker* marker = new LegendMarker(series,s,this);
        marker->setName(s->label());
        marker->setBrush(s->sliceBrush());
        connect(marker,SIGNAL(clicked(QPieSlice*,Qt::MouseButton)),this,SIGNAL(clicked(QPieSlice*,Qt::MouseButton)));
        connect(s,SIGNAL(changed()),marker,SLOT(changed()));
        mMarkers.append(marker);
        childItems().append(marker);
    }
}

void QLegend::deleteMarkers(QSeries *series)
{
    // Search all markers that belong to given series and delete them.
    foreach (LegendMarker *m, mMarkers) {
        if (m->series() == series) {
            mMarkers.removeOne(m);
            delete m;
        }
    }
}

void QLegend::layoutChanged()
{
    // Calculate layout for markers and text
    if (mMarkers.count() <= 0) {
        // Nothing to do
        return;
    }

    // Find out widest item.
    qreal itemMaxWidth = 0;
    qreal itemMaxHeight = 0;
    foreach (LegendMarker* m, mMarkers) {
        if (m->boundingRect().width() > itemMaxWidth) {
            itemMaxWidth = m->boundingRect().width();
        }
        if (m->boundingRect().height() > itemMaxHeight) {
            itemMaxHeight = m->boundingRect().height();
        }
    }

    int maxHorizontalItems = boundingRect().width() / itemMaxWidth;
    int maxVerticalItems = boundingRect().height() / itemMaxHeight;

    if (mMarkers.count() > maxHorizontalItems * maxVerticalItems) {
        // TODO: overlapping layout
        qDebug() << "Warning. Not enough space to layout all legend items properly.";
    }

    qreal margin = 5;
    qreal totalWidth = 0;
    qreal totalHeight = 0;
    switch (mPreferredLayout)
    {
    case QLegend::PreferredLayoutHorizontal: {
        /*
        qreal xStep = mMaximumSize.width() / (mMarkers.count()+1);
        if (xStep > itemMaxWidth) {
            xStep = itemMaxWidth;
        }
        qreal yStep = mMaximumSize.height() / (mMarkers.count()+1);
        if (yStep > itemMaxHeight) {
            yStep = itemMaxHeight;
        }*/
        qreal xStep = itemMaxWidth;
        qreal yStep = itemMaxHeight;
        qreal x = mPos.x() + margin;
        qreal y = mPos.y() + margin;
        int row = 1;
        int column = 0;
        int maxRows = 1;
        int maxColumns = 1;
        foreach (LegendMarker* m, mMarkers) {
            maxRows = row;
            m->setPos(x,y);
            x += xStep;
            column++;
            if (column > maxColumns) {
                maxColumns = column;
            }
            if ((x + itemMaxWidth + margin*2) > (mPos.x() + mMaximumSize.width())) {
                x = mPos.x() + margin;
                y += yStep;
                row++;
                column = 0;
            }
        }
        totalWidth = maxColumns * itemMaxWidth + margin * 2;
        totalHeight = maxRows * itemMaxHeight + margin * 2;
        break;
    }
    case QLegend::PreferredLayoutVertical: {
        /*
        qreal xStep = mMaximumSize.width() / (mMarkers.count()+1);
        if (xStep > itemMaxWidth) {
            xStep = itemMaxWidth;
        }
        qreal yStep = mMaximumSize.height() / (mMarkers.count()+1);
        if (yStep > itemMaxHeight) {
            yStep = itemMaxHeight;
        }*/
        qreal xStep = itemMaxWidth;
        qreal yStep = itemMaxHeight;
        qreal x = mPos.x() + margin;
        qreal y = mPos.y() + margin;
        int row = 0;
        int column = 1;
        int maxRows = 1;
        int maxColumns = 1;
        foreach (LegendMarker* m, mMarkers) {
            maxColumns = column;
            m->setPos(x,y);
            y += yStep;
            row++;
            if (row > maxRows) {
                maxRows = row;
            }
            if ((y + itemMaxHeight + margin*2) > (mPos.y() + mMaximumSize.height())) {
                y = mPos.y() + margin;
                x += xStep;
                column++;
                row = 0;
            }
        }
        totalWidth = maxColumns * itemMaxWidth + margin * 2;
        totalHeight = maxRows * itemMaxHeight + margin * 2;
        break;
    }
    default: {
        break;
    }
    }

    mSize.setWidth(totalWidth);
    mSize.setHeight(totalHeight);
}

#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
