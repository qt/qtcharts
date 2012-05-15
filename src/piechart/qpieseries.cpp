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
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"
#include "legendmarker_p.h"
#include <QAbstractItemModel>
#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPieSeries
    \brief Pie series API for QtCommercial Charts

    The pie series defines a pie chart which consists of pie slices which are defined as QPieSlice objects.
    The slices can have any values as the QPieSeries will calculate its relative value to the sum of all slices.
    The actual slice size is determined by that relative value.

    Pie size and position on the chart is controlled by using relative values which range from 0.0 to 1.0
    These relate to the actual chart rectangle.

    By default the pie is defined as a full pie but it can also be a partial pie.
    This can be done by setting a starting angle and angle span to the series.
    Full pie is 360 degrees where 0 is at 12 a'clock.

    See the \l {PieChart Example} {pie chart example} to learn how to create a simple pie chart.
    \image examples_piechart.png
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
    \o 0.0 is the minimum size (pie not drawn).
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
    QAbstractSeries(*new QPieSeriesPrivate(this),parent)
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
QAbstractSeries::SeriesType QPieSeries::type() const
{
    return QAbstractSeries::SeriesTypePie;
}

/*!
    Appends an array of \a slices to the series.
    Slice ownership is passed to the series.
*/
bool QPieSeries::append(QList<QPieSlice*> slices)
{
    Q_D(QPieSeries);

    if (slices.count() == 0)
        return false;

    foreach (QPieSlice* s, slices) {
        if (!s || d->m_slices.contains(s))
            return false;
    }

    foreach (QPieSlice* s, slices) {
        s->setParent(this);
        d->m_slices << s;
    }

    d->updateDerivativeData();

    foreach (QPieSlice* s, slices) {
        connect(s, SIGNAL(changed()), d, SLOT(sliceChanged()));
        connect(s, SIGNAL(clicked()), d, SLOT(sliceClicked()));
        connect(s, SIGNAL(hovered(bool)), d, SLOT(sliceHovered(bool)));
    }

    emit d->added(slices);

    return true;
}

