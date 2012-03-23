#include "qchartglobal.h"
#include "qlegend.h"
#include "qseries.h"
#include "legendmarker_p.h"
#include "legendscrollbutton_p.h"
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
    ,m_brush(Qt::darkGray)       // TODO: from theme?
    ,mPreferredLayout(QLegend::PreferredLayoutTop)
    ,mFirstMarker(0)
    ,mMargin(5)
{
//    setVisible(false);

    mScrollButtonLeft = new LegendScrollButton(LegendScrollButton::ScrollButtonIdLeft, this);
    mScrollButtonRight = new LegendScrollButton(LegendScrollButton::ScrollButtonIdRight, this);
    mScrollButtonUp = new LegendScrollButton(LegendScrollButton::ScrollButtonIdUp, this);
    mScrollButtonDown = new LegendScrollButton(LegendScrollButton::ScrollButtonIdDown, this);

    connect(mScrollButtonLeft,SIGNAL(clicked(QGraphicsSceneMouseEvent*)),this,SLOT(handleScrollButtonClicked(QGraphicsSceneMouseEvent*)));
    connect(mScrollButtonRight,SIGNAL(clicked(QGraphicsSceneMouseEvent*)),this,SLOT(handleScrollButtonClicked(QGraphicsSceneMouseEvent*)));
    connect(mScrollButtonUp,SIGNAL(clicked(QGraphicsSceneMouseEvent*)),this,SLOT(handleScrollButtonClicked(QGraphicsSceneMouseEvent*)));
    connect(mScrollButtonDown,SIGNAL(clicked(QGraphicsSceneMouseEvent*)),this,SLOT(handleScrollButtonClicked(QGraphicsSceneMouseEvent*)));

    setZValue(ChartPresenter::LegendZValue);
}

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setOpacity(0.8);
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawRect(boundingRect());
}

QRectF QLegend::boundingRect() const
{
    return QRectF(mPos,mSize);
}

void QLegend::setBrush(const QBrush& brush)
{
    if(m_brush!=brush){
        m_brush = brush;
        update();
    }
}

QBrush QLegend::brush() const
{
    return m_brush;
}

void QLegend::setPen(const QPen& pen)
{
    if(m_pen!=pen){
        m_pen = pen;
        update();
    }
}

QPen QLegend::pen() const
{
    return m_pen;
}

void QLegend::setPreferredLayout(QLegend::PreferredLayout preferred)
{
    mPreferredLayout = preferred;
    updateLayout();
}

QLegend::PreferredLayout QLegend::preferredLayout() const
{
    return mPreferredLayout;
}

QSizeF QLegend::maximumSize() const
{
    return mMaximumSize;
}

void QLegend::setMaximumSize(const QSizeF size)
{
    mMaximumSize = size;
    updateLayout();
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
    updateLayout();
}

void QLegend::handleSeriesAdded(QSeries* series, Domain* domain)
{
    Q_UNUSED(domain)

    createMarkers(series);
    connectSeries(series);
    updateLayout();
}

void QLegend::handleSeriesRemoved(QSeries* series)
{
    disconnectSeries(series);

    if (series->type() == QSeries::SeriesTypeArea)
    {
        // This is special case. Area series has upper and lower series, which each have markers
        QAreaSeries* s = static_cast<QAreaSeries*> (series);
        deleteMarkers(s->upperSeries());
        deleteMarkers(s->lowerSeries());
    } else {
        deleteMarkers(series);
    }

    updateLayout();
}

void QLegend::handleAdded(QList<QPieSlice*> slices)
{
    QPieSeries* series = static_cast<QPieSeries*> (sender());
    foreach(QPieSlice* s, slices) {
        LegendMarker* marker = new LegendMarker(series,s,this);
        marker->setName(s->label());
        marker->setBrush(s->sliceBrush());
        connect(marker,SIGNAL(clicked(QPieSlice*,Qt::MouseButton)),this,SIGNAL(clicked(QPieSlice*,Qt::MouseButton)));
        connect(s,SIGNAL(changed()),marker,SLOT(changed()));
        connect(s,SIGNAL(destroyed()),marker,SLOT(deleteLater()));
        connect(marker,SIGNAL(destroyed()),this,SLOT(handleMarkerDestroyed()));
        mMarkers.append(marker);
        childItems().append(marker);
    }
    updateLayout();
}

