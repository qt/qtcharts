#include <QtGui/QApplication>
#include <QGraphicsScene>
//QGraphicsScene *scene, QWidget *parent = 0#include <QGraphicsView>
//#include "widget.h"
//#include "qbarchart.h"
#include "qchartview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    //QGraphicsView view(&scene);
    QChartView view(&scene);
/*
    QBarChart *barChart = new QBarChart();
    barChart->setSize(640,480);
    scene.addItem(barChart);

    QList<int> data;
    data << 1;
    data << 1;
    data << 2;
    data << 3;
    data << 5;
    data << 8;
    data << 13;
    data << 21;
    data << 42;
    barChart->addSeries(data);
*/
    view.resize(640, 480);
    QPalette p(view.palette());
    p.setColor(QPalette::Base, QColor(0,0,0));
    view.setPalette(p);
    view.show();

    return a.exec();
}