/*!
    Appends a single \a slice to the series.
    Slice ownership is passed to the series.
*/
bool QPieSeries::append(QPieSlice* slice)
{
    return append(QList<QPieSlice*>() << slice);
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
bool QPieSeries::insert(int index, QPieSlice* slice)
{
    Q_D(QPieSeries);

    if (index < 0 || index > d->m_slices.count())
        return false;

    if (!slice || d->m_slices.contains(slice))
        return false;

    slice->setParent(this);
    d->m_slices.insert(index, slice);

    d->updateDerivativeData();

    connect(slice, SIGNAL(changed()), d, SLOT(sliceChanged()));
    connect(slice, SIGNAL(clicked()), d, SLOT(sliceClicked()));
    connect(slice, SIGNAL(hovered(bool)), d, SLOT(sliceHovered(bool)));

    emit d->added(QList<QPieSlice*>() << slice);

    return true;
}

/*!
    Removes a single \a slice from the series and deletes the slice.

    Do not reference the pointer after this call.
*/
bool QPieSeries::remove(QPieSlice* slice)
{
    Q_D(QPieSeries);

    if (!d->m_slices.removeOne(slice))
        return false;

    d->updateDerivativeData();

    emit d->removed(QList<QPieSlice*>() << slice);

    delete slice;
    slice = 0;

    return true;
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

    emit d->removed(slices);
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
        emit d->piePositionChanged();
}

void QPieSeries::setVerticalPosition(qreal relativePosition)
{
    Q_D(QPieSeries);
    if (d->setRealValue(d->m_pieRelativeVerPos, relativePosition, 1.0))
        emit d->piePositionChanged();
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
        emit d->pieSizeChanged();
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

    \sa QPieSlice::value(), QPieSlice::setValue(), QPieSlice::percentage()
*/
qreal QPieSeries::sum() const
{
    Q_D(const QPieSeries);
    return d->m_sum;
}

/*!
    \fn void QPieSeries::clicked(QPieSlice* slice)

    This signal is emitted when a \a slice has been clicked.

    \sa QPieSlice::clicked()
*/

/*!
    \fn void QPieSeries::hovered(QPieSlice* slice, bool state)

    This signal is emitted when user has hovered over or away from the \a slice.

    \a state is true when user has hovered over the slice and false when hover has moved away from the slice.

    \sa QPieSlice::hovered()
*/

/*!
     \fn bool QPieSeries::setModel(QAbstractItemModel *model)
     Sets the \a model to be used as a data source
 */
void QPieSeries::setModel(QAbstractItemModel* model)
{
    Q_D(QPieSeries);
    // disconnect signals from old model
    if(d->m_model)
    {
        disconnect(d->m_model, 0, this, 0);
    }

    // set new model
    if(model)
    {
        d->m_model = model;
        // connect signals from the model
        connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
        connect(d->m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelRowsAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelRowsRemoved(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelColumnsAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelColumnsRemoved(QModelIndex,int,int)));

        if (d->m_mapper)
            d->initializePieFromModel();
    }
    else
    {
        d->m_model = 0;
    }
}

void QPieSeries::setModelMapper(QPieModelMapper *mapper)
{
    Q_D(QPieSeries);
    // disconnect signals from old mapper
    if (d->m_mapper) {
        QObject::disconnect(d->m_mapper, 0, this, 0);
    }

    if (mapper) {
        d->m_mapper = mapper;
        // connect the signal from the mapper
        connect(d->m_mapper, SIGNAL(updated()), d, SLOT(initializePieFromModel()));

        if (d->m_model)
            d->initializePieFromModel();
    } else {
        d->m_mapper = 0;
    }
}

QPieModelMapper* QPieSeries::modelMapper() const
{
    Q_D(const QPieSeries);
    return d->m_mapper;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QPieSeriesPrivate::QPieSeriesPrivate(QPieSeries *parent) :
    QAbstractSeriesPrivate(parent),
    m_pieRelativeHorPos(0.5),
    m_pieRelativeVerPos(0.5),
    m_pieRelativeSize(0.7),
    m_pieStartAngle(0),
    m_pieEndAngle(360),
    m_sum(0),
    m_mapper(0)
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

QPieSeriesPrivate* QPieSeriesPrivate::seriesData(QPieSeries &series)
{
    return series.d_func();
}

void QPieSeriesPrivate::sliceChanged()
{
    Q_ASSERT(m_slices.contains(qobject_cast<QPieSlice *>(sender())));
    updateDerivativeData();
}

void QPieSeriesPrivate::sliceClicked()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    Q_Q(QPieSeries);
    emit q->clicked(slice);
}

void QPieSeriesPrivate::sliceHovered(bool state)
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    Q_Q(QPieSeries);
    emit q->hovered(slice, state);
}

void QPieSeriesPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    if (m_mapper) {
        for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
            for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
                if (m_mapper->orientation() == Qt::Vertical)
                {
                    if ( topLeft.row() >= m_mapper->first() && (m_mapper->count() == - 1 || topLeft.row() < m_mapper->first() + m_mapper->count())) {
                        if (topLeft.column() == m_mapper->mapValues())
                            m_slices.at(topLeft.row() - m_mapper->first())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                        if (topLeft.column() == m_mapper->mapLabels())
                            m_slices.at(topLeft.row() - m_mapper->first())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
                    }
                }
                else
                {
                    if (topLeft.column() >= m_mapper->first() && (m_mapper->count() == - 1 || topLeft.column() < m_mapper->first() + m_mapper->count())) {
                        if (topLeft.row() == m_mapper->mapValues())
                            m_slices.at(topLeft.column() - m_mapper->first())->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                        if (topLeft.row() == m_mapper->mapLabels())
                            m_slices.at(topLeft.column() - m_mapper->first())->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
                    }
                }
            }
        }
    }
}


