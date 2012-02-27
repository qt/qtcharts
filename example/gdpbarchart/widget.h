#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <qchartview.h>
#include <qbarseries.h>
#include <QSqlDatabase>

QTCOMMERCIALCHART_USE_NAMESPACE

class QListWidget;
class QRadioButton;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void refreshChart();
    void printChart();

private:
    QChartView* chartArea;
    QListWidget* countrieslist;
    QListWidget* yearslist;
    QSqlDatabase db;
    QBarSeries* series0;
    QRadioButton* barChartRadioButton;
    QRadioButton* scatterChartRadioButton;
};

#endif // WIDGET_H
