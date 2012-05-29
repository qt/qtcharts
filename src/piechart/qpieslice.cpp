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
#include "qpieslice_p.h"

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

    \sa QPieSeries::append(), QPieSeries::insert()
*/
QPieSlice::QPieSlice(QObject *parent)
    :QObject(parent),
    d_ptr(new QPieSlicePrivate(this))
{

}

/*!
    Constructs an empty slice with given \a value, \a label and a \a parent.
    \sa QPieSeries::append(), QPieSeries::insert()
*/
QPieSlice::QPieSlice(QString label, qreal value, QObject *parent)
    :QObject(parent),
    d_ptr(new QPieSlicePrivate(this))
{
    d_ptr->m_data.m_value = value;
    d_ptr->m_data.m_labelText = label;
}

/*!
    Destroys the slice.
    User should not delete the slice if it has been added to the series.
*/
QPieSlice::~QPieSlice()
{

}

/*!
    Gets the value of the slice.
    Note that all values in the series
    \sa setValue()
*/
qreal QPieSlice::value() const
{
    return d_ptr->m_data.m_value;
}

/*!
    Gets the label of the slice.
    \sa setLabel()
*/
QString QPieSlice::label() const
{ 
    return d_ptr->m_data.m_labelText;
}

/*!
    Returns true if label is set as visible.
    \sa setLabelVisible()
*/
bool QPieSlice::isLabelVisible() const
{
    return d_ptr->m_data.m_isLabelVisible;
}

/*!
    Returns true if slice is exloded from the pie.
    \sa setExploded(), explodeDistanceFactor(), setExplodeDistanceFactor()
*/
bool QPieSlice::isExploded() const
{
    return d_ptr->m_data.m_isExploded;
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
    return d_ptr->m_data.m_explodeDistanceFactor;
}

/*!
    Returns the percentage of this slice compared to the sum of all slices in the same series.
    The returned value ranges from 0 to 1.0.

    Updated internally after the slice is added to the series.

    \sa QPieSeries::sum()
*/
qreal QPieSlice::percentage() const
{
    return d_ptr->m_data.m_percentage;
}

/*!
    Returns the starting angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::startAngle() const
{
    return d_ptr->m_data.m_startAngle;
}

/*!
    Returns the end angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::angleSpan() const
{
    return d_ptr->m_data.m_angleSpan;
}

/*!
    Returns the pen used to draw this slice.
    \sa setPen()
*/
QPen QPieSlice::pen() const
{
    return d_ptr->m_data.m_slicePen;
}

/*!
    Returns the brush used to draw this slice.
    \sa setBrush()
*/
QBrush QPieSlice::brush() const
{
    return d_ptr->m_data.m_sliceBrush;
}

/*!
    Returns the pen used to draw the label in this slice.
    \sa setLabelPen()
*/
QPen QPieSlice::labelPen() const
{
    return d_ptr->m_data.m_labelPen;
}

/*!
    Returns the font used to draw label in this slice.
    \sa setLabelFont()
*/
QFont QPieSlice::labelFont() const
{
    return d_ptr->m_data.m_labelFont;
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
    return d_ptr->m_data.m_labelArmLengthFactor;
}

/*!
    \fn void QPieSlice::labelChanged()

    This signal is emitted when the slice label changes.

    \sa setLabel()
*/

/*!
    \fn void QPieSlice::valueChanged()

    This signal is emitted when the slice value changes.

    \sa setValue()
*/

/*!
    \fn void QPieSlice::appearanceChanged()

    This signal is emitted when visual appearance of the slice changes.

    \sa setPen(), setBrush(), setLabelVisible(), setExploded()
*/

/*!
    \fn void QPieSlice::calculatedDataChanged()

    This signal is emitted when calculated data for this slice changes.

    \sa percentage(), startAngle(), endAngle()
*/

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
    Sets the \a value of this slice.
    \sa value()
*/
void QPieSlice::setValue(qreal value)
{
    if (!qFuzzyIsNull(d_ptr->m_data.m_value - value)) {
        d_ptr->m_data.m_value = value;
        emit valueChanged();
    }
}

/*!
    Sets the \a label of the slice.
    \sa label()
*/
void QPieSlice::setLabel(QString label)
{
    if (d_ptr->m_data.m_labelText != label) {
        d_ptr->m_data.m_labelText = label;
        emit labelChanged();
    }
}

