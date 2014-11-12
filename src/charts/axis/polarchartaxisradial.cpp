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

#include <private/polarchartaxisradial_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <private/qabstractaxis_p.h>
#include <private/linearrowitem_p.h>
#include <QtGui/QTextDocument>

QT_CHARTS_BEGIN_NAMESPACE

PolarChartAxisRadial::PolarChartAxisRadial(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : PolarChartAxis(axis, item, intervalAxis)
{
}

PolarChartAxisRadial::~PolarChartAxisRadial()
{
}

void PolarChartAxisRadial::updateGeometry()
{
    const QVector<qreal> &layout = this->layout();
    if (layout.isEmpty())
        return;

    createAxisLabels(layout);
    QStringList labelList = labels();
    QPointF center = axisGeometry().center();
    QList<QGraphicsItem *> arrowItemList = arrowItems();
    QList<QGraphicsItem *> gridItemList = gridItems();
    QList<QGraphicsItem *> labelItemList = labelItems();
    QList<QGraphicsItem *> shadeItemList = shadeItems();
    QGraphicsTextItem* title = titleItem();
    qreal radius = axisGeometry().height() / 2.0;

    QLineF line(center, center + QPointF(0, -radius));
    QGraphicsLineItem *axisLine = static_cast<QGraphicsLineItem *>(arrowItemList.at(0));
    axisLine->setLine(line);

    QRectF previousLabelRect;
    bool firstShade = true;
    bool nextTickVisible = false;
    if (layout.size())
        nextTickVisible = !(layout.at(0) < 0.0 || layout.at(0) > radius);

    for (int i = 0; i < layout.size(); ++i) {
        qreal radialCoordinate = layout.at(i);

        QGraphicsEllipseItem *gridItem = static_cast<QGraphicsEllipseItem *>(gridItemList.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem *>(arrowItemList.at(i + 1));
        QGraphicsTextItem *labelItem = static_cast<QGraphicsTextItem *>(labelItemList.at(i));
        QGraphicsPathItem *shadeItem = 0;
        if (i == 0)
            shadeItem = static_cast<QGraphicsPathItem *>(shadeItemList.at(0));
        else if (i % 2)
            shadeItem = static_cast<QGraphicsPathItem *>(shadeItemList.at((i / 2) + 1));

        // Ignore ticks outside valid range
        bool currentTickVisible = nextTickVisible;
        if ((i == layout.size() - 1)
            || layout.at(i + 1) < 0.0
            || layout.at(i + 1) > radius) {
            nextTickVisible = false;
        } else {
            nextTickVisible = true;
        }

        qreal labelCoordinate = radialCoordinate;
        qreal labelVisible = currentTickVisible;
        qreal labelPad = labelPadding() / 2.0;
        if (intervalAxis()) {
            qreal farEdge;
            if (i == (layout.size() - 1))
                farEdge = radius;
            else
                farEdge = qMin(radius, layout.at(i + 1));

            // Adjust the labelCoordinate to show it if next tick is visible
            if (nextTickVisible)
                labelCoordinate = qMax(qreal(0.0), labelCoordinate);

            labelCoordinate = (labelCoordinate + farEdge) / 2.0;
            if (labelCoordinate > 0.0 && labelCoordinate < radius)
                labelVisible =  true;
            else
                labelVisible = false;
        }

        // Radial axis label
        if (axis()->labelsVisible() && labelVisible) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   labelList.at(i),
                                                                   axis()->labelsAngle());
            labelItem->setTextWidth(boundingRect.width());
            labelItem->setHtml(labelList.at(i));
            QRectF labelRect = labelItem->boundingRect();
            QPointF labelCenter = labelRect.center();
            labelItem->setTransformOriginPoint(labelCenter.x(), labelCenter.y());
            boundingRect.moveCenter(labelCenter);
            QPointF positionDiff(labelRect.topLeft() - boundingRect.topLeft());
            QPointF labelPoint = center;
            if (intervalAxis())
                labelPoint += QPointF(labelPad, -labelCoordinate - (boundingRect.height() / 2.0));
            else
                labelPoint += QPointF(labelPad, labelPad - labelCoordinate);
            labelRect.moveTopLeft(labelPoint);
            labelItem->setPos(labelRect.topLeft() + positionDiff);

            // Label overlap detection
            labelRect.setSize(boundingRect.size());
            if ((i && previousLabelRect.intersects(labelRect))
                 || !axisGeometry().contains(labelRect)) {
                labelVisible = false;
            } else {
                previousLabelRect = labelRect;
                labelVisible = true;
            }
        }

        labelItem->setVisible(labelVisible);
        if (!currentTickVisible) {
            gridItem->setVisible(false);
            tickItem->setVisible(false);
            if (shadeItem)
                shadeItem->setVisible(false);
            continue;
        }

        // Radial grid line
        QRectF gridRect;
        gridRect.setWidth(radialCoordinate * 2.0);
        gridRect.setHeight(radialCoordinate * 2.0);
        gridRect.moveCenter(center);

        gridItem->setRect(gridRect);
        gridItem->setVisible(true);

        // Tick
        QLineF tickLine(-tickWidth(), 0.0, tickWidth(), 0.0);
        tickLine.translate(center.rx(), gridRect.top());
        tickItem->setLine(tickLine);
        tickItem->setVisible(true);

        // Shades
        if (i % 2 || (i == 0 && !nextTickVisible)) {
            QPainterPath path;
            if (i == 0) {
                // If first tick is also the last, we need to custom fill the inner circle
                // or it won't get filled.
                QRectF innerCircle(0.0, 0.0, layout.at(0) * 2.0, layout.at(0) * 2.0);
                innerCircle.moveCenter(center);
                path.addEllipse(innerCircle);
            } else {
                QRectF otherGridRect;
                if (!nextTickVisible) { // Last visible tick
                    otherGridRect = axisGeometry();
                } else {
                    qreal otherGridRectDimension = layout.at(i + 1) * 2.0;
                    otherGridRect.setWidth(otherGridRectDimension);
                    otherGridRect.setHeight(otherGridRectDimension);
                    otherGridRect.moveCenter(center);
                }
                path.addEllipse(gridRect);
                path.addEllipse(otherGridRect);

                // Add additional shading in first visible shade item if there is a partial tick
                // to be filled at the center (log & category axes)
                if (firstShade) {
                    QGraphicsPathItem *specialShadeItem = static_cast<QGraphicsPathItem *>(shadeItemList.at(0));
                    if (layout.at(i - 1) > 0.0) {
                        QRectF innerCircle(0.0, 0.0, layout.at(i - 1) * 2.0, layout.at(i - 1) * 2.0);
                        innerCircle.moveCenter(center);
                        QPainterPath specialPath;
                        specialPath.addEllipse(innerCircle);
                        specialShadeItem->setPath(specialPath);
                        specialShadeItem->setVisible(true);
                    } else {
                        specialShadeItem->setVisible(false);
                    }
                }
            }
            shadeItem->setPath(path);
            shadeItem->setVisible(true);
            firstShade = false;
        }
    }

    // Title, along the 0 axis
    QString titleText = axis()->titleText();
    if (!titleText.isEmpty() && axis()->isTitleVisible()) {
        QRectF truncatedRect;
        title->setHtml(ChartPresenter::truncatedText(axis()->titleFont(), titleText, qreal(0.0),
                                                     radius, radius, truncatedRect));
        title->setTextWidth(truncatedRect.width());

        QRectF titleBoundingRect = title->boundingRect();
        QPointF titleCenter = titleBoundingRect.center();
        QPointF arrowCenter = axisLine->boundingRect().center();
        QPointF titleCenterDiff = arrowCenter - titleCenter;
        title->setPos(titleCenterDiff.x() - titlePadding() - (titleBoundingRect.height() / 2.0), titleCenterDiff.y());
        title->setTransformOriginPoint(titleCenter);
        title->setRotation(270.0);
    }

    QGraphicsLayoutItem::updateGeometry();
}

