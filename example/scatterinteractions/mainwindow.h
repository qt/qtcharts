#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <qchartglobal.h>
#include <qscatterseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void clickPoint(QPointF coordinate);

private:
    QScatterSeries *m_scatter;
    QScatterSeries *m_scatter2;
    QScatterSeries *m_scatter3;
};

#endif // MAINWINDOW_H
