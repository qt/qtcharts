#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include "customslice.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QPieSeries *series = new QPieSeries();
    series->add(5, "Slice 1");
    series->add(2, "Slice 2");
    series->add(3, "Slice 3");
    series->add(4, "Slice 4");
    series->add(5, "Slice 5");
    series->add(6, "Slice 6");
    series->add(7, "Slice 7");
    series->add(new CustomSlice(8));
    series->enableClickExplodes(true);
    series->enableHoverHighlight(true);

    QChartView* chartView =  new QChartView(&window);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->addSeries(series);
    chartView->setChartTitle("simple piechart");
    chartView->setChartTheme(QChart::ChartThemeIcy);

    window.setCentralWidget(chartView);
    window.resize(600, 600);
    window.show();

    return a.exec();
}
