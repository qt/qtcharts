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

    ChartAxis(QAbstractAxis *axis, QGraphicsItem* item = 0, bool intervalAxis = false);
    ~ChartAxis();

    QAbstractAxis* axis() const { return m_axis; }

    void setLabelPadding(int padding);
    int labelPadding() const { return m_labelPadding;};

    QFont titleFont() const;
    QString titleText() const;

    void setLayout(QVector<qreal> &layout);
    QVector<qreal> layout() const { return m_layoutVector; }

    void setAnimation(AxisAnimation *animation);
    ChartAnimation *animation() const { return m_animation; };

    Qt::Orientation orientation() const;
    Qt::Alignment alignment() const;

    void setGeometry(const QRectF &axis, const QRectF &grid);
    QRectF axisGeometry() const { return m_axisRect; }
    QRectF gridGeometry() const { return m_gridRect; }

    void setLabels(const QStringList &labels);
    QStringList labels() const { return m_labelsList; }

    //this flag indicates that axis is used to show intervals it means labels are in between ticks
    bool intervalAxis() const { return m_intervalAxis; }

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;


    QRectF boundingRect() const{
        return QRectF();
    }

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
    {

    }

//helpers
    static QStringList createValueLabels(qreal max, qreal min, int ticks, const QString &format);
    static QStringList createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString& format);
    static QStringList createDateTimeLabels(qreal max, qreal min, int ticks, const QString &format);

protected:
    void setGeometry(const QRectF &size) { Q_UNUSED(size);};
    virtual void updateGeometry() = 0;
    virtual QVector<qreal> calculateLayout() const = 0;

    QList<QGraphicsItem *> lineItems() { return m_grid->childItems(); };
    QList<QGraphicsItem *> labelItems() { return m_labels->childItems();};
    QList<QGraphicsItem *> shadeItems() { return m_shades->childItems();};
    QList<QGraphicsItem *> arrowItems() { return m_arrow->childItems();};
    QGraphicsSimpleTextItem* titleItem() const { return m_title.data();}

    QFont font() const;
    qreal min() const;
    qreal max() const;

//handlers
public Q_SLOTS:
	void handleVisibleChanged(bool visible);
	void handleArrowVisibleChanged(bool visible);
	void handleGridVisibleChanged(bool visible);
	void handleLabelsVisibleChanged(bool visible);
	void handleShadesVisibleChanged(bool visible);
	void handleLabelsAngleChanged(int angle);
	void handleShadesBrushChanged(const QBrush &brush);
	void handleShadesPenChanged(const QPen &pen);
	void handleArrowPenChanged(const QPen &pen);
	void handleGridPenChanged(const QPen &pen);
	void handleLabelsPenChanged(const QPen &pen);
	void handleLabelsBrushChanged(const QBrush &brush);
	void handleLabelsFontChanged(const QFont &font);
    void handleTitlePenChanged(const QPen &pen);
    void handleTitleBrushChanged(const QBrush &brush);
    void handleTitleFontChanged(const QFont &font);
    void handleTitleTextChanged(const QString &title);
    void handleRangeChanged(qreal min , qreal max);

Q_SIGNALS:
	void clicked();

private:
    inline bool isEmpty();
    void createItems(int count);
    void deleteItems(int count);
    void updateLayout(QVector<qreal> &layout);
    void axisSelected();
    void connectSlots();

private:
    QAbstractAxis *m_axis;
    int m_labelsAngle;
    QRectF m_axisRect;
    QRectF m_gridRect;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_arrow;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsSimpleTextItem> m_title;
    QVector<qreal> m_layoutVector;
    AxisAnimation *m_animation;
    int m_labelPadding;
    QStringList m_labelsList;
    bool m_intervalAxis;

    friend class AxisAnimation;
    friend class ArrowItem;

};

class ArrowItem: public QGraphicsLineItem
{

public:
    explicit ArrowItem(ChartAxis *axis, QGraphicsItem *parent = 0) : QGraphicsLineItem(parent), m_axis(axis) {}

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
