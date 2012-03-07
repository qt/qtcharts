#include <QtGui/QApplication>
#include <QMainWindow>
#include "multichartwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MultiChartWidget *multi = new MultiChartWidget();

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(multi);
    w.show();

    return a.exec();
}
