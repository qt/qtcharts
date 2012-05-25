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
    \brief part of QtCommercial chart API.

    QBarSet represents one set of bars. Set of bars contains one data value for each category.
    First value of set is assumed to belong to first category, second to second category and so on.
    If set has fewer values than there are categories, then the missing values are assumed to be
    at the end of set. For missing values in middle of a set, numerical value of zero is used.

    \mainclass

    \sa QBarSeries, QGroupedBarSeries, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn void QBarSet::clicked(QString category)
    \brief signals that set has been clicked
    Parameter \a category describes on which category was clicked
*/

/*!
    \fn void QBarSet::hovered(bool status)
    \brief signals that mouse has hovered over the set. If \a status is true, then mouse was entered. If \a status is false, then mouse was left.

    The signal is emitted if mouse is hovered on top of set
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
*/

/*!
    Constructs QBarSet with a name of \a name and with parent of \a parent
*/
QBarSet::QBarSet(const QString name, QObject *parent)
    : QObject(parent)
    ,d_ptr(new QBarSetPrivate(name,this))
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
    Sets new \a name for set.
*/
void QBarSet::setName(const QString name)
{
    d_ptr->m_name = name;
}

/*!
    Returns name of the set.
*/
QString QBarSet::name() const
{
    return d_ptr->m_name;
}

/*!
    Appends a point to set. Parameter \a value x coordinate defines the
    position in x-axis and y coordinate defines the height of bar.
    Depending on presentation (QBarSeries, QGroupedBarSeries, QStackedBarSeries, QPercentBarSeries)
    the x values are used or ignored.
*/
void QBarSet::append(const QPointF value)
{
    d_ptr->m_values.append(value);
    emit d_ptr->restructuredBars();
}

/*!
    Appends a list of \a values to set. Works like append with single point.
    \sa append()
*/
void QBarSet::append(const QList<QPointF> values)
{
    for (int i=0; i<values.count(); i++) {
        d_ptr->m_values.append(values.at(i));
    }
    emit d_ptr->restructuredBars();
}

/*!
    Appends new value \a value to the end of set. Internally the value is converted to QPointF,
    with x coordinate being the index of appended value and y coordinate is the value.
*/
void QBarSet::append(const qreal value)
{
    append(QPointF(d_ptr->m_values.count(), value));
}

/*!
    Appends a list of reals to set. Works like append with single real value. The values in list
    are converted to QPointF, where x coordinate is the index of point and y coordinate is the value.
    \sa append()
*/
void QBarSet::append(const QList<qreal> values)
{
    int index = d_ptr->m_values.count();
    for (int i=0; i<values.count(); i++) {
        d_ptr->m_values.append(QPointF(index,values.at(i)));
        index++;
    }
    emit d_ptr->restructuredBars();
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
    d_ptr->m_values.insert(index, QPointF(index, value));
//    emit d_ptr->updatedBars();
}

/*!
    Removes the value specified by \a index
    \sa insert()
*/
void QBarSet::remove(const int index)
{
    d_ptr->m_values.removeAt(index);
//    emit d_ptr->updatedBars();
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::replace(const int index, const qreal value)
{
    d_ptr->m_values.replace(index,QPointF(index,value));
    emit d_ptr->updatedBars();
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
    Sets \a pen of the values that are drawn on top of this barset
*/
void QBarSet::setLabelPen(const QPen &pen)
{
    if(d_ptr->m_labelPen!=pen){
        d_ptr->m_labelPen = pen;
        emit d_ptr->updatedBars();
    }
}

/*!
    Returns pen of the values that are drawn on top of this barset
*/
QPen QBarSet::labelPen() const
{
    return d_ptr->m_labelPen;
}

/*!
    Sets \a brush of the values that are drawn on top of this barset
*/
void QBarSet::setLabelBrush(const QBrush &brush)
{
    if(d_ptr->m_labelBrush!=brush){
        d_ptr->m_labelBrush = brush;
        emit d_ptr->updatedBars();
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
    }

}

/*!
    Returns the pen for values that are drawn on top of this set
*/
QFont QBarSet::labelFont() const
{
    return d_ptr->m_labelFont;
}

/*!
    Sets visibility of bar labels. If \a visible is true, labels are drawn on top of barsets.
*/

void QBarSet::setLabelsVisible(bool visible)
{
    if(d_ptr->m_labelsVisible!=visible) {
        d_ptr->m_labelsVisible = visible;
        emit d_ptr->labelsVisibleChanged(visible);
    }
}

/*!
    Returns the visibility of values
*/
bool QBarSet::labelsVisible() const
{
    return d_ptr->m_labelsVisible;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSetPrivate::QBarSetPrivate(const QString name, QBarSet *parent) : QObject(parent),
    q_ptr(parent),
    m_name(name),
    m_labelsVisible(false)
{
}

QBarSetPrivate::~QBarSetPrivate()
{
}

#include "moc_qbarset.cpp"
#include "moc_qbarset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