void QPieSeriesPrivate::modelRowsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_mapper) {
        if (m_mapper->orientation() == Qt::Vertical)
            insertData(start, end);
        else if (start <= m_mapper->mapValues() || start <= m_mapper->mapLabels()) // if the changes affect the map - reinitialize the pie
            initializePieFromModel();
    }
}

void QPieSeriesPrivate::modelRowsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_mapper) {
        if (m_mapper->orientation() == Qt::Vertical)
            removeData(start, end);
        else if (start <= m_mapper->mapValues() || start <= m_mapper->mapLabels()) // if the changes affect the map - reinitialize the pie
            initializePieFromModel();
    }
}

void QPieSeriesPrivate::modelColumnsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_mapper) {
        if (m_mapper->orientation() == Qt::Horizontal)
            insertData(start, end);
        else if (start <= m_mapper->mapValues() || start <= m_mapper->mapLabels()) // if the changes affect the map - reinitialize the pie
            initializePieFromModel();
    }
}

void QPieSeriesPrivate::modelColumnsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_mapper) {
        if (m_mapper->orientation() == Qt::Horizontal)
            removeData(start, end);
        else if (start <= m_mapper->mapValues() || start <= m_mapper->mapLabels()) // if the changes affect the map - reinitialize the pie
            initializePieFromModel();
    }
}

void QPieSeriesPrivate::insertData(int start, int end)
{
    Q_Q(QPieSeries);
    if (m_mapper) {
        if (m_mapper->count() != -1 && start >= m_mapper->first() + m_mapper->count()) {
            return;
        } else {
            int addedCount = end - start + 1;
            if (m_mapper->count() != -1 && addedCount > m_mapper->count())
                addedCount = m_mapper->count();
            int first = qMax(start, m_mapper->first());
            int last = qMin(first + addedCount - 1, m_mapper->orientation() == Qt::Vertical ? m_model->rowCount() - 1 : m_model->columnCount() - 1);
            for (int i = first; i <= last; i++) {
                QPieSlice *slice = new QPieSlice;
                if (m_mapper->orientation() == Qt::Vertical) {
                    slice->setValue(m_model->data(m_model->index(i, m_mapper->mapValues()), Qt::DisplayRole).toDouble());
                    slice->setLabel(m_model->data(m_model->index(i, m_mapper->mapLabels()), Qt::DisplayRole).toString());
                } else {
                    slice->setValue(m_model->data(m_model->index(m_mapper->mapValues(), i), Qt::DisplayRole).toDouble());
                    slice->setLabel(m_model->data(m_model->index(m_mapper->mapLabels(), i), Qt::DisplayRole).toString());
                }
                slice->setLabelVisible();
                q->insert(i - m_mapper->first(), slice);
            }
            if (m_mapper->count() != -1 && m_slices.size() > m_mapper->count())
                for (int i = m_slices.size() - 1; i >= m_mapper->count(); i--)
                    q->remove(q->slices().at(i));
        }
    }
}

