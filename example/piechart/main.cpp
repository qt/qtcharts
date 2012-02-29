#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>
#include <qpieslice.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QChartView* chartView =  new QChartView(&window);

    //! [1]
    QPieSeries *series = new QPieSeries();
    series->add(1, "Slice 1");
    series->add(2, "Slice 2");
    series->add(3, "Slice 3");
    series->add(4, "Slice 4");
    series->add(5, "Slice 5");
    chartView->addSeries(series);
    //! [1]

    //! [2]
    series->setHoverHighlighting();
    series->setClickExplodes();
    //! [2]

    window.setCentralWidget(chartView);
    window.resize(600, 600);
    window.show();

    return a.exec();
}
