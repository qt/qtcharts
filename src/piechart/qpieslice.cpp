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
    the user is overriding the default appearance set by the theme.

    Note that if the user has customized slices and theme is changed all customizations will be lost.

    To enable user interaction with the pie some basic signals are provided about clicking and hovering.
*/

/*!
    \property QPieSlice::label

    Label of the slice.

    \sa labelVisible, labelBrush, labelFont, labelArmLengthFactor
*/

/*!
    \fn void QPieSlice::labelChanged()

    This signal emitted when the slice label has been changed.

    \sa label
*/

/*!
    \property QPieSlice::value

    Value of the slice.

    Note that if users sets a negative value it is converted to a positive value.

    \sa percentage(), QPieSeries::sum()
*/

/*!
    \fn void QPieSlice::valueChanged()

    This signal is emitted when the slice value changes.

    \sa value
*/

/*!
    \property QPieSlice::labelVisible

    Defienes the visibility of the slice label.

    Default is not visible.

    \sa label, labelBrush, labelFont, labelArmLengthFactor
*/

/*!
    \fn void QPieSlice::labelVisibleChanged()

    This signal emitted when visibility of the slice label has changed.

    \sa labelVisible
*/

/*!
    \property QPieSlice::exploded

    Defines if the slice is exploded from the pie.

    \sa explodeDistanceFactor
*/

/*!
    \fn void QPieSlice::explodedChanged()

    This signal is emitted the the slice has been exploded from the pie or is returned back to the pie.

    \sa exploded
*/

/*!
    \property QPieSlice::pen

    Pen used to draw the slice border.
*/

/*!
    \fn void QPieSlice::penChanged()

    This signal is emitted when the pen of the slice has changed.

    \sa pen
*/

/*!
    \property QPieSlice::brush

    Brush used to draw the slice.
*/

/*!
    \fn void QPieSlice::brushChanged()

    This signal is emitted when the brush of the slice has changed.

    \sa brush
*/

/*!
    \property QPieSlice::labelBrush

    Pen used to draw label and label arm of the slice.

    \sa label, labelVisible, labelFont, labelArmLengthFactor
*/

/*!
    \fn void QPieSlice::labelBrushChanged()

    This signal is emitted when the label pen of the slice has changed.

    \sa labelBrush
*/

/*!
    \property QPieSlice::labelFont

    Font used for drawing label text.

    \sa label, labelVisible, labelArmLengthFactor
*/

/*!
    \fn void QPieSlice::labelFontChanged()

    This signal is emitted when the label font of the slice has changed.

    \sa labelFont
*/

/*!
    \property QPieSlice::labelArmLengthFactor

    Defines the length of the label arm.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa label, labelVisible, labelBrush, labelFont
*/

/*!
    \fn void QPieSlice::labelArmLengthFactorChanged()

    This signal is emitted when the label arm factor of the slice has changed.

    \sa labelArmLengthFactor
*/

/*!
    \property QPieSlice::explodeDistanceFactor

    When the slice is exploded this factor defines how far the slice is exploded away from the pie.

    The factor is relative to pie radius. For example:
    1.0 means the distance is the same as the radius.
    0.5 means the distance is half of the radius.

    Default value is 0.15

    \sa exploded
*/

/*!
    \fn void QPieSlice::explodeDistanceFactorChanged()

    This signal is emitted when the explode distance factor of the slice has changed.

    \sa explodeDistanceFactor
*/

/*!
    \property QPieSlice::percentage

    Percentage of the slice compared to the sum of all slices in the series.

    The actual value ranges from 0.0 to 1.0.

    Updated automatically once the slice is added to the series.

    \sa value, QPieSeries::sum
*/

/*!
    \fn void QPieSlice::percentageChanged()

    This signal is emitted when the percentage of the slice has changed.

    \sa percentage
*/

/*!
    \property QPieSlice::startAngle

    Defines the starting angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated automatically once the slice is added to the series.
*/

/*!
    \fn void QPieSlice::startAngleChanged()

    This signal is emitted when the starting angle f the slice has changed.

    \sa startAngle
*/

/*!
    \property QPieSlice::angleSpan

    Span of the slice in degrees.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated automatically once the slice is added to the series.
*/

/*!
    \fn void QPieSlice::angleSpanChanged()

    This signal is emitted when the angle span of the slice has changed.

    \sa angleSpan
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
    setValue(value);
    setLabel(label);
}

/*!
    Destroys the slice.
    User should not delete the slice if it has been added to the series.
*/
QPieSlice::~QPieSlice()
{

}

void QPieSlice::setLabel(QString label)
{
    if (d_ptr->m_data.m_labelText != label) {
        d_ptr->m_data.m_labelText = label;
        emit labelChanged();
    }
}

QString QPieSlice::label() const
{
    return d_ptr->m_data.m_labelText;
}

void QPieSlice::setValue(qreal value)
{
    value = qAbs(value); // negative values not allowed
    if (!qFuzzyIsNull(d_ptr->m_data.m_value - value)) {
        d_ptr->m_data.m_value = value;
        emit valueChanged();
    }
}

qreal QPieSlice::value() const
{
    return d_ptr->m_data.m_value;
}

