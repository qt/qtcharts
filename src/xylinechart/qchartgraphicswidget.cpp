#include "qchartgraphicswidget.h"
#include "qchart.h"

QCHART_BEGIN_NAMESPACE


class QChartGraphicsWidgetPrivate
{
public:
    QChart* chart;
    //Q_DECLARE_PUBLIC(ChartWidget)
    QChartGraphicsWidgetPrivate() {}
};

////////////////////////////////////////////////////////////////////////////

QChartGraphicsWidget::QChartGraphicsWidget(QGraphicsItem *parent,Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent,wFlags),
      d_ptr(new QChartGraphicsWidgetPrivate())
{
}

QChartGraphicsWidget::~QChartGraphicsWidget()
{
    delete d_ptr;
}


void QChartGraphicsWidget::addChart(QChart *chart)
{
    d_ptr->chart=chart;
    chart->setParentItem(this);
}

void QChartGraphicsWidget::setGeometry(const QRectF & rect)
{
    d_ptr->chart->setSize(rect.size());
    QGraphicsWidget::setGeometry(rect);
}

QCHART_END_NAMESPACE
