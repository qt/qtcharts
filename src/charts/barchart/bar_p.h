/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
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

#ifndef BAR_H
#define BAR_H

#include "qchartglobal.h"
#include <QGraphicsRectItem>

QT_CHARTS_BEGIN_NAMESPACE

class QBarSet;

// Single visual bar item of chart
class Bar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Bar(QBarSet *barset, int index, QGraphicsItem *parent = 0);
    ~Bar();

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

Q_SIGNALS:
    void clicked(int index, QBarSet *barset);
    void hovered(bool status, QBarSet *barset);
    void hovered(bool status, int index, QBarSet *barset);

private:
    int m_index;
    QBarSet *m_barset;
    bool m_hovering;
};

QT_CHARTS_END_NAMESPACE

#endif // BAR_H
