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
    \fn void QBarSetPrivate::showToolTip(QPoint pos, QString tip)
    \brief \internal \a pos \a tip
*/


/*!
    Constructs QBarSet with a name of \a name and with parent of \a parent
*/
QBarSet::QBarSet(QString name, QObject *parent)
    : QObject(parent)
    ,d_ptr(new QBarSetPrivate(name,this))
//    ,m_name(name)
//    ,m_labelsVisible(false)
{
}

QBarSet::~QBarSet()
{

}

/*!
    Sets new \a name for set.
*/
void QBarSet::setName(QString name)
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
    Appends new value \a value to the end of set.
*/
QBarSet& QBarSet::operator << (const qreal &value)
{
    d_ptr->m_values.append(value);
    emit d_ptr->structureChanged();
    return *this;
}

/*!
    Inserts new \a value on the \a i position.
    The value that is currently at this postion is moved to postion i + 1
    \sa removeValue()
*/
void QBarSet::insertValue(int i, qreal value)
{
    d_ptr->m_values.insert(i, value);
}

/*!
    Removes the value specified by \a i
    \sa insertValue()
*/
void QBarSet::removeValue(int i)
{
    d_ptr->m_values.removeAt(i);
}

/*!
    Returns count of values in set.
*/
int QBarSet::count() const
{
    return d_ptr->m_values.count();
}

/*!
    Returns value of set indexed by \a index
*/
qreal QBarSet::valueAt(int index) const
{
    return d_ptr->m_values.at(index);
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::setValue(int index, qreal value)
{
    d_ptr->m_values.replace(index,value);
    emit d_ptr->valueChanged();
}

/*!
    Returns sum of all values in barset.
*/
qreal QBarSet::sum() const
{
    qreal total(0);
    for (int i=0; i < d_ptr->m_values.count(); i++) {
        total += d_ptr->m_values.at(i);
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
          emit d_ptr->valueChanged();
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
      emit d_ptr->valueChanged();
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
        emit d_ptr->valueChanged();
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
        emit d_ptr->valueChanged();
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
        emit d_ptr->valueChanged();
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

/*
void QBarSet::barHoverEnterEvent(QPoint pos)
{
    emit showToolTip(pos, m_name);
    emit hoverEnter(pos);
}
*/
/*
void QBarSet::barHoverLeaveEvent()
{
    // Emit signal to user of charts
    emit hoverLeave();
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSetPrivate::QBarSetPrivate(QString name, QBarSet *parent) : QObject(parent),
    q_ptr(parent),
    m_name(name),
    m_labelsVisible(false)
{

}

QBarSetPrivate::~QBarSetPrivate()
{

}


//TODO: fixme , refactor it and get rid of it
void QBarSetPrivate::barHoverEnterEvent(QPoint pos)
{
    emit showToolTip(pos, m_name);
    emit hoverEnter(pos);
}

//TODO: fixme , refactor it and get rid of it
void QBarSetPrivate::barHoverLeaveEvent()
{
    // Emit signal to user of charts
    emit hoverLeave();
}

#include "moc_qbarset.cpp"
#include "moc_qbarset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