void QLegend::handleRemoved(QList<QPieSlice *> slices)
{
    Q_UNUSED(slices)
    // Propably no need to listen for this, since removed slices are deleted and we listen destroyed signal
//    qDebug() << "QLegend::handleRemoved(QList<QPieSlice*> slices) count:" << slices.count();
}


void QLegend::handleMarkerDestroyed()
{
    // TODO: what if more than one markers are destroyed and we update layout after first one?
    LegendMarker* m = static_cast<LegendMarker*> (sender());
    mMarkers.removeOne(m);
    updateLayout();
}

void QLegend::handleScrollButtonClicked(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);    // Maybe later somethin happens with right click...

    // TODO: detect sender object. scroll to appropiate direction.
    LegendScrollButton* scrollButton = static_cast<LegendScrollButton*> (sender());
    Q_ASSERT(scrollButton);

    switch (scrollButton->id()) {
    case LegendScrollButton::ScrollButtonIdLeft:
    case LegendScrollButton::ScrollButtonIdUp: {
        // Lower limit is same in these cases
        mFirstMarker--;
        checkMarkerBounds();
        break;
    }
    case LegendScrollButton::ScrollButtonIdRight:
    case LegendScrollButton::ScrollButtonIdDown: {
        mFirstMarker++;
        checkMarkerBounds();
        break;
    }
    default: {
        break;
    }
    }
    updateLayout();
}

void QLegend::connectSeries(QSeries *series)
{
    // Connect relevant signals from series
    switch (series->type())
    {
    case QSeries::SeriesTypeLine: {
//        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeArea: {
//        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeBar: {
//        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeStackedBar: {
//        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        break;
    }
    case QSeries::SeriesTypePercentBar: {
//        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeScatter: {
//        QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
        break;
    }
    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        connect(pieSeries,SIGNAL(added(QList<QPieSlice*>)),this,SLOT(handleAdded(QList<QPieSlice*>)));
//        connect(pieSeries,SIGNAL(removed(QList<QPieSlice*>)),this,SLOT(handleRemoved(QList<QPieSlice*>)));
        break;
    }
    case QSeries::SeriesTypeSpline: {
//        QSplineSeries* splineSeries = static_cast<QSplineSeries*>(series);
        break;
    }
    default: {
        qDebug()<< "QLegend::connectSeries" << series->type() << "not implemented.";
        break;
    }
    }
}

void QLegend::disconnectSeries(QSeries *series)
{
    // Connect relevant signals from series
    switch (series->type())
    {
    case QSeries::SeriesTypeLine: {
//        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeArea: {
//        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeBar: {
//        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeStackedBar: {
//        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        break;
    }
    case QSeries::SeriesTypePercentBar: {
//        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        break;
    }
    case QSeries::SeriesTypeScatter: {
//        QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
        break;
    }
    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        disconnect(pieSeries,SIGNAL(added(QList<QPieSlice*>)),this,SLOT(handleAdded(QList<QPieSlice*>)));
//        disconnect(pieSeries,SIGNAL(removed(QList<QPieSlice*>)),this,SLOT(handleRemoved(QList<QPieSlice*>)));
        break;
    }
    case QSeries::SeriesTypeSpline: {
//        QSplineSeries* splineSeries = static_cast<QSplineSeries*>(series);
        break;
    }
    default: {
        qDebug()<< "QLegend::disconnectSeries" << series->type() << "not implemented.";
        break;
    }
    }
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
    connect(marker,SIGNAL(destroyed()),this,SLOT(handleMarkerDestroyed()));
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
        connect(s,SIGNAL(valueChanged()),marker,SLOT(changed()));
        connect(marker,SIGNAL(destroyed()),this,SLOT(handleMarkerDestroyed()));
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
        connect(s,SIGNAL(destroyed()),marker,SLOT(deleteLater()));
        connect(marker,SIGNAL(destroyed()),this,SLOT(handleMarkerDestroyed()));
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

