#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarSet::QBarSet(QString name, QObject *parent)
    : QObject(parent)
    ,mName(name)
    ,mHoverNamesEnabled(true)       // TODO: these 2 as false by default, when implementation is ready
    ,mFloatingValuesEnabled(true)
{
}

void QBarSet::setName(QString name)
{
    mName = name;
}
QString QBarSet::name()
{
    return mName;
}

QBarSet& QBarSet::operator << (const qreal &value)
{
    mValues.append(value);
    return *this;
}

int QBarSet::count()
{
    return mValues.count();
}

qreal QBarSet::valueAt(int index)
{
    return mValues.at(index);
}

void QBarSet::setValue(int index, qreal value)
{
    mValues.replace(index,value);
}

void QBarSet::setPen(const QPen& pen)
{
    mPen = pen;
}

const QPen& QBarSet::pen() const
{
    return mPen;
}

void QBarSet::setBrush(const QBrush& brush)
{
    mBrush = brush;
}

const QBrush& QBarSet::brush() const
{
    return mBrush;
}

void QBarSet::enableFloatingValues(bool enabled)
{
    qDebug() << "QBarSet::enableFloatingValues" << enabled;
    mFloatingValuesEnabled = enabled;
}

void QBarSet::enableHoverNames(bool enabled)
{
    qDebug() << "QBarSet::enableHoverNames" << enabled;
    mHoverNamesEnabled = enabled;
}

void QBarSet::barClicked()
{
    qDebug() << "QBarset::barClicked" << this;
    // Some bar of this set has been clicked
    // TODO: What happens then?
    emit clicked();     // Notify that set has been clicked
}

void QBarSet::barHoverEntered()
{
    qDebug() << "QBarset::barHoverEntered" << this;
    if (mHoverNamesEnabled) {
        emit hoverEnter();
    }
}

void QBarSet::barHoverLeaved()
{
    qDebug() << "QBarset::barHoverLeaved" << this;
    if (mHoverNamesEnabled) {
        emit hoverLeave();
    }
}

#include "moc_qbarset.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
