#include "qbarcategory.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarCategory::QBarCategory()
{
}

QBarCategory& QBarCategory::operator << (const QString &label)
{
    mList.append(label);
    return *this;
}

int QBarCategory::count()
{
    return mList.count();
}

QList<QString>& QBarCategory::items()
{
    return mList;
}


QTCOMMERCIALCHART_END_NAMESPACE
