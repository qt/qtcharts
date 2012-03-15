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
    m_pieRelativeHorPos(0.5),
    m_pieRelativeVerPos(0.5),
    m_pieRelativeSize(0.7),
    m_pieStartAngle(0),
    m_pieEndAngle(360),
    m_total(0)
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
    foreach (QPieSlice* s, slices) {
        s->setParent(this);
        m_slices << s;
    }

    updateDerivativeData();

    foreach (QPieSlice* s, slices) {
        connect(s, SIGNAL(changed()), this, SLOT(sliceChanged()));
        connect(s, SIGNAL(clicked()), this, SLOT(sliceClicked()));
        connect(s, SIGNAL(hoverEnter()), this, SLOT(sliceHoverEnter()));
        connect(s, SIGNAL(hoverLeave()), this, SLOT(sliceHoverLeave()));
    }

    emit changed();
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
    emit changed();

    updateDerivativeData();

    delete slice;
    slice = NULL;
}

/*!
    Clears all slices from the series.
*/
void QPieSeries::clear()
{
    if (m_slices.count() == 0)
        return;

    foreach (QPieSlice* s, m_slices) {
        m_slices.removeOne(s);
        delete s;
    }

    emit changed();

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
    Sets the center position of the pie by \a relativeHorizontalPosition and \a relativeVerticalPosition.

    The factors are relative to the chart rectangle where:

    \a relativeHorizontalPosition 0.0 means the absolute left.
    \a relativeHorizontalPosition 1.0 means the absolute right.
    \a relativeVerticalPosition 0.0 means the absolute top.
    \a relativeVerticalPosition 1.0 means the absolute bottom.

    By default both values are 0.5 which puts the pie in the middle of the chart rectangle.

    \sa pieHorizontalPosition(), pieVerticalPosition(), setPieSize()
*/
void QPieSeries::setPiePosition(qreal relativeHorizontalPosition, qreal relativeVerticalPosition)
{
    if (relativeHorizontalPosition < 0.0 || relativeHorizontalPosition > 1.0 ||
            relativeVerticalPosition < 0.0 || relativeVerticalPosition > 1.0)
        return;

    if (m_pieRelativeHorPos != relativeHorizontalPosition || m_pieRelativeVerPos != relativeVerticalPosition) {
        m_pieRelativeHorPos = relativeHorizontalPosition;
        m_pieRelativeVerPos = relativeVerticalPosition;
        emit changed();
    }
}

/*!
    Gets the horizontal position of the pie.

    The returned value is relative to the chart rectangle where:

    0.0 means the absolute left.
    1.0 means the absolute right.

    By default it is 0.5 which puts the pie in the horizontal middle of the chart rectangle.

    \sa setPiePosition(), pieVerticalPosition(), setPieSize()
*/
qreal QPieSeries::pieHorizontalPosition() const
{
    return m_pieRelativeHorPos;
}

/*!
    Gets the vertical position position of the pie.

    The returned value is relative to the chart rectangle where:

    0.0 means the absolute top.
    1.0 means the absolute bottom.

    By default it is 0.5 which puts the pie in the vertical middle of the chart rectangle.

    \sa setPiePosition(), pieHorizontalPosition(), setPieSize()
*/
qreal QPieSeries::pieVerticalPosition() const
{
    return m_pieRelativeVerPos;
}

/*!
    Sets the relative size of the pie.

    The \a relativeSize is defined so that the 1.0 is the maximum that can fit the given chart rectangle.

    Default value is 0.7.

    \sa pieSize(), setPiePosition(), pieVerticalPosition(), pieHorizontalPosition()
*/
void QPieSeries::setPieSize(qreal relativeSize)
{
    if (relativeSize < 0.0 || relativeSize > 1.0)
        return;

    if (m_pieRelativeSize != relativeSize) {
        m_pieRelativeSize = relativeSize;
        emit changed();
    }
}

/*!
    Gets the relative size of the pie.

    The size is defined so that the 1.0 is the maximum that can fit the given chart rectangle.

    Default value is 0.7.

    \sa setPieSize(), setPiePosition(), pieVerticalPosition(), pieHorizontalPosition()
*/
qreal QPieSeries::pieSize() const
{
    return m_pieRelativeSize;
}


/*!
    Sets the end angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    \a angle must be less than pie end angle. Default value is 0.

    \sa pieStartAngle(), pieEndAngle(), setPieEndAngle()
*/
void QPieSeries::setPieStartAngle(qreal angle)
{
    if (angle >= 0 && angle <= 360 && angle != m_pieStartAngle && angle <= m_pieEndAngle) {
        m_pieStartAngle = angle;
        updateDerivativeData();
    }
}

/*!
    Gets the start angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock. Default value is 360.

    \sa setPieStartAngle(), pieEndAngle(), setPieEndAngle()
*/
qreal QPieSeries::pieStartAngle() const
{
    return m_pieStartAngle;
}

/*!
    Sets the end angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    \a angle must be greater than start angle.

    \sa pieEndAngle(), pieStartAngle(), setPieStartAngle()
*/
void QPieSeries::setPieEndAngle(qreal angle)
{
    if (angle >= 0 && angle <= 360 && angle != m_pieEndAngle && angle >= m_pieStartAngle) {
        m_pieEndAngle = angle;
        updateDerivativeData();
    }
}

/*!
    Returns the end angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    \sa setPieEndAngle(), pieStartAngle(), setPieStartAngle()
*/
qreal QPieSeries::pieEndAngle() const
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
    \fn void QPieSeries::changed()

    This signal emitted when something has changed in the series.

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

void QPieSeries::sliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
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

bool QPieSeries::setModel(QAbstractItemModel* model)
{
    // disconnect signals from old model
    if(m_model)
    {
        disconnect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), 0, 0);
        disconnect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)), 0, 0);
        disconnect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), 0, 0);
    }

    // set new model if not NULL and connect necessary signals from it
    if(model)
    {
        m_model = model;
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }
}

void QPieSeries::setModelMapping(int modelValuesLine, int modelLabelsLine, Qt::Orientation orientation)
{
    m_mapValues = modelValuesLine;
    m_mapLabels = modelLabelsLine;
    m_mapOrientation = orientation;

    if (m_model == NULL)
        return;

    if (m_mapOrientation == Qt::Vertical)
        for (int i = 0; i < m_model->rowCount(); i++)
            add(m_model->data(m_model->index(i, m_mapValues), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(i, m_mapLabels), Qt::DisplayRole).toString());
    else
        for (int i = 0; i < m_model->columnCount(); i++)
            add(m_model->data(m_model->index(m_mapValues, i), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(m_mapLabels, i), Qt::DisplayRole).toString());


}

void QPieSeries::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    if (m_mapOrientation == Qt::Vertical)
        //        slices().at(topLeft.row())->setValue(m_model->data(m_model->index(topLeft.row(), topLeft.column()), Qt::DisplayRole).toDouble());
        if (topLeft.column() == m_mapValues)
            slices().at(topLeft.row())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
        else if (topLeft.column() == m_mapLabels)
            slices().at(topLeft.row())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
        else
            //        slices().at(topLeft.column())->setValue(m_model->data(m_model->index(topLeft.row(), topLeft.column()), Qt::DisplayRole).toDouble());
            if (topLeft.column() == m_mapValues)
                slices().at(topLeft.column())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
            else if (topLeft.column() == m_mapLabels)
                slices().at(topLeft.column())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
}

void QPieSeries::modelDataAdded(QModelIndex parent, int start, int end)
{
    //
}

void QPieSeries::modelDataRemoved(QModelIndex parent, int start, int end)
{
    remove(slices().at(start));
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
