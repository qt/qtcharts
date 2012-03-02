#include "qpieseries.h"
#include "qpieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


/*!
    \class QPieSeries::ChangeSet
    \brief Defines the changes in the series.

    Contains the changes that have occurred in the series. Lists of added, changed and removed slices.

    \sa QPieSeries::changed()
*/

/*!
    \internal
*/
void QPieSeries::ChangeSet::appendAdded(QPieSlice* slice)
{
    if (!m_added.contains(slice))
        m_added << slice;
}

/*!
    \internal
*/
void QPieSeries::ChangeSet::appendAdded(QList<QPieSlice*> slices)
{
    foreach (QPieSlice* s, slices)
        appendAdded(s);
}

/*!
    \internal
*/
void QPieSeries::ChangeSet::appendChanged(QPieSlice* slice)
{
    if (!m_changed.contains(slice))
        m_changed << slice;
}

/*!
    \internal
*/
void QPieSeries::ChangeSet::appendRemoved(QPieSlice* slice)
{
    if (!m_removed.contains(slice))
        m_removed << slice;
}

/*!
    Returns a list of slices that have been added to the series.
    \sa QPieSeries::changed()
*/
QList<QPieSlice*> QPieSeries::ChangeSet::added() const
{
    return m_added;
}

/*!
    Returns a list of slices that have been changed in the series.
    \sa QPieSeries::changed()
*/
QList<QPieSlice*> QPieSeries::ChangeSet::changed() const
{
    return m_changed;
}

/*!
    Returns a list of slices that have been removed from the series.
    \sa QPieSeries::changed()
*/
QList<QPieSlice*> QPieSeries::ChangeSet::removed() const
{
    return m_removed;
}


/*!
    Returns true if there are no added/changed or removed slices in the change set.
*/
bool QPieSeries::ChangeSet::isEmpty() const
{
    if (m_added.count() || m_changed.count() || m_removed.count())
        return false;
    return true;
}

/*!
    \enum QPieSeries::PiePosition

    This enum describes pie position within its bounding rectangle

    \value PiePositionMaximized
    \value PiePositionTopLeft
    \value PiePositionTopRight
    \value PiePositionBottomLeft
    \value PiePositionBottomRight
*/

/*!
    \class QPieSeries
    \brief Pie series API for QtCommercial Charts

    The pie series defines a pie chart which consists of pie slices which are QPieSlice objects.
    The slices can have any values as the QPieSeries will calculate its relative value to the sum of all slices.
    The actual slice size is determined by that relative value.

    By default the pie is defined as a full pie but it can be a partial pie.
    This can be done by setting a starting angle and angle span to the series.
*/

/*!
    Constructs a series object which is a child of \a parent.
*/
QPieSeries::QPieSeries(QObject *parent) :
    QSeries(parent),
    m_sizeFactor(1.0),
    m_position(PiePositionCenter),
    m_sizePolicy(PieSizePolicyMaximized),
    m_pieStartAngle(0),
    m_pieEndAngle(360)
{

}

/*!
    Destroys the object. Note that adding series to QChart transfers the ownership to the chart.
*/
QPieSeries::~QPieSeries()
{

}

/*!
    Returns QChartSeries::SeriesTypePie.
*/
QSeries::QSeriesType QPieSeries::type() const
{
    return QSeries::SeriesTypePie;
}

/*!
    Sets an array of \a slices to the series replacing the existing slices.
    Slice ownership is passed to the series.
*/
void QPieSeries::replace(QList<QPieSlice*> slices)
{
    clear();
    add(slices);
}

/*!
    Adds an array of \a slices to the series.
    Slice ownership is passed to the series.
*/
void QPieSeries::add(QList<QPieSlice*> slices)
{
    ChangeSet changeSet;
    foreach (QPieSlice* s, slices) {
        s->setParent(this);
        m_slices << s;
        changeSet.appendAdded(s);
    }

    updateDerivativeData();

    foreach (QPieSlice* s, slices) {
        connect(s, SIGNAL(changed()), this, SLOT(sliceChanged()));
        connect(s, SIGNAL(clicked()), this, SLOT(sliceClicked()));
        connect(s, SIGNAL(hoverEnter()), this, SLOT(sliceHoverEnter()));
        connect(s, SIGNAL(hoverLeave()), this, SLOT(sliceHoverLeave()));
    }

    emit changed(changeSet);
}