void QPieSeriesPrivate::removeData(int start, int end)
{
    Q_Q(QPieSeries);
    if (m_mapper) {
        int removedCount = end - start + 1;
        if (m_mapper->count() != -1 && start >= m_mapper->first() + m_mapper->count()) {
            return;
        } else {
            int toRemove = qMin(m_slices.size(), removedCount);     // first find how many items can actually be removed
            int first = qMax(start, m_mapper->first());    // get the index of the first item that will be removed.
            int last = qMin(first + toRemove - 1, m_slices.size() + m_mapper->first() - 1);    // get the index of the last item that will be removed.
            for (int i = last; i >= first; i--)
                q->remove(q->slices().at(i - m_mapper->first()));

            if (m_mapper->count() != -1) {
                int itemsAvailable;     // check how many are available to be added
                if (m_mapper->orientation() == Qt::Vertical)
                    itemsAvailable = m_model->rowCount() - m_mapper->first() - m_slices.size();
                else
                    itemsAvailable = m_model->columnCount() - m_mapper->first() - m_slices.size();
                int toBeAdded = qMin(itemsAvailable, m_mapper->count() - m_slices.size());     // add not more items than there is space left to be filled.
                int currentSize = m_slices.size();
                if (toBeAdded > 0)
                    for (int i = m_slices.size(); i < currentSize + toBeAdded; i++) {
                        QPieSlice *slice = new QPieSlice;
                        if (m_mapper->orientation() == Qt::Vertical) {
                            slice->setValue(m_model->data(m_model->index(i + m_mapper->first(), m_mapper->mapValues()), Qt::DisplayRole).toDouble());
                            slice->setLabel(m_model->data(m_model->index(i + m_mapper->first(), m_mapper->mapLabels()), Qt::DisplayRole).toString());
                        } else {
                            slice->setValue(m_model->data(m_model->index(m_mapper->mapValues(), i + m_mapper->first()), Qt::DisplayRole).toDouble());
                            slice->setLabel(m_model->data(m_model->index(m_mapper->mapLabels(), i + m_mapper->first()), Qt::DisplayRole).toString());
                        }
                        slice->setLabelVisible();
                        q->insert(i, slice);
                    }
            }
        }
    }
}

void QPieSeriesPrivate::initializePieFromModel()
{
    Q_Q(QPieSeries);
    // clear current content
    q->clear();

    // create the initial slices set
    if (m_mapper->orientation() == Qt::Vertical) {
        if (m_mapper->mapValues() >= m_model->columnCount() || m_mapper->mapLabels() >= m_model->columnCount())
            return;   // mapped columns are not existing

        int sliceCount = 0;
        if(m_mapper->count() == -1)
            sliceCount = m_model->rowCount() - m_mapper->first();
        else
            sliceCount = qMin(m_mapper->count(), m_model->rowCount() - m_mapper->first());
        for (int i = m_mapper->first(); i < m_mapper->first() + sliceCount; i++)
            q->append(m_model->data(m_model->index(i, m_mapper->mapValues()), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(i, m_mapper->mapLabels()), Qt::DisplayRole).toString());
    } else {
        if (m_mapper->mapValues() >= m_model->rowCount() || m_mapper->mapLabels() >= m_model->rowCount())
            return;   // mapped columns are not existing

        int sliceCount = 0;
        if(m_mapper->count() == -1)
            sliceCount = m_model->columnCount() - m_mapper->first();
        else
            sliceCount = qMin(m_mapper->count(), m_model->columnCount() - m_mapper->first());
        for (int i = m_mapper->first(); i < m_mapper->first() + sliceCount; i++)
            q->append(m_model->data(m_model->index(m_mapper->mapValues(), i), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(m_mapper->mapLabels(), i), Qt::DisplayRole).toString());
    }
    q->setLabelsVisible(true);
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

void QPieSeriesPrivate::scaleDomain(Domain& domain)
{
    Q_UNUSED(domain);
#ifndef QT_NO_DEBUG
    qWarning() << __FILE__<<__FUNCTION__<<"not implemented";
#endif
}

Chart* QPieSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QPieSeries);
    PieChartItem* pie = new PieChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(pie);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return pie;
}

QList<LegendMarker*> QPieSeriesPrivate::createLegendMarker(QLegend* legend)
{
    Q_Q(QPieSeries);
    QList<LegendMarker*> markers;
    foreach(QPieSlice* slice, q->slices()) {
        PieLegendMarker* marker = new PieLegendMarker(q,slice,legend);
        markers << marker;
    }
    return markers;
}

#include "moc_qpieseries.cpp"
#include "moc_qpieseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
