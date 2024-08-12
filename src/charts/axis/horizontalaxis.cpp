// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/qcategoryaxis.h>
#include <QtCharts/qlogvalueaxis.h>
#include <QtCharts/qcoloraxis.h>
#include <QtCore/qmath.h>
#include <private/chartpresenter_p.h>
#include <private/horizontalaxis_p.h>
#include <private/qabstractaxis_p.h>

QT_BEGIN_NAMESPACE

HorizontalAxis::HorizontalAxis(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : CartesianChartAxis(axis, item, intervalAxis)
{
}

HorizontalAxis::~HorizontalAxis()
{
}

QSizeF HorizontalAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    QSizeF sh(0,0);
    // Size hint from here is used as the base for label size hints; if labels are not
    // visible, we need to increase the size or we end up showing "..." when
    // the title should be visible
    qreal labelPaddingFactor = labelsVisible() ? 1 : 2;

    if (axis()->titleText().isEmpty() || !titleItem()->isVisible())
        return sh;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(axis()->titleFont(),
                                                            QStringLiteral("..."));
        sh = QSizeF(titleRect.width(),
                    labelPaddingFactor * (titleRect.height() + (titlePadding() * 2.0)));
        break;
    }
    case Qt::MaximumSize:
    case Qt::PreferredSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(axis()->titleFont(),
                                                            axis()->titleText());
        sh = QSizeF(titleRect.width(),
                    labelPaddingFactor * (titleRect.height() + (titlePadding() * 2.0)));
        break;
    }
    default:
        break;
    }
    return sh;
}