void QLegend::updateLayout()
{
    // Calculate layout for markers and text
    if (mMarkers.count() <= 0) {
        // Nothing to do
        return;
    }
    checkMarkerBounds();

    // Find out widest item.
    QSizeF markerMaxSize = maximumMarkerSize();

    // Use max height as scroll button size
    rescaleScrollButtons(QSize(markerMaxSize.height() ,markerMaxSize.height()));

    qreal totalWidth = 0;
    qreal totalHeight = 0;
    switch (mPreferredLayout)
    {
    // Both cases organise items horizontally
    case QLegend::PreferredLayoutBottom:
    case QLegend::PreferredLayoutTop: {

        qreal xStep = markerMaxSize.width();
        qreal x = mPos.x() + mMargin;
        qreal y = mPos.y() + mMargin;
        int column = 0;
        int maxColumns = 1;
        qreal scrollButtonPadding = 0;

        // Set correct visibility for scroll scrollbuttons
        if (scrollButtonsVisible()) {
            mScrollButtonLeft->setVisible(true);
            mScrollButtonRight->setVisible(true);
            totalWidth += (mScrollButtonLeft->boundingRect().width() + mMargin) * 2;   // scrollbuttons visible, so add their width to total width
            x += mScrollButtonLeft->boundingRect().width() + mMargin;                  // start position changes by scrollbutton width
            scrollButtonPadding = mScrollButtonLeft->boundingRect().width();
        } else {
            mScrollButtonLeft->setVisible(false);
            mScrollButtonRight->setVisible(false);
        }
        mScrollButtonUp->setVisible(false);
        mScrollButtonDown->setVisible(false);

        for (int i=0; i<mMarkers.count(); i++) {
            LegendMarker* m = mMarkers.at(i);
            if (i<mFirstMarker) {
                // Markers before first are not visible.
                m->setVisible(false);
            } else {
                if ((x + xStep + scrollButtonPadding) > (mPos.x() + mMaximumSize.width())) {
                    // This marker would go outside legend rect.
                    m->setVisible(false);
                } else {
                    // This marker is ok
                    m->setVisible(true);
                    m->setPos(x,y);
                    x += xStep;
                    column++;
                }
            }
            maxColumns = column;
        }

        mScrollButtonLeft->setPos(mPos.x() + mMargin, y);
        mScrollButtonRight->setPos(x+mMargin,y);

        totalWidth += maxColumns * markerMaxSize.width() + mMargin * 2;
        totalHeight = markerMaxSize.height() + mMargin * 2;

        break;
    }
    // Both cases organize items vertically
    case QLegend::PreferredLayoutLeft:
    case QLegend::PreferredLayoutRight: {
        qreal yStep = markerMaxSize.height();
        qreal x = mPos.x() + mMargin;
        qreal y = mPos.y() + mMargin;
        int row = 1;
        int maxRows = 1;
        qreal scrollButtonPadding = 0;

        // Set correct visibility for scroll scrollbuttons
        if (scrollButtonsVisible()) {
            mScrollButtonUp->setVisible(true);
            mScrollButtonDown->setVisible(true);
            totalHeight += (mScrollButtonUp->boundingRect().height() + mMargin) * 2;   // scrollbuttons visible, so add their height to total height
            y += mScrollButtonUp->boundingRect().height() + mMargin;                  // start position changes by scrollbutton height
            scrollButtonPadding = mScrollButtonUp->boundingRect().height();
        } else {
            mScrollButtonUp->setVisible(false);
            mScrollButtonDown->setVisible(false);
        }
        mScrollButtonLeft->setVisible(false);
        mScrollButtonRight->setVisible(false);

        for (int i=0; i<mMarkers.count(); i++) {
            LegendMarker* m = mMarkers.at(i);
            if (i<mFirstMarker) {
                // Markers before first are not visible.
                m->setVisible(false);
            } else {
                if ((y + yStep + scrollButtonPadding) > (mPos.y() + mMaximumSize.height())) {
                    // This marker would go outside legend rect.
                    m->setVisible(false);
                } else {
                    // This marker is ok
                    m->setVisible(true);
                    m->setPos(x,y);
                    y += yStep;
                    row++;
                }
            }
            maxRows = row;
        }

        mScrollButtonUp->setPos(mPos.x() + mMargin, mPos.y() + mMargin);
        mScrollButtonDown->setPos(mPos.x() + mMargin, y + mMargin);

        totalWidth += markerMaxSize.width() + mMargin * 2;
        totalHeight = maxRows * markerMaxSize.height() + mMargin * 4 + scrollButtonPadding; // TODO: check this

        /*
        qreal yStep = markerMaxSize.height();
        qreal x = mPos.x() + mMargin;
        qreal y = mPos.y() + mMargin;
        int row = 0;
        int maxRows = 1;
        int maxColumns = 1;
        for (int i=0; i<mMarkers.count(); i++) {
            LegendMarker* m = mMarkers.at(i);
            if (i<mFirstMarker) {
                // Markers before first are not visible.
                m->setVisible(false);
            } else {
                if ((y + markerMaxSize.height() + mMargin*2) > (mPos.y() + mMaximumSize.height())) {
                    // This marker would go outside legend rect.
                    m->setVisible(false);
                } else {
                    // This marker is ok
                    m->setVisible(true);
                    maxRows = row;
                    m->setPos(x,y);
                    y += yStep;
                    row++;
                }
            }
            maxRows = row;
        }
        totalWidth = maxColumns * markerMaxSize.width() + mMargin * 2;
        totalHeight = maxRows * markerMaxSize.height() + mMargin * 2;
        */
        break;
    }
    default: {
        break;
    }
    }

    mSize.setWidth(totalWidth);
    mSize.setHeight(totalHeight);

    update();
}

