#include "qlegend.h"
#include "qchart_p.h"
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

/*!
    \class QLegend
    \brief part of QtCommercial chart API.

    QLegend is a graphical object, whics displays legend of the chart. Legend state is updated by QChart, when
    series have been changed. By default, legend is drawn by QChart, but user can set a new parent to legend and
    handle the drawing manually.
    User isn't supposed to create or delete legend objects, but can reference it via QChart class.

    \mainclass

    \sa QChart, QSeries
*/

/*!
    \enum QLegend::Layout

    This enum describes the possible position for legend inside chart.

    \value LayoutTop
    \value LayoutBottom
    \value LayoutLeft
    \value LayoutRight
*/


/*!
    \fn void QLegend::clicked(QSeries* series, Qt::MouseButton button)
    \brief Notifies when series has been clicked on legend \a series \a button
*/

/*!
    \fn void QLegend::clicked(QBarSet* barset, Qt::MouseButton button)
    \brief Notifies when barset has been clicked on legend \a barset \a button
*/

/*!
    \fn void QLegend::clicked(QPieSlice* slice, Qt::MouseButton button)
    \brief Notifies when pie slice has been clicked on legend \a slice \a button
*/

/*!
    Constructs the legend object and sets the parent to \a parent
*/
QLegend::QLegend(QChart *chart):QGraphicsWidget(chart->d_ptr->m_presenter->rootItem()),
    m_margin(5),
    m_pos(0,0),
    m_minimumSize(50,20),                // TODO: magic numbers
    m_maximumSize(150,100),
    m_size(m_minimumSize),
    m_brush(Qt::darkGray),              // TODO: default should come from theme
    m_alignment(QLegend::LayoutTop),
    mFirstMarker(0)
{
    m_scrollButtonLeft = new LegendScrollButton(LegendScrollButton::ScrollButtonIdLeft, this);
    m_scrollButtonRight = new LegendScrollButton(LegendScrollButton::ScrollButtonIdRight, this);
    m_scrollButtonUp = new LegendScrollButton(LegendScrollButton::ScrollButtonIdUp, this);
    m_scrollButtonDown = new LegendScrollButton(LegendScrollButton::ScrollButtonIdDown, this);
    setZValue(ChartPresenter::LegendZValue);
}

/*!
    Paints the legend to given \a painter. Paremeters \a option and \a widget arent used.
*/
void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setOpacity(opacity());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
//    painter->drawRect(boundingRect());
}

/*!
    Bounding rect of legend.
*/
QRectF QLegend::boundingRect() const
{
    return QRectF(m_pos,m_size);
}

/*!
    Sets the \a brush of legend. Brush affects the background of legend.
*/
void QLegend::setBrush(const QBrush &brush)
{
    if (m_brush != brush) {
        m_brush = brush;
        update();
    }
}

/*!
    Returns the brush used by legend.
*/
QBrush QLegend::brush() const
{
    return m_brush;
}

/*!
    Sets the \a pen of legend. Pen affects the legend borders.
*/
void QLegend::setPen(const QPen &pen)
{
    if (m_pen != pen) {
        m_pen = pen;
        update();
    }
}

/*!
    Returns the pen used by legend
*/

QPen QLegend::pen() const
{
    return m_pen;
}

/*!
    Sets the \a preferred layout for legend. Legend tries to paint itself on the defined position in chart.
    \sa QLegend::Layout
*/
void QLegend::setAlignmnent(QLegend::Layout alignment)
{
    m_alignment = alignment;
    updateLayout();
}

/*!
    Returns the preferred layout for legend
*/
QLegend::Layout QLegend::alignment() const
{
    return m_alignment;
}

/*!
    Returns the maximum size of legend.
*/
QSizeF QLegend::maximumSize() const
{
    return m_maximumSize;
}

/*!
    Sets the maximum \a size for legend. The legend can't grow bigger than this size. If there are
    more series than legend can fit to this size, scroll buttons are displayed.
*/
void QLegend::setMaximumSize(const QSizeF size)
{
    m_maximumSize = size;
    updateLayout();
}

/*!
    Returns the current size of legend.
*/
QSizeF QLegend::size() const
{
    return m_size;
}

