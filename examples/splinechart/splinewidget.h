#ifndef SPLINEWIDGET_H
#define SPLINEWIDGET_H

#include <QtGui/QWidget>
#include "qsplineseries.h"

QTCOMMERCIALCHART_USE_NAMESPACE

class SplineWidget : public QWidget
{
    Q_OBJECT
    
public:
    SplineWidget(QWidget *parent = 0);
    ~SplineWidget();

public slots:
    void addNewPoint();
    void removePoint();

private:
    QSplineSeries* series;
};

#endif // SPLINEWIDGET_H
