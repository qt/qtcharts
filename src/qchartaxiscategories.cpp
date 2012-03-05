#include "qchartaxiscategories.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxisCategories::QChartAxisCategories()
{
    // TODO Auto-generated constructor stub

}

QChartAxisCategories::~QChartAxisCategories()
{
    // TODO Auto-generated destructor stub
}

void QChartAxisCategories::insert(qreal value,QString label)
{
    m_map.insert(value,label);
    emit updated();
}
void QChartAxisCategories::remove(qreal value)
{
    m_map.remove(value);
    emit updated();
}
void QChartAxisCategories::clear()
{
    m_map.clear();
    emit updated();
}
int QChartAxisCategories::count()
{
    return m_map.count();
    emit updated();
}

#include "moc_qchartaxiscategories.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
