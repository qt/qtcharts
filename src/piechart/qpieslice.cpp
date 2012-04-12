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

#include "qpieslice.h"
#include "pieslicedata_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPieSlice
    \brief Defines a slice in pie series.

    This object defines the properties of a single slice in a QPieSeries.

    In addition to the obvious value and label properties the user can also control
    the visual appearance of a slice. By modifying the visual appearance also means that
    the user is overriding the default appearance set by the theme. Even if the theme is
    changed users settings will persist.

    To enable user interaction customization with the slices some basic signals
    are provided about clicking and hovering.
*/

/*!
    \property QPieSlice::label

    Label of the slice.
*/

/*!
    \property QPieSlice::value

    Value of the slice.

    \sa percentage(), QPieSeries::sum()
*/

/*!
    Constructs an empty slice with a \a parent.

    \sa QPieSeries::append(), QPieSeries::insert(), QPieSeries::replace()
*/
QPieSlice::QPieSlice(QObject *parent)
    :QObject(parent),
    d(new PieSliceData())
{

}

/*!
    Constructs an empty slice with given \a value, \a label and a \a parent.
    \sa QPieSeries::append(), QPieSeries::insert(), QPieSeries::replace()
*/
QPieSlice::QPieSlice(qreal value, QString label, QObject *parent)
    :QObject(parent),
    d(new PieSliceData())
{
    d->m_value = value;
    d->m_labelText = label;
}

/*!
    Destroys the slice.
    User should not delete the slice if it has been added to the series.
*/
QPieSlice::~QPieSlice()
{
    delete d;
}

/*!
    Gets the value of the slice.
    Note that all values in the series
    \sa setValue()
*/
qreal QPieSlice::value() const
{
    return d->m_value;
}

/*!
    Gets the label of the slice.
    \sa setLabel()
*/
QString QPieSlice::label() const
{ 
    return d->m_labelText;
}

/*!
    Returns true if label is set as visible.
    \sa setLabelVisible()
*/
bool QPieSlice::isLabelVisible() const
{
    return d->m_isLabelVisible;
}

/*!
    Returns true if slice is exloded from the pie.
    \sa setExploded(), explodeDistanceFactor(), setExplodeDistanceFactor()
*/
bool QPieSlice::isExploded() const
{
    return d->m_isExploded;
}

/*!
    Returns the explode distance factor.

    The factor is relative to pie radius. For example:
    1.0 means the distance is the same as the radius.
    0.5 means the distance is half of the radius.

    Default value is 0.15.

    \sa setExplodeDistanceFactor(), isExploded(), setExploded()
*/
qreal QPieSlice::explodeDistanceFactor() const
{
    return d->m_explodeDistanceFactor;
}

/*!
    Returns the percentage of this slice compared to the sum of all slices in the same series.
    The returned value ranges from 0 to 1.0.

    Updated internally after the slice is added to the series.

    \sa QPieSeries::sum()
*/
qreal QPieSlice::percentage() const
{
    return d->m_percentage;
}

/*!
    Returns the starting angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::startAngle() const
{
    return d->m_startAngle;
}

/*!
    Returns the end angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::endAngle() const
{
    return d->m_startAngle + d->m_angleSpan;
}

/*!
    Returns the pen used to draw this slice.
    \sa setPen()
*/
QPen QPieSlice::pen() const
{
    return d->m_slicePen;
}

/*!
    Returns the brush used to draw this slice.
    \sa setBrush()
*/
QBrush QPieSlice::brush() const
{
    return d->m_sliceBrush;
}

/*!
    Returns the pen used to draw the label in this slice.
    \sa setLabelPen()
*/
QPen QPieSlice::labelPen() const
{
    return d->m_labelPen;
}

/*!
    Returns the font used to draw label in this slice.
    \sa setLabelFont()
*/
QFont QPieSlice::labelFont() const
{
    return d->m_labelFont;
}

