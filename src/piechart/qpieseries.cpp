#include "qpieseries.h"
#include "qpieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

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

    emit added(slices);
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

void QPieSeries::insert(int i, QPieSlice* slice)
{
    Q_ASSERT(i <= m_slices.count());
    slice->setParent(this);
    m_slices.insert(i, slice);

    updateDerivativeData();

    connect(slice, SIGNAL(changed()), this, SLOT(sliceChanged()));
    connect(slice, SIGNAL(clicked()), this, SLOT(sliceClicked()));
    connect(slice, SIGNAL(hoverEnter()), this, SLOT(sliceHoverEnter()));
    connect(slice, SIGNAL(hoverLeave()), this, SLOT(sliceHoverLeave()));

    emit added(QList<QPieSlice*>() << slice);
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

    updateDerivativeData();

    emit removed(QList<QPieSlice*>() << slice);

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

    QList<QPieSlice*> slices = m_slices;
    foreach (QPieSlice* s, m_slices) {
        m_slices.removeOne(s);
        delete s;
    }

    updateDerivativeData();

    emit removed(slices);
}

/*!
    Counts the number of the slices in this series.
*/
int QPieSeries::count() const
{
    return m_slices.count();
}

/*!
    Returns true is the series is empty.
*/
bool QPieSeries::isEmpty() const
{
    return m_slices.isEmpty();
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
        emit piePositionChanged();
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
        emit pieSizeChanged();
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

    // nothing to show..
    if (m_total == 0)
        return;

    // update slice attributes
    qreal sliceAngle = m_pieStartAngle;
    qreal pieSpan = m_pieEndAngle - m_pieStartAngle;
    QVector<QPieSlice*> changed;
    foreach (QPieSlice* s, m_slices) {

        bool isChanged = false;

        qreal percentage = s->value() / m_total;
        if (s->m_percentage != percentage) {
            s->m_percentage = percentage;
            isChanged = true;
        }

        qreal sliceSpan = pieSpan * percentage;
        if (s->m_angleSpan != sliceSpan) {
            s->m_angleSpan = sliceSpan;
            isChanged = true;
        }

        if (s->m_startAngle != sliceAngle) {
            s->m_startAngle = sliceAngle;
            isChanged = true;
        }
        sliceAngle += sliceSpan;

        if (isChanged)
            changed << s;
    }

    // emit signals
    foreach (QPieSlice* s, changed)
        emit s->changed();
}

bool QPieSeries::setModel(QAbstractItemModel* model)
{
    // disconnect signals from old model
    if(m_model)
    {
        disconnect(m_model, 0, this, 0);
        m_mapValues = -1;
        m_mapLabels = -1;
        m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if(model)
    {
        m_model = model;
        return true;
    }
    else
    {
        m_model = NULL;
        return false;
    }
}

void QPieSeries::setModelMapping(int modelValuesLine, int modelLabelsLine, Qt::Orientation orientation)
{
    if (m_model == NULL)
        return;
    m_mapValues = modelValuesLine;
    m_mapLabels = modelLabelsLine;
    m_mapOrientation = orientation;

    // connect the signals
    if (m_mapOrientation == Qt::Vertical)
    {
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }
    else
    {
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(columnsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }

    // create the initial slices set
    if (m_mapOrientation == Qt::Vertical)
        for (int i = 0; i < m_model->rowCount(); i++)
            add(m_model->data(m_model->index(i, m_mapValues), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(i, m_mapLabels), Qt::DisplayRole).toString());
    else
        for (int i = 0; i < m_model->columnCount(); i++)
            add(m_model->data(m_model->index(m_mapValues, i), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(m_mapLabels, i), Qt::DisplayRole).toString());


}

void QPieSeries::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_UNUSED(bottomRight)

    if (m_mapOrientation == Qt::Vertical)
    {
        //        slices().at(topLeft.row())->setValue(m_model->data(m_model->index(topLeft.row(), topLeft.column()), Qt::DisplayRole).toDouble());
        if (topLeft.column() == m_mapValues)
            if (m_mapValues == m_mapLabels)
            {
                slices().at(topLeft.row())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                slices().at(topLeft.row())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
            }
            else
            {
                slices().at(topLeft.row())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
            }
        else if (topLeft.column() == m_mapLabels)
            slices().at(topLeft.row())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
    }
    else
    {
        //        slices().at(topLeft.column())->setValue(m_model->data(m_model->index(topLeft.row(), topLeft.column()), Qt::DisplayRole).toDouble());
        if (topLeft.row() == m_mapValues)
            if (m_mapValues == m_mapLabels)
            {
                slices().at(topLeft.column())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                slices().at(topLeft.column())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
            }
            else
            {
                slices().at(topLeft.column())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
            }
        else if (topLeft.row() == m_mapLabels)
            slices().at(topLeft.column())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
    }
}

void QPieSeries::modelDataAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(end)

    QPieSlice* newSlice = new QPieSlice;
    newSlice->setLabelVisible(true);
    if (m_mapOrientation == Qt::Vertical)
    {
        newSlice->setValue(m_model->data(m_model->index(start, m_mapValues), Qt::DisplayRole).toDouble());
        newSlice->setLabel(m_model->data(m_model->index(start, m_mapLabels), Qt::DisplayRole).toString());
    }
    else
    {
        newSlice->setValue(m_model->data(m_model->index(m_mapValues, start), Qt::DisplayRole).toDouble());
        newSlice->setLabel(m_model->data(m_model->index(m_mapLabels, start), Qt::DisplayRole).toString());
    }

    insert(start, newSlice);
}

void QPieSeries::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(end)
    remove(slices().at(start));
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
