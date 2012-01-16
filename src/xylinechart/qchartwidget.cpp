#include "qchartwidget.h"
#include "qchart.h"

QCHART_BEGIN_NAMESPACE


class QChartWidgetPrivate
{
public:
    QChart* chart;
    //Q_DECLARE_PUBLIC(ChartWidget)
    QChartWidgetPrivate() {}
};

////////////////////////////////////////////////////////////////////////////

QChartWidget::QChartWidget(QGraphicsItem *parent,Qt::WindowFlags wFlags)
    : QGraphicsWidget(parent,wFlags),
      d_ptr(new QChartWidgetPrivate())
{
}

QChartWidget::~QChartWidget()
{
    delete d_ptr;
}


void QChartWidget::addChart(QChart *chart)
{
    d_ptr->chart=chart;
    chart->setParentItem(this);
}

void QChartWidget::setGeometry(const QRectF & rect)
{
    d_ptr->chart->setSize(rect.size());
    QGraphicsWidget::setGeometry(rect);
}

QCHART_END_NAMESPACE
