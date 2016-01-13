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

#include "declarativebarseries.h"
#include "declarativeboxplotseries.h"
#include <QtCharts/QBoxSet>
#include <QtCharts/QVBoxPlotModelMapper>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \qmltype BoxSet
    \instantiates QBoxSet
    \inqmlmodule QtCharts

    \brief Building block for box-and-whiskers chart.

    BoxSet represents one box-and-whiskers item. It takes five values to create a graphical
    representation of range and three medians. There are two ways to give the values. The first one
    is with constructor or with append method. In these the values have to be given in the following
    order: lower extreme, lower quartile, median, upper quartile and upper extreme. The second
    method is to create an empty QBoxSet instance and give the values using value specific methods.
    \sa BoxPlotSeries
*/
/*!
    \qmlproperty string BoxSet::values
    The values on the box-and-whiskers set.
*/
/*!
    \qmlproperty string BoxSet::label
    Defines the label of the category of the box-and-whiskers set.
*/
/*!
    \qmlproperty int BoxSet::count
    The count of values on the box-and-whiskers set
*/
/*!
    \qmlmethod void BoxSet::at(int index)
    Returns the value at \a index position.
*/
/*!
    \qmlmethod void BoxSet::append(qreal value)
    Appends new value \a value to the end of set.
*/
/*!
    \qmlmethod void BoxSet::clear()
    Sets all values on the set to 0.
*/
/*!
    \qmlmethod void BoxSet::setValue(int index, qreal value)
    Sets a new \a value on the \a index position.
*/
/*!
    \qmlsignal BoxSet::onClicked()
    This signal is emitted when the user clicks with a mouse on top of box-and-whiskers item.
*/
/*!
    \qmlsignal BoxSet::onPressed()
    This signal is emitted when the user presses with a mouse on top of box-and-whiskers item.
*/
/*!
    \qmlsignal BoxSet::onReleased()
    This signal is emitted when the user releases with a mouse on top of box-and-whiskers item.
*/
/*!
    \qmlsignal BoxSet::onDoubleClicked()
    This signal is emitted when the user doubleclicks with a mouse on top of box-and-whiskers item.
*/
/*!
    \qmlsignal BoxSet::onHovered(bool status)
    The signal is emitted if mouse is hovered on top of box-and-whiskers item.
    Parameter \a status is true, if mouse entered on top of the item, and false if mouse left from top of the item.
*/
/*!
    \qmlsignal BoxSet::onPenChanged()
    This signal is emitted when the pen of the box-and-whiskers item has changed.
*/
/*!
    \qmlsignal BoxSet::onBrushChanged()
    This signal is emitted when the brush of the box-and-whiskers item has changed.
*/
/*!
    \qmlsignal BoxSet::onChangedValues()
    This signal is emitted when multiple values have been changed on the box-and-whiskers item.
*/
/*!
    \qmlsignal BoxSet::onChangedValue(int index)
    This signal is emitted values the value in the box-and-whiskers item has been modified.
    Parameter \a index indicates the position of the modified value.
*/
/*!
    \qmlsignal BoxSet::onCleared()
    This signal is emitted when all the values on the set are cleared to 0.
*/

