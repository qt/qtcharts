#include <QtGui/QApplication>
#include <QMainWindow>
#include <cmath>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create widget and scatter series
    QChartView *chartWidget = new QChartView();
    QPieSeries *series = qobject_cast<QPieSeries *>(chartWidget->createSeries(QChartSeries::SeriesTypePie));
    Q_ASSERT(series);

    // Add test data to the series
    series->add(QPieSlice(1, "test1", Qt::red));
    series->add(QPieSlice(2, "test2", Qt::green));
    series->add(QPieSlice(3, "test3", Qt::blue));
    series->add(QPieSlice(4, "test4", Qt::darkRed));
    series->add(QPieSlice(5, "test5", Qt::darkGreen));

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartWidget);
    w.show();

    return a.exec();
}