/*!
    Sets the \a size of legend. If size is bigger than maximum size of legend, the legend is resized to the maximum size.
    \sa setMmaximumSize()
*/
void QLegend::setSize(const QSizeF size)
{
    m_size = size;
    if (m_size.width() > m_maximumSize.width()) {
        m_size.setWidth(m_maximumSize.width());
    }
    if (m_size.height() > m_maximumSize.height()) {
        m_size.setHeight(m_maximumSize.height());
    }
}

/*!
    Sets position of legend to \a pos
*/
void QLegend::setPos(const QPointF &pos)
{
    m_pos = pos;
    updateLayout();
}

/*!
    \internal \a series \a domain Should be called when series is added to chart.
*/
void QLegend::handleSeriesAdded(QSeries *series, Domain *domain)
{
    Q_UNUSED(domain)

    createMarkers(series);
    connectSeries(series);
    updateLayout();
}

/*!
    \internal \a series Should be called when series is removed from chart.
*/
void QLegend::handleSeriesRemoved(QSeries *series)
{
    disconnectSeries(series);

    if (series->type() == QSeries::SeriesTypeArea) {
        // This is special case. Area series has upper and lower series, which each have markers
        QAreaSeries* s = static_cast<QAreaSeries *> (series);
        deleteMarkers(s->upperSeries());
        deleteMarkers(s->lowerSeries());
    } else {
        deleteMarkers(series);
    }

    updateLayout();
}

/*!
    \internal \a slices Should be called when slices are added to pie chart.
*/
void QLegend::handleAdded(QList<QPieSlice *> slices)
{
    QPieSeries* series = static_cast<QPieSeries *> (sender());
    foreach(QPieSlice* s, slices) {
        LegendMarker* marker = new LegendMarker(series, s, this);
        marker->setName(s->label());
        marker->setBrush(s->brush());
        connect(marker, SIGNAL(clicked(QPieSlice*,Qt::MouseButton)),
                this, SIGNAL(clicked(QPieSlice*,Qt::MouseButton)));
        connect(s, SIGNAL(changed()), marker, SLOT(changed()));
        connect(s, SIGNAL(destroyed()), marker, SLOT(deleteLater()));
        connect(marker, SIGNAL(destroyed()), this, SLOT(handleMarkerDestroyed()));
        m_markers.append(marker);
        childItems().append(marker);
    }
    updateLayout();
}

/*!
    \internal \a slices Should be called when slices are removed from pie chart. Currently unused,
    because removed slices are also deleted and we listen destroyed signal
*/
void QLegend::handleRemoved(QList<QPieSlice *> slices)
{
    Q_UNUSED(slices)
}


/*!
    \internal Notifies legend that some marker has been removed. Sent by legend markers when destroyed
*/
void QLegend::handleMarkerDestroyed()
{
    LegendMarker* m = static_cast<LegendMarker *> (sender());
    m_markers.removeOne(m);
    updateLayout();
}

/*!
    \internal \a event Handles clicked signals from scroll buttons
*/
void QLegend::scrollButtonClicked(LegendScrollButton *scrollButton)
{
     Q_ASSERT(scrollButton);

    switch (scrollButton->id()) {
    case LegendScrollButton::ScrollButtonIdLeft:
    case LegendScrollButton::ScrollButtonIdUp: {
        // Lower limit is same in these cases
        mFirstMarker--;
        checkFirstMarkerBounds();
        break;
    }
    case LegendScrollButton::ScrollButtonIdRight:
    case LegendScrollButton::ScrollButtonIdDown: {
        mFirstMarker++;
        checkFirstMarkerBounds();
        break;
    }
    default: {
        break;
    }
    }
    updateLayout();
}

/*!
    \internal Connects the \a series to legend. Legend listens changes in series, for example pie slices added / removed.
    Not all series notify about events
*/
void QLegend::connectSeries(QSeries *series)
{
    // Connect relevant signals from series. Currently only pie series has interesting signals
    // TODO: bar chart may have
    if  (series->type() == QSeries::SeriesTypePie) {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        connect(pieSeries,SIGNAL(added(QList<QPieSlice*>)),this,SLOT(handleAdded(QList<QPieSlice*>)));
    }
}

/*!
    \internal Disconnects \a series from legend. No more status updates from series to legend.
*/
void QLegend::disconnectSeries(QSeries *series)
{
    if (series->type() == QSeries::SeriesTypePie) {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        disconnect(pieSeries, SIGNAL(added(QList<QPieSlice *>)), this, SLOT(handleAdded(QList<QPieSlice *>)));
    }
}