void HorizontalAxis::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    const QList<qreal> &dynamicMinorTicklayout = ChartAxisElement::dynamicMinorTicklayout();

    if (layout.isEmpty() && dynamicMinorTicklayout.isEmpty()
            && axis()->type() != QAbstractAxis::AxisTypeLogValue) {
        return;
    }

    QStringList labelList = labels();

    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> arrow = arrowItems();
    QGraphicsTextItem *title = titleItem();

    Q_ASSERT(labels.size() == labelList.size());
    Q_ASSERT(layout.size() == labelList.size());

    const QRectF &axisRect = axisGeometry();
    const QRectF &gridRect = gridGeometry();

    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem *>(arrow.at(0));

    if (axis()->type() != QAbstractAxis::AxisTypeColor) {
        if (axis()->alignment() == Qt::AlignTop)
            arrowItem->setLine(gridRect.left(), axisRect.bottom(), gridRect.right(),
                               axisRect.bottom());
        else if (axis()->alignment() == Qt::AlignBottom)
            arrowItem->setLine(gridRect.left(), axisRect.top(), gridRect.right(), axisRect.top());
    }

    const QLatin1String ellipsis("...");

    //title
    QRectF titleBoundingRect;
    QString titleText = axis()->titleText();
    qreal availableSpace = axisRect.height() - labelPadding();
    if (!titleText.isEmpty() && titleItem()->isVisible()) {
        availableSpace -= titlePadding() * 2.0;
        qreal minimumLabelHeight = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                    QStringLiteral("...")).height();
        qreal titleSpace = availableSpace - minimumLabelHeight;
        if (axis()->type() == QAbstractAxis::AxisTypeColor) {
            QColorAxis *colorAxis = static_cast<QColorAxis *>(axis());
            titleSpace -= colorAxis->size() + colorScalePadding();
        }

        title->setHtml(ChartPresenter::truncatedText(axis()->titleFont(), titleText, qreal(0.0),
                                                     gridRect.width(), titleSpace,
                                                     titleBoundingRect));
        title->setTextWidth(titleBoundingRect.width());

        titleBoundingRect = title->boundingRect();

        QPointF center = gridRect.center() - titleBoundingRect.center();
        if (axis()->alignment() == Qt::AlignTop)
            title->setPos(center.x(), axisRect.top() + titlePadding());
        else  if (axis()->alignment() == Qt::AlignBottom)
            title->setPos(center.x(), axisRect.bottom() - titleBoundingRect.height() - titlePadding());

        availableSpace -= titleBoundingRect.height();
        if (axis()->type() == QAbstractAxis::AxisTypeColor) {
            QColorAxis *colorAxis = static_cast<QColorAxis *>(axis());
            availableSpace -= colorAxis->size() + colorScalePadding();
        }
    }

    QList<QGraphicsItem *> lines = gridItems();
    QList<QGraphicsItem *> shades = shadeItems();

    qreal last_label_max_x = 0;

    bool labelsTruncated = false;

    for (int i = 0; i < layout.size(); ++i) {
        //items
        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem*>(arrow.at(i + 1));
        QGraphicsTextItem *labelItem = static_cast<QGraphicsTextItem *>(labels.at(i));

        //grid line
        if (axis()->isReverse()) {
            gridItem->setLine(gridRect.right() - layout[i] + gridRect.left(), gridRect.top(),
                    gridRect.right() - layout[i] + gridRect.left(), gridRect.bottom());
        } else {
            gridItem->setLine(layout[i], gridRect.top(), layout[i], gridRect.bottom());
        }

        //label text wrapping
        QString text;
        if (axis()->isReverse() && axis()->type() != QAbstractAxis::AxisTypeCategory)
            text = labelList.at(labelList.size() - i - 1);
        else
            text = labelList.at(i);

        QRectF boundingRect;
        // don't truncate empty labels
        if (text.isEmpty()) {
            labelItem->setHtml(text);
        } else  {
            QString displayText = text;
            if (axis()->truncateLabels()) {
                qreal labelWidth = axisRect.width() / layout.size() - (2 * labelPadding());
                // Replace digits with ellipsis "..." if number does not fit
                displayText = ChartPresenter::truncatedText(axis()->labelsFont(), text,
                                                            axis()->labelsAngle(),
                                                            labelWidth,
                                                            availableSpace, boundingRect);
            } else {
                boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                displayText, axis()->labelsAngle());
            }

            labelItem->setTextWidth(ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                     displayText).width());

            labelItem->setHtml(displayText);

            labelsTruncated |= displayText != text;
        }

        //label transformation origin point
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        qreal heightDiff = rect.height() - boundingRect.height();
        qreal widthDiff = rect.width() - boundingRect.width();

        //ticks and label position
        QPointF labelPos;
        if (axis()->alignment() == Qt::AlignTop) {
            qreal tickStopY = axisRect.bottom();

            if (axis()->type() == QAbstractAxis::AxisTypeColor) {
                QColorAxis *colorAxis = static_cast<QColorAxis *>(axis());
                QGraphicsPixmapItem *colorScale = colorScaleItem();

                const qreal penWidth = axis()->linePen().widthF();
                // penWidth / 2 is half of tick width
                colorScale->setOffset(gridRect.left() - penWidth / 2,
                                      axisRect.bottom() - colorScalePadding() - colorAxis->size());
                prepareColorScale(gridRect.width() + penWidth + 1, colorAxis->size());

                tickStopY = axisRect.bottom() - colorScalePadding() - colorAxis->size();
            }

            if (axis()->isReverse()) {
                labelPos = QPointF(gridRect.right() - layout[layout.size() - i - 1]
                                           + gridRect.left() - center.x(),
                                   tickStopY - rect.height() + (heightDiff / 2.0) - labelPadding());
                tickItem->setLine(gridRect.right() + gridRect.left() - layout[i], tickStopY,
                                  gridRect.right() + gridRect.left() - layout[i],
                                  tickStopY - labelPadding());
            } else {
                labelPos = QPointF(layout[i] - center.x(),
                                   tickStopY - rect.height() + (heightDiff / 2.0) - labelPadding());
                tickItem->setLine(layout[i], tickStopY, layout[i], tickStopY - labelPadding());
            }
        } else if (axis()->alignment() == Qt::AlignBottom) {

            qreal tickStartY = axisRect.top();

            if (axis()->type() == QAbstractAxis::AxisTypeColor) {
                QColorAxis *colorAxis = static_cast<QColorAxis *>(axis());
                QGraphicsPixmapItem *colorScale = colorScaleItem();

                const qreal penWidth = axis()->linePen().widthF();
                // penWidth / 2 is half of tick width
                colorScale->setOffset(gridRect.left() - penWidth / 2,
                                      axisRect.top() + colorScalePadding());
                prepareColorScale(gridRect.width() + penWidth + 1, colorAxis->size());

                tickStartY = axisRect.top() + colorScalePadding() + colorAxis->size();
            }

            if (axis()->isReverse()) {
                labelPos = QPointF(gridRect.right() - layout[layout.size() - i - 1]
                                           + gridRect.left() - center.x(),
                                   tickStartY - (heightDiff / 2.0) + labelPadding());
                tickItem->setLine(gridRect.right() + gridRect.left() - layout[i], tickStartY,
                                  gridRect.right() + gridRect.left() - layout[i],
                                  tickStartY + labelPadding());
            } else {
                labelPos = QPointF(layout[i] - center.x(),
                                   tickStartY - (heightDiff / 2.0) + labelPadding());
                tickItem->setLine(layout[i], tickStartY, layout[i], tickStartY + labelPadding());
            }
        }

        //label in between
        bool forceHide = false;
        if (intervalAxis() && (i + 1) != layout.size()
            && axis()->type() != QAbstractAxis::AxisTypeColor) {
            qreal leftBound;
            qreal rightBound;
            if (axis()->isReverse()) {
                leftBound = qMax(gridRect.right() + gridRect.left() - layout[i + 1],
                        gridRect.left());
                rightBound = qMin(gridRect.right() + gridRect.left() - layout[i], gridRect.right());
            } else {
                leftBound = qMax(layout[i], gridRect.left());
                rightBound = qMin(layout[i + 1], gridRect.right());
            }
            const qreal delta = rightBound - leftBound;
            if (axis()->type() != QAbstractAxis::AxisTypeCategory) {
                // Hide label in case visible part of the category at the grid edge is too narrow
                if (delta < boundingRect.width()
                    && (leftBound == gridRect.left() || rightBound == gridRect.right())) {
                    forceHide = true;
                } else {
                    labelPos.setX(leftBound + (delta / 2.0) - center.x());
                }
            } else {
                QCategoryAxis *categoryAxis = static_cast<QCategoryAxis *>(axis());
                if (categoryAxis->labelsPosition() == QCategoryAxis::AxisLabelsPositionCenter) {
                    if (delta < boundingRect.width()
                        && (leftBound == gridRect.left() || rightBound == gridRect.right())) {
                        forceHide = true;
                    } else {
                        labelPos.setX(leftBound + (delta / 2.0) - center.x());
                    }
                } else if (categoryAxis->labelsPosition()
                           == QCategoryAxis::AxisLabelsPositionOnValue) {
                    if (axis()->isReverse())
                        labelPos.setX(leftBound - center.x());
                    else
                        labelPos.setX(rightBound - center.x());
                }
            }
        }

        // Round to full pixel via QPoint to avoid one pixel clipping on the edge in some cases
        labelItem->setPos(labelPos.toPoint());

        // Label overlap detection - compensate one pixel for rounding errors.
        // This is not needed for color axis as its labels don't collide with other labels
        if ((labelItem->pos().x() < last_label_max_x && labelItem->toPlainText() == ellipsis)
            || forceHide
            || (labelItem->pos().x() + (widthDiff / 2.0))       < (axisRect.left() - 1.0)
            || (labelItem->pos().x() + (widthDiff / 2.0) - 1.0) > axisRect.right()) {
            if (axis()->type() != QAbstractAxis::AxisTypeColor)
                labelItem->setVisible(false);
        } else {
            labelItem->setVisible(true);
            last_label_max_x = boundingRect.width() + labelItem->pos().x();
        }

        //shades
        QGraphicsRectItem *shadeItem = 0;
        if (i == 0)
            shadeItem = static_cast<QGraphicsRectItem *>(shades.at(0));
        else if (i % 2)
            shadeItem = static_cast<QGraphicsRectItem *>(shades.at((i / 2) + 1));
        if (shadeItem) {
            qreal leftBound;
            qreal rightBound;
            if (i == 0) {
                if (axis()->isReverse()) {
                    leftBound = gridRect.right() + gridRect.left() - layout[i];
                    rightBound = gridRect.right();
                } else {
                    leftBound = gridRect.left();
                    rightBound = layout[0];
                }
            } else {
                if (axis()->isReverse()) {
                    rightBound = gridRect.right() + gridRect.left() - layout[i];
                    if (i == layout.size() - 1) {
                        leftBound = gridRect.left();
                    } else {
                        leftBound = qMax(gridRect.right() + gridRect.left() - layout[i + 1],
                                gridRect.left());
                    }
                } else {
                    leftBound = layout[i];
                    if (i == layout.size() - 1)
                        rightBound = gridRect.right();
                    else
                        rightBound = qMin(layout[i + 1], gridRect.right());
                }
            }
            if (leftBound < gridRect.left())
                leftBound = gridRect.left();
            if (rightBound > gridRect.right())
                rightBound = gridRect.right();
            shadeItem->setRect(leftBound, gridRect.top(), rightBound - leftBound,
                               gridRect.height());
            if (shadeItem->rect().width() <= 0.0)
                shadeItem->setVisible(false);
            else
                shadeItem->setVisible(true);
        }

        // check if the grid line and the axis tick should be shown
        const bool gridLineVisible = (gridItem->line().p1().x() >= gridRect.left()
                                      && gridItem->line().p1().x() <= gridRect.right());
        gridItem->setVisible(gridLineVisible);
        tickItem->setVisible(gridLineVisible);
    }

    axis()->d_ptr->setLabelsTruncated(labelsTruncated);

    updateMinorTickGeometry();

    // begin/end grid line in case labels between
    if (intervalAxis()) {
        QGraphicsLineItem *gridLine;
        gridLine = static_cast<QGraphicsLineItem *>(lines.at(layout.size()));
        gridLine->setLine(gridRect.right(), gridRect.top(), gridRect.right(), gridRect.bottom());
        gridLine->setVisible(true);
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size()+1));
        gridLine->setLine(gridRect.left(), gridRect.top(), gridRect.left(), gridRect.bottom());
        gridLine->setVisible(true);
    }
}

