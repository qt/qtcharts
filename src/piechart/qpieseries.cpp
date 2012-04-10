/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qpieseries.h"
#include "qpieseries_p.h"
#include "qpieslice.h"
#include "pieslicedata_p.h"
#include <QAbstractItemModel>
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
    \property QPieSeries::horizontalPosition
    \brief Defines the horizontal position of the pie.

    The value is a relative value to the chart rectangle where:

    \list
    \o 0.0 is the absolute left.
    \o 1.0 is the absolute right.
    \endlist

    Default value is 0.5 (center).
*/

/*!
    \property QPieSeries::verticalPosition
    \brief Defines the vertical position of the pie.

    The value is a relative value to the chart rectangle where:

    \list
    \o 0.0 is the absolute top.
    \o 1.0 is the absolute bottom.
    \endlist

    Default value is 0.5 (center).
*/

/*!
    \property QPieSeries::size
    \brief Defines the pie size.

    The value is a relative value to the chart rectangle where:

    \list
    \o 0.0 is the minumum size (pie not drawn).
    \o 1.0 is the maximum size that can fit the chart.
    \endlist

    Default value is 0.7.
*/

/*!
    \property QPieSeries::startAngle
    \brief Defines the starting angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Default is value is 0.
*/

/*!
    \property QPieSeries::endAngle
    \brief Defines the ending angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Default is value is 360.
*/


/*!
    Constructs a series object which is a child of \a parent.
*/
QPieSeries::QPieSeries(QObject *parent) :
    QSeries(*new QPieSeriesPrivate(this),parent)
{

}

/*!
    Destroys the series and its slices.
*/
QPieSeries::~QPieSeries()
{
    // NOTE: d_prt destroyed by QObject
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
    append(slices);
}

/*!
    Appends an array of \a slices to the series.
    Slice ownership is passed to the series.
*/
void QPieSeries::append(QList<QPieSlice*> slices)
{
    Q_D(QPieSeries);

    foreach (QPieSlice* s, slices) {
        s->setParent(this);
        d->m_slices << s;
    }

    d->updateDerivativeData();

    foreach (QPieSlice* s, slices) {
        connect(s, SIGNAL(changed()), d, SLOT(sliceChanged()));
        connect(s, SIGNAL(clicked(Qt::MouseButtons)), d, SLOT(sliceClicked(Qt::MouseButtons)));
        connect(s, SIGNAL(hoverEnter()), d, SLOT(sliceHoverEnter()));
        connect(s, SIGNAL(hoverLeave()), d, SLOT(sliceHoverLeave()));
    }

    emit added(slices);
}

/*!
    Appends a single \a slice to the series.
    Slice ownership is passed to the series.
*/
void QPieSeries::append(QPieSlice* slice)
{
    append(QList<QPieSlice*>() << slice);
}

/*!
    Appends a single \a slice to the series and returns a reference to the series.
    Slice ownership is passed to the series.
*/
QPieSeries& QPieSeries::operator << (QPieSlice* slice)
{
    append(slice);
    return *this;
}


/*!
    Appends a single slice to the series with give \a value and \a name.
    Slice ownership is passed to the series.
*/
QPieSlice* QPieSeries::append(qreal value, QString name)
{
    QPieSlice* slice = new QPieSlice(value, name);
    append(slice);
    return slice;
}

/*!
    Inserts a single \a slice to the series before the slice at \a index position.
    Slice ownership is passed to the series.
*/
void QPieSeries::insert(int index, QPieSlice* slice)
{
    Q_D(QPieSeries);
    Q_ASSERT(index <= d->m_slices.count());
    slice->setParent(this);
    d->m_slices.insert(index, slice);

    d->updateDerivativeData();

    connect(slice, SIGNAL(changed()), d, SLOT(sliceChanged()));
    connect(slice, SIGNAL(clicked(Qt::MouseButtons)), d, SLOT(sliceClicked(Qt::MouseButtons)));
    connect(slice, SIGNAL(hoverEnter()), d, SLOT(sliceHoverEnter()));
    connect(slice, SIGNAL(hoverLeave()), d, SLOT(sliceHoverLeave()));

    emit added(QList<QPieSlice*>() << slice);
}

