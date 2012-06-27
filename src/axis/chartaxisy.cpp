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

#include "chartaxisy_p.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <QDebug>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAxisY::ChartAxisY(QAbstractAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter)
{
}

ChartAxisY::~ChartAxisY()
{
}

QVector<qreal> ChartAxisY::calculateLayout() const
{
    Q_ASSERT(m_ticksCount>=2);

    QVector<qreal> points;
    points.resize(m_ticksCount);

    const qreal deltaY = m_rect.height()/(m_ticksCount-1);
    for (int i = 0; i < m_ticksCount; ++i) {
        int y = i * -deltaY + m_rect.bottom();
        points[i] = y;
    }

    return points;
}

void ChartAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();
    m_minWidth = 0;
    m_minHeight = 0;

    if(layout.isEmpty()) return;

    QStringList ticksList;

    bool categories = createLabels(ticksList,m_min,m_max,layout.size());

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_axis->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    qreal height =  2*m_rect.bottom();

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine(m_rect.left() , m_rect.top(), m_rect.left(), m_rect.bottom());

    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(m_rect.left() , layout[i], m_rect.right(), layout[i]);
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));

        if (!categories || i<1) {
            labelItem->setText(ticksList.at(i));
            const QRectF& rect = labelItem->boundingRect();

            QPointF center = rect.center();
            labelItem->setTransformOriginPoint(center.x(), center.y());
            labelItem->setPos(m_rect.left() - rect.width() - label_padding , layout[i]-center.y());

            if(labelItem->pos().y()+rect.height()>height) {
                labelItem->setVisible(false);
                lineItem->setVisible(false);
            }
            else {
                labelItem->setVisible(true);
                lineItem->setVisible(true);
                height=labelItem->pos().y();
            }

            m_minWidth=qMax(rect.width()+label_padding,m_minWidth);
            m_minHeight+=rect.height();
        }
        else {
            labelItem->setText(ticksList.at(i));
            const QRectF& rect = labelItem->boundingRect();
            m_minWidth=qMax(rect.width(),m_minWidth);
            m_minHeight+=rect.height();
            QPointF center = rect.center();
            labelItem->setTransformOriginPoint(center.x(), center.y());
            labelItem->setPos(m_rect.left() - rect.width() - label_padding , layout[i] - (layout[i] - layout[i-1])/2 -center.y());
        }

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(m_rect.left(),layout[i],m_rect.width(),layout[i-1]-layout[i]);
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        lineItem->setLine(m_rect.left()-5,layout[i],m_rect.left(),layout[i]);
    }
}


QTCOMMERCIALCHART_END_NAMESPACE