/*!
    \qmltype BoxPlotSeries
    \instantiates QBoxPlotSeries
    \inqmlmodule QtCharts

    \inherits AbstractSeries

    \brief Series for creating box-and-whiskers chart.

    BoxPlotSeries represents a series of data shown as box-and-whiskers bars. The purpose of this
    class is to act as a container for single box-and-whiskers items. Each item is drawn to own
    slot. If chart includes multiple instances of BoxPlotSeries then box-and-whiskers items with the
    same index are drawn to same slot.

    \note The slot, each item in BoxPlotSeries is drawn, represents a category in BarCategoryAxis.
    The category labels have to be unique. If same category label is defined for several
    box-and-whisker items only the first one is drawn.

    The following QML shows how to create a simple box-and-whiskers chart:
    \code
    import QtQuick 2.0
    import QtCharts 2.0

    ChartView {
        title: "Box Plot series"
        width: 400
        height: 300
        theme: ChartView.ChartThemeBrownSand
        legend.alignment: Qt.AlignBottom

        BoxPlotSeries {
            id: plotSeries
            name: "Income"
            BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }
            BoxSet { label: "Feb"; values: [5, 6, 7.5, 8.6, 11.8] }
            BoxSet { label: "Mar"; values: [3.2, 5, 5.7, 8, 9.2] }
            BoxSet { label: "Apr"; values: [3.8, 5, 6.4, 7, 8] }
            BoxSet { label: "May"; values: [4, 5, 5.2, 6, 7] }
        }
    }
    \endcode

    \beginfloatleft
    \image examples_qmlboxplot.png
    \endfloat
    \clearfloat

    \sa BoxSet, BarCategoryAxis
*/

/*!
    \qmlmethod BoxPlotSeries::append(string label, VariantList values)
    Appends a new box-and-whiskers set with \a label and \a values to the series.
 */
/*!
    \qmlmethod BoxPlotSeries::append(BoxSet box)
    Appends the \a box to the series.
*/
/*!
    \qmlmethod BoxPlotSeries::insert(int index, string label, VariantList values)
    Inserts a new box-and-whiskers set with \a label and \a values at the \a index position.
*/
/*!
    \qmlmethod BoxPlotSeries::remove(QBoxSet boxset)
    Removes the \a boxset from the series.
*/
/*!
    \qmlmethod BoxPlotSeries::clear()
    Removes all boxsets from the series. Deletes removed sets.
*/
/*!
    \qmlsignal BoxPlotSeries::onClicked(BoxSet boxset);
    Signal is emitted when the user clicks the \a boxset on the chart.
*/
/*!
    \qmlsignal BoxPlotSeries::onHovered(bool status, BoxSet boxset);
    Signal is emitted when there is change in hover \a status over \a boxset.
*/
/*!
    \qmlsignal BoxPlotSeries::onPressed(BoxSet boxset)
    This signal is emitted when the user presses the \a boxset on the chart.
*/
/*!
    \qmlsignal BoxPlotSeries::onReleased(BoxSet boxset)
    This signal is emitted when the user releases the \a boxset on the chart.
*/
/*!
    \qmlsignal BoxPlotSeries::onDoubleClicked(BoxSet boxset)
    This signal is emitted when the user doubleclicks the \a boxset on the chart.
*/
/*!
    \qmlsignal BoxPlotSeries::onCountChanged();
    Signal is emitted when there is change in count of box-and-whiskers items in the series.
*/
/*!
    \qmlsignal BoxPlotSeries::onBoxsetsAdded()
    Signal is emitted when new box-and-whiskers sets are added to the series.
 */
/*!
    \qmlsignal BoxPlotSeries::onBoxsetsRemoved()
    Signal is emitted when new box-and-whiskers sets are removed from the series.
 */
