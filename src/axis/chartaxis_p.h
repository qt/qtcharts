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
#include "chartelement_p.h"
#include "axisanimation_p.h"
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractAxis;
class ChartPresenter;

class ChartAxis : public ChartElement, public QGraphicsLayoutItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsLayoutItem)
public:
    enum AxisType{ X_AXIS,Y_AXIS };

    ChartAxis(QAbstractAxis *axis, ChartPresenter *presenter);
    ~ChartAxis();

    virtual AxisType axisType() const = 0;

    void setArrowOpacity(qreal opacity);
    qreal arrowOpacity() const;
    void setArrowVisibility(bool visible);

    void setGridOpacity(qreal opacity);
    qreal gridOpacity() const;
    void setGridVisibility(bool visible);

    void setLabelsOpacity(qreal opacity);
    qreal labelsOpacity() const;
    void setLabelsVisibility(bool visible);

    void setShadesOpacity(qreal opacity);
    qreal shadesOpacity() const;
    void setShadesVisibility(bool visible);

    void setLabelsAngle(int angle);
    int labelsAngle()const { return m_labelsAngle; }

    void setShadesBrush(const QBrush &brush);
    void setShadesPen(const QPen &pen);

    void setArrowPen(const QPen &pen);
    void setGridPen(const QPen &pen);

    void setLabelsPen(const QPen &pen);
    void setLabelsBrush(const QBrush &brush);
    void setLabelsFont(const QFont &font);

    void setTitlePen(const QPen &pen);
    void setTitleBrush(const QBrush &brush);
    void setTitleFont(const QFont &font);
    void setTitleText(const QString& title);


    void setLayout(QVector<qreal> &layout);
    QVector<qreal> layout() const { return m_layoutVector; }

    void setAnimation(AxisAnimation* animation);
    ChartAnimation* animation() const { return m_animation; };

    Qt::Orientation orientation() const;
    bool alternativePlacement() const;

    bool isVisible();
    void hide();

    void setGeometry(const QRectF &size);
    QRectF geometry() const { return m_rect; }

    void setInternalRect(const QRectF &size);

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

protected:
    virtual void updateGeometry() = 0;
    virtual QVector<qreal> calculateLayout() const = 0;
    QStringList createNumberLabels(qreal min, qreal max,int ticks) const;


public Q_SLOTS:
    virtual void handleAxisUpdated();
    virtual void handleDomainUpdated();


private:
    inline bool isEmpty();
    void createItems(int count);
    void deleteItems(int count);
    void updateLayout(QVector<qreal> &layout);
    void axisSelected();

protected:
    QAbstractAxis* m_chartAxis;
    int m_labelsAngle;
    //TODO: to be removed
    QRectF m_rect;
    QRectF m_internalRect;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsItemGroup> m_arrow;
    QGraphicsSimpleTextItem* m_title;
    QVector<qreal> m_layoutVector;
    qreal m_min;
    qreal m_max;
    AxisAnimation *m_animation;
    QFont m_font;
    QString m_titleText;

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

#endif /* CHARTAXI_H */
