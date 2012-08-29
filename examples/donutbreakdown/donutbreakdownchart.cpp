#include "donutbreakdownchart.h"
#include <QPieSlice>

QTCOMMERCIALCHART_USE_NAMESPACE

//![1]
DonutBreakdownChart::DonutBreakdownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    :QChart(parent, wFlags)
{
    // create the series for main center pie
    mainSeries = new QPieSeries();
    mainSeries->setPieSize(0.7);
    QChart::addSeries(mainSeries);
}
//![1]

//![2]
void DonutBreakdownChart::addBreakdownSeries(QPieSeries *breakdownSeries, QColor color)
{
    // add breakdown series as a slice to center pie
    QPieSlice *slice = mainSeries->append(breakdownSeries->name(), breakdownSeries->sum());

    // customize the slice
    slice->setBrush(color);
    slice->setLabelVisible();
    slice->setLabelColor(Qt::white);
    slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);

    // position and customize the breakdown series
    breakdownSeries->setPieSize(0.8);
    breakdownSeries->setHoleSize(0.7);
    breakdownSeries->setLabelsVisible();
    foreach (QPieSlice *slice, breakdownSeries->slices()) {
        color = color.lighter(110);
        slice->setBrush(color);
        slice->setLabelFont(QFont("Arial", 7));
        slice->setLabelArmLengthFactor(0.05);
    }

    // add the series to the chart
    QChart::addSeries(breakdownSeries);

    // recalculate breakdown donut segments
    recalculateAngles();
}
//![2]

//![3]
void DonutBreakdownChart::recalculateAngles()
{
    qreal angle = 0;
    foreach (QPieSlice *slice, mainSeries->slices()) {
        QPieSeries *s = find(slice->label());
        if (s) {
            s->setPieStartAngle(angle);
            angle += slice->percentage() * 360.0; // full pie is 360.0
            s->setPieEndAngle(angle);
        }
    }
}
//![3]

//![4]
QPieSeries *DonutBreakdownChart::find(QString seriesName) const
{
    // find pieseries by name
    foreach (QAbstractSeries *series, QChart::series()) {
        QPieSeries *s = qobject_cast<QPieSeries*>(series);
        if (!s)
            continue;
        if (s->name() == seriesName)
            return s;
    }
    return 0;
}
//![4]
