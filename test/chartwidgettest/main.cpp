#include <QtCore/QtGlobal>
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QApplication>
#else
#include <QtWidgets/QApplication>
#endif
#include <chartwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChartWidget w;
    w.resize(QSize(200,200));
    w.setColor(Qt::red);
    w.show();
    
    return a.exec();
}
