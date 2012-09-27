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

#include "horizontalaxis_p.h"
#include "qabstractaxis.h"
#include <QFontMetrics>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalAxis::HorizontalAxis(QAbstractAxis *axis, ChartPresenter *presenter,bool intervalAxis):ChartAxis(axis,presenter,intervalAxis)
{
}

HorizontalAxis::~HorizontalAxis()
{
}

void HorizontalAxis::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    if(layout.isEmpty()) return;

    QStringList ticksList = labels();

    QList<QGraphicsItem *> lines = lineItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> axis = arrowItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    const QRectF& axisRect = axisGeometry();
    const QRectF& gridRect = gridGeometry();

    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem*>(axis.at(0));

    if (alignment()==Qt::AlignTop)
        arrowItem->setLine(gridRect.left(), axisRect.bottom(), gridRect.right(), axisRect.bottom());
    else if(alignment()==Qt::AlignBottom)
        arrowItem->setLine(gridRect.left(), axisRect.top(), gridRect.right(), axisRect.top());

    qreal width = 0;

    for (int i = 0; i < layout.size(); ++i) {

        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));

        //grid line
        gridItem->setLine(layout[i], gridRect.top(), layout[i], gridRect.bottom());

        //label text
        labelItem->setText(ticksList.at(i));
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        //ticks and label position
        if (alignment()==Qt::AlignTop){
            labelItem->setPos(layout[i] - center.x(), axisRect.bottom() - rect.height() - labelPadding());
            tickItem->setLine(layout[i],axisRect.bottom(),layout[i],axisRect.bottom() - labelPadding());
        }else if(alignment()==Qt::AlignBottom){
            labelItem->setPos(layout[i] - center.x(), axisRect.top() + labelPadding());
            tickItem->setLine(layout[i],axisRect.top(),layout[i],axisRect.top() + labelPadding());
        }

        if(intervalAxis()&& i+1!=layout.size()) {
            const qreal delta = (layout[i+1] - layout[i])/2;
            labelItem->setPos(layout[i] + delta - center.x(), labelItem->pos().y());
        }

        //overlap detection
        if(labelItem->pos().x() <= width ||
            labelItem->pos().x() < axisRect.left() ||
            labelItem->pos().x() + rect.width() > axisRect.right()) {
            labelItem->setVisible(false);
            gridItem->setVisible(false);
            tickItem->setVisible(false);
        }
        else {
            labelItem->setVisible(true);
            gridItem->setVisible(true);
            tickItem->setVisible(true);
            width=rect.width()+labelItem->pos().x();
        }

        //shades
        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(layout[i-1],gridRect.top(),layout[i]-layout[i-1],gridRect.height());
        }

        // check if the grid line and the axis tick should be shown
        qreal x = gridItem->line().p1().x();
        if (x < gridRect.left() || x > gridRect.right()) {
              gridItem->setVisible(false);
              tickItem->setVisible(false);
              if( intervalAxis() && ( labelItem->pos().x() < gridRect.left() || labelItem->pos().x() + rect.width() > gridRect.right()))
                  labelItem->setVisible(false);
        }

    }

    //begin/end grid line in case labels between
    if(intervalAxis()) {
        QGraphicsLineItem *gridLine;
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size()));
        gridLine->setLine(gridRect.right(), gridRect.top(), gridRect.right(), gridRect.bottom());
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size()+1));
        gridLine->setLine(gridRect.left(), gridRect.top(), gridRect.left(), gridRect.bottom());
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
