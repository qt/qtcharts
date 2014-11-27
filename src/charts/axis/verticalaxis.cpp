/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/verticalaxis_p.h>
#include <QtCharts/QAbstractAxis>
#include <private/chartpresenter_p.h>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

VerticalAxis::VerticalAxis(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : CartesianChartAxis(axis, item, intervalAxis)
{
}

VerticalAxis::~VerticalAxis()
{
}

void VerticalAxis::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxisElement::layout();

    if (layout.isEmpty() && axis()->type() != QAbstractAxis::AxisTypeLogValue)
        return;

    QStringList labelList = labels();

    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> arrow = arrowItems();
    QGraphicsTextItem *title = titleItem();

    Q_ASSERT(labels.size() == labelList.size());
    Q_ASSERT(layout.size() == labelList.size());

    const QRectF &axisRect = axisGeometry();
    const QRectF &gridRect = gridGeometry();

    qreal height = axisRect.bottom();

    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem*>(arrow.at(0));

    //arrow position
    if (axis()->alignment() == Qt::AlignLeft)
        arrowItem->setLine(axisRect.right(), gridRect.top(), axisRect.right(), gridRect.bottom());
    else if (axis()->alignment() == Qt::AlignRight)
        arrowItem->setLine(axisRect.left(), gridRect.top(), axisRect.left(), gridRect.bottom());

    //title
    QRectF titleBoundingRect;
    QString titleText = axis()->titleText();
    qreal availableSpace = axisRect.width() - labelPadding();
    if (!titleText.isEmpty() && titleItem()->isVisible()) {
        availableSpace -= titlePadding() * 2.0;
        qreal minimumLabelWidth = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("...")).width();
        qreal titleSpace = availableSpace - minimumLabelWidth;
        title->setHtml(ChartPresenter::truncatedText(axis()->titleFont(), titleText, qreal(90.0),
                                                     titleSpace, gridRect.height(),
                                                     titleBoundingRect));
        title->setTextWidth(titleBoundingRect.height());

        titleBoundingRect = title->boundingRect();

        QPointF center = gridRect.center() - titleBoundingRect.center();
        if (axis()->alignment() == Qt::AlignLeft)
            title->setPos(axisRect.left() - titleBoundingRect.width() / 2.0 + titleBoundingRect.height() / 2.0 + titlePadding(), center.y());
        else if (axis()->alignment() == Qt::AlignRight)
            title->setPos(axisRect.right() - titleBoundingRect.width() / 2.0 - titleBoundingRect.height() / 2.0 - titlePadding(), center.y());

        title->setTransformOriginPoint(titleBoundingRect.center());
        title->setRotation(270);

        availableSpace -= titleBoundingRect.height();
    }

    if (layout.isEmpty() && axis()->type() == QAbstractAxis::AxisTypeLogValue)
        return;

    QList<QGraphicsItem *> lines = gridItems();
    QList<QGraphicsItem *> shades = shadeItems();

    for (int i = 0; i < layout.size(); ++i) {
        //items
        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem *>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem *>(arrow.at(i + 1));
        QGraphicsTextItem *labelItem = static_cast<QGraphicsTextItem *>(labels.at(i));

        //grid line
        gridItem->setLine(gridRect.left(), layout[i], gridRect.right(), layout[i]);

        //label text wrapping
        QString text = labelList.at(i);
        QRectF boundingRect;
        // don't truncate empty labels
        if (text.isEmpty()) {
            labelItem->setHtml(text);
        } else {
            qreal labelHeight = (axisRect.height() / layout.count()) - (2 * labelPadding());
            QString truncatedText = ChartPresenter::truncatedText(axis()->labelsFont(), text,
                                                                  axis()->labelsAngle(),
                                                                  availableSpace,
                                                                  labelHeight, boundingRect);
            labelItem->setTextWidth(ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                     truncatedText).width());
            labelItem->setHtml(truncatedText);
        }

        //label transformation origin point
        const QRectF &rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        qreal widthDiff = rect.width() - boundingRect.width();
        qreal heightDiff = rect.height() - boundingRect.height();

        //ticks and label position
        if (axis()->alignment() == Qt::AlignLeft) {
            labelItem->setPos(axisRect.right() - rect.width() + (widthDiff / 2.0) - labelPadding(), layout[i] - center.y());
            tickItem->setLine(axisRect.right() - labelPadding(), layout[i], axisRect.right(), layout[i]);
        } else if (axis()->alignment() == Qt::AlignRight) {
            labelItem->setPos(axisRect.left() + labelPadding() - (widthDiff / 2.0), layout[i] - center.y());
            tickItem->setLine(axisRect.left(), layout[i], axisRect.left() + labelPadding(), layout[i]);
        }

        //label in between
        bool forceHide = false;
        if (intervalAxis() && (i + 1) != layout.size()) {
            qreal lowerBound = qMin(layout[i], gridRect.bottom());
            qreal upperBound = qMax(layout[i + 1], gridRect.top());
            const qreal delta = lowerBound - upperBound;
            // Hide label in case visible part of the category at the grid edge is too narrow
            if (delta < boundingRect.height()
                && (lowerBound == gridRect.bottom() || upperBound == gridRect.top())) {
                forceHide = true;
            } else {
                labelItem->setPos(labelItem->pos().x() , lowerBound - (delta / 2.0) - center.y());
            }
        }

        //label overlap detection - compensate one pixel for rounding errors
        if (labelItem->pos().y() + boundingRect.height() > height || forceHide ||
            (labelItem->pos().y() + (heightDiff / 2.0) - 1.0) > axisRect.bottom() ||
            labelItem->pos().y() + (heightDiff / 2.0) < (axisRect.top() - 1.0)) {
            labelItem->setVisible(false);
        }
        else {
            labelItem->setVisible(true);
            height=labelItem->pos().y();
        }

        //shades
        QGraphicsRectItem *shadeItem = 0;
        if (i == 0)
            shadeItem = static_cast<QGraphicsRectItem *>(shades.at(0));
        else if (i % 2)
            shadeItem = static_cast<QGraphicsRectItem *>(shades.at((i / 2) + 1));
        if (shadeItem) {
            qreal lowerBound;
            qreal upperBound;
            if (i == 0) {
                lowerBound = gridRect.bottom();
                upperBound = layout[0];
            } else {
                lowerBound = layout[i];
                if (i == layout.size() - 1)
                    upperBound = gridRect.top();
                else
                    upperBound = qMax(layout[i + 1], gridRect.top());

            }
            if (lowerBound > gridRect.bottom())
                lowerBound = gridRect.bottom();
            if (upperBound < gridRect.top())
                upperBound = gridRect.top();
            shadeItem->setRect(gridRect.left(), upperBound, gridRect.width(),
                               lowerBound - upperBound);
            if (shadeItem->rect().height() <= 0.0)
                shadeItem->setVisible(false);
            else
                shadeItem->setVisible(true);
        }

        // check if the grid line and the axis tick should be shown
        qreal y = gridItem->line().p1().y();
        if ((y < gridRect.top() || y > gridRect.bottom()))
        {
            gridItem->setVisible(false);
            tickItem->setVisible(false);
        }else{
            gridItem->setVisible(true);
            tickItem->setVisible(true);
        }

    }
    //begin/end grid line in case labels between
    if (intervalAxis()) {
        QGraphicsLineItem *gridLine;
        gridLine = static_cast<QGraphicsLineItem *>(lines.at(layout.size()));
        gridLine->setLine(gridRect.left(), gridRect.top(), gridRect.right(), gridRect.top());
        gridLine->setVisible(true);
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size() + 1));
        gridLine->setLine(gridRect.left(), gridRect.bottom(), gridRect.right(), gridRect.bottom());
        gridLine->setVisible(true);
    }
}

QSizeF VerticalAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    QSizeF sh(0, 0);

    if (axis()->titleText().isEmpty() || !titleItem()->isVisible())
        return sh;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(axis()->titleFont(),
                                                            QStringLiteral("..."));
        sh = QSizeF(titleRect.height() + (titlePadding() * 2.0), titleRect.width());
        break;
    }
    case Qt::MaximumSize:
    case Qt::PreferredSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(axis()->titleFont(), axis()->titleText());
        sh = QSizeF(titleRect.height() + (titlePadding() * 2.0), titleRect.width());
        break;
    }
    default:
        break;
    }

    return sh;
}

QT_CHARTS_END_NAMESPACE
