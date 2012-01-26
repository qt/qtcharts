#include <QApplication>
#include <QMainWindow>
#include <QStandardItemModel>
#include <barchartseries.h>
#include "chartwidget.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    BarChartSeries* series0 = new BarChartSeries();

    // Create some test data to chart
    QStandardItemModel dataModel(2,10);
    QModelIndex index;
    index = dataModel.index(0,0);
    // Series 1, items 6 to 9 missing.
    dataModel.setData(dataModel.index(0,0),1);
    dataModel.setData(dataModel.index(0,1),12);
    dataModel.setData(dataModel.index(0,2),5);
    dataModel.setData(dataModel.index(0,3),8);
    dataModel.setData(dataModel.index(0,4),17);
    dataModel.setData(dataModel.index(0,5),9);

    // Series 2, some other items missing
    dataModel.setData(dataModel.index(1,0),5);
    dataModel.setData(dataModel.index(1,3),4);
    dataModel.setData(dataModel.index(1,5),7);
    dataModel.setData(dataModel.index(1,6),8);
    dataModel.setData(dataModel.index(1,8),9);
    dataModel.setData(dataModel.index(1,9),9);

    series0->setData(&dataModel);

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->addSeries(series0);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

