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

#ifndef CHARTAXIS_H
#define CHARTAXIS_H

#include "qchartglobal.h"
#include "chart_p.h"
#include "axisanimation_p.h"
#include <QGraphicsItem>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractAxis;
class ChartPresenter;

class ChartAxis : public Chart
{
    Q_OBJECT
public:
    enum AxisType{ X_AXIS,Y_AXIS };

    ChartAxis(QAbstractAxis *axis, ChartPresenter *presenter);
    ~ChartAxis();

    virtual AxisType axisType() const = 0;

    void setAxisOpacity(qreal opacity);
    qreal axisOpacity() const;

    void setGridOpacity(qreal opacity);
    qreal gridOpacity() const;

    void setLabelsOpacity(qreal opacity);
    qreal labelsOpacity() const;

    void setShadesOpacity(qreal opacity);
    qreal shadesOpacity() const;

    void setLabelsAngle(int angle);
    int labelsAngle()const { return m_labelsAngle; }

    void setShadesBrush(const QBrush &brush);
    void setShadesPen(const QPen &pen);

    void setAxisPen(const QPen &pen);
    void setGridPen(const QPen &pen);

    void setLabelsPen(const QPen &pen);
    void setLabelsBrush(const QBrush &brush);
    void setLabelsFont(const QFont &font);

    void setLayout(QVector<qreal> &layout);
    QVector<qreal> layout() const { return m_layoutVector; }

    void setAnimation(AxisAnimation* animation);
    ChartAnimation* animation() const { return m_animation; };

    QRectF geometry() const { return m_rect; }

    qreal minimumWidth();
    qreal minimumHeight();

protected:
    virtual void updateGeometry() = 0;
    virtual QVector<qreal> calculateLayout() const = 0;
    void createNumberLabels(QStringList &labels,qreal min, qreal max,int ticks) const;

public Q_SLOTS:
    virtual void handleAxisUpdated();
    virtual void handleDomainUpdated();
    void handleGeometryChanged(const QRectF &size);

private:
    inline bool isEmpty();
    void createItems(int count);
    void deleteItems(int count);
    void updateLayout(QVector<qreal> &layout);
    void axisSelected();

protected:
    QAbstractAxis* m_chartAxis;
    QRectF m_rect;
    int m_labelsAngle;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsItemGroup> m_axis;
    QVector<qreal> m_layoutVector;
    qreal m_min;
    qreal m_max;
    AxisAnimation *m_animation;
    qreal m_minWidth;
    qreal m_minHeight;
    QFont m_font;

    friend class AxisAnimation;
    friend class AxisItem;

};

class AxisItem: public QGraphicsLineItem
{

public:
    explicit AxisItem(ChartAxis *axis, QGraphicsItem *parent = 0) : QGraphicsLineItem(parent), m_axis(axis) {}

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event)
   {
       Q_UNUSED(event)
       m_axis->axisSelected();
   }

   QRectF boundingRect() const
   {
      return shape().boundingRect();
   }

   QPainterPath shape() const
   {
       QPainterPath path = QGraphicsLineItem::shape();
       QRectF rect = path.boundingRect();
       path.addRect(rect.adjusted(0,0,m_axis->axisType()!=ChartAxis::X_AXIS?8:0,m_axis->axisType()!=ChartAxis::Y_AXIS?8:0));
       return path;
   }

private:
   ChartAxis* m_axis;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXISITEM_H_ */
