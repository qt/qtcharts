#ifndef DONUTBREAKDOWNCHART_H
#define DONUTBREAKDOWNCHART_H

#include <QChart>
#include <QPieSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

class DonutBreakdownChart : public QChart
{
public:
    DonutBreakdownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    void addBreakdownSeries(QPieSeries *series, QColor color);

private:
    void recalculateAngles();
    QPieSeries *find(QString seriesName) const;

private:
    QPieSeries *mainSeries;
};

#endif // DONUTBREAKDOWNCHART_H
