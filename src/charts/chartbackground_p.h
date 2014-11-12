/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTBACKGROUND_H
#define CHARTBACKGROUND_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsRectItem>

class QGraphicsDropShadowEffect;
QT_CHARTS_BEGIN_NAMESPACE

class ChartBackground: public QGraphicsRectItem
{
public:
    ChartBackground(QGraphicsItem *parent = 0);
    ~ChartBackground();

    void setDiameter(qreal diameter);
    qreal diameter() const;
    void setDropShadowEnabled(bool enabled);
    bool isDropShadowEnabled() { return m_dropShadow != 0; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal m_diameter;
    QGraphicsDropShadowEffect *m_dropShadow;
};

QT_CHARTS_END_NAMESPACE

#endif /* CHARTBACKGROUND_H */


