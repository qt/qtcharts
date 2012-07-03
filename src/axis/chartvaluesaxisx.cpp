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

#include "chartvaluesaxisx_p.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QGraphicsLayout>
#include <QDebug>
#include <QFontMetrics>
#include <cmath>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartValuesAxisX::ChartValuesAxisX(QAbstractAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter)
{
}

ChartValuesAxisX::~ChartValuesAxisX()
{
}

QVector<qreal> ChartValuesAxisX::calculateLayout() const
{
    Q_ASSERT(m_ticksCount>=2);

    QVector<qreal> points;
    points.resize(m_ticksCount);

    const qreal deltaX = m_rect.width()/(m_ticksCount-1);
    for (int i = 0; i < m_ticksCount; ++i) {
        int x = i * deltaX + m_rect.left();
        points[i] = x;
    }
    return points;
}

void ChartValuesAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    m_minWidth = 0;
    m_minHeight = 0;

    if(layout.isEmpty()) return;

    QStringList ticksList;

    createNumberLabels(ticksList,m_min,m_max,layout.size());

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_axis->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine(m_rect.left(), m_rect.bottom(), m_rect.right(), m_rect.bottom());

    qreal width = 0;
    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(layout[i], m_rect.top(), layout[i], m_rect.bottom());
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
            labelItem->setText(ticksList.at(i));
            const QRectF& rect = labelItem->boundingRect();
            QPointF center = rect.center();
            labelItem->setTransformOriginPoint(center.x(), center.y());
            labelItem->setPos(layout[i] - center.x(), m_rect.bottom() + label_padding);

            if(labelItem->pos().x()<=width){
                labelItem->setVisible(false);
                lineItem->setVisible(false);
            }else{
                labelItem->setVisible(true);
                lineItem->setVisible(true);
                width=rect.width()+labelItem->pos().x();
            }
            m_minWidth+=rect.width();
            m_minHeight=qMax(rect.height(),m_minHeight);

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(layout[i-1],m_rect.top(),layout[i]-layout[i-1],m_rect.height());
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        lineItem->setLine(layout[i],m_rect.bottom(),layout[i],m_rect.bottom()+5);
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
