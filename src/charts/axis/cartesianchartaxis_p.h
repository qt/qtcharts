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

#ifndef CARTESIANCHARTAXIS_H
#define CARTESIANCHARTAXIS_H

#include "qchartglobal.h"
#include "chartaxiselement_p.h"

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractAxis;

class CartesianChartAxis : public ChartAxisElement
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsLayoutItem)
public:

    CartesianChartAxis(QAbstractAxis *axis, QGraphicsItem *item = 0, bool intervalAxis = false);
    ~CartesianChartAxis();

    void setGeometry(const QRectF &axis, const QRectF &grid);
    QRectF gridGeometry() const { return m_gridRect; }
    bool isEmpty();

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

protected:
    void setGeometry(const QRectF &size) { Q_UNUSED(size);}
    virtual void updateGeometry() = 0;
    void updateLayout(QVector<qreal> &layout);

public Q_SLOTS:
    virtual void handleArrowPenChanged(const QPen &pen);
    virtual void handleGridPenChanged(const QPen &pen);
    virtual void handleShadesBrushChanged(const QBrush &brush);
    virtual void handleShadesPenChanged(const QPen &pen);

private:
    void createItems(int count);
    void deleteItems(int count);

private:
    QRectF m_gridRect;

    friend class AxisAnimation;
    friend class LineArrowItem;
};

QT_CHARTS_END_NAMESPACE

#endif /* CARTESIANCHARTAXIS_H */