/*!
    \qmlproperty AbstractAxis BoxPlotSeries::axisX
    The x axis used for the series. If you leave both axisX and axisXTop undefined, a BarCategoriesAxis is created for
    the series.
    \sa axisXTop
*/
/*!
    \qmlproperty AbstractAxis BoxPlotSeries::axisY
    The y axis used for the series. If you leave both axisY and axisYRight undefined, a ValueAxis is created for
    the series.
    \sa axisYRight
*/
/*!
    \qmlproperty AbstractAxis BoxPlotSeries::axisXTop
    The x axis used for the series, drawn on top of the chart view. Note that you can only provide either axisX or
    axisXTop, but not both.
    \sa axisX
*/
/*!
    \qmlproperty AbstractAxis BoxPlotSeries::axisYRight
    The y axis used for the series, drawn to the right on the chart view. Note that you can only provide either axisY
    or axisYRight, but not both.
    \sa axisY
*/
/*!
    \qmlproperty bool BoxPlotSeries::boxOutlineVisible
    This property configures the visibility of the middle box outline.
*/
/*!
    \qmlproperty qreal BoxPlotSeries::boxWidth
    This property configures the width of the box-and-whiskers item. The value signifies the relative
    width of the box-and-whiskers item inside its own slot. The value can between 0.0 and 1.0. Negative values
    are clamped to 0.0 and values over 1.0 are clamped to 1.0.
*/
/*!
    \qmlproperty Pen BoxPlotSeries::pen
    This property configures the pen of the box-and-whiskers items.
*/
/*!
    \qmlproperty Brush BoxPlotSeries::brush
    This property configures the brush of the box-and-whiskers items.
*/
/*!
    \qmlproperty int BoxPlotSeries::count
    The count of sets in series.
*/
/*!
    \qmlsignal BoxPlotSeries::onBoxOutlineVisibilityChanged()
    Signal is emitted when the middle box outline visibility is changed.
 */
/*!
    \qmlsignal BoxPlotSeries::onBoxWidthChanged()
    Signal is emitted when the width of the box-and-whiskers item is changed.
 */
/*!
    \qmlsignal BoxPlotSeries::onPenChanged()
    Signal is emitted when the pen for box-and-whiskers items has changed.
*/
/*!
    \qmlsignal BoxPlotSeries::onBrushChanged()
    Signal is emitted when the brush for box-and-whiskers items has changed.
*/
/*!
    \qmlsignal BoxPlotSeries::onAxisXChanged(AbstractAxis axis)
    Signal is emitted when there is change in X axis.
*/
/*!
    \qmlsignal BoxPlotSeries::onAxisYChanged(AbstractAxis axis)
    Signal is emitted when there is change in Y axis.
*/
/*!
    \qmlsignal BoxPlotSeries::onAxisXTopChanged(AbstractAxis axis)
    Signal is emitted when there is change in top X axis.
*/
/*!
    \qmlsignal BoxPlotSeries::onAxisYRightChanged(AbstractAxis axis)
    Signal is emitted when there is change in Y right axis.
*/


DeclarativeBoxSet::DeclarativeBoxSet(const QString label, QObject *parent)
    : QBoxSet(label, parent)
{
    connect(this, SIGNAL(valuesChanged()), this, SIGNAL(changedValues()));
    connect(this, SIGNAL(valueChanged(int)), this, SIGNAL(changedValue(int)));
    connect(this, SIGNAL(brushChanged()), this, SLOT(handleBrushChanged()));
}

QVariantList DeclarativeBoxSet::values()
{
    QVariantList values;
    for (int i(0); i < 5; i++)
        values.append(QVariant(QBoxSet::at(i)));
    return values;
}

void DeclarativeBoxSet::setValues(QVariantList values)
{
    for (int i(0); i < values.count(); i++) {
        if (values.at(i).canConvert(QVariant::Double))
            QBoxSet::append(values[i].toDouble());
    }
}

QString DeclarativeBoxSet::brushFilename() const
{
    return m_brushFilename;
}

void DeclarativeBoxSet::setBrushFilename(const QString &brushFilename)
{
    QImage brushImage(brushFilename);
    if (QBoxSet::brush().textureImage() != brushImage) {
        QBrush brush = QBoxSet::brush();
        brush.setTextureImage(brushImage);
        QBoxSet::setBrush(brush);
        m_brushFilename = brushFilename;
        m_brushImage = brushImage;
        emit brushFilenameChanged(brushFilename);
    }
}

void DeclarativeBoxSet::handleBrushChanged()
{
    // If the texture image of the brush has changed along the brush
    // the brush file name needs to be cleared.
    if (!m_brushFilename.isEmpty() && QBoxSet::brush().textureImage() != m_brushImage) {
        m_brushFilename.clear();
        emit brushFilenameChanged(QString(""));
    }
}

