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

    ChartAxis(QAbstractAxis *axis, ChartPresenter *presenter);
    ~ChartAxis();

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
    void setLabelPadding(int padding);
    int labelPadding() const { return m_labelPadding;};

    void setTitlePen(const QPen &pen);
    void setTitleBrush(const QBrush &brush);
    void setTitleFont(const QFont &font);
    void setTitleText(const QString &title);

    void setLayout(QVector<qreal> &layout);
    QVector<qreal> layout() const { return m_layoutVector; }

    void setAnimation(AxisAnimation *animation);
    ChartAnimation *animation() const { return m_animation; };

    Qt::Orientation orientation() const;
    Qt::Alignment alignment() const;

    bool isVisible();
    void hide();

    void setGeometry(const QRectF &axis, const QRectF &grid);
    QRectF axisGeometry() const { return m_axisRect; }
    QRectF gridGeometry() const { return m_gridRect; }

    void setLabels(const QStringList& labels);
    QStringList labels() const { return m_labelsList; }

    void setLabelBetweenTicks(bool enabled);
    bool labelBetweenTicks() const { return m_labelBetween; }

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

protected:
    void setGeometry(const QRectF &size){ Q_UNUSED(size);};
    virtual void updateGeometry() = 0;
    virtual QVector<qreal> calculateLayout() const = 0;

    QList<QGraphicsItem *> lineItems() { return m_grid->childItems(); };
    QList<QGraphicsItem *> labelItems() { return m_labels->childItems();};
    QList<QGraphicsItem *> shadeItems() { return m_shades->childItems();};
    QList<QGraphicsItem *> arrowItems() { return m_arrow->childItems();};

    QFont font() const { return m_font; }
    qreal min() const {return m_min; }
    qreal max() const {return m_max; }
    QStringList createValueLabels(int ticks) const;
    QStringList createDateTimeLabels(const QString& format,int ticks) const;

public Q_SLOTS:
    virtual void handleAxisUpdated();
    virtual void handleDomainUpdated();

private:
    inline bool isEmpty();
    void createItems(int count);
    void deleteItems(int count);
    void updateLayout(QVector<qreal> &layout);
    void axisSelected();

private:
    QAbstractAxis *m_chartAxis;
    int m_labelsAngle;
    QRectF m_axisRect;
    QRectF m_gridRect;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsItemGroup> m_arrow;
    QGraphicsSimpleTextItem *m_title;
    QVector<qreal> m_layoutVector;
    qreal m_min;
    qreal m_max;
    AxisAnimation *m_animation;
    QFont m_font;
    QString m_titleText;
    int m_labelPadding;
    QStringList m_labelsList;
    bool m_labelBetween;

friend class AxisAnimation;
friend class AxisItem;

};

class AxisItem: public QGraphicsLineItem
{

public:
    explicit AxisItem(ChartAxis *axis, QGraphicsItem *parent = 0) : QGraphicsLineItem(parent), m_axis(axis) {}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        Q_UNUSED(event)
        m_axis->axisSelected();
    }

    QRectF boundingRect() const {
        return shape().boundingRect();
    }

    QPainterPath shape() const {
        QPainterPath path = QGraphicsLineItem::shape();
        QRectF rect = path.boundingRect();
        path.addRect(rect.adjusted(0, 0, m_axis->orientation() != Qt::Horizontal ? 8 : 0, m_axis->orientation() != Qt::Vertical ? 8 : 0));
        return path;
    }

private:
    ChartAxis *m_axis;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTAXI_H */
