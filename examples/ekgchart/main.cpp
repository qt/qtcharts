#include "chartview.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    ChartView chartView(&window);
    chartView.setRenderHint(QPainter::Antialiasing);
    chartView.setAnimationOptions(QChart::AllAnimations);
    window.setCentralWidget(&chartView);
    window.resize(400, 300);
    window.show();
    return a.exec();
}