/*!
    \internal Creates new markers for \a series. Marker contains the colored rectangle and series name.
    With pie chart, created markers depend on pie slices.
    With bar chart, created markers depend on bar sets.
*/
void QLegend::createMarkers(QSeries *series)
{
    switch (series->type())
    {
    case QSeries::SeriesTypeLine: {
        QLineSeries *lineSeries = static_cast<QLineSeries *>(series);
        appendMarkers(lineSeries);
        break;
    }
    case QSeries::SeriesTypeArea: {
        QAreaSeries *areaSeries = static_cast<QAreaSeries *>(series);
        appendMarkers(areaSeries->upperSeries());
        if(areaSeries->lowerSeries())
            appendMarkers(areaSeries->lowerSeries());
        break;
    }
    case QSeries::SeriesTypeBar: {
        QBarSeries *barSeries = static_cast<QBarSeries *>(series);
        appendMarkers(barSeries);
        break;
    }
    case QSeries::SeriesTypeStackedBar: {
        QStackedBarSeries *stackedBarSeries = static_cast<QStackedBarSeries *>(series);
        appendMarkers(stackedBarSeries);
        break;
    }
    case QSeries::SeriesTypePercentBar: {
        QPercentBarSeries *percentBarSeries = static_cast<QPercentBarSeries *>(series);
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
        QSplineSeries *splineSeries = static_cast<QSplineSeries *>(series);
        appendMarkers(splineSeries);
        break;
    }
    default: {
        qWarning()<< "QLegend::createMarkers" << series->type() << "unknown series type.";
        break;
    }
    }
}

/*!
    \internal Helper function. Appends markers from \a series to legend.
*/
void QLegend::appendMarkers(QXYSeries* series)
{
    LegendMarker* marker = new LegendMarker(series,this);
    marker->setName(series->name());
    marker->setPen(series->pen());
    marker->setBrush(series->brush());
    connect(marker, SIGNAL(clicked(QSeries *, Qt::MouseButton)), this, SIGNAL(clicked(QSeries *, Qt::MouseButton)));
    connect(marker, SIGNAL(destroyed()), this, SLOT(handleMarkerDestroyed()));
    m_markers.append(marker);
    childItems().append(marker);
}

/*!
    \internal Helper function. Appends markers from  \a series to legend.
*/
void QLegend::appendMarkers(QBarSeries *series)
{
    foreach(QBarSet* set, series->barSets()) {
        LegendMarker* marker = new LegendMarker(series, set, this);
        marker->setName(set->name());
        marker->setPen(set->pen());
        marker->setBrush(set->brush());
        connect(marker, SIGNAL(clicked(QBarSet *, Qt::MouseButton)),
                this, SIGNAL(clicked(QBarSet *, Qt::MouseButton)));
        connect(set, SIGNAL(valueChanged()), marker, SLOT(changed()));
        connect(marker, SIGNAL(destroyed()), this, SLOT(handleMarkerDestroyed()));
        m_markers.append(marker);
        childItems().append(marker);
    }
}

/*!
    \internal Helper function. Appends markers from  \a series to legend.
*/
void QLegend::appendMarkers(QPieSeries *series)
{
    foreach(QPieSlice* slice, series->slices()) {
        LegendMarker* marker = new LegendMarker(series, slice, this);
        marker->setName(slice->label());
        marker->setPen(slice->pen());
        marker->setBrush(slice->brush());
        connect(marker, SIGNAL(clicked(QPieSlice *, Qt::MouseButton)),
                this, SIGNAL(clicked(QPieSlice *, Qt::MouseButton)));
        connect(slice, SIGNAL(changed()), marker, SLOT(changed()));
        connect(slice, SIGNAL(destroyed()), marker, SLOT(deleteLater()));
        connect(marker, SIGNAL(destroyed()), this, SLOT(handleMarkerDestroyed()));
        m_markers.append(marker);
        childItems().append(marker);
    }
}

/*!
    \internal Deletes all markers that are created from \a series
*/
void QLegend::deleteMarkers(QSeries *series)
{
    // Search all markers that belong to given series and delete them.
    foreach (LegendMarker *m, m_markers) {
        if (m->series() == series) {
            m_markers.removeOne(m);
            delete m;
        }
    }
}

