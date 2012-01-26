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
    QStandardItemModel dataModel(5,10);
    QModelIndex index;
    index = dataModel.index(0,0);

    // Series 0
    dataModel.setData(dataModel.index(0,0),1);
    dataModel.setData(dataModel.index(0,1),2);
    dataModel.setData(dataModel.index(0,2),3);
    dataModel.setData(dataModel.index(0,3),4);
    dataModel.setData(dataModel.index(0,4),5);
    dataModel.setData(dataModel.index(0,5),6);
    dataModel.setData(dataModel.index(0,6),7);
    dataModel.setData(dataModel.index(0,7),8);
    dataModel.setData(dataModel.index(0,8),9);
    dataModel.setData(dataModel.index(0,9),10);

    // Series 1, some other items missing
    dataModel.setData(dataModel.index(1,0),5);
    dataModel.setData(dataModel.index(1,3),4);
    dataModel.setData(dataModel.index(1,5),7);
    dataModel.setData(dataModel.index(1,6),8);
    dataModel.setData(dataModel.index(1,8),9);
    dataModel.setData(dataModel.index(1,9),9);

    // Series 2
    dataModel.setData(dataModel.index(2,0),3);
    dataModel.setData(dataModel.index(2,1),5);
    dataModel.setData(dataModel.index(2,2),8);
    dataModel.setData(dataModel.index(2,3),13);
    dataModel.setData(dataModel.index(2,4),8);
    dataModel.setData(dataModel.index(2,5),5);
    dataModel.setData(dataModel.index(2,6),3);
    dataModel.setData(dataModel.index(2,7),2);
    dataModel.setData(dataModel.index(2,8),1);
    dataModel.setData(dataModel.index(2,9),1);

    // Series 3
    dataModel.setData(dataModel.index(3,0),5);
    dataModel.setData(dataModel.index(3,1),6);
    dataModel.setData(dataModel.index(3,2),7);
    dataModel.setData(dataModel.index(3,3),3);
    dataModel.setData(dataModel.index(3,4),4);
    dataModel.setData(dataModel.index(3,5),5);
    dataModel.setData(dataModel.index(3,6),8);
    dataModel.setData(dataModel.index(3,7),9);
    dataModel.setData(dataModel.index(3,8),10);
    dataModel.setData(dataModel.index(3,9),5);

    // Series 4
    dataModel.setData(dataModel.index(4,0),9);
    dataModel.setData(dataModel.index(4,1),7);
    dataModel.setData(dataModel.index(4,2),5);
    dataModel.setData(dataModel.index(4,3),3);
    dataModel.setData(dataModel.index(4,4),1);
    dataModel.setData(dataModel.index(4,5),2);
    dataModel.setData(dataModel.index(4,6),4);
    dataModel.setData(dataModel.index(4,7),6);
    dataModel.setData(dataModel.index(4,8),8);
    dataModel.setData(dataModel.index(4,9),10);

    series0->setData(&dataModel);

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->addSeries(series0);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

