#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarSet::QBarSet()
{
    mFloatingValuesVisible = false;
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

bool QBarSet::isFloatingValuesVisible()
{
    return mFloatingValuesVisible;
}

void QBarSet::barClicked()
{
    qDebug() << "QBarset::barClicked" << this;
    // Some bar of this set has been clicked
    // TODO: What happens then?
    emit clicked();     // Notify that set has been clicked
}

#include "moc_qbarset.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
