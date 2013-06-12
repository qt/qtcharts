/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef CHARTBACKGROUND_H
#define CHARTBACKGROUND_H

#include "qchartglobal.h"
#include <QGraphicsRectItem>

class QGraphicsDropShadowEffect;
QTCOMMERCIALCHART_BEGIN_NAMESPACE

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

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTBACKGROUND_H */


