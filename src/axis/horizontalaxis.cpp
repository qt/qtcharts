/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "horizontalaxis_p.h"
#include "qabstractaxis_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalAxis::HorizontalAxis(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : CartesianChartAxis(axis, item, intervalAxis)
{
}

HorizontalAxis::~HorizontalAxis()
{
}

void HorizontalAxis::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxisElement::layout();

    if (layout.isEmpty())
        return;

    QStringList labelList = labels();

    QList<QGraphicsItem *> lines = gridItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> arrow = arrowItems();
    QGraphicsSimpleTextItem *title = titleItem();

    Q_ASSERT(labels.size() == labelList.size());
    Q_ASSERT(layout.size() == labelList.size());

    const QRectF &axisRect = axisGeometry();
    const QRectF &gridRect = gridGeometry();

    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem *>(arrow.at(0));

    if (axis()->alignment() == Qt::AlignTop)
        arrowItem->setLine(gridRect.left(), axisRect.bottom(), gridRect.right(), axisRect.bottom());
    else if (axis()->alignment() == Qt::AlignBottom)
        arrowItem->setLine(gridRect.left(), axisRect.top(), gridRect.right(), axisRect.top());

    qreal width = 0;

    //title
    int titlePad = 0;
    QRectF titleBoundingRect;
    QString titleText = axis()->titleText();
    if (!titleText.isEmpty() && titleItem()->isVisible()) {
        title->setText(truncatedText(axis()->titleFont(), titleText, 0.0, gridRect.width(), Qt::Horizontal, QRectF()));

        titlePad = titlePadding();
        titleBoundingRect = title->boundingRect();

        QPointF center = gridRect.center() - titleBoundingRect.center();
        if (axis()->alignment() == Qt::AlignTop) {
            title->setPos(center.x(), axisRect.top() + titlePad);
        } else  if (axis()->alignment() == Qt::AlignBottom) {
            title->setPos(center.x(), axisRect.bottom() - titleBoundingRect.height() - titlePad);
        }
    }

    for (int i = 0; i < layout.size(); ++i) {
        //items
        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem*>(arrow.at(i + 1));
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem *>(labels.at(i));

        //grid line
        gridItem->setLine(layout[i], gridRect.top(), layout[i], gridRect.bottom());

        //label text wrapping
        QString text = labelList.at(i);
        QRectF boundingRect;
        qreal size = axisRect.bottom() - axisRect.top() - labelPadding() - titleBoundingRect.height() - (titlePad * 2);
        labelItem->setText(truncatedText(axis()->labelsFont(), text, axis()->labelsAngle(),
                                         size, Qt::Vertical, boundingRect));

        //label transformation origin point
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        int heightDiff = rect.height() - boundingRect.height();

        //ticks and label position
        if (axis()->alignment() == Qt::AlignTop) {
            labelItem->setPos(layout[i] - center.x(), axisRect.bottom() - rect.height() + (heightDiff / 2) - labelPadding());
            tickItem->setLine(layout[i], axisRect.bottom(), layout[i], axisRect.bottom() - labelPadding());
        } else if (axis()->alignment() == Qt::AlignBottom) {
            labelItem->setPos(layout[i] - center.x(), axisRect.top() - (heightDiff / 2) + labelPadding());
            tickItem->setLine(layout[i], axisRect.top(), layout[i], axisRect.top() + labelPadding());
        }

        //label in between
        bool forceHide = false;
        if (intervalAxis() && (i + 1) != layout.size()) {
            qreal leftBound = qMax(layout[i], gridRect.left());
            qreal rightBound = qMin(layout[i + 1], gridRect.right());
            const qreal delta = rightBound - leftBound;
            // Hide label in case visible part of the category at the grid edge is too narrow
            if (delta < boundingRect.width()
                && (leftBound == gridRect.left() || rightBound == gridRect.right())) {
                forceHide = true;
            } else {
                labelItem->setPos(leftBound + (delta / 2.0) - center.x(), labelItem->pos().y());
            }
        }

        //label overlap detection - compensate one pixel for rounding errors
        if (labelItem->pos().x() < width || forceHide ||
            labelItem->pos().x() < (axisRect.left() - 1.0) ||
            (labelItem->pos().x() + boundingRect.width() - 1.0) > axisRect.right()){
            labelItem->setVisible(false);
        } else {
            labelItem->setVisible(true);
            width = boundingRect.width() + labelItem->pos().x();
        }

        //shades
        if ((i + 1) % 2 && i > 1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem *>(shades.at(i / 2 - 1));
            qreal leftBound = qMax(layout[i - 1], gridRect.left());
            qreal rightBound = qMin(layout[i], gridRect.right());
            rectItem->setRect(leftBound, gridRect.top(), rightBound - leftBound, gridRect.height());
            if (rectItem->rect().width() <= 0.0)
                rectItem->setVisible(false);
            else
                rectItem->setVisible(true);
        }

        // check if the grid line and the axis tick should be shown
        qreal x = gridItem->line().p1().x();
        if (x < gridRect.left() || x > gridRect.right()) {
            gridItem->setVisible(false);
            tickItem->setVisible(false);
        } else {
            gridItem->setVisible(true);
            tickItem->setVisible(true);
        }

    }

    //begin/end grid line in case labels between
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

QSizeF HorizontalAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    QSizeF sh(0,0);

    if (axis()->titleText().isEmpty() || !titleItem()->isVisible())
        return sh;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF titleRect = textBoundingRect(axis()->titleFont(), "...");
        sh = QSizeF(titleRect.width(), titleRect.height() + (titlePadding() * 2));
        break;
    }
    case Qt::MaximumSize:
    case Qt::PreferredSize: {
        QRectF titleRect = textBoundingRect(axis()->titleFont(), axis()->titleText());
        sh = QSizeF(titleRect.width(), titleRect.height() + (titlePadding() * 2));
        break;
    }
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
