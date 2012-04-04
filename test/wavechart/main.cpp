#include "wavechart.h"
#include <QApplication>
#include <QMainWindow>
#include <QGLWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    QChart *chart = new QChart();
    WaveChart *waveChart = new WaveChart(chart,&window);

    waveChart->setViewport( new QGLWidget() );
    waveChart->setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle("This is wave generator.");

    window.setCentralWidget(waveChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