/*!
    Adds a single \a slice to the series.
    Slice ownership is passed to the series.
*/
void QPieSeries::add(QPieSlice* slice)
{
    add(QList<QPieSlice*>() << slice);
}

/*!
    Adds a single \a slice to the series and returns a reference to the series.
    Slice ownership is passed to the series.
*/
QPieSeries& QPieSeries::operator << (QPieSlice* slice)
{
    add(slice);
    return *this;
}


/*!
    Adds a single slice to the series with give \a value and \a name.
    Slice ownership is passed to the series.
*/
QPieSlice* QPieSeries::add(qreal value, QString name)
{
    QPieSlice* slice = new QPieSlice(value, name);
    add(slice);
    return slice;
}

/*!
    Removes a single \a slice from the series and deletes the slice.

    Do not reference this pointer after this call.
*/
void QPieSeries::remove(QPieSlice* slice)
{
    if (!m_slices.removeOne(slice)) {
        Q_ASSERT(0); // TODO: how should this be reported?
        return;
    }

    ChangeSet changeSet;
    changeSet.appendRemoved(slice);
    emit changed(changeSet);

    delete slice;
    slice = NULL;

    updateDerivativeData();
}

/*!
    Clears all slices from the series.
*/
void QPieSeries::clear()
{
    if (m_slices.count() == 0)
        return;

    ChangeSet changeSet;
    foreach (QPieSlice* s, m_slices) {
        changeSet.appendRemoved(s);
        m_slices.removeOne(s);
        delete s;
    }
    emit changed(changeSet);
    updateDerivativeData();
}

/*!
    Counts the number of the slices in this series.
*/
int QPieSeries::count() const
{
    return m_slices.count();
}

/*!
    Returns a list of slices that belong to this series.
*/
QList<QPieSlice*> QPieSeries::slices() const
{
    return m_slices;
}

/*!
    Sets the size \a factor of the pie. 1.0 is the default value.
    Note that the pie will not grow beyond its absolute maximum size.
    In practice its use is to make the pie appear smaller.
    \sa sizeFactor()
*/
void QPieSeries::setSizeFactor(qreal factor)
{
    if (factor < 0.0)
        return;

    if (m_sizeFactor != factor) {
        m_sizeFactor = factor;
        emit sizeFactorChanged();
    }
}

/*!
    Gets the size factor of the pie.
    \sa setSizeFactor()
*/
qreal QPieSeries::sizeFactor() const
{
    return m_sizeFactor;
}

/*!
    Sets the \a position of the pie within its bounding rectangle.
    \sa PiePosition, position()
*/
void QPieSeries::setPosition(PiePosition position)
{
    // TODO: sanity check
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}

/*!
    Gets the position of the pie within its bounding rectangle.
    \sa PiePosition, setPosition()
*/
QPieSeries::PiePosition QPieSeries::position() const
{
    return m_position;
}

/*!
    Sets the \a sizePolicy of the pie.
    \sa PieSizePolicy, sizePolicy()
*/
void QPieSeries::setSizePolicy(PieSizePolicy sizePolicy)
{
    // TODO: sanity check
    if (m_sizePolicy != sizePolicy) {
        m_sizePolicy = sizePolicy;
        emit sizePolicyChanged();
    }
}

/*!
    Gets the size policy of the pie.
    \sa PieSizePolicy, setSizePolicy()
*/
QPieSeries::PieSizePolicy QPieSeries::sizePolicy() const
{
    return m_sizePolicy;
}


