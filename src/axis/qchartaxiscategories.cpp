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

void QChartAxisCategories::insert(const QBarCategories& categories)
{
    int i=1;
    foreach(QString string , categories){
        m_map.insert(i,string);
        i++;
    }
    emit updated();
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

QString QChartAxisCategories::label(qreal value) const
{
    return m_map.value(value);
}

#include "moc_qchartaxiscategories.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
