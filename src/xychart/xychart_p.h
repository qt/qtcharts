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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef XYCHARTITEM_H
#define XYCHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include "xyanimation_p.h"
#include "qvaluesaxis.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QXYSeries;

class XYChart :  public ChartElement
{
     Q_OBJECT
public:
     explicit XYChart(QXYSeries *series, ChartPresenter *presenter);
    ~XYChart() {}

    void setGeometryPoints(const QVector<QPointF>& points);
    QVector<QPointF> geometryPoints() const { return m_points; }

    void setClipRect(const QRectF &rect);
    QRectF clipRect() const { return m_clipRect; }

    QSizeF size() const { return m_size; }
    QPointF origin() const { return m_origin; }

    void setAnimation(XYAnimation* animation);
    ChartAnimation* animation() const { return m_animation; }
    virtual void updateGeometry() = 0;

    bool isDirty() const { return m_dirty; }
    void setDirty(bool dirty);

public Q_SLOTS:
    void handlePointAdded(int index);
    void handlePointRemoved(int index);
    void handlePointReplaced(int index);
    void handlePointsReplaced();
    void handleDomainUpdated();
    void handleGeometryChanged(const QRectF &size);

Q_SIGNALS:
    void clicked(const QPointF& point);

protected:
    virtual void updateChart(QVector<QPointF> &oldPoints,QVector<QPointF> &newPoints,int index = -1);
    QPointF calculateGeometryPoint(const QPointF &point) const;
    QPointF calculateGeometryPoint(int index) const;
    QPointF calculateDomainPoint(const QPointF &point) const;
    QVector<QPointF> calculateGeometryPoints() const;

private:
    inline bool isEmpty();

protected:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    QXYSeries* m_series;
    QSizeF m_size;
    QPointF m_origin;
    QRectF m_clipRect;
    QVector<QPointF> m_points;
    XYAnimation* m_animation;
    bool m_dirty;

    friend class AreaChartItem;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