/*!
    \internal Updates layout of legend. Tries to fit as many markers as possible up to the maximum size of legend.
    If items don't fit, sets the visibility of scroll buttons accordingly.
    Causes legend to be resized.
*/
void QLegend::updateLayout()
{
    // Calculate layout for markers and text
    if (m_markers.count() <= 0) {
        // Nothing to do
        return;
    }

    // Find out widest item.
    QSizeF markerMaxSize = maximumMarkerSize();
    checkFirstMarkerBounds();

    // Use max height as scroll button size
    rescaleScrollButtons(QSize(markerMaxSize.height() ,markerMaxSize.height()));

    qreal totalWidth = 0;
    qreal totalHeight = 0;
    switch (m_alignment)
    {
    // Both cases organise items horizontally
    case QLegend::LayoutBottom:
    case QLegend::LayoutTop: {

        qreal xStep = markerMaxSize.width();
        qreal x = m_pos.x() + m_margin;
        qreal y = m_pos.y() + m_margin;
        int column = 0;
        int maxColumns = 1;
        qreal scrollButtonWidth = 0;

        // Set correct visibility for scroll scrollbuttons
        if (scrollButtonsVisible()) {
            m_scrollButtonLeft->setVisible(true);
            m_scrollButtonRight->setVisible(true);
            // scrollbuttons visible, so add their width to total width
            totalWidth += (m_scrollButtonLeft->boundingRect().width() + m_margin) * 2;
            scrollButtonWidth = m_scrollButtonLeft->boundingRect().width() + m_margin;
            // start position changes by scrollbutton width
            x += scrollButtonWidth;
        } else {
            m_scrollButtonLeft->setVisible(false);
            m_scrollButtonRight->setVisible(false);
        }
        m_scrollButtonUp->setVisible(false);
        m_scrollButtonDown->setVisible(false);

        for (int i=0; i < m_markers.count(); i++) {
            LegendMarker *m = m_markers.at(i);
            if (i < mFirstMarker) {
                // Markers before first are not visible.
                m->setVisible(false);
            } else {
                if ((x + xStep + scrollButtonWidth + m_margin) > (m_pos.x() + m_maximumSize.width())) {
                    // This marker would go outside legend rect.
                    m->setVisible(false);
                } else {
                    // This marker is ok
                    m->setVisible(true);
                    m->setPos(x, y);
                    x += xStep;
                    column++;
                }
            }
            maxColumns = column;
        }

        m_scrollButtonLeft->setPos(m_pos.x() + m_margin, y);
        m_scrollButtonRight->setPos(x + m_margin, y);

        totalWidth += maxColumns * markerMaxSize.width() + m_margin * 2;
        totalHeight = markerMaxSize.height() + m_margin * 2;

        break;
    }
    // Both cases organize items vertically
    case QLegend::LayoutLeft:
    case QLegend::LayoutRight: {
        qreal yStep = markerMaxSize.height();
        qreal x = m_pos.x() + m_margin;
        qreal y = m_pos.y() + m_margin;
        int row = 1;
        int maxRows = 1;
        qreal scrollButtonHeight = 0;

        // Set correct visibility for scroll scrollbuttons
        if (scrollButtonsVisible()) {
            m_scrollButtonUp->setVisible(true);
            m_scrollButtonDown->setVisible(true);
            totalHeight += (m_scrollButtonUp->boundingRect().height() + m_margin) * 2;   // scrollbuttons visible, so add their height to total height
            scrollButtonHeight = m_scrollButtonUp->boundingRect().height();
            y += scrollButtonHeight + m_margin;                                         // start position changes by scrollbutton height
        } else {
            m_scrollButtonUp->setVisible(false);
            m_scrollButtonDown->setVisible(false);
        }
        m_scrollButtonLeft->setVisible(false);
        m_scrollButtonRight->setVisible(false);

        for (int i=0; i < m_markers.count(); i++) {
            LegendMarker* m = m_markers.at(i);
            if (i < mFirstMarker) {
                // Markers before first are not visible.
                m->setVisible(false);
            } else {
                if ((y + yStep + scrollButtonHeight) > (m_pos.y() + m_maximumSize.height())) {
                    // This marker would go outside legend rect.
                    m->setVisible(false);
                } else {
                    // This marker is ok
                    m->setVisible(true);
                    m->setPos(x, y);
                    y += yStep;
                    row++;
                }
            }
            maxRows = row;
        }

        m_scrollButtonUp->setPos(m_pos.x() + m_margin, m_pos.y() + m_margin);
        m_scrollButtonDown->setPos(m_pos.x() + m_margin, y + m_margin);

        totalWidth += markerMaxSize.width() + m_margin * 2;
        totalHeight = maxRows * markerMaxSize.height() + m_margin * 4 + scrollButtonHeight; // TODO: check this
        break;
    }
    default: {
        break;
    }
    }

    m_size.setWidth(totalWidth);
    m_size.setHeight(totalHeight);

    update();
}

