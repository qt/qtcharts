#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtGui/QWidget>
#include "qchartview.h"

QTCOMMERCIALCHART_USE_NAMESPACE

class TableWidget : public QWidget
{
    Q_OBJECT
    
public:
    TableWidget(QWidget *parent = 0);
    ~TableWidget();



    private:
    QChartView* chartView;
};

#endif // TABLEWIDGET_H
