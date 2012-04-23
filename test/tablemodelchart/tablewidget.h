/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtGui/QWidget>
//#include <QChartGlobal>
#include "qchartview.h"
//#include "qxyseries.h"
//#include <QPieSeries>

class CustomTableModel;
class QTableView;
class QRadioButton;
class QSpinBox;

QTCOMMERCIALCHART_USE_NAMESPACE

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
    void addColumnRight();
    void removeColumn();
    void updateChartType(bool toggle);
    void testPie();

    private:
    QChartView* m_chartView;
    QChart* m_chart;
    QXYSeries* m_series;
    CustomTableModel* m_model;
    QTableView* m_tableView;
    QRadioButton* m_lineRadioButton;
    QRadioButton* m_splineRadioButton;
    QRadioButton* m_scatterRadioButton;
    QRadioButton* m_pieRadioButton;
    QRadioButton* m_areaRadioButton;
    QRadioButton* m_barRadioButton;
    QSpinBox* m_linesCountSpinBox;
//    QPieSeries* specialPie;
};

#endif // TABLEWIDGET_H
