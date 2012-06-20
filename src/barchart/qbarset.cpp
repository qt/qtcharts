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

#include "qbarset.h"
#include "qbarset_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSet
    \brief Building block for different bar charts

    QBarSet represents one set of bars. Set of bars contains one data value for each category.
    First value of set is assumed to belong to first category, second to second category and so on.
    If set has fewer values than there are categories, then the missing values are assumed to be
    at the end of set. For missing values in middle of a set, numerical value of zero is used.

    \mainclass

    \sa QBarSeries, QGroupedBarSeries, QStackedBarSeries, QPercentBarSeries
*/
/*!
    \qmlclass BarSet QBarSet

    BarSet represents one set of bars. Set of bars contains one data value for each category.
    First value of set is assumed to belong to first category, second to second category and so on.
    If set has fewer values than there are categories, then the missing values are assumed to be
    at the end of set. For missing values in middle of a set, numerical value of zero is used.
    \sa BarSeries, GroupedBarSeries, StackedBarSeries, PercentBarSeries
*/

/*!
    \property QBarSet::label
    Defines the label of the barSet.
*/
/*!
    \qmlproperty string BarSet::label
    Defines the label of the barSet.
*/

/*!
    \property QBarSet::pen
    \brief Defines the pen used by the barSet.
*/

/*!
    \property QBarSet::brush
    \brief Defines the brush used by the barSet.
*/

/*!
    \property QBarSet::labelBrush
    \brief Defines the brush used by the barSet's label.
*/

/*!
    \property QBarSet::labelFont
    \brief Defines the font used by the barSet's label.
*/

/*!
    \property QBarSet::color
    The fill (brush) color of the bar set.
*/
/*!
    \qmlproperty color BarSet::color
    The fill (brush) color of the bar set.
*/

/*!
    \property QBarSet::borderColor
    The line (pen) color of the bar set.
*/
/*!
    \qmlproperty color BarSet::borderColor
    The line (pen) color of the bar set.
*/

/*!
    \property QBarSet::labelColor
    The text (label) color of the bar set.
*/
/*!
    \qmlproperty color BarSet::labelColor
    The text (label) color of the bar set.
*/

/*!
    \fn void QBarSet::clicked(int index)

    The signal is emitted if the user clicks with a mouse on top of barset.
    Clicked bar inside set is indexed by \a index
*/

/*!
    \fn void QBarSet::hovered(bool status)

    The signal is emitted if mouse is hovered on top of barset.
    Parameter \a status is true, if mouse entered on top of barset, false if mouse left from top of barset.
*/


/*!
    \fn void QBarSet::labelChanged()
    This signal is emitted when the label of the barSet has changed.
    \sa label
*/

/*!
    \fn void QBarSet::penChanged()
    This signal is emitted when the pen of the barSet has changed.
    \sa pen
*/

/*!
    \fn void QBarSet::brushChanged()
    This signal is emitted when the brush of the barSet has changed.
    \sa brush
*/

/*!
    \fn void QBarSet::labelBrushChanged()
    This signal is emitted when the brush of the barSet's label has changed.
    \sa labelBrush
*/

/*!
    \fn void QBarSet::labelFontChanged()
    This signal is emitted when the font of the barSet's label has changed.
    \sa labelBrush
*/

/*!
    \fn void QBarSet::colorChanged(QColor)
    This signal is emitted when the fill (brush) color of the set has changed to \a color.
*/
/*!
    \qmlsignal BarSet::onColorChanged(color color)
    This signal is emitted when the fill (brush) color of the set has changed to \a color.
*/

/*!
    \fn void QBarSet::borderColorChanged(QColor)
    This signal is emitted when the line (pen) color of the set has changed to \a color.
*/
/*!
    \qmlsignal BarSet::onBorderColorChanged(color color)
    This signal is emitted when the line (pen) color of the set has changed to \a color.
*/

/*!
    \fn void QBarSet::labelColorChanged(QColor)
    This signal is emitted when the text (label) color of the set has changed to \a color.
*/
/*!
    \qmlsignal BarSet::onLabelColorChanged(color color)
    This signal is emitted when the text (label) color of the set has changed to \a color.
*/

/*!
    \fn void QBarSet::valuesAdded(int index, int count)
    This signal is emitted when new values have been added to the set.
    Parameter \a index indicates the position of the first inserted value.
    Parameter \a count is the number of iserted values.
    \sa append(), insert()
*/
/*!
    \qmlsignal BarSet::onValuesAdded(int index, int count)
    This signal is emitted when new values have been added to the set.
    Parameter \a index indicates the position of the first inserted value.
    Parameter \a count is the number of iserted values.
*/

/*!
    \fn void QBarSet::valuesRemoved(int index, int count)
    This signal is emitted values have been removed from the set.
    Parameter \a index indicates the position of the first removed value.
    Parameter \a count is the number of removed values.
    \sa remove()
*/
/*!
    \qmlsignal BarSet::onValuesRemoved(int index, int count)
    This signal is emitted values have been removed from the set.
    Parameter \a index indicates the position of the first removed value.
    Parameter \a count is the number of removed values.
*/

