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

#ifndef LEGENDSCROLLBUTTON_P_H
#define LEGENDSCROLLBUTTON_P_H

#include <QObject>
#include <qchartglobal.h>
#include <QGraphicsPolygonItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegend;

class LegendScrollButton : public QGraphicsPolygonItem
{
public:
    enum ScrollButtonId {
        ScrollButtonIdLeft,
        ScrollButtonIdRight,
        ScrollButtonIdUp,
        ScrollButtonIdDown
    };

    explicit LegendScrollButton(ScrollButtonId id, QLegend *legend);
    ScrollButtonId id();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    ScrollButtonId m_id;
    QLegend *m_ledgend;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // LEGENDSCROLLBUTTON_P_H
