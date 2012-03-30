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
#include <QDebug>
#include <QToolTip>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSet
    \brief part of QtCommercial chart API.

    QBarSet represents one set of bars. Set of bars contains one data value for each category.
    First value of set is assumed to belong to first category, second to second category and so on.
    If set has fewer values than there are categories, then the missing values are assumed to be
    at the end of set. For missing values in middle of a set, numerical value of zero is used.

    \mainclass

    \sa QBarSeries, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn void QBarSet::clicked(QString category, Qt::MouseButtons button)
    \brief signals that set has been clicked
    Parameter \a category describes on which category was clicked
    Parameter \a button mouse button
*/

/*!
    \fn void QBarSet::hoverEnter(QPoint pos)
    \brief signals that mouse has entered over the set at position \a pos.
*/

/*!
    \fn void QBarSet::hoverLeave()
    \brief signals that mouse has left from the set.
*/

/*!
    \fn void QBarSet::toggleFloatingValues()
    \brief \internal
*/

/*!
    \fn void QBarSet::showToolTip(QPoint pos, QString tip)
    \brief \internal \a pos \a tip
*/


/*!
    Constructs QBarSet with a name of \a name and with parent of \a parent
*/
QBarSet::QBarSet(QString name, QObject *parent)
    : QObject(parent)
    ,m_name(name)
{
}

/*!
    Sets new \a name for set.
*/
void QBarSet::setName(QString name)
{
    m_name = name;
}

/*!
    Returns name of the set.
*/
QString QBarSet::name() const
{
    return m_name;
}

/*!
    Appends new value \a value to the end of set.
*/
QBarSet& QBarSet::operator << (const qreal &value)
{
    m_values.append(value);
    emit structureChanged();
    return *this;
}

void QBarSet::insertValue(int i, qreal value)
{
    m_values.insert(i, value);
}

void QBarSet::removeValue(int i)
{
    m_values.removeAt(i);
}

/*!
    Returns count of values in set.
*/
int QBarSet::count() const
{
    return m_values.count();
}

/*!
    Returns value of set indexed by \a index
*/
qreal QBarSet::valueAt(int index) const
{
    return m_values.at(index);
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::setValue(int index, qreal value)
{
    m_values.replace(index,value);
    emit valueChanged();
}

/*!
    Returns total sum of all values in barset.
*/
qreal QBarSet::total() const
{
    qreal total(0);
    for (int i=0; i < m_values.count(); i++) {
        total += m_values.at(i);
    }
    return total;
}

/*!
    Sets pen for set. Bars of this set are drawn using \a pen
*/
void QBarSet::setPen(const QPen &pen)
{
    m_pen = pen;
    emit valueChanged();
}

/*!
    Returns pen of the set.
*/
QPen QBarSet::pen() const
{
    return m_pen;
}

/*!
    Sets brush for the set. Bars of this set are drawn using \a brush
*/
void QBarSet::setBrush(const QBrush &brush)
{
    m_brush = brush;
    emit valueChanged();
}

/*!
    Returns brush of the set.
*/
QBrush QBarSet::brush() const
{
    return m_brush;
}

/*!
    Sets the pen for floating values that are drawn on top of this set
*/
void QBarSet::setFloatingValuePen(const QPen &pen)
{
    m_floatingValuePen = pen;
}

/*!
    Returns the pen for floating values that are drawn on top of this set
*/
QPen QBarSet::floatingValuePen() const
{
    return m_floatingValuePen;
}

/*!
    \internal \a pos
*/
void QBarSet::barHoverEnterEvent(QPoint pos)
{
    emit showToolTip(pos, m_name);
    emit hoverEnter(pos);
}

/*!
    \internal
*/
void QBarSet::barHoverLeaveEvent()
{
    // Emit signal to user of charts
    emit hoverLeave();
}

#include "moc_qbarset.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
