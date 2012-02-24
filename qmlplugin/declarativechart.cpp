#include "declarativechart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      m_chart(new QChart(this))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

DeclarativeChart::ChartTheme DeclarativeChart::theme()
{
    return (ChartTheme) m_chart->chartTheme();
}

void DeclarativeChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    qDebug() << "geometryChanged " << this << " old geometry: " << oldGeometry;
    if (newGeometry.isValid()) {
        if (newGeometry.width() > 0 && newGeometry.height() > 0) {
            // TODO: setting margin should not be needed to make axis visible?
            const int margin = 30;
            if (m_chart->margin() == 0
                    && newGeometry.width() > (margin * 2)
                    && newGeometry.height() > (margin * 2)) {
                m_chart->setMargin(margin);
                m_chart->resize(newGeometry.width(), newGeometry.height());
            } else {
                m_chart->resize(newGeometry.width(), newGeometry.height());
            }
        }
    }
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
