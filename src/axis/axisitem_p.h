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

#ifndef AXISITEM_H_
#define AXISITEM_H_

#include "chart_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis;
class ChartPresenter;

class Axis : public Chart
{
    Q_OBJECT
public:
    enum AxisType{X_AXIS,Y_AXIS};

    Axis(QChartAxis *axis, ChartPresenter *presenter, AxisType type = X_AXIS);
    ~Axis();

    AxisType axisType() const { return m_type; }

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

    inline QRectF geometry() const { return m_rect; }
    inline QVector<qreal> layout() { return m_layoutVector; }

public Q_SLOTS:
    void handleAxisUpdated();
    void handleAxisCategoriesUpdated();
    void handleRangeChanged(qreal min , qreal max,int tickCount);
    void handleGeometryChanged(const QRectF &size);


private:
    inline bool isEmpty();
    void createItems(int count);
    void deleteItems(int count);

    QVector<qreal> calculateLayout() const;
    void updateLayout(QVector<qreal> &layout);
    void setLayout(QVector<qreal> &layout);

    bool createLabels(QStringList &labels,qreal min, qreal max,int ticks) const;
    void axisSelected();

private:
    QChartAxis* m_chartAxis;
    AxisType m_type;
    QRectF m_rect;
    int m_labelsAngle;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsItemGroup> m_axis;
    QVector<qreal> m_layoutVector;
    qreal m_min;
    qreal m_max;
    int m_ticksCount;
    qreal m_zoomFactor;

    friend class AxisAnimation;
    friend class AxisItem;

};

class AxisItem: public QGraphicsLineItem
{
public:

    AxisItem(Axis *axis, QGraphicsItem *parent = 0) : QGraphicsLineItem(parent), m_axis(axis) {}

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
       path.addRect(rect.adjusted(0,0,m_axis->axisType()!=Axis::X_AXIS?8:0,m_axis->axisType()!=Axis::Y_AXIS?8:0));
       return path;
   }

private:
   Axis* m_axis;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXISITEM_H_ */
