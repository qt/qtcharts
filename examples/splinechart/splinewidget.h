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