void HorizontalAxis::updateMinorTickGeometry()
{
    if (!axis())
        return;

    QList<qreal> layout = ChartAxisElement::layout();
    int minorTickCount = 0;
    qreal tickSpacing = 0.0;
    QList<qreal> minorTickSpacings;
    switch (axis()->type()) {
    case QAbstractAxis::AxisTypeValue: {
        const QValueAxis *valueAxis = qobject_cast<QValueAxis *>(axis());

        minorTickCount = valueAxis->minorTickCount();

        if (valueAxis->tickType() == QValueAxis::TicksFixed) {
            if (valueAxis->tickCount() >= 2)
                tickSpacing = layout.at(0) - layout.at(1);

            for (int i = 0; i < minorTickCount; ++i) {
                const qreal ratio = (1.0 / qreal(minorTickCount + 1)) * qreal(i + 1);
                minorTickSpacings.append(tickSpacing * ratio);
            }
        }
        break;
    }
    case QAbstractAxis::AxisTypeLogValue: {
        const QLogValueAxis *logValueAxis = qobject_cast<QLogValueAxis *>(axis());
        const qreal base = logValueAxis->base();
        const qreal logBase = qLn(base);

        minorTickCount = logValueAxis->minorTickCount();
        if (minorTickCount < 0)
            minorTickCount = qMax(qFloor(base) - 2, 0);

        // Two "virtual" ticks are required to make sure that all minor ticks
        // are displayed properly (even for the partially visible segments of
        // the chart).
        if (layout.size() >= 2) {
            // Calculate tickSpacing as a difference between visible ticks
            // whenever it is possible. Virtual ticks will not be correctly
            // positioned when the layout is animating.
            tickSpacing = layout.at(0) - layout.at(1);
            layout.prepend(layout.at(0) + tickSpacing);
            layout.append(layout.at(layout.size() - 1) - tickSpacing);
        } else {
            const qreal logMax = qLn(logValueAxis->max());
            const qreal logMin = qLn(logValueAxis->min());
            const qreal logExtraMaxTick = qLn(qPow(base, qFloor(logMax / logBase) + 1.0));
            const qreal logExtraMinTick = qLn(qPow(base, qCeil(logMin / logBase) - 1.0));
            const qreal edge = gridGeometry().left();
            const qreal delta = gridGeometry().width() / qAbs(logMax - logMin);
            const qreal extraMaxTick = edge + (logExtraMaxTick - qMin(logMin, logMax)) * delta;
            const qreal extraMinTick = edge + (logExtraMinTick - qMin(logMin, logMax)) * delta;

            // Calculate tickSpacing using one (if layout.size() == 1) or two
            // (if layout.size() == 0) "virtual" ticks. In both cases animation
            // will not work as expected. This should be fixed later.
            layout.prepend(extraMinTick);
            layout.append(extraMaxTick);
            tickSpacing = layout.at(0) - layout.at(1);
        }

        const qreal minorTickStepValue = qFabs(base - 1.0) / qreal(minorTickCount + 1);
        for (int i = 0; i < minorTickCount; ++i) {
            const qreal x = minorTickStepValue * qreal(i + 1) + 1.0;
            const qreal minorTickSpacing = tickSpacing * (qLn(x) / logBase);
            minorTickSpacings.append(minorTickSpacing);
        }
        break;
    }
    default:
        // minor ticks are not supported
        break;
    }

    const QValueAxis *valueAxis = qobject_cast<QValueAxis *>(axis());
    if (valueAxis && valueAxis->tickType() == QValueAxis::TicksDynamic) {
        const QList<qreal> dynamicMinorTicklayout = ChartAxisElement::dynamicMinorTicklayout();
        const QRectF &gridRect = gridGeometry();
        const qreal deltaX = gridRect.width() / (valueAxis->max() - valueAxis->min());
        const qreal leftPos = gridRect.left();
        const qreal rightPos = gridRect.right();

        for (int i = 0; i < dynamicMinorTicklayout.size(); i++) {
            QGraphicsLineItem *minorGridLineItem =
                    static_cast<QGraphicsLineItem *>(minorGridItems().value(i));
            QGraphicsLineItem *minorArrowLineItem =
                    static_cast<QGraphicsLineItem *>(minorArrowItems().value(i));
            if (!minorGridLineItem || !minorArrowLineItem)
                continue;

            qreal minorGridLineItemX = 0.0;
            if (axis()->isReverse())
                minorGridLineItemX = rightPos - dynamicMinorTicklayout.at(i) * deltaX;
            else
                minorGridLineItemX = dynamicMinorTicklayout.at(i) * deltaX + leftPos;

            qreal minorArrowLineItemY1;
            qreal minorArrowLineItemY2;
            switch (axis()->alignment()) {
            case Qt::AlignTop:
                minorArrowLineItemY1 = gridGeometry().top();
                minorArrowLineItemY2 = gridGeometry().top() - labelPadding() / 2.0;
                break;
            case Qt::AlignBottom:
                minorArrowLineItemY1 = gridGeometry().bottom();
                minorArrowLineItemY2 = gridGeometry().bottom() + labelPadding() / 2.0;
                break;
            default:
                minorArrowLineItemY1 = 0.0;
                minorArrowLineItemY2 = 0.0;
                break;
            }

            minorGridLineItem->setLine(minorGridLineItemX, gridGeometry().top(),
                                       minorGridLineItemX, gridGeometry().bottom());
            minorArrowLineItem->setLine(minorGridLineItemX, minorArrowLineItemY1,
                                        minorGridLineItemX, minorArrowLineItemY2);

            // check if the minor grid line and the minor axis arrow should be shown
            bool minorGridLineVisible = (minorGridLineItemX >= gridGeometry().left()
                                         && minorGridLineItemX <= gridGeometry().right());
            minorGridLineItem->setVisible(minorGridLineVisible);
            minorArrowLineItem->setVisible(minorGridLineVisible);
        }
    } else {
        if (minorTickCount < 1 || tickSpacing == 0.0 || minorTickSpacings.size() != minorTickCount)
            return;

        for (int i = 0; i < layout.size() - 1; ++i) {
            for (int j = 0; j < minorTickCount; ++j) {
                const int minorItemIndex = i * minorTickCount + j;
                QGraphicsLineItem *minorGridLineItem =
                        static_cast<QGraphicsLineItem *>(minorGridItems().value(minorItemIndex));
                QGraphicsLineItem *minorArrowLineItem =
                        static_cast<QGraphicsLineItem *>(minorArrowItems().value(minorItemIndex));
                if (!minorGridLineItem || !minorArrowLineItem)
                    continue;

                const qreal minorTickSpacing = minorTickSpacings.value(j, 0.0);

                qreal minorGridLineItemX = 0.0;
                if (axis()->isReverse()) {
                    minorGridLineItemX = std::floor(gridGeometry().left() + gridGeometry().right()
                                                    - layout.at(i) + minorTickSpacing);
                } else {
                    minorGridLineItemX = std::ceil(layout.at(i) - minorTickSpacing);
                }

                qreal minorArrowLineItemY1;
                qreal minorArrowLineItemY2;
                switch (axis()->alignment()) {
                case Qt::AlignTop:
                    minorArrowLineItemY1 = gridGeometry().top();
                    minorArrowLineItemY2 = gridGeometry().top() - labelPadding() / 2.0;
                    break;
                case Qt::AlignBottom:
                    minorArrowLineItemY1 = gridGeometry().bottom();
                    minorArrowLineItemY2 = gridGeometry().bottom() + labelPadding() / 2.0;
                    break;
                default:
                    minorArrowLineItemY1 = 0.0;
                    minorArrowLineItemY2 = 0.0;
                    break;
                }

                minorGridLineItem->setLine(minorGridLineItemX, gridGeometry().top(),
                                           minorGridLineItemX, gridGeometry().bottom());
                minorArrowLineItem->setLine(minorGridLineItemX, minorArrowLineItemY1,
                                            minorGridLineItemX, minorArrowLineItemY2);

                // check if the minor grid line and the minor axis arrow should be shown
                bool minorGridLineVisible = (minorGridLineItemX >= gridGeometry().left()
                                             && minorGridLineItemX <= gridGeometry().right());
                minorGridLineItem->setVisible(minorGridLineVisible);
                minorArrowLineItem->setVisible(minorGridLineVisible);
            }
        }
    }
}

QT_END_NAMESPACE
