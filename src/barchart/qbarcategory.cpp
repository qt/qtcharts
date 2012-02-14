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

QString QBarCategory::label(int category)
{
    return mList.at(category);
}

// TODO?:
//#include "moc_qbarcategory.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
