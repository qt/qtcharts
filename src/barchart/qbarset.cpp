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
    \fn void QBarSet::clicked(QString category)
    \brief signals that set has been clicked
    Parameter \a category describes on which category was clicked
*/

/*!
    \fn void QBarSet::rightClicked(QString category)
    \brief signals that set has been clicked with right mouse button
    Parameter \a category describes on which category was clicked
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
    ,m_Name(name)
{
}

/*!
    Sets new \a name for set.
*/
void QBarSet::setName(QString name)
{
    m_Name = name;
}

/*!
    Returns name of the set.
*/
QString QBarSet::name()
{
    return m_Name;
}

/*!
    Appends new value \a value to the end of set.
*/
QBarSet& QBarSet::operator << (const qreal &value)
{
    m_Values.append(value);
    emit structureChanged();
    return *this;
}

void QBarSet::insertValue(int i, qreal value)
{
    m_Values.insert(i, value);
}

void QBarSet::removeValue(int i)
{
    m_Values.removeAt(i);
}

/*!
    Returns count of values in set.
*/
int QBarSet::count()
{
    return m_Values.count();
}

/*!
    Returns value of set indexed by \a index
*/
qreal QBarSet::valueAt(int index)
{
    return m_Values.at(index);
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::setValue(int index, qreal value)
{
    m_Values.replace(index,value);
    emit valueChanged();
}

/*!
    Returns total sum of all values in barset.
*/
qreal QBarSet::total()
{
    qreal total(0);
    for (int i=0; i < m_Values.count(); i++) {
        total += m_Values.at(i);
    }
    return total;
}

/*!
    Sets pen for set. Bars of this set are drawn using \a pen
*/
void QBarSet::setPen(const QPen pen)
{
    m_Pen = pen;
    emit valueChanged();
}

/*!
    Returns pen of the set.
*/
QPen QBarSet::pen() const
{
    return m_Pen;
}

/*!
    Sets brush for the set. Bars of this set are drawn using \a brush
*/
void QBarSet::setBrush(const QBrush brush)
{
    m_Brush = brush;
    emit valueChanged();
}

/*!
    Returns brush of the set.
*/
QBrush QBarSet::brush() const
{
    return m_Brush;
}

/*!
    Sets the pen for floating values that are drawn on top of this set
*/
void QBarSet::setFloatingValuePen(const QPen pen)
{
    m_FloatingValuePen = pen;
}

/*!
    Returns the pen for floating values that are drawn on top of this set
*/
QPen QBarSet::floatingValuePen() const
{
    return m_FloatingValuePen;
}

/*!
    \internal \a pos
*/
void QBarSet::barHoverEnterEvent(QPoint pos)
{
    emit showToolTip(pos, m_Name);
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