/*!
    \fn void QBarSet::valueChanged(int index)
    This signal is emitted values the value in the set has been modified.
    Parameter \a index indicates the position of the modified value.
    \sa at()
*/
/*!
    \qmlsignal BarSet::onValueChanged(int index)
    This signal is emitted values the value in the set has been modified.
    Parameter \a index indicates the position of the modified value.
*/

/*!
    Constructs QBarSet with a label of \a label and with parent of \a parent
*/
QBarSet::QBarSet(const QString label, QObject *parent)
    : QObject(parent)
    ,d_ptr(new QBarSetPrivate(label,this))
{
}

/*!
    Destroys the barset
*/
QBarSet::~QBarSet()
{
    // NOTE: d_ptr destroyed by QObject
}

/*!
    Sets new \a label for set.
*/
void QBarSet::setLabel(const QString label)
{
    d_ptr->m_label = label;
    emit labelChanged();
}

/*!
    Returns label of the set.
*/
QString QBarSet::label() const
{
    return d_ptr->m_label;
}

/*!
    Appends a point to set. Parameter \a value x coordinate defines the
    position in x-axis and y coordinate defines the height of bar.
    Depending on presentation (QBarSeries, QGroupedBarSeries, QStackedBarSeries, QPercentBarSeries)
    the x values are used or ignored.
*/
void QBarSet::append(const QPointF value)
{
    int index = d_ptr->m_values.count();
    d_ptr->append(value);
    emit valuesAdded(index, 1);
}

/*!
    Appends a list of \a values to set. Works like append with single point.
    \sa append()
*/
void QBarSet::append(const QList<QPointF> &values)
{
    int index = d_ptr->m_values.count();
    d_ptr->append(values);
    emit valuesAdded(index, values.count());
}

/*!
    Appends new value \a value to the end of set. Internally the value is converted to QPointF,
    with x coordinate being the index of appended value and y coordinate is the value.
*/
void QBarSet::append(const qreal value)
{
    // Convert to QPointF and use other append(QPointF) method.
    append(QPointF(d_ptr->m_values.count(), value));
}

/*!
    Appends a list of reals to set. Works like append with single real value. The \a values in list
    are converted to QPointF, where x coordinate is the index of point and y coordinate is the value.
    \sa append()
*/
void QBarSet::append(const QList<qreal> &values)
{
    int index = d_ptr->m_values.count();
    d_ptr->append(values);
    emit valuesAdded(index, values.count());
}

/*!
    Convinience operator. Same as append, with real \a value.
    \sa append()
*/
QBarSet& QBarSet::operator << (const qreal &value)
{
    append(value);
    return *this;
}

/*!
    Convinience operator. Same as append, with QPointF \a value.
    \sa append()
*/
QBarSet& QBarSet::operator << (const QPointF &value)
{
    append(value);
    return *this;
}

/*!
    Inserts new \a value on the \a index position.
    The value that is currently at this postion is moved to postion index + 1
    \sa remove()
*/
void QBarSet::insert(const int index, const qreal value)
{
    d_ptr->insert(index, value);
    emit valuesAdded(index,1);
}

/*!
    Inserts new \a value on the \a index position.
    The value that is currently at this postion is moved to postion index + 1
    \sa remove()
*/
void QBarSet::insert(const int index, const QPointF value)
{
    d_ptr->insert(index,value);
    emit valuesAdded(index,1);
}