void QPieSeries::setStartAngle(qreal startAngle)
{
    if (startAngle >= 0 && startAngle <= 360 && startAngle != m_pieStartAngle && startAngle <= m_pieEndAngle) {
        m_pieStartAngle = startAngle;
        updateDerivativeData();
    }
}

qreal QPieSeries::startAngle() const
{
    return m_pieStartAngle;
}

void QPieSeries::setEndAngle(qreal endAngle)
{
    if (endAngle >= 0 && endAngle <= 360 && endAngle != m_pieEndAngle && endAngle >= m_pieStartAngle) {
        m_pieEndAngle = endAngle;
        updateDerivativeData();
    }
}

qreal QPieSeries::endAngle() const
{
    return m_pieEndAngle;
}

/*!
    Sets the all the slice labels \a visible or invisible.

    \sa QPieSlice::isLabelVisible(), QPieSlice::setLabelVisible()
*/
void QPieSeries::setLabelsVisible(bool visible)
{
    foreach (QPieSlice* s, m_slices)
        s->setLabelVisible(visible);
}

/*!
    Returns the sum of all slice values in this series.

    \sa QPieSlice::value(), QPieSlice::setValue()
*/
qreal QPieSeries::total() const
{
    return m_total;
}

/*!
    \fn void QPieSeries::changed(const QPieSeries::ChangeSet& changeSet)

    This signal emitted when something has changed in the series.
    The \a changeSet contains the details of which slices have been added, changed or removed.

    \sa QPieSeries::ChangeSet, QPieSlice::changed()
*/

/*!
    \fn void QPieSeries::clicked(QPieSlice* slice)

    This signal is emitted when a \a slice has been clicked.

    \sa QPieSlice::clicked()
*/

/*!
    \fn void QPieSeries::hoverEnter(QPieSlice* slice)

    This signal is emitted when user has hovered over a \a slice.

    \sa QPieSlice::hoverEnter()
*/

/*!
    \fn void QPieSeries::hoverLeave(QPieSlice* slice)

    This signal is emitted when user has hovered away from a \a slice.

    \sa QPieSlice::hoverLeave()
*/

/*!
    \fn void QPieSeries::sizeFactorChanged()

    This signal is emitted when size factor has been changed.

    \sa sizeFactor(), setSizeFactor()
*/

/*!
    \fn void QPieSeries::positionChanged()

    This signal is emitted when position of the pie has been changed.

    \sa position(), setPosition()
*/

void QPieSeries::sliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));

    ChangeSet changeSet;
    changeSet.appendChanged(slice);
    emit changed(changeSet);

    updateDerivativeData();
}

void QPieSeries::sliceClicked()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    emit clicked(slice);
}

void QPieSeries::sliceHoverEnter()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    emit hoverEnter(slice);
}

void QPieSeries::sliceHoverLeave()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    emit hoverLeave(slice);
}

void QPieSeries::updateDerivativeData()
{
    m_total = 0;

    // nothing to do?
    if (m_slices.count() == 0)
        return;

    // calculate total
    foreach (QPieSlice* s, m_slices)
        m_total += s->value();

    // we must have some values
    if (m_total == 0) {
        qDebug() << "QPieSeries::updateDerivativeData() total == 0";
        Q_ASSERT(m_total > 0); // TODO: is this the correct way to handle this?
    }

    // update slice attributes
    qreal sliceAngle = m_pieStartAngle;
    qreal pieSpan = m_pieEndAngle - m_pieStartAngle;
    foreach (QPieSlice* s, m_slices) {

        bool changed = false;

        qreal percentage = s->value() / m_total;
        if (s->m_percentage != percentage) {
            s->m_percentage = percentage;
            changed = true;
        }

        qreal sliceSpan = pieSpan * percentage;
        if (s->m_angleSpan != sliceSpan) {
            s->m_angleSpan = sliceSpan;
            changed = true;
        }

        if (s->m_startAngle != sliceAngle) {
            s->m_startAngle = sliceAngle;
            changed = true;
        }
        sliceAngle += sliceSpan;

        if (changed)
            emit s->changed();
    }
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
