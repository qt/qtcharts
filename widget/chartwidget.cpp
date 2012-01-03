#include "chartwidget.h"
#include "../src/chart.h"
#include <QPainter>

class ChartWidgetPrivate : public Chart
{
public:
    //Q_DECLARE_PUBLIC(ChartWidget)
    ChartWidgetPrivate() {}
};

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget(parent)
{
    d_ptr = new ChartWidgetPrivate();
}

ChartWidget::~ChartWidget()
{
    delete d_ptr;
    d_ptr = 0;
}

QColor ChartWidget::color() const
{
    return d_ptr->color();
}

void ChartWidget::setColor(const QColor &color)
{
    d_ptr->setColor(color);
}

void ChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    d_ptr->drawChart(&painter, rect());
}
