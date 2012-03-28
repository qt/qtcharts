#include "stackedbarchartitem_p.h"
#include "bar_p.h"
#include "barvalue_p.h"
#include "qbarset.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartItem::StackedBarChartItem(QBarSeries *series, ChartPresenter *presenter) :
    BarChartItem(series, presenter)
{
}

StackedBarChartItem::~StackedBarChartItem()
{
}

QVector<QRectF> StackedBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;
    // Use temporary qreals for accurancy (we might get some compiler warnings... :)

    qreal maxSum = m_series->maxCategorySum();
    // Domain:
    if (m_domainMaxY > maxSum) {
        maxSum = m_domainMaxY;
    }

    qreal height = geometry().height();
    qreal width = geometry().width();
    qreal scale = (height /  m_series->maxCategorySum());
    qreal categotyCount = m_series->categoryCount();
    qreal barWidth = width / (categotyCount * 2);
    qreal xStep = width / categotyCount;
    qreal xPos = xStep / 2 - barWidth / 2;

    int itemIndex(0);
    for (int category = 0; category < categotyCount; category++) {
        qreal yPos = height;
        for (int set=0; set < m_series->barsetCount(); set++) {
            qreal barHeight = m_series->valueAt(set, category) * scale;
            Bar* bar = m_bars.at(itemIndex);
            bar->setPen(m_series->barsetAt(set)->pen());
            bar->setBrush(m_series->barsetAt(set)->brush());
            QRectF rect(xPos, yPos-barHeight, barWidth, barHeight);
            layout.append(rect);
            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }

    // Position floating values
    itemIndex = 0;
    xPos = (width/categotyCount);
    for (int category=0; category < m_series->categoryCount(); category++) {
        qreal yPos = height;
        for (int set=0; set < m_series->barsetCount(); set++) {
            qreal barHeight = m_series->valueAt(set, category) * scale;
            BarValue* value = m_floatingValues.at(itemIndex);

            QBarSet* barSet = m_series->barsetAt(set);
            value->resize(100, 50);  // TODO: proper layout for this.
            value->setPos(xPos, yPos-barHeight / 2);
            value->setPen(barSet->floatingValuePen());

            if (!qFuzzyIsNull(m_series->valueAt(set, category))) {
                value->setValueString(QString::number(m_series->valueAt(set,category)));
            } else {
                value->setValueString(QString(""));
            }

            itemIndex++;
            yPos -= barHeight;
        }
        xPos += xStep;
    }
    return layout;
}

#include "moc_stackedbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