// =====================================================

DeclarativeBoxPlotSeries::DeclarativeBoxPlotSeries(QQuickItem *parent) :
    QBoxPlotSeries(parent),
    m_axes(new DeclarativeAxes(this))
{
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
    connect(this, SIGNAL(hovered(bool, QBoxSet*)), this, SLOT(onHovered(bool, QBoxSet*)));
    connect(this, SIGNAL(clicked(QBoxSet*)), this, SLOT(onClicked(QBoxSet*)));
    connect(this, SIGNAL(brushChanged()), this, SLOT(handleBrushChanged()));
    connect(this, SIGNAL(pressed(QBoxSet*)), this, SLOT(onPressed(QBoxSet*)));
    connect(this, SIGNAL(released(QBoxSet*)), this, SLOT(onReleased(QBoxSet*)));
    connect(this, SIGNAL(doubleClicked(QBoxSet*)), this, SLOT(onDoubleClicked(QBoxSet*)));
}

void DeclarativeBoxPlotSeries::classBegin()
{
}

void DeclarativeBoxPlotSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBoxSet *>(child)) {
            QBoxPlotSeries::append(qobject_cast<DeclarativeBoxSet *>(child));
        } else if (qobject_cast<QVBoxPlotModelMapper *>(child)) {
            QVBoxPlotModelMapper *mapper = qobject_cast<QVBoxPlotModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativeBoxPlotSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeBoxPlotSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativeBoxPlotSeries::appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBoxSet *DeclarativeBoxPlotSeries::at(int index)
{
    QList<QBoxSet *> setList = boxSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBoxSet *>(setList[index]);

    return 0;
}

DeclarativeBoxSet *DeclarativeBoxPlotSeries::insert(int index, const QString label, QVariantList values)
{
    DeclarativeBoxSet *barset = new DeclarativeBoxSet(label, this);
    barset->setValues(values);
    if (QBoxPlotSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

void DeclarativeBoxPlotSeries::onHovered(bool status, QBoxSet *boxset)
{
    emit hovered(status, qobject_cast<DeclarativeBoxSet *>(boxset));
}

void DeclarativeBoxPlotSeries::onClicked(QBoxSet *boxset)
{
    emit clicked(qobject_cast<DeclarativeBoxSet *>(boxset));
}

void DeclarativeBoxPlotSeries::onPressed(QBoxSet *boxset)
{
    emit pressed(qobject_cast<DeclarativeBoxSet *>(boxset));
}

void DeclarativeBoxPlotSeries::onReleased(QBoxSet *boxset)
{
    emit released(qobject_cast<DeclarativeBoxSet *>(boxset));
}

void DeclarativeBoxPlotSeries::onDoubleClicked(QBoxSet *boxset)
{
    emit doubleClicked(qobject_cast<DeclarativeBoxSet *>(boxset));
}

QString DeclarativeBoxPlotSeries::brushFilename() const
{
    return m_brushFilename;
}

void DeclarativeBoxPlotSeries::setBrushFilename(const QString &brushFilename)
{
    QImage brushImage(brushFilename);
    if (QBoxPlotSeries::brush().textureImage() != brushImage) {
        QBrush brush = QBoxPlotSeries::brush();
        brush.setTextureImage(brushImage);
        QBoxPlotSeries::setBrush(brush);
        m_brushFilename = brushFilename;
        m_brushImage = brushImage;
        emit brushFilenameChanged(brushFilename);
    }
}

void DeclarativeBoxPlotSeries::handleBrushChanged()
{
    // If the texture image of the brush has changed along the brush
    // the brush file name needs to be cleared.
    if (!m_brushFilename.isEmpty() && QBoxPlotSeries::brush().textureImage() != m_brushImage) {
        m_brushFilename.clear();
        emit brushFilenameChanged(QString(""));
    }
}

#include "moc_declarativeboxplotseries.cpp"

QT_CHARTS_END_NAMESPACE
