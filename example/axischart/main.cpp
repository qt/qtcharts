#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlineseries.h>
#include <qchart.h>
#include <qchartaxis.h>
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
    axisX->addAxisTickLabel(0,"low");
    axisX->addAxisTickLabel(50,"medium");
    axisX->addAxisTickLabel(100,"High");

    QChartAxis* axisY = chartView->axisY();
    axisY->setLabelsAngle(45);
    axisY->setShadesBrush(Qt::yellow);
    axisY->addAxisTickLabel(0,"low");
    axisY->addAxisTickLabel(50,"medium");
    axisY->addAxisTickLabel(100,"High");

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
