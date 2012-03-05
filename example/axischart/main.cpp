#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlineseries.h>
#include <qchart.h>
#include <qchartaxis.h>
#include <qchartaxiscategories.h>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QLineSeries* series0 = new QLineSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);
    QLineSeries* series1 = new QLineSeries();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);

    int numPoints = 100;

    for (int x = 0; x <= numPoints; ++x) {
    	  series0->add(x, fabs(sin(PI/50*x)*100));
    	  series1->add(x, fabs(cos(PI/50*x)*100));
    }

    QChartView* chartView =  new QChartView(&window);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTitle("This is custom axis chart example");
    chartView->addSeries(series0);
    chartView->addSeries(series1);

    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, Qt::white);
    backgroundGradient.setColorAt(1.0, QRgb(0xffff80));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chartView->setChartBackgroundBrush(backgroundGradient);

    QChartAxis* axisX = chartView->axisX();
    axisX->setLabelsAngle(45);
    axisX->setGridPen(Qt::DashLine);

    QChartAxisCategories& categoriesX = axisX->categories();
    categoriesX.insert(0,"low");
    categoriesX.insert(50,"medium");
    categoriesX.insert(100,"High");

    axisX->setMin(-10);
    axisX->setMax(200);

    QChartAxis* axisY = chartView->axisY();
    axisY->setLabelsAngle(45);
    axisY->setShadesBrush(Qt::yellow);

    QChartAxisCategories& categoriesY = axisY->categories();
    categoriesY.insert(0,"low");
    categoriesY.insert(50,"medium");
    categoriesY.insert(100,"High");

    axisY->setMin(-10);
    axisY->setMax(200);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
