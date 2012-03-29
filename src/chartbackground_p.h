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

#ifndef CHARTBACKGROUND_H_
#define CHARTBACKGROUND_H_

#include "qchartglobal.h"
#include <QGraphicsRectItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartBackground: public QGraphicsRectItem
{
public:
    ChartBackground(QGraphicsItem *parent =0);
    ~ChartBackground();

    void setDimeter(int dimater);
    int diameter() const;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    int roundness(qreal size) const;

private:
     int m_diameter;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTBACKGROUND_H_ */