Qt::Orientation PolarChartAxisRadial::orientation() const
{
    return Qt::Vertical;
}

void PolarChartAxisRadial::createItems(int count)
{
     if (arrowItems().count() == 0) {
        // radial axis center line
        QGraphicsLineItem *arrow = new LineArrowItem(this, presenter()->rootItem());
        arrow->setPen(axis()->linePen());
        arrowGroup()->addToGroup(arrow);
    }

    QGraphicsTextItem *title = titleItem();
    title->setFont(axis()->titleFont());
    title->setDefaultTextColor(axis()->titleBrush().color());
    title->setHtml(axis()->titleText());

    for (int i = 0; i < count; ++i) {
        QGraphicsLineItem *arrow = new QGraphicsLineItem(presenter()->rootItem());
        QGraphicsEllipseItem *grid = new QGraphicsEllipseItem(presenter()->rootItem());
        QGraphicsTextItem *label = new QGraphicsTextItem(presenter()->rootItem());
        label->document()->setDocumentMargin(ChartPresenter::textMargin());
        arrow->setPen(axis()->linePen());
        grid->setPen(axis()->gridLinePen());
        label->setFont(axis()->labelsFont());
        label->setDefaultTextColor(axis()->labelsBrush().color());
        label->setRotation(axis()->labelsAngle());
        arrowGroup()->addToGroup(arrow);
        gridGroup()->addToGroup(grid);
        labelGroup()->addToGroup(label);
        if (gridItems().size() == 1 || (((gridItems().size() + 1) % 2) && gridItems().size() > 0)) {
            QGraphicsPathItem *shade = new QGraphicsPathItem(presenter()->rootItem());
            shade->setPen(axis()->shadesPen());
            shade->setBrush(axis()->shadesBrush());
            shadeGroup()->addToGroup(shade);
        }
    }
}

void PolarChartAxisRadial::handleArrowPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, arrowItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void PolarChartAxisRadial::handleGridPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, gridItems())
        static_cast<QGraphicsEllipseItem *>(item)->setPen(pen);
}

QSizeF PolarChartAxisRadial::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return QSizeF(-1.0, -1.0);
}

qreal PolarChartAxisRadial::preferredAxisRadius(const QSizeF &maxSize)
{
    qreal radius = maxSize.height() / 2.0;
    if (maxSize.width() < maxSize.height())
        radius = maxSize.width() / 2.0;
    return radius;
}

#include "moc_polarchartaxisradial_p.cpp"

QT_CHARTS_END_NAMESPACE
