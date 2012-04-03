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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QChartView>
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
    QChartView* chartView;
    QListWidget* countrieslist;
    QListWidget* yearslist;
    QSqlDatabase db;
    QRadioButton* barChartRadioButton;
    QRadioButton* scatterChartRadioButton;
};

#endif // WIDGET_H
