// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTAXISELEMENT_H
#define CHARTAXISELEMENT_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>
#include <private/chartelement_p.h>
#include <private/axisanimation_p.h>
#include <private/datetimeaxislabel_p.h>
#include <private/valueaxislabel_p.h>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsLayoutItem>
#include <QtCharts/qdatetimeaxis.h>
#include <QtCharts/QValueAxis>
#include <QtGui/QFont>

QT_BEGIN_NAMESPACE

class ChartPresenter;
class QAbstractAxis;

class Q_CHARTS_EXPORT ChartAxisElement : public ChartElement, public QGraphicsLayoutItem
{
    Q_OBJECT

    using QGraphicsLayoutItem::setGeometry;
public:
    ChartAxisElement(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~ChartAxisElement();

    virtual QRectF gridGeometry() const = 0;
    virtual void setGeometry(const QRectF &axis, const QRectF &grid) = 0;
    virtual bool emptyAxis() const = 0;

    void setAnimation(AxisAnimation *animation) { m_animation = animation; }
    AxisAnimation *animation() const override { return m_animation; }

    QAbstractAxis *axis() const { return m_axis; }
    void setLayout(const QList<qreal> &layout) { m_layout = layout; }
    QList<qreal> &layout() { return m_layout; } // Modifiable reference
    void setDynamicMinorTickLayout(const QList<qreal> &layout)
    {
        m_dynamicMinorTickLayout = layout;
    }
    QList<qreal> &dynamicMinorTicklayout()
    {
        return m_dynamicMinorTickLayout;
    } // Modifiable reference
    inline qreal labelPadding() const { return qreal(4.0); }
    inline qreal titlePadding() const { return qreal(2.0); }
    inline qreal colorScalePadding() const { return qreal { 8.0 }; }
    void setLabels(const QStringList &labels) { m_labelsList = labels; }
    QStringList labels() const { return m_labelsList; }

    qreal min() const;
    qreal max() const;

    qreal tickInterval() const;
    qreal tickAnchor() const;

    QRectF axisGeometry() const { return m_axisRect; }
    void setAxisGeometry(const QRectF &axisGeometry) { m_axisRect = axisGeometry; }

    void axisSelected();

    //this flag indicates that axis is used to show intervals it means labels are in between ticks
    bool intervalAxis() const { return m_intervalAxis; }

    QStringList createValueLabels(qreal max, qreal min, int ticks,
                                  qreal tickInterval, qreal tickAnchor,
                                  QValueAxis::TickType tickType, const QString &format) const;
    QStringList createLogValueLabels(qreal min, qreal max, qreal base, int ticks,
                                     const QString &format) const;
    QStringList createDateTimeLabels(qreal max, qreal min, int ticks, const QString &format) const;
    QStringList createColorLabels(qreal min, qreal max, int ticks) const;

    // from QGraphicsLayoutItem
    QRectF boundingRect() const override
    {
        return QRectF();
    }

    // from QGraphicsLayoutItem
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override
    {
    }

    bool labelsEditable() const;
    void setLabelsEditable(bool labelsEditable);
    bool labelsVisible() const;

protected:
    virtual QList<qreal> calculateLayout() const = 0;
    virtual void updateLayout(const QList<qreal> &layout) = 0;

    QList<QGraphicsItem *> gridItems() { return m_grid->childItems(); }
    QList<QGraphicsItem *> minorGridItems() { return m_minorGrid->childItems(); }
    QList<QGraphicsItem *> labelItems() { return m_labels->childItems(); }
    QList<QGraphicsItem *> shadeItems() { return m_shades->childItems(); }
    QList<QGraphicsItem *> arrowItems() { return m_arrow->childItems(); }
    QList<QGraphicsItem *> minorArrowItems() { return m_minorArrow->childItems(); }
    QGraphicsTextItem *titleItem() const { return m_title.data(); }
    QGraphicsPixmapItem *colorScaleItem() const { return m_colorScale.get(); }
    QGraphicsItemGroup *gridGroup() { return m_grid.data(); }
    QGraphicsItemGroup *minorGridGroup() { return m_minorGrid.data(); }
    QGraphicsItemGroup *labelGroup() { return m_labels.data(); }
    QGraphicsItemGroup *shadeGroup() { return m_shades.data(); }
    QGraphicsItemGroup *arrowGroup() { return m_arrow.data(); }
    QGraphicsItemGroup *minorArrowGroup() { return m_minorArrow.data(); }

    void prepareColorScale(const qreal width, const qreal height);

public Q_SLOTS:
    void handleVisibleChanged(bool visible);
    void handleArrowVisibleChanged(bool visible);
    void handleGridVisibleChanged(bool visible);
    void handleLabelsVisibleChanged(bool visible);
    void handleShadesVisibleChanged(bool visible);
    void handleLabelsAngleChanged(int angle);
    virtual void handleShadesBrushChanged(const QBrush &brush) = 0;
    virtual void handleShadesPenChanged(const QPen &pen) = 0;
    virtual void handleArrowPenChanged(const QPen &pen) = 0;
    virtual void handleGridPenChanged(const QPen &pen) = 0;
    virtual void handleMinorArrowPenChanged(const QPen &pen) = 0;
    virtual void handleMinorGridPenChanged(const QPen &pen) = 0;
    virtual void handleMinorGridLineColorChanged(const QColor &color) = 0;
    virtual void handleGridLineColorChanged(const QColor &color) = 0;
    void handleLabelsBrushChanged(const QBrush &brush);
    void handleLabelsFontChanged(const QFont &font);
    void handleTitleBrushChanged(const QBrush &brush);
    void handleTitleFontChanged(const QFont &font);
    void handleTitleTextChanged(const QString &title);
    void handleTitleVisibleChanged(bool visible);
    void handleRangeChanged(qreal min, qreal max);
    void handleReverseChanged(bool reverse);
    void handleMinorArrowVisibleChanged(bool visible);
    void handleMinorGridVisibleChanged(bool visible);
    void handleLabelsPositionChanged();
    void handleTruncateLabelsChanged();
    void handleColorScaleSizeChanged();
    void handleColorScaleGradientChanged();
    void valueLabelEdited(qreal oldValue, qreal newValue);
    void dateTimeLabelEdited(const QDateTime &oldTime, const QDateTime &newTime);

Q_SIGNALS:
    void clicked();

private:
    void connectSlots();
    QString formatLabel(const QString &formatSpec, const QByteArray &array,
                        qreal value, int precision, const QString &preStr,
                        const QString &postStr) const;

    QAbstractAxis *m_axis;
    AxisAnimation *m_animation;
    QList<qreal> m_layout;
    QList<qreal> m_dynamicMinorTickLayout;
    QStringList m_labelsList;
    QRectF m_axisRect;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_arrow;
    QScopedPointer<QGraphicsItemGroup> m_minorGrid;
    QScopedPointer<QGraphicsItemGroup> m_minorArrow;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsTextItem> m_title;
    std::unique_ptr<QGraphicsPixmapItem> m_colorScale;
    bool m_intervalAxis;
    bool m_labelsEditable = false;
};

QT_END_NAMESPACE

#endif /* CHARTAXISELEMENT_H */
