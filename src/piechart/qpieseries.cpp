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
#include "qpiemodelmapper_p.h"

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
    \property QPieSeries::count
    \brief Number of slices in the series.

*/

/*!
    \property QPieSeries::sum
    \brief Sum of all slices.

    The series keeps track of the sum of all slices it holds.
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

    Returns true if append was successfull.
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
        connect(s, SIGNAL(valueChanged()), d, SLOT(sliceChanged()));
        connect(s, SIGNAL(clicked()), d, SLOT(sliceClicked()));
        connect(s, SIGNAL(hovered(bool)), d, SLOT(sliceHovered(bool)));
    }

    emit added(slices);

    return true;
}

/*!
    Appends a single \a slice to the series.
    Slice ownership is passed to the series.

    Returns true if append was succesfull.
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
    Appends a single slice to the series with give \a value and \a label.
    Slice ownership is passed to the series.
*/
QPieSlice* QPieSeries::append(QString label, qreal value)
{
    QPieSlice* slice = new QPieSlice(label, value);
    append(slice);
    return slice;
}

/*!
    Inserts a single \a slice to the series before the slice at \a index position.
    Slice ownership is passed to the series.

    Returns true if insert was successfull.
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

    connect(slice, SIGNAL(valueChanged()), d, SLOT(sliceChanged()));
    connect(slice, SIGNAL(clicked()), d, SLOT(sliceClicked()));
    connect(slice, SIGNAL(hovered(bool)), d, SLOT(sliceHovered(bool)));

    emit added(QList<QPieSlice*>() << slice);

    return true;
}

/*!
    Removes a single \a slice from the series and deletes the slice.

    Do not reference the pointer after this call.

    Returns true if remove was successfull.
*/
bool QPieSeries::remove(QPieSlice* slice)
{
    Q_D(QPieSeries);

    if (!d->m_slices.removeOne(slice))
        return false;

    d->updateDerivativeData();

    emit removed(QList<QPieSlice*>() << slice);

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
    if (qFuzzyIsNull(d->m_pieStartAngle - angle))
        return;
    d->m_pieStartAngle = angle;
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
    if (qFuzzyIsNull(d->m_pieEndAngle - angle))
        return;
    d->m_pieEndAngle = angle;
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
    \fn void QPieSeries::added(QList<QPieSlice*> slices)

    This signal is emitted when \a slices have been added to the series.

    \sa append(), insert()
*/

/*!
    \fn void QPieSeries::removed(QList<QPieSlice*> slices)

    This signal is emitted when \a slices have been removed from the series.

    \sa remove()
*/

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
    d->setModel(model);
    //    // disconnect signals from old model
    //    if(d->m_model)
    //    {
    //        disconnect(d->m_model, 0, this, 0);
    //    }

    //    // set new model
    //    if(model)
    //    {
    //        d->m_model = model;
    //        // connect signals from the model
    ////        connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    ////        connect(d->m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelRowsAdded(QModelIndex,int,int)));
    ////        connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelRowsRemoved(QModelIndex,int,int)));
    ////        connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelColumnsAdded(QModelIndex,int,int)));
    ////        connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelColumnsRemoved(QModelIndex,int,int)));

    ////        if (d->m_mapper)
    ////            d->initializePieFromModel();
    //    }
    //    else
    //    {
    //        d->m_model = 0;
    //    }
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
        //        connect(d->m_mapper, SIGNAL(updated()), d, SLOT(initializePieFromModel()));

        //        if (d->m_model)
        //            d->initializePieFromModel();
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
    m_model(0),
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

        PieSliceData data = PieSliceData::fromSlice(s);
        data.m_percentage = s->value() / m_sum;
        data.m_angleSpan = pieSpan * data.m_percentage;
        data.m_startAngle = sliceAngle;
        sliceAngle += data.m_angleSpan;

        if (PieSliceData::fromSlice(s) != data) {
            PieSliceData::fromSlice(s) = data;
            changed << s;
        }
    }

    // emit signals
    foreach (QPieSlice* s, changed)
        PieSliceData::emitCalculatedDataChanged(s);
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
    // does not apply to pie
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

void QPieSeriesPrivate::setModel(QAbstractItemModel* model)
{
    Q_Q(QPieSeries);
    QPieModelMapperPrivate *mapperPrivate = m_mapper->d_func();
    mapperPrivate->setModel(model);
    if(mapperPrivate->m_series != q)
    {
        disconnect(mapperPrivate->m_series, 0, mapperPrivate, 0);
        mapperPrivate->m_series = q;
        connect(this, SIGNAL(added(QList<QPieSlice*>)), mapperPrivate, SLOT(slicesAdded()));
        connect(this, SIGNAL(removed(QList<QPieSlice*>)), mapperPrivate, SLOT(slicesRemoved()));
        connect(this, SIGNAL(modified()), mapperPrivate, SLOT(sliceChanged()));
    }
}

#include "moc_qpieseries.cpp"
#include "moc_qpieseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