/*!
    Sets the label \a visible in this slice.
    \sa isLabelVisible(), QPieSeries::setLabelsVisible()
*/
void QPieSlice::setLabelVisible(bool visible)
{
    if (d_ptr->m_data.m_isLabelVisible != visible) {
        d_ptr->m_data.m_isLabelVisible = visible;
        emit labelVisibleChanged();
    }
}

/*!
    Sets this slices \a exploded state.

    If the slice is exploded it is moved away from the pie center. The distance is defined by the explode distance factor.

    \sa isExploded(), explodeDistanceFactor(), setExplodeDistanceFactor()
*/
void QPieSlice::setExploded(bool exploded)
{
    if (d_ptr->m_data.m_isExploded != exploded) {
        d_ptr->m_data.m_isExploded = exploded;
        emit explodedChanged();
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
    if (!qFuzzyIsNull(d_ptr->m_data.m_explodeDistanceFactor - factor)) {
        d_ptr->m_data.m_explodeDistanceFactor = factor;
        emit explodeDistanceFactorChanged();
    }
}

/*!
    Sets the \a pen used to draw this slice.

    Overrides the pen set by the theme.

    \sa pen()
*/
void QPieSlice::setPen(const QPen &pen)
{
    d_ptr->setPen(pen, false);
}

/*!
    Sets the \a brush used to draw this slice.

    Overrides the brush set by the theme.

    \sa brush()
*/
void QPieSlice::setBrush(const QBrush &brush)
{
    d_ptr->setBrush(brush, false);
}

/*!
    Sets the \a pen used to draw the label in this slice.

    Overrides the pen set by the theme.

    \sa labelPen()
*/
void QPieSlice::setLabelPen(const QPen &pen)
{
    d_ptr->setLabelPen(pen, false);
}

/*!
    Sets the \a font used to draw the label in this slice.

    Overrides the font set by the theme.

    \sa labelFont()
*/
void QPieSlice::setLabelFont(const QFont &font)
{
    d_ptr->setLabelFont(font, false);
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
    if (!qFuzzyIsNull(d_ptr->m_data.m_labelArmLengthFactor - factor)) {
        d_ptr->m_data.m_labelArmLengthFactor = factor;
        emit labelArmLengthFactorChanged();
    }
}

QPieSlicePrivate::QPieSlicePrivate(QPieSlice *parent)
    :QObject(parent),
    q_ptr(parent)
{

}

QPieSlicePrivate::~QPieSlicePrivate()
{

}

QPieSlicePrivate *QPieSlicePrivate::fromSlice(QPieSlice *slice)
{
    return slice->d_func();
}

void QPieSlicePrivate::setPen(const QPen &pen, bool themed)
{
    if (m_data.m_slicePen != pen) {
        m_data.m_slicePen = pen;
        m_data.m_slicePen.setThemed(themed);
        emit q_ptr->penChanged();
    }
}

void QPieSlicePrivate::setBrush(const QBrush &brush, bool themed)
{
    if (m_data.m_sliceBrush != brush) {
        m_data.m_sliceBrush = brush;
        m_data.m_sliceBrush.setThemed(themed);
        emit q_ptr->brushChanged();
    }
}

void QPieSlicePrivate::setLabelPen(const QPen &pen, bool themed)
{
    if (m_data.m_labelPen != pen) {
        m_data.m_labelPen = pen;
        m_data.m_labelPen.setThemed(themed);
        emit q_ptr->labelPenChanged();
    }
}

void QPieSlicePrivate::setLabelFont(const QFont &font, bool themed)
{
    if (m_data.m_labelFont != font) {
        m_data.m_labelFont = font;
        m_data.m_labelFont.setThemed(themed);
        emit q_ptr->labelFontChanged();
    }
}

void QPieSlicePrivate::setPercentage(qreal percentage)
{
    if (!qFuzzyIsNull(m_data.m_percentage - percentage)) {
        m_data.m_percentage = percentage;
        emit q_ptr->percentageChanged();
    }
}

void QPieSlicePrivate::setStartAngle(qreal angle)
{
    if (!qFuzzyIsNull(m_data.m_startAngle - angle)) {
        m_data.m_startAngle = angle;
        emit q_ptr->startAngleChanged();
    }
}

void QPieSlicePrivate::setAngleSpan(qreal span)
{
    if (!qFuzzyIsNull(m_data.m_angleSpan - span)) {
        m_data.m_angleSpan = span;
        emit q_ptr->angleSpanChanged();
    }
}

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE
#include "moc_qpieslice.cpp"
#include "moc_qpieslice_p.cpp"