/*!
    Removes a single \a slice from the series and deletes the slice.

    Do not reference this pointer after this call.
*/
void QPieSeries::remove(QPieSlice* slice)
{
    Q_D(QPieSeries);
    if (!d->m_slices.removeOne(slice)) {
        Q_ASSERT(0); // TODO: how should this be reported?
        return;
    }

    d->updateDerivativeData();

    emit removed(QList<QPieSlice*>() << slice);

    delete slice;
    slice = 0;
}

/*!
    Clears all slices from the series.
*/
void QPieSeries::clear()
{
    Q_D(QPieSeries);
    if (d->m_slices.count() == 0)
        return;

    QList<QPieSlice*> slices = d->m_slices;
    foreach (QPieSlice* s, d->m_slices) {
        d->m_slices.removeOne(s);
        delete s;
    }

    d->updateDerivativeData();

    emit removed(slices);
}

/*!
    returns the number of the slices in this series.
*/
int QPieSeries::count() const
{
    Q_D(const QPieSeries);
    return d->m_slices.count();
}

/*!
    Returns true is the series is empty.
*/
bool QPieSeries::isEmpty() const
{
    Q_D(const QPieSeries);
    return d->m_slices.isEmpty();
}

/*!
    Returns a list of slices that belong to this series.
*/
QList<QPieSlice*> QPieSeries::slices() const
{
    Q_D(const QPieSeries);
    return d->m_slices;
}

void QPieSeries::setHorizontalPosition(qreal relativePosition)
{
    Q_D(QPieSeries);
    if (d->setRealValue(d->m_pieRelativeHorPos, relativePosition, 1.0))
        emit piePositionChanged();
}

void QPieSeries::setVerticalPosition(qreal relativePosition)
{
    Q_D(QPieSeries);
    if (d->setRealValue(d->m_pieRelativeVerPos, relativePosition, 1.0))
        emit piePositionChanged();
}

qreal QPieSeries::horizontalPosition() const
{
    Q_D(const QPieSeries);
    return d->m_pieRelativeHorPos;
}

qreal QPieSeries::verticalPosition() const
{
    Q_D(const QPieSeries);
    return d->m_pieRelativeVerPos;
}

void QPieSeries::setPieSize(qreal relativeSize)
{
    Q_D(QPieSeries);
    if (d->setRealValue(d->m_pieRelativeSize, relativeSize, 1.0))
        emit pieSizeChanged();
}

qreal QPieSeries::pieSize() const
{
    Q_D(const QPieSeries);
    return d->m_pieRelativeSize;
}


void QPieSeries::setPieStartAngle(qreal angle)
{
    Q_D(QPieSeries);
    if (d->setRealValue(d->m_pieStartAngle, angle, d->m_pieEndAngle))
        d->updateDerivativeData();
}

qreal QPieSeries::pieStartAngle() const
{
    Q_D(const QPieSeries);
    return d->m_pieStartAngle;
}

/*!
    Sets the end angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    \a angle must be greater than start angle.

    \sa pieEndAngle(), pieStartAngle(), setPieStartAngle()
*/
void QPieSeries::setPieEndAngle(qreal angle)
{
    Q_D(QPieSeries);

    if (d->setRealValue(d->m_pieEndAngle, angle, 360.0, d->m_pieStartAngle))
        d->updateDerivativeData();
}

/*!
    Returns the end angle of the pie.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    \sa setPieEndAngle(), pieStartAngle(), setPieStartAngle()
*/
qreal QPieSeries::pieEndAngle() const
{
    Q_D(const QPieSeries);
    return d->m_pieEndAngle;
}

/*!
    Sets the all the slice labels \a visible or invisible.

    \sa QPieSlice::isLabelVisible(), QPieSlice::setLabelVisible()
*/
void QPieSeries::setLabelsVisible(bool visible)
{
    Q_D(QPieSeries);
    foreach (QPieSlice* s, d->m_slices)
        s->setLabelVisible(visible);
}

