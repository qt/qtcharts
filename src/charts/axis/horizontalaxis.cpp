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

#include <private/horizontalaxis_p.h>
#include <private/qabstractaxis_p.h>
#include <private/chartpresenter_p.h>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

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

    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem *>(arrow.at(0));

    if (axis()->alignment() == Qt::AlignTop)
        arrowItem->setLine(gridRect.left(), axisRect.bottom(), gridRect.right(), axisRect.bottom());
    else if (axis()->alignment() == Qt::AlignBottom)
        arrowItem->setLine(gridRect.left(), axisRect.top(), gridRect.right(), axisRect.top());

    qreal width = 0;
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
    }

    if (layout.isEmpty() && axis()->type() == QAbstractAxis::AxisTypeLogValue)
        return;

    QList<QGraphicsItem *> lines = gridItems();
    QList<QGraphicsItem *> shades = shadeItems();

    for (int i = 0; i < layout.size(); ++i) {
        //items
        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem*>(arrow.at(i + 1));
        QGraphicsTextItem *labelItem = static_cast<QGraphicsTextItem *>(labels.at(i));

        //grid line
        gridItem->setLine(layout[i], gridRect.top(), layout[i], gridRect.bottom());

        //label text wrapping
        QString text = labelList.at(i);
        QRectF boundingRect;
        // don't truncate empty labels
        if (text.isEmpty()) {
            labelItem->setHtml(text);
        } else  {
            qreal labelWidth = axisRect.width() / layout.count() - (2 * labelPadding());
            QString truncatedText = ChartPresenter::truncatedText(axis()->labelsFont(), text,
                                                                  axis()->labelsAngle(),
                                                                  labelWidth,
                                                                  availableSpace, boundingRect);
            labelItem->setTextWidth(ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                     truncatedText).width());
            labelItem->setHtml(truncatedText);
        }

        //label transformation origin point
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        qreal heightDiff = rect.height() - boundingRect.height();
        qreal widthDiff = rect.width() - boundingRect.width();

        //ticks and label position
        if (axis()->alignment() == Qt::AlignTop) {
            labelItem->setPos(layout[i] - center.x(), axisRect.bottom() - rect.height() + (heightDiff / 2.0) - labelPadding());
            tickItem->setLine(layout[i], axisRect.bottom(), layout[i], axisRect.bottom() - labelPadding());
        } else if (axis()->alignment() == Qt::AlignBottom) {
            labelItem->setPos(layout[i] - center.x(), axisRect.top() - (heightDiff / 2.0) + labelPadding());
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
        if ((labelItem->pos().x() < width && labelItem->toPlainText() == ellipsis) || forceHide ||
            (labelItem->pos().x() + (widthDiff / 2.0)) < (axisRect.left() - 1.0) ||
            (labelItem->pos().x() + (widthDiff / 2.0) - 1.0) > axisRect.right()) {
            labelItem->setVisible(false);
        } else {
            labelItem->setVisible(true);
            width = boundingRect.width() + labelItem->pos().x();
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
                leftBound = gridRect.left();
                rightBound = layout[0];
            } else {
                leftBound = layout[i];
                if (i == layout.size() - 1)
                    rightBound = gridRect.right();
                else
                    rightBound = qMin(layout[i + 1], gridRect.right());
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
        QRectF titleRect = ChartPresenter::textBoundingRect(axis()->titleFont(),
                                                            QStringLiteral("..."));
        sh = QSizeF(titleRect.width(), titleRect.height() + (titlePadding() * 2.0));
        break;
    }
    case Qt::MaximumSize:
    case Qt::PreferredSize: {
        QRectF titleRect = ChartPresenter::textBoundingRect(axis()->titleFont(), axis()->titleText());
        sh = QSizeF(titleRect.width(), titleRect.height() + (titlePadding() * 2.0));
        break;
    }
    default:
        break;
    }

    return sh;
}

QT_CHARTS_END_NAMESPACE
