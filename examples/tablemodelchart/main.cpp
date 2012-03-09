#include <QtGui/QApplication>
#include "tablewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TableWidget w;
    w.show();
    
    return a.exec();
}