/*!
    Returns the sum of all slice values in this series.

    \sa QPieSlice::value(), QPieSlice::setValue()
*/
qreal QPieSeries::sum() const
{
    Q_D(const QPieSeries);
    return d->m_sum;
}

/*!
    \fn void QPieSeries::clicked(QPieSlice* slice, Qt::MouseButtons buttons)

    This signal is emitted when a \a slice has been clicked with mouse \a buttons.

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
    \fn void QPieSeries::added(QList<QPieSlice*> slices)

    This signal is emitted when \a slices has been added to the series.

    \sa append(), insert()
*/

/*!
    \fn void QPieSeries::removed(QList<QPieSlice*> slices)

    This signal is emitted when \a slices has been removed from the series.

    \sa remove(), clear()
*/

/*!
    \fn void QPieSeries::piePositionChanged()

    This signal is emitted when pie position has changed.

    \sa verticalPosition(), setVerticalPosition(), horizontalPosition(), setHorizontalPosition()
*/

/*!
    \fn void QPieSeries::pieSizeChanged()

    This signal is emitted when pie size has changed.

    \sa pieSize(), setPieSize()
*/

/*!
     \fn bool QPieSeries::setModel(QAbstractItemModel *model)
     Sets the \a model to be used as a data source
 */
bool QPieSeries::setModel(QAbstractItemModel* model)
{
    Q_D(QPieSeries);
    // disconnect signals from old model
    if(d->m_model)
    {
        disconnect(d->m_model, 0, this, 0);
        d->m_mapValues = -1;
        d->m_mapLabels = -1;
        d->m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if(model)
    {
        d->m_model = model;
        return true;
    }
    else
    {
        d->m_model = 0;
        return false;
    }
}

/*!
     \fn bool QPieSeries::setModelMapping(int modelValuesLine, int modelLabelsLine, Qt::Orientation orientation)
     Sets column/row specified by \a modelValuesLine to be used as a list of pie slice values for the pie.
     Parameter \a modelValuesLine indicates the column/row where the values for the pie slices are located in the model.
     Parameter \a modelLabelsLine indicates the column/row where the labels for the pie slices are located in the model.
     The \a orientation paramater specifies whether the data is in columns or in rows.
 */
void QPieSeries::setModelMapping(int modelValuesLine, int modelLabelsLine, Qt::Orientation orientation)
{
    Q_D(QPieSeries);

    if (d->m_model == 0)
        return;

    d->m_mapValues = modelValuesLine;
    d->m_mapLabels = modelLabelsLine;
    d->m_mapOrientation = orientation;

    // connect the signals
    if (d->m_mapOrientation == Qt::Vertical) {
        connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(d->m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), d, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), d, SLOT(modelDataRemoved(QModelIndex,int,int)));
    } else {
        connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(d->m_model, SIGNAL(columnsInserted(QModelIndex, int, int)), d, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)), d, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }

    // create the initial slices set
    if (d->m_mapOrientation == Qt::Vertical) {
        for (int i = 0; i < d->m_model->rowCount(); i++)
            append(d->m_model->data(d->m_model->index(i, d->m_mapValues), Qt::DisplayRole).toDouble(), d->m_model->data(d->m_model->index(i, d->m_mapLabels), Qt::DisplayRole).toString());
    } else {
        for (int i = 0; i < d->m_model->columnCount(); i++)
            append(d->m_model->data(d->m_model->index(d->m_mapValues, i), Qt::DisplayRole).toDouble(), d->m_model->data(d->m_model->index(d->m_mapLabels, i), Qt::DisplayRole).toString());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QPieSeriesPrivate::QPieSeriesPrivate(QPieSeries *parent)
    :QSeriesPrivate(parent),
    m_pieRelativeHorPos(0.5),
    m_pieRelativeVerPos(0.5),
    m_pieRelativeSize(0.7),
    m_pieStartAngle(0),
    m_pieEndAngle(360),
    m_sum(0),
    m_mapValues(0),
    m_mapLabels(0),
    m_mapOrientation(Qt::Horizontal)
{

}

QPieSeriesPrivate::~QPieSeriesPrivate()
{

}

void QPieSeriesPrivate::updateDerivativeData()
{
    m_sum = 0;

    // nothing to do?
    if (m_slices.count() == 0)
        return;

    // calculate sum of all slices
    foreach (QPieSlice* s, m_slices)
        m_sum += s->value();

    // nothing to show..
    if (qFuzzyIsNull(m_sum))
        return;

    // update slice attributes
    qreal sliceAngle = m_pieStartAngle;
    qreal pieSpan = m_pieEndAngle - m_pieStartAngle;
    QVector<QPieSlice*> changed;
    foreach (QPieSlice* s, m_slices) {

        PieSliceData data = PieSliceData::data(s);
        data.m_percentage = s->value() / m_sum;
        data.m_angleSpan = pieSpan * data.m_percentage;
        data.m_startAngle = sliceAngle;
        sliceAngle += data.m_angleSpan;

        if (PieSliceData::data(s) != data) {
            PieSliceData::data(s) = data;
            changed << s;
        }
    }

    // emit signals
    foreach (QPieSlice* s, changed)
        PieSliceData::data(s).emitChangedSignal(s);
}

void QPieSeriesPrivate::sliceChanged()
{
    Q_ASSERT(m_slices.contains(qobject_cast<QPieSlice *>(sender())));
    updateDerivativeData();
}

void QPieSeriesPrivate::sliceClicked(Qt::MouseButtons buttons)
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    Q_Q(QPieSeries);
    emit q->clicked(slice, buttons);
}

