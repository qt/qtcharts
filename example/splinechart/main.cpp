#include <QtGui/QApplication>
#include "splinewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SplineWidget w;
    w.show();
    
    return a.exec();
}