/*!
    Gets the label arm length factor.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa setLabelArmLengthFactor()
*/
qreal QPieSlice::labelArmLengthFactor() const
{
    return d->m_labelArmLengthFactor;
}

/*!
    \fn void QPieSlice::clicked()

    This signal is emitted when user has clicked the slice.

    \sa QPieSeries::clicked()
*/

/*!
    \fn void QPieSlice::hovered(bool state)

    This signal is emitted when user has hovered over or away from the slice.

    \a state is true when user has hovered over the slice and false when hover has moved away from the slice.

    \sa QPieSeries::hovered()
*/

/*!
    \fn void QPieSlice::changed()

    This signal emitted when something has changed in the slice.
*/

/*!
    Sets the \a value of this slice.
    \sa value()
*/
void QPieSlice::setValue(qreal value)
{
    if (!qFuzzyIsNull(d->m_value - value)) {
        d->m_value = value;
        emit changed();
    }
}

/*!
    Sets the \a label of the slice.
    \sa label()
*/
void QPieSlice::setLabel(QString label)
{
    if (d->m_labelText != label) {
        d->m_labelText = label;
        emit changed();
    }
}

/*!
    Sets the label \a visible in this slice.
    \sa isLabelVisible(), QPieSeries::setLabelsVisible()
*/
void QPieSlice::setLabelVisible(bool visible)
{
    if (d->m_isLabelVisible != visible) {
        d->m_isLabelVisible = visible;
        emit changed();
    }
}

/*!
    Sets this slices \a exploded state.

    If the slice is exploded it is moved away from the pie center. The distance is defined by the explode distance factor.

    \sa isExploded(), explodeDistanceFactor(), setExplodeDistanceFactor()
*/
void QPieSlice::setExploded(bool exploded)
{
    if (d->m_isExploded != exploded) {
        d->m_isExploded = exploded;
        emit changed();
    }
}

/*!
    Sets the explode distance \a factor.

    The factor is relative to pie radius. For example:
    1.0 means the distance is the same as the radius.
    0.5 means the distance is half of the radius.

    Default value is 0.15

    \sa explodeDistanceFactor(), isExploded(), setExploded()
*/
void QPieSlice::setExplodeDistanceFactor(qreal factor)
{
    if (!qFuzzyIsNull(d->m_explodeDistanceFactor - factor)) {
        d->m_explodeDistanceFactor = factor;
        emit changed();
    }
}

/*!
    Sets the \a pen used to draw this slice.

    Overrides the pen set by the theme.

    \sa pen()
*/
void QPieSlice::setPen(const QPen &pen)
{
    if (d->m_slicePen != pen) {
        d->m_slicePen = pen;
        d->m_slicePen.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the \a brush used to draw this slice.

    Overrides the brush set by the theme.

    \sa brush()
*/
void QPieSlice::setBrush(const QBrush &brush)
{
    if (d->m_sliceBrush != brush) {
        d->m_sliceBrush = brush;
        d->m_sliceBrush.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the \a pen used to draw the label in this slice.

    Overrides the pen set by the theme.

    \sa labelPen()
*/
void QPieSlice::setLabelPen(const QPen &pen)
{
    if (d->m_labelPen != pen) {
        d->m_labelPen = pen;
        d->m_labelPen.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the \a font used to draw the label in this slice.

    Overrides the font set by the theme.

    \sa labelFont()
*/
void QPieSlice::setLabelFont(const QFont &font)
{
    if (d->m_labelFont != font) {
        d->m_labelFont = font;
        d->m_labelFont.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the label arm length \a factor.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa labelArmLengthFactor()
*/
void QPieSlice::setLabelArmLengthFactor(qreal factor)
{
    if (!qFuzzyIsNull(d->m_labelArmLengthFactor - factor)) {
        d->m_labelArmLengthFactor = factor;
        emit changed();
    }
}

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE
#include "moc_qpieslice.cpp"
