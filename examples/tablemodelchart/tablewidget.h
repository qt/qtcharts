#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtGui/QWidget>
#include "qchartview.h"
#include "qxyseries.h"

QTCOMMERCIALCHART_USE_NAMESPACE

class CustomTableModel;
class QTableView;
class QRadioButton;
//class QSeries;

class TableWidget : public QWidget
{
    Q_OBJECT
    
public:
    TableWidget(QWidget *parent = 0);
    ~TableWidget();


    public slots:
    void addRowAbove();
    void addRowBelow();
    void removeRow();
    void updateChartType();

    private:
    QChartView* chartView;
    QXYSeries* series;
    CustomTableModel* m_model;
    QTableView* tableView;
    QRadioButton* lineRadioButton;
    QRadioButton* splineRadioButton;
    QRadioButton* scatterRadioButton;
    QRadioButton* pieRadioButton;
    QRadioButton* areaRadioButton;
    QRadioButton* barRadioButton;
};

#endif // TABLEWIDGET_H
