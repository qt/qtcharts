#include "declarativebarseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qbarseries.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeBarSeries::DeclarativeBarSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeBarSeries::componentComplete()
{
    if (!m_series) {
        DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

        if (declarativeChart) {
            QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
            Q_ASSERT(chart);

//            QStringList categories;
//            categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
//            m_series = new QBarSeries(categories);
//            m_series = new QBarSeries(m_categories);
            m_series = new QBarSeries(m_categories);

            // TODO: use data from model
            QBarSet *set0 = new QBarSet("Bub");
            QBarSet *set1 = new QBarSet("Bob");
            QBarSet *set2 = new QBarSet("Guybrush");

            *set0 << 1 << 2 << 3 << 4 << 5 << 6;
            *set1 << 5 << 0 << 0 << 4 << 0 << 7;
            *set2 << 3 << 5 << 8 << 13 << 8 << 5;

            m_series->appendBarSet(set0);
            m_series->appendBarSet(set1);
            m_series->appendBarSet(set2);

            chart->addSeries(m_series);
        }
    }
}

void DeclarativeBarSeries::setBarCategories(QStringList categories)
{
    m_categories = categories;
    if (m_series) {
        // Replace categories of the QBarSeries with the new categories
        for (int i(0); i < m_categories.count(); i++) {
            if (m_series->categories().at(i) != m_categories.at(i))
                m_series->insertCategory(m_series->categoryCount(), m_categories.at(i));
        }
        while (m_series->categoryCount() > m_categories.count())
            m_series->removeCategory(m_series->categoryCount() - 1);
    }
}

QStringList DeclarativeBarSeries::barCategories()
{
    return m_categories;
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
