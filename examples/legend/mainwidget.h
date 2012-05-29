#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "qchartglobal.h"
#include "qchart.h"
#include "qchartview.h"
#include <QWidget>
#include <QGraphicsWidget>
#include <QGridLayout>
#include <QGraphicsGridLayout>

QTCOMMERCIALCHART_USE_NAMESPACE

class MainWidget : public QWidget
//class MainWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

    void createSeries();
    
signals:
    
public slots:
    void detachLegend();
    void attachLegend();
    void addBarset();
    void removeBarset();

private:

    QChart *m_chart;
    QBarSeries *m_series;

    QGraphicsScene *m_scene;
    QChartView *m_chartView;
    QGridLayout *m_mainLayout;
    QGridLayout *m_buttonLayout;

    QGraphicsView *m_customView;
    QGraphicsScene *m_customScene;
    QGraphicsGridLayout *m_customLayout;


    int m_setCount;
};

#endif // MAINWIDGET_H
