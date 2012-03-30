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

#ifndef BAR_H
#define BAR_H

#include "qchartglobal.h"
#include <QGraphicsRectItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single visual bar item of chart
class Bar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bar(QString category, QGraphicsItem *parent = 0);

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

Q_SIGNALS:
    void clicked(QString category, Qt::MouseButtons button);
    void hoverEntered(QPoint pos);
    void hoverLeaved();

private:
    QString m_category;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
