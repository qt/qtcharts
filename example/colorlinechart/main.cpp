#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlinechartseries.h>
#include <qchart.h>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QLineChartSeries* series0 = new QLineChartSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);
    QLineChartSeries* series1 = new QLineChartSeries();
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

    QFont font;
    font.setPixelSize(18);
    chartView->setChartTitleFont(font);
    chartView->setChartTitle("Custom color line chart example");
    chartView->addSeries(series0);
    chartView->addSeries(series1);

    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, Qt::blue);
    backgroundGradient.setColorAt(1.0, Qt::yellow);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chartView->setChartBackgroundBrush(backgroundGradient);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
