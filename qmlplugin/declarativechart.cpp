#include "declarativechart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      m_chart(new QChart(this))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    m_chart->resize(QSize(height(), width()));
    m_chart->setMargin(25); // TODO: should not be needed?
}

DeclarativeChart::ChartTheme DeclarativeChart::theme()
{
    if (m_chart)
        return (ChartTheme) m_chart->chartTheme();
}

void DeclarativeChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    m_chart->resize(QSize(newGeometry.width(), newGeometry.height()));
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