/*!
    \internal Sets the size of scroll buttons to \a size
*/
void QLegend::rescaleScrollButtons(const QSize &size)
{
    QPolygonF left;
    left << QPointF(size.width(), 0) << QPointF(0, size.height() / 2) << QPointF(size.width(), size.height());
    QPolygonF right;
    right << QPointF(0, 0) << QPointF(size.width(), size.height() / 2) << QPointF(0, size.height());
    QPolygonF up;
    up << QPointF(0, size.height()) << QPointF(size.width() / 2,0) << QPointF(size.width(), size.height());
    QPolygonF down;
    down << QPointF(0, 0) << QPointF(size.width() / 2, size.height()) << QPointF(size.width(), 0);

    m_scrollButtonLeft->setPolygon(left);
    m_scrollButtonRight->setPolygon(right);
    m_scrollButtonUp->setPolygon(up);
    m_scrollButtonDown->setPolygon(down);
}

/*!
    \internal Finds out maximum size of single marker. Marker sizes depend on series names.
*/
QSizeF QLegend::maximumMarkerSize()
{
    QSizeF max(0,0);
    foreach (LegendMarker* m, m_markers) {
        if (m->boundingRect().width() > max.width())
            max.setWidth(m->boundingRect().width());
        if (m->boundingRect().height() > max.height())
            max.setHeight(m->boundingRect().height());
    }
    return max;
}

/*!
    \internal Checks that first marker is in acceptable bounds. Bounds range from 0 to (maximum number of markers - visible markers)
    If scrollbuttons are visible, they affect the number of visible markers.
*/
void QLegend::checkFirstMarkerBounds()
{
    if ((m_alignment == QLegend::LayoutLeft) || (m_alignment == QLegend::LayoutRight)) {
        // Bounds limited by height.
        int max;
        if (scrollButtonsVisible()) {
            max = (m_maximumSize.height() - m_scrollButtonLeft->boundingRect().height() * 2 - m_margin * 4) / maximumMarkerSize().height();
        } else {
            max = m_maximumSize.height() / maximumMarkerSize().height();
        }

        if (mFirstMarker > m_markers.count() - max)
            mFirstMarker = m_markers.count() - max;
    } else {
        // Bounds limited by width
        int max;
        if (scrollButtonsVisible()) {
            max = (m_maximumSize.width() - m_scrollButtonLeft->boundingRect().width() * 2 - m_margin*4) / maximumMarkerSize().width();
        } else {
            max = m_maximumSize.width() / maximumMarkerSize().width();
        }

        if (mFirstMarker > m_markers.count() - max)
            mFirstMarker = m_markers.count() - max;
    }

    if (mFirstMarker < 0)
        mFirstMarker = 0;
}

/*!
    \internal Helper function. Visibility of scroll buttons isn't quite obvious, so helper function clarifies the logic.
*/
bool QLegend::scrollButtonsVisible()
{
    // Just a helper to clarify, what the magic below means :)
    if ((m_alignment == QLegend::LayoutTop) || (m_alignment == QLegend::LayoutBottom)) {
        return (maximumMarkerSize().width() * m_markers.count() + m_margin * 2 > m_maximumSize.width());
    } else if ((m_alignment == QLegend::LayoutLeft) || (m_alignment == QLegend::LayoutRight)) {
        return (maximumMarkerSize().height() * m_markers.count() + m_margin * 2 > m_maximumSize.height());
    }

    return (maximumMarkerSize().height() * m_markers.count() + m_margin * 2 > m_maximumSize.height());
}

#include "moc_qlegend.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
