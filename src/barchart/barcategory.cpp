#include "barcategory_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
BarCategory::BarCategory(QString name, QObject *parent) :
    QObject(parent)
    ,mName(name)
{
}

void BarCategory::barRightClickEvent()
{
    // TODO:
    emit rightClicked(mName);
}

#include "moc_barcategory_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
