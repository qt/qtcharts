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
#include "qchartview.h"
#include "qxyseries.h"

QTCOMMERCIALCHART_USE_NAMESPACE

class CustomTableModel;
class QTableView;
class QRadioButton;
class QSpinBox;
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
    QSpinBox* linesCountSpinBox;
};

#endif // TABLEWIDGET_H
