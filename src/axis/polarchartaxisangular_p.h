/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef POLARCHARTAXISANGULAR_P_H
#define POLARCHARTAXISANGULAR_P_H

#include "polarchartaxis_p.h"
#include "qvalueaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PolarChartAxisAngular : public PolarChartAxis
{
    Q_OBJECT
public:
    PolarChartAxisAngular(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~PolarChartAxisAngular();

    Qt::Orientation orientation() const;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    virtual void updateGeometry();
    virtual void createItems(int count);

    qreal preferredAxisRadius(const QSizeF &maxSize);

public Q_SLOTS:
    virtual void handleArrowPenChanged(const QPen &pen);
    virtual void handleGridPenChanged(const QPen &pen);

private:
    QRectF moveLabelToPosition(qreal angularCoordinate, QPointF labelPoint, QRectF labelRect) const;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // POLARCHARTAXISANGULAR_P_H