void QLegend::rescaleScrollButtons(const QSize &size)
{
    QPolygonF left;
    left << QPointF(size.width(),0) << QPointF(0,size.height()/2) << QPointF(size.width(),size.height());
    QPolygonF right;
    right << QPointF(0,0) << QPointF(size.width(),size.height()/2) << QPointF(0,size.height());
    QPolygonF up;
    up << QPointF(0,size.height()) << QPointF(size.width()/2,0) << QPointF(size.width(),size.height());
    QPolygonF down;
    down << QPointF(0,0) << QPointF(size.width()/2,size.height()) << QPointF(size.width(),0);

    mScrollButtonLeft->setPolygon(left);
    mScrollButtonRight->setPolygon(right);
    mScrollButtonUp->setPolygon(up);
    mScrollButtonDown->setPolygon(down);
}

QSizeF QLegend::maximumMarkerSize()
{
    QSizeF max(0,0);
    foreach (LegendMarker* m, mMarkers) {
        if (m->boundingRect().width() > max.width()) {
            max.setWidth(m->boundingRect().width());
        }
        if (m->boundingRect().height() > max.height()) {
            max.setHeight(m->boundingRect().height());
        }
    }
    return max;
}

void QLegend::checkMarkerBounds()
{
    if ((mPreferredLayout == QLegend::PreferredLayoutLeft) || (mPreferredLayout == QLegend::PreferredLayoutRight)) {
        // Bounds limited by height
        int max;
        if (scrollButtonsVisible()) {
            max = (mMaximumSize.height() - mScrollButtonLeft->boundingRect().height() * 2 - mMargin*2) / maximumMarkerSize().height();
        } else {
            max = mMaximumSize.height() / maximumMarkerSize().height();
        }

        if (mFirstMarker > mMarkers.count() - max) {
            mFirstMarker = mMarkers.count() - max;
        }
    } else {
        // Bounds limited by width
        int max;
        if (scrollButtonsVisible()) {
            max = (mMaximumSize.width() - mScrollButtonLeft->boundingRect().width() * 2 - mMargin*2) / maximumMarkerSize().width();
        } else {
            max = mMaximumSize.width() / maximumMarkerSize().width();
        }

        if (mFirstMarker > mMarkers.count() - max) {
            mFirstMarker = mMarkers.count() - max;
        }
    }

    if (mFirstMarker < 0) {
        mFirstMarker = 0;
    }
}

bool QLegend::scrollButtonsVisible()
{
    // Just a helper to clarify, what the magic below means :)
    if ((mPreferredLayout == QLegend::PreferredLayoutTop) || (mPreferredLayout == QLegend::PreferredLayoutBottom)) {
        return (maximumMarkerSize().width() * mMarkers.count() + mMargin * 3 > mMaximumSize.width());
    }
    return (maximumMarkerSize().height() * mMarkers.count() + mMargin * 3 > mMaximumSize.height());
}

#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