void QPieSeriesPrivate::sliceHoverEnter()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    Q_Q(QPieSeries);
    emit q->hoverEnter(slice);
}

void QPieSeriesPrivate::sliceHoverLeave()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    Q_Q(QPieSeries);
    emit q->hoverLeave(slice);
}

void QPieSeriesPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_UNUSED(bottomRight)

    if (m_mapOrientation == Qt::Vertical)
    {
        if (topLeft.column() == m_mapValues)
            if (m_mapValues == m_mapLabels)
            {
                m_slices.at(topLeft.row())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                m_slices.at(topLeft.row())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
            }
            else
            {
                m_slices.at(topLeft.row())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
            }
        else if (topLeft.column() == m_mapLabels)
            m_slices.at(topLeft.row())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
    }
    else
    {
        if (topLeft.row() == m_mapValues)
            if (m_mapValues == m_mapLabels)
            {
                m_slices.at(topLeft.column())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                m_slices.at(topLeft.column())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
            }
            else
            {
                m_slices.at(topLeft.column())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
            }
        else if (topLeft.row() == m_mapLabels)
            m_slices.at(topLeft.column())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
    }
}

void QPieSeriesPrivate::modelDataAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(end)
    Q_Q(QPieSeries);

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

    q->insert(start, newSlice);
}

void QPieSeriesPrivate::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(end)
    Q_Q(QPieSeries);
    q->remove(m_slices.at(start));
}

bool QPieSeriesPrivate::setRealValue(qreal &value, qreal newValue, qreal max, qreal min)
{
    // Remove rounding errors
    qreal roundedValue = newValue;
    if (qFuzzyIsNull(min) && qFuzzyIsNull(newValue))
        roundedValue = 0.0;
    else if (qFuzzyCompare(newValue, max))
        roundedValue = max;
    else if (qFuzzyCompare(newValue, min))
        roundedValue = min;

    // Check if the position is valid after removing the rounding errors
    if (roundedValue < min || roundedValue > max) {
        qWarning("QPieSeries: Illegal value");
        return false;
    }

    if (!qFuzzyIsNull(value - roundedValue)) {
        value = roundedValue;
        return true;
    }

    // The change was so small it is considered a rounding error
    return false;
}


#include "moc_qpieseries.cpp"
#include "moc_qpieseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
