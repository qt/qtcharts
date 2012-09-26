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

#include "verticalaxis_p.h"
#include "qabstractaxis.h"
#include <QFontMetrics>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

VerticalAxis::VerticalAxis(QAbstractAxis *axis, ChartPresenter *presenter):ChartAxis(axis,presenter)
{

}

VerticalAxis::~VerticalAxis()
{

}

void VerticalAxis::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();

    if(layout.isEmpty()) return;

    QStringList labelList = labels();

    QList<QGraphicsItem *> lines = lineItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> axis = arrowItems();

    Q_ASSERT(labels.size() == labelList.size());
    Q_ASSERT(layout.size() == labelList.size());

    const QRectF& axisRect = axisGeometry();
    const QRectF& gridRect = gridGeometry();

    qreal height = axisRect.bottom();

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));

    if (alignment()==Qt::AlignLeft)
    lineItem->setLine( axisRect.right() , gridRect.top(), axisRect.right(), gridRect.bottom());
    else if(alignment()==Qt::AlignRight)
    lineItem->setLine( axisRect.left() , gridRect.top(), axisRect.left(), gridRect.bottom());

    QFontMetrics fn(font());

    for (int i = 0; i < layout.size(); ++i) {

        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));

        //grid line
        gridItem->setLine( gridRect.left() , layout[i], gridRect.right(), layout[i]);

        //label text
        QString text = labelList.at(i);
        if (fn.boundingRect(text).width() > axisRect.right() - axisRect.left() - labelPadding() )
        {
            QString label = text + "...";
            while (fn.boundingRect(label).width() > axisRect.right() - axisRect.left() - labelPadding() && label.length() > 3)
            label.remove(label.length() - 4, 1);
            labelItem->setText(label);
        }
        else {
            labelItem->setText(text);
        }
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        //ticks and label position
        if (alignment()==Qt::AlignLeft) {
            labelItem->setPos( axisRect.right() - rect.width() - labelPadding() , layout[i]-center.y());
            tickItem->setLine( axisRect.right()- labelPadding(),layout[i], axisRect.right(),layout[i]);
        }
        else if(alignment()==Qt::AlignRight) {
            labelItem->setPos( axisRect.left() + labelPadding() , layout[i]-center.y());
            tickItem->setLine( axisRect.left(),layout[i], axisRect.left()+ labelPadding(),layout[i]);
        }
        if(labelBetweenTicks()&& i+1!=layout.size()) {
            const qreal delta = (layout[i+1] - layout[i])/2;
            labelItem->setPos(labelItem->pos().x() , layout[i] + delta - center.y());
        }

        //overlap detection
        if(labelItem->pos().y() + rect.height() > height ||
            labelItem->pos().y() + rect.height() > axisRect.bottom() ||
            labelItem->pos().y() < axisRect.top()) {
            labelItem->setVisible(false);
            gridItem->setVisible(false);
            tickItem->setVisible(false);
        }
        else {
            labelItem->setVisible(true);
            gridItem->setVisible(true);
            height=labelItem->pos().y();
        }

        //shades
        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect( gridRect.left(),layout[i], gridRect.width(),layout[i-1]-layout[i]);
        }

        // check if the grid line and the axis tick should be shown
        qreal y = gridItem->line().p1().y();
        if (y < gridRect.top() || y > gridRect.bottom()) {
            gridItem->setVisible(false);
            tickItem->setVisible(false);
            if( labelBetweenTicks() && ( labelItem->pos().y() < gridRect.top() || labelItem->pos().y() + rect.height() > gridRect.bottom()))
            labelItem->setVisible(false);
        }

    }
    //begin/end grid line in case labels between
    if(labelBetweenTicks()) {
        QGraphicsLineItem *gridLine;
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size()));
        gridLine->setLine(gridRect.left(), gridRect.top(), gridRect.right(), gridRect.top());
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size()+1));
        gridLine->setLine(gridRect.left(), gridRect.bottom(), gridRect.right(), gridRect.bottom());
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
