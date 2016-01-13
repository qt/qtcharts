/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QLegendMarker>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <QtCharts/QLegend>
#include <private/qlegend_p.h>
#include <private/legendlayout_p.h>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtCharts/QAbstractSeries>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QLegendMarker
    \inmodule Qt Charts
    \brief LegendMarker object.

    QLegendMarker is abstract object that can be used to access markers inside QLegend. Legend marker consists of two
    items: The colored box, which reflects the color of series and label, which is the name of series (or label of slice/barset
    in case of pie or bar series)
    The QLegendMarker is always related to one series.

    \image examples_percentbarchart_legend.png

    \sa QLegend
*/
/*!
    \enum QLegendMarker::LegendMarkerType

    The type of the legendmarker object.

    \value LegendMarkerTypeArea
    \value LegendMarkerTypeBar
    \value LegendMarkerTypePie
    \value LegendMarkerTypeXY
    \value LegendMarkerTypeBoxPlot
*/

/*!
    \fn virtual LegendMarkerType QLegendMarker::type() = 0;
    Returns the type of legendmarker. Type depends of the related series. LegendMarkerTypeXY is used for all QXYSeries derived
    classes.
*/

/*!
    \fn virtual QAbstractSeries* QLegendMarker::series() = 0;
    Returns pointer to series, which is related to this marker. Marker is always related to some series.
*/

/*!
  \fn void QLegendMarker::clicked();
  This signal is emitted, when marker is clicked with mouse.
*/

/*!
  \fn void QLegendMarker::hovered(bool status);
  This signal is emitted, when mouse is hovered over marker. \a status is true, when mouse enters the marker
  and false when it leaves the marker.
*/

/*!
    \fn void QLegendMarker::labelChanged()
    This signal is emitted when the label of the legend marker has changed.
*/

/*!
    \fn void QLegendMarker::labelBrushChanged()
    This signal is emitted when the label brush of the legend marker has changed.
*/

/*!
    \fn void QLegendMarker::fontChanged()
    This signal is emitted when the (label) font of the legend marker has changed.
*/

/*!
    \fn void QLegendMarker::penChanged()
    This signal is emitted when the pen of the legend marker has changed.
*/

/*!
    \fn void QLegendMarker::brushChanged()
    This signal is emitted when the brush of the legend marker has changed.
*/

/*!
    \fn void QLegendMarker::visibleChanged()
    This signal is emitted when the visibility of the legend marker has changed.
*/

/*!
    \property QLegendMarker::label
    Label of the marker. This is the text that is shown in legend.
*/

/*!
    \property QLegendMarker::labelBrush
    Brush of the label
*/

/*!
    \property QLegendMarker::font
    Font of the label
*/

/*!
    \property QLegendMarker::pen
    Pen of the marker. This is the outline of the colored square.
*/

/*!
    \property QLegendMarker::brush
    Brush of the marker. This is the inside of the colored square.
*/

/*!
    \property QLegendMarker::visible
    Visibility of the legend marker. Affects label and the colored square.
*/


/*!
    \internal
 */
QLegendMarker::QLegendMarker(QLegendMarkerPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
    d_ptr->m_item->setVisible(d_ptr->series()->isVisible());
}

/*!
  Destructor of marker
*/
QLegendMarker::~QLegendMarker()
{
}

/*!
  Returns the label of the marker.
*/
QString QLegendMarker::label() const
{
    return d_ptr->m_item->label();
}

/*!
  Sets the \a label of marker. Note that changing name of series will also change label of its marker.
*/
void QLegendMarker::setLabel(const QString &label)
{
    if (label.isEmpty()) {
        d_ptr->m_customLabel = false;
    } else {
        d_ptr->m_customLabel = true;
        d_ptr->m_item->setLabel(label);
    }
}
/*!
  Returns the brush which is used to draw label.
*/
QBrush QLegendMarker::labelBrush() const
{
    return d_ptr->m_item->labelBrush();
}

/*!
  Sets the \a brush of label
*/
void QLegendMarker::setLabelBrush(const QBrush &brush)
{
    d_ptr->m_item->setLabelBrush(brush);
}

/*!
  Retuns the font of label
*/
QFont QLegendMarker::font() const
{
    return d_ptr->m_item->font();
}

/*!
  Sets the \a font of label
*/
void QLegendMarker::setFont(const QFont &font)
{
    d_ptr->m_item->setFont(font);
}

/*!
  Returns the pen of marker item
*/
QPen QLegendMarker::pen() const
{
    return d_ptr->m_item->pen();
}

/*!
  Sets the \a pen of marker item
*/
void QLegendMarker::setPen(const QPen &pen)
{
    if (pen == QPen(Qt::NoPen)) {
        d_ptr->m_customPen = false;
    } else {
        d_ptr->m_customPen = true;
        d_ptr->m_item->setPen(pen);
    }
}

/*!
  Returns the brush of marker item
*/
QBrush QLegendMarker::brush() const
{
    return d_ptr->m_item->brush();
}

/*!
  Sets the \a brush of marker item. Note that changing color of the series also changes this.
*/
void QLegendMarker::setBrush(const QBrush &brush)
{
    if (brush == QBrush(Qt::NoBrush)) {
        d_ptr->m_customBrush = false;
    } else {
        d_ptr->m_customBrush = true;
        d_ptr->m_item->setBrush(brush);
    }
}

/*!
  Returns visibility of the marker
*/
bool QLegendMarker::isVisible() const
{
    return d_ptr->m_item->isVisible();
}

/*!
  Sets markers visibility to \a visible
*/
void QLegendMarker::setVisible(bool visible)
{
    d_ptr->m_item->setVisible(visible);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QLegendMarkerPrivate::QLegendMarkerPrivate(QLegendMarker *q, QLegend *legend) :
    m_legend(legend),
    m_customLabel(false),
    m_customBrush(false),
    m_customPen(false),
    q_ptr(q)
{
    m_item = new LegendMarkerItem(this);
}

QLegendMarkerPrivate::~QLegendMarkerPrivate()
{
    delete m_item;
}

void QLegendMarkerPrivate::invalidateLegend()
{
    m_legend->d_ptr->m_layout->invalidate();
}

#include "moc_qlegendmarker.cpp"
#include "moc_qlegendmarker_p.cpp"

QT_CHARTS_END_NAMESPACE
