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

    Example on how to create sets of data:
    \snippet ../example/barchart/main.cpp 2

    \sa QBarCategory, QBarSeries, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn void QBarSet::clicked()
    \brief signals that set has been clicked
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
    ,mName(name)
{
}

/*!
    Sets new \a name for set.
*/
void QBarSet::setName(QString name)
{
    mName = name;
}

/*!
    Returns name of the set.
*/
QString QBarSet::name()
{
    return mName;
}

/*!
    Appends new value \a value to the end of set.
*/
QBarSet& QBarSet::operator << (const qreal &value)
{
    mValues.append(value);
    return *this;
}

/*!
    Returns count of values in set.
*/
int QBarSet::count()
{
    return mValues.count();
}

/*!
    Returns value of set indexed by \a index
*/
qreal QBarSet::valueAt(int index)
{
    return mValues.at(index);
}

/*!
    Sets a new value \a value to set, indexed by \a index
*/
void QBarSet::setValue(int index, qreal value)
{
    mValues.replace(index,value);
}

/*!
    Sets pen for set. Bars of this set are drawn using \a pen
*/
void QBarSet::setPen(const QPen& pen)
{
    mPen = pen;
}

/*!
    Returns pen of the set.
*/
const QPen& QBarSet::pen() const
{
    return mPen;
}

/*!
    Sets brush for the set. Bars of this set are drawn using \a brush
*/
void QBarSet::setBrush(const QBrush& brush)
{
    mBrush = brush;
}

/*!
    Returns brush of the set.
*/
const QBrush& QBarSet::brush() const
{
    return mBrush;
}

/*!
    \internal
*/
void QBarSet::barClicked()
{
//    qDebug() << "QBarset::barClicked" << this;
    // Some bar of this set has been clicked
    // TODO: What happens then?
    emit clicked();     // Notify that set has been clicked
}

/*!
    \internal \a pos
*/
void QBarSet::barHoverEntered(QPoint pos)
{
    emit showToolTip(pos, mName);
    emit hoverEnter(pos);
}

/*!
    \internal
*/
void QBarSet::barHoverLeaved()
{
//    qDebug() << "QBarset::barHoverLeaved" << this;
//    if (mToolTipEnabled) {
        // TODO: do what?
//    }
    // Emit signal to user of charts
    emit hoverLeave();
}

#include "moc_qbarset.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
