#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlineseries.h>
#include <qchart.h>
#include <qchartaxis.h>
#include <qchartaxiscategories.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QLineSeries* series0 = new QLineSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);

    *series0 << QPointF(0, 6) << QPointF(2, 4) << QPointF(3, 8) << QPointF(7, 4) << QPointF(10,5);

    QChartView* chartView =  new QChartView(&window);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTitle("Simple axis example");
    chartView->addSeries(series0);

    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, Qt::white);
    backgroundGradient.setColorAt(1.0, Qt::white);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chartView->setChartBackgroundBrush(backgroundGradient);

    QChartAxis* axisX = chartView->axisX();
    axisX->setRange(0,10);
    axisX->setTicksCount(4);
    axisX->setGridLineVisible(true);
    axisX->setShadesVisible(false);

    QChartAxis* axisY = chartView->axisY();
    axisY->setRange(0,10);
    axisY->setLabelsAngle(45);
    axisY->setTicksCount(4);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesOpacity(0.5);
    axisY->setShadesBrush(Qt::blue);
    axisY->setGridLineVisible(false);
    axisY->setShadesVisible(true);

    QChartAxisCategories* categoriesX = axisX->categories();
    categoriesX->insert(1,"low");
    categoriesX->insert(5,"optimal");
    categoriesX->insert(10,"high");

    QChartAxisCategories* categoriesY = axisY->categories();
    categoriesY->insert(1,"slow");
    categoriesY->insert(5,"med");
    categoriesY->insert(10,"fast");

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
