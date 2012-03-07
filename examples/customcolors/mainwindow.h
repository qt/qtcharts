#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qchartglobal.h>
#include <QtGui/QMainWindow>
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QChartView;
class QLineSeries;
class QScatterSeries;
class QPieSeries;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void customize();

private:
    QColor m_companyColor1;
    QColor m_companyColor2;
    QColor m_companyColor3;
    QColor m_companyColor4;
    QChartView *m_chartView;
    QLineSeries *m_line;
    QScatterSeries *m_scatter;
    QPieSeries *m_pie;
    QTimer m_timer;
};

#endif // MAINWINDOW_H