/*!
    Removes \a count number of values from the set starting at \a index.
    \sa insert()
*/
void QBarSet::remove(const int index, const int count)
{
    int removedCount = d_ptr->remove(index,count);
    if (removedCount > 0) {
        emit valuesRemoved(index,removedCount);
    }
    return;
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::replace(const int index, const qreal value)
{
    if (index >= 0 && index < d_ptr->m_values.count()) {
        d_ptr->replace(index,value);
        emit valueChanged(index);
    }
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::replace(const int index, const QPointF value)
{
    if (index >= 0 && index < d_ptr->m_values.count()) {
        d_ptr->replace(index,value);
        emit valueChanged(index);
    }
}

/*!
    Returns value of set indexed by \a index. Note that all appended values are stored internally as QPointF.
    The returned QPointF has x coordinate, which is index (if appended with qreal append) or the x value
    of the QPointF (if appended with QPointF append).
    If the index is out of bounds QPointF(0, 0.0) is returned.
*/
QPointF QBarSet::at(const int index) const
{
    if (index < 0 || index >= d_ptr->m_values.count()) {
        return QPointF(index, 0.0);
    }

    return d_ptr->m_values.at(index);
}

/*!
    Returns value of set indexed by \a index. ote that all appended values are stored internally as QPointF.
    The returned QPointF has x coordinate, which is index (if appended with qreal append) or the x value
    of the QPointF (if appended with QPointF append).
*/
QPointF QBarSet::operator [](const int index) const
{
    return d_ptr->m_values.at(index);
}

/*!
    Returns count of values in set.
*/
int QBarSet::count() const
{
    return d_ptr->m_values.count();
}

/*!
    Returns sum of all values in barset. The sum is sum of y coordinates in the QPointF representation.
*/
qreal QBarSet::sum() const
{
    qreal total(0);
    for (int i=0; i < d_ptr->m_values.count(); i++) {
        //total += d_ptr->m_values.at(i);
        total += d_ptr->m_values.at(i).y();
    }
    return total;
}

/*!
    Sets pen for set. Bars of this set are drawn using \a pen
*/
void QBarSet::setPen(const QPen &pen)
{
      if(d_ptr->m_pen!=pen){
          d_ptr->m_pen = pen;
          emit d_ptr->updatedBars();
          emit penChanged();
      }
}

/*!
    Returns pen of the set.
*/
QPen QBarSet::pen() const
{
    return d_ptr->m_pen;
}

/*!
    Sets brush for the set. Bars of this set are drawn using \a brush
*/
void QBarSet::setBrush(const QBrush &brush)
{
    if(d_ptr->m_brush!=brush){
      d_ptr->m_brush = brush;
      emit d_ptr->updatedBars();
      emit brushChanged();
    }
}

/*!
    Returns brush of the set.
*/
QBrush QBarSet::brush() const
{
    return d_ptr->m_brush;
}

/*!
    Sets \a brush of the values that are drawn on top of this barset
*/
void QBarSet::setLabelBrush(const QBrush &brush)
{
    if(d_ptr->m_labelBrush!=brush){
        d_ptr->m_labelBrush = brush;
        emit d_ptr->updatedBars();
        emit labelBrushChanged();
    }
}

/*!
    Returns brush of the values that are drawn on top of this barset
*/
QBrush QBarSet::labelBrush() const
{
    return d_ptr->m_labelBrush;
}

/*!
    Sets the \a font for values that are drawn on top of this barset
*/
void QBarSet::setLabelFont(const QFont &font)
{
    if(d_ptr->m_labelFont!=font) {
        d_ptr->m_labelFont = font;
        emit d_ptr->updatedBars();
        emit labelFontChanged();
    }

}

/*!
    Returns the pen for values that are drawn on top of this barset
*/
QFont QBarSet::labelFont() const
{
    return d_ptr->m_labelFont;
}

/*!
    Returns the color of the brush of barset.
*/
QColor QBarSet::color()
{
    return brush().color();
}

/*!
    Sets the \a color of brush for this barset
*/
void QBarSet::setColor(QColor color)
{
    QBrush b = brush();
    if (b.color() != color) {
        b.setColor(color);
        setBrush(b);
        emit colorChanged(color);
    }
}

/*!
    Returns the color of pen of this barset
*/
QColor QBarSet::borderColor()
{
    return pen().color();
}

/*!
    Sets the color of pen for this barset
*/
void QBarSet::setBorderColor(QColor color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
        emit borderColorChanged(color);
    }
}

/*!
    Returns the color of labels of this barset
*/
QColor QBarSet::labelColor()
{
    return labelBrush().color();
}

/*!
    Sets the color of labels for this barset
*/
void QBarSet::setLabelColor(QColor color)
{
    QBrush b = labelBrush();
    if (b.color() != color) {
        b.setColor(color);
        setLabelBrush(b);
        emit labelColorChanged(color);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSetPrivate::QBarSetPrivate(const QString label, QBarSet *parent) : QObject(parent),
    q_ptr(parent),
    m_label(label)
{
}

QBarSetPrivate::~QBarSetPrivate()
{
}

void QBarSetPrivate::append(QPointF value)
{
    m_values.append(value);
    emit restructuredBars();
}

void QBarSetPrivate::append(QList<QPointF> values)
{
    for (int i=0; i<values.count(); i++) {
        m_values.append(values.at(i));
    }
    emit restructuredBars();
}

void QBarSetPrivate::append(QList<qreal> values)
{
    int index = m_values.count();
    for (int i=0; i<values.count(); i++) {
        m_values.append(QPointF(index,values.at(i)));
        index++;
    }
    emit restructuredBars();
}

void QBarSetPrivate::insert(const int index, const qreal value)
{
    m_values.insert(index, QPointF(index, value));
    emit restructuredBars();
}

void QBarSetPrivate::insert(const int index, const QPointF value)
{
    m_values.insert(index, value);
    emit restructuredBars();
}

int QBarSetPrivate::remove(const int index, const int count)
{
    int removeCount = count;

    if ((index <0) || (m_values.count() == 0)) {
        // Invalid index or not values in list, remove nothing.
        return 0;
    } else if ((index + count) > m_values.count()) {
        // Trying to remove more items than list has. Limit amount to be removed.
        removeCount = m_values.count() - index;
    }

    int c = 0;
    while (c < removeCount) {
        m_values.removeAt(index);
        c++;
    }
    emit restructuredBars();
    return removeCount;
}

void QBarSetPrivate::replace(const int index, const qreal value)
{
    m_values.replace(index,QPointF(index,value));
    emit updatedBars();
}

void QBarSetPrivate::replace(const int index, const QPointF value)
{
    m_values.replace(index,value);
    emit updatedBars();
}

#include "moc_qbarset.cpp"
#include "moc_qbarset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
