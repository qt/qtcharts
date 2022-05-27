/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef LEGENDMARKERITEM_P_H
#define LEGENDMARKERITEM_P_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegend>
#include <QGraphicsObject>
#include <QtGui/QFont>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsLayoutItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QLegendMarkerPrivate;

class Q_CHARTS_PRIVATE_EXPORT LegendMarkerItem : public QGraphicsObject, public QGraphicsLayoutItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsLayoutItem)
public:
    enum ItemType {
        TypeRect,
        TypeLine,
        TypeCircle,
        TypeRotatedRect,
        TypeTriangle,
        TypeStar,
        TypePentagon
    };

    explicit LegendMarkerItem(QLegendMarkerPrivate *marker, QGraphicsObject *parent = nullptr);
    ~LegendMarkerItem();

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setSeriesPen(const QPen &pen);
    void setSeriesBrush(const QBrush &brush);
    void setSeriesLightMarker(const QImage &image);

    void setFont(const QFont &font);
    QFont font() const;

    void setLabel(const QString label);
    QString label() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setGeometry(const QRectF &rect) override;
    QRectF boundingRect() const override;
    QRectF markerRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    QSizeF sizeHint (Qt::SizeHint which, const QSizeF &constraint) const override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    QString displayedLabel() const;
    void setToolTip(const QString &tooltip);

    QLegend::MarkerShape markerShape() const;
    void setMarkerShape(QLegend::MarkerShape shape);

    void updateMarkerShapeAndSize();
    QLegend::MarkerShape effectiveMarkerShape() const;
    qreal effectiveMarkerWidth() const;

    ItemType itemType() const { return m_itemType; }

Q_SIGNALS:
    void markerRectChanged();

protected:
    void setItemBrushAndPen();
    void setItemRect();
    bool useMaxWidth() const;

    QLegendMarkerPrivate *m_marker; // Knows
    QRectF m_defaultMarkerRect;
    QRectF m_markerRect;
    QRectF m_boundingRect;
    QGraphicsTextItem *m_textItem;
    QGraphicsItem *m_markerItem;
    qreal m_margin;
    qreal m_space;
    QString m_label;
    QLegend::MarkerShape m_markerShape;
    QImage m_seriesLightMarker;

    QBrush m_labelBrush;
    QPen m_pen;
    QBrush m_brush;
    QPen m_seriesPen;
    QBrush m_seriesBrush;
    QFont m_font;
    bool m_hovering;

    ItemType m_itemType;

    friend class QLegendMarker;
    friend class QLegendMarkerPrivate;
    friend class LegendLayout;
};

QT_END_NAMESPACE

#endif // LEGENDMARKERITEM_P_H