void QPieSlice::setLabelVisible(bool visible)
{
    if (d_ptr->m_data.m_isLabelVisible != visible) {
        d_ptr->m_data.m_isLabelVisible = visible;
        emit labelVisibleChanged();
    }
}

bool QPieSlice::isLabelVisible() const
{
    return d_ptr->m_data.m_isLabelVisible;
}

void QPieSlice::setExploded(bool exploded)
{
    if (d_ptr->m_data.m_isExploded != exploded) {
        d_ptr->m_data.m_isExploded = exploded;
        emit explodedChanged();
    }
}

bool QPieSlice::isExploded() const
{
    return d_ptr->m_data.m_isExploded;
}

void QPieSlice::setPen(const QPen &pen)
{
    d_ptr->setPen(pen, false);
}

QPen QPieSlice::pen() const
{
    return d_ptr->m_data.m_slicePen;
}

void QPieSlice::setBrush(const QBrush &brush)
{
    d_ptr->setBrush(brush, false);
}

QBrush QPieSlice::brush() const
{
    return d_ptr->m_data.m_sliceBrush;
}

void QPieSlice::setLabelBrush(const QBrush &brush)
{
    d_ptr->setLabelBrush(brush, false);
}

QBrush QPieSlice::labelBrush() const
{
    return d_ptr->m_data.m_labelBrush;
}

void QPieSlice::setLabelFont(const QFont &font)
{
    d_ptr->setLabelFont(font, false);
}

QFont QPieSlice::labelFont() const
{
    return d_ptr->m_data.m_labelFont;
}

void QPieSlice::setLabelArmLengthFactor(qreal factor)
{
    if (!qFuzzyIsNull(d_ptr->m_data.m_labelArmLengthFactor - factor)) {
        d_ptr->m_data.m_labelArmLengthFactor = factor;
        emit labelArmLengthFactorChanged();
    }
}

qreal QPieSlice::labelArmLengthFactor() const
{
    return d_ptr->m_data.m_labelArmLengthFactor;
}

void QPieSlice::setExplodeDistanceFactor(qreal factor)
{
    if (!qFuzzyIsNull(d_ptr->m_data.m_explodeDistanceFactor - factor)) {
        d_ptr->m_data.m_explodeDistanceFactor = factor;
        emit explodeDistanceFactorChanged();
    }
}

qreal QPieSlice::explodeDistanceFactor() const
{
    return d_ptr->m_data.m_explodeDistanceFactor;
}

qreal QPieSlice::percentage() const
{
    return d_ptr->m_data.m_percentage;
}

qreal QPieSlice::startAngle() const
{
    return d_ptr->m_data.m_startAngle;
}

qreal QPieSlice::angleSpan() const
{
    return d_ptr->m_data.m_angleSpan;
}

QColor QPieSlice::color()
{
    return brush().color();
}

void QPieSlice::setColor(QColor color)
{
    QBrush b = brush();
    if (color != b.color()) {
        b.setColor(color);
        setBrush(b);
    }
}

QColor QPieSlice::borderColor()
{
    return pen().color();
}

void QPieSlice::setBorderColor(QColor color)
{
    QPen p = pen();
    if (color != p.color()) {
        p.setColor(color);
        setPen(p);
        emit borderColorChanged();
    }
}

int QPieSlice::borderWidth()
{
    return pen().width();
}

void QPieSlice::setBorderWidth(int width)
{
    QPen p = pen();
    if (width != p.width()) {
        p.setWidth(width);
        setPen(p);
    }
}

QColor QPieSlice::labelColor()
{
    return labelBrush().color();
}

void QPieSlice::setLabelColor(QColor color)
{
    QBrush b = labelBrush();
    if (color != b.color()) {
        b.setColor(color);
        setLabelBrush(b);
    }
}

/*!
  Returns the series that this slice belongs to.

  \sa QPieSeries::append()
*/
QPieSeries *QPieSlice::series() const
{
    return d_ptr->m_series;
}

QPieSlicePrivate::QPieSlicePrivate(QPieSlice *parent)
    :QObject(parent),
    q_ptr(parent),
    m_series(0)
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
        if (m_data.m_slicePen.color() != pen.color())
            emit q_ptr->borderColorChanged();
        if (m_data.m_slicePen.width() != pen.width())
            emit q_ptr->borderWidthChanged();
        m_data.m_slicePen = pen;
        m_data.m_slicePen.setThemed(themed);
        emit q_ptr->penChanged();
    }
}

void QPieSlicePrivate::setBrush(const QBrush &brush, bool themed)
{
    if (m_data.m_sliceBrush != brush) {
        if (m_data.m_sliceBrush.color() != brush.color())
            emit q_ptr->colorChanged();
        m_data.m_sliceBrush = brush;
        m_data.m_sliceBrush.setThemed(themed);
        emit q_ptr->brushChanged();
    }
}

void QPieSlicePrivate::setLabelBrush(const QBrush &brush, bool themed)
{
    if (m_data.m_labelBrush != brush) {
        if (m_data.m_labelBrush.color() != brush.color())
            emit q_ptr->labelColorChanged();
        m_data.m_labelBrush = brush;
        m_data.m_labelBrush.setThemed(themed);
        emit q_ptr->labelBrushChanged();
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
