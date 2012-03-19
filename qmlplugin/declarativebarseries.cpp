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
    connect(this, SIGNAL(parentChanged()),
            this, SLOT(setParentForSeries()));
}

void DeclarativeBarSeries::setParentForSeries()
{
    if (!m_series) {
        DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

        if (declarativeChart) {
            QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
            Q_ASSERT(chart);

            QStringList categories;
            categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
            m_series = new QBarSeries(categories);

            // TODO: use data from model
            QBarSet *set0 = new QBarSet("Bub");
            QBarSet *set1 = new QBarSet("Bob");
            QBarSet *set2 = new QBarSet("Guybrush");

            *set0 << 1 << 2 << 3 << 4 << 5 << 6;
            *set1 << 5 << 0 << 0 << 4 << 0 << 7;
            *set2 << 3 << 5 << 8 << 13 << 8 << 5;

            m_series->addBarSet(set0);
            m_series->addBarSet(set1);
            m_series->addBarSet(set2);

            chart->addSeries(m_series);
        }
    }
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
