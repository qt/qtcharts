#include <limits.h>
#include <QVector>
#include <QDebug>
#include "barchartmodel_p.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartModel::BarChartModel(QStringList categories, QObject *parent) : QObject(parent),
    m_Category(categories)
{
}

QStringList BarChartModel::category()
{
    return m_Category;
}

void BarChartModel::addBarSet(QBarSet *set)
{
    m_DataModel.append(set);
}

void BarChartModel::removeBarSet(QBarSet *set)
{
    if (m_DataModel.contains(set)) {
        m_DataModel.removeOne(set);
    }
}

void BarChartModel::insertBarSet(int i, QBarSet *set)
{
    m_DataModel.insert(i, set);
}

void BarChartModel::insertCategory(int i, QString category)
{
    m_Category.insert(i, category);
}

void BarChartModel::removeCategory(int i)
{
    m_Category.removeAt(i);
}

QBarSet* BarChartModel::setAt(int index)
{
    return m_DataModel.at(index);
}

QList<QBarSet*> BarChartModel::barSets()
{
    return m_DataModel;
}

int BarChartModel::barsetCount()
{
    return m_DataModel.count();
}

int BarChartModel::categoryCount()
{
    return m_Category.count();
}

qreal BarChartModel::min()
{
    Q_ASSERT(m_DataModel.count() > 0);
    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    qreal min = INT_MAX;

    for (int i = 0; i < m_DataModel.count(); i++) {
        int itemCount = m_DataModel.at(i)->count();
        for (int j = 0; j < itemCount; j++) {
            qreal temp = m_DataModel.at(i)->valueAt(j);
            if (temp < min)
                min = temp;
        }
    }
    return min;
}

qreal BarChartModel::max()
{
    Q_ASSERT(m_DataModel.count() > 0);

    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    qreal max = INT_MIN;

    for (int i = 0; i < m_DataModel.count(); i++) {
        int itemCount = m_DataModel.at(i)->count();
        for (int j = 0; j < itemCount; j++) {
            qreal temp = m_DataModel.at(i)->valueAt(j);
            if (temp > max)
                max = temp;
        }
    }

    return max;
}

qreal BarChartModel::valueAt(int set, int category)
{
    if ((set < 0) || (set >= m_DataModel.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= m_DataModel.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    return m_DataModel.at(set)->valueAt(category);
}

qreal BarChartModel::percentageAt(int set, int category)
{
    if ((set < 0) || (set >= m_DataModel.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= m_DataModel.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    qreal value = m_DataModel.at(set)->valueAt(category);
    qreal total = categorySum(category);
    if (0 == total)
        return 100.0;

    return value / total;
}


qreal BarChartModel::categorySum(int category)
{
    qreal sum(0);
    int count = m_DataModel.count(); // Count sets

    for (int set = 0; set < count; set++) {
        if (category < m_DataModel.at(set)->count())
            sum += m_DataModel.at(set)->valueAt(category);
    }
    return sum;
}

qreal BarChartModel::maxCategorySum()
{
    qreal max = INT_MIN;
    int count = categoryCount();

    for (int col = 0; col < count; col++) {
        qreal sum = categorySum(col);
        if (sum > max)
            max = sum;
    }
    return max;
}

QString BarChartModel::categoryName(int category)
{
    return m_Category.at(category);
}

#include "moc_barchartmodel_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
