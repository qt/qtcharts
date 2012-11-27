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
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalAxis::HorizontalAxis(QAbstractAxis *axis, QGraphicsItem* item , bool intervalAxis)
    : ChartAxis(axis, item, intervalAxis)
{
}

HorizontalAxis::~HorizontalAxis()
{
}

void HorizontalAxis::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    if (layout.isEmpty())
        return;

    QStringList labelList = labels();

    QList<QGraphicsItem *> lines = lineItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> axis = arrowItems();
    QGraphicsSimpleTextItem* title = titleItem();

    Q_ASSERT(labels.size() == labelList.size());
    Q_ASSERT(layout.size() == labelList.size());

    const QRectF &axisRect = axisGeometry();
    const QRectF &gridRect = gridGeometry();

    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem *>(axis.at(0));

    if (alignment() == Qt::AlignTop)
        arrowItem->setLine(gridRect.left(), axisRect.bottom(), gridRect.right(), axisRect.bottom());
    else if (alignment() == Qt::AlignBottom)
        arrowItem->setLine(gridRect.left(), axisRect.top(), gridRect.right(), axisRect.top());

    qreal width = 0;
    QFontMetrics fn(font());

    //title

    if (!titleText().isNull()) {
        QFontMetrics fn(title->font());

        int size(0);

        size = gridRect.width();
        QString titleText = this->titleText();

        if (fn.boundingRect(titleText).width() > size) {
            QString string = titleText + "...";
            while (fn.boundingRect(string).width() > size && string.length() > 3)
                string.remove(string.length() - 4, 1);
            title->setText(string);
        } else {
            title->setText(titleText);
        }

        QPointF center = gridRect.center() - title->boundingRect().center();
        if (alignment() == Qt::AlignTop) {
            title->setPos(center.x(), axisRect.top());
        } else  if (alignment() == Qt::AlignBottom) {
            title->setPos(center.x(), axisRect.bottom() - title->boundingRect().height());
        }
    }

    for (int i = 0; i < layout.size(); ++i) {

        //items
        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem*>(axis.at(i + 1));
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem *>(labels.at(i));

        //grid line
        gridItem->setLine(layout[i], gridRect.top(), layout[i], gridRect.bottom());

        //label text wrapping
        if(intervalAxis()&& i+1!=layout.size()) {
            //wrapping in case of interval axis
            const qreal delta = layout[i+1] - layout[i];
            QString text = labelList.at(i);
            if (fn.boundingRect(text).width() + 1 > delta )
            {
                QString label = text + "...";
                while (fn.boundingRect(label).width() >= delta && label.length() > 3)
                label.remove(label.length() - 4, 1);
                labelItem->setText(label);
            }
            else {
                labelItem->setText(text);
            }
        }else{
            labelItem->setText(labelList.at(i));
        }

        //label transformation origin point
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        //ticks and label position
        if (alignment() == Qt::AlignTop) {
            labelItem->setPos(layout[i] - center.x(), axisRect.bottom() - rect.height() - labelPadding());
            tickItem->setLine(layout[i], axisRect.bottom(), layout[i], axisRect.bottom() - labelPadding());
        } else if (alignment() == Qt::AlignBottom) {
            labelItem->setPos(layout[i] - center.x(), axisRect.top() + labelPadding());
            tickItem->setLine(layout[i], axisRect.top(), layout[i], axisRect.top() + labelPadding());
        }

        //label in beetwen
        if(intervalAxis()&& i+1!=layout.size()) {
            const qreal delta = (layout[i+1] - layout[i])/2;
            labelItem->setPos(layout[i] + delta - center.x(), labelItem->pos().y());
        }

        //label overlap detection
        if(labelItem->pos().x() < width ||
            labelItem->pos().x() < axisRect.left() ||
            labelItem->pos().x() + rect.width() > axisRect.right()) {
            labelItem->setVisible(false);
        } else {
            labelItem->setVisible(true);
            width=rect.width()+labelItem->pos().x();
        }

        //shades
        if ((i + 1) % 2 && i > 1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem *>(shades.at(i / 2 - 1));
            rectItem->setRect(layout[i - 1], gridRect.top(), layout[i] - layout[i - 1], gridRect.height());
        }

        // check if the grid line and the axis tick should be shown
        qreal x = gridItem->line().p1().x();
        if (x < gridRect.left() || x > gridRect.right()) {
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
    QFontMetrics fn(titleFont());
    QSizeF sh(0,0);

    if (titleText().isNull() || !titleItem()->isVisible())
        return sh;

    switch (which) {
    case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width(), fn.height());
        break;
    case Qt::MaximumSize:
    case Qt::PreferredSize:
            sh = QSizeF(fn.boundingRect(axis()->titleText()).width(), fn.height());
        break;
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
