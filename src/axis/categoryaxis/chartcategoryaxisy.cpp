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

#include "chartcategoryaxisy_p.h"
#include "qcategoryaxis.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartCategoryAxisY::ChartCategoryAxisY(QAbstractAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter)
{
}

ChartCategoryAxisY::~ChartCategoryAxisY()
{
}

QVector<qreal> ChartCategoryAxisY::calculateLayout() const
{
    QCategoryAxis *axis = qobject_cast<QCategoryAxis *>(m_chartAxis);
    int tickCount = axis->categoriesLabels().count() + 1;
    QVector<qreal> points;

    if (tickCount < 2)
        return points;

    qreal range = axis->max() - axis->min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = m_rect.height() / range;
        for (int i = 0; i < tickCount; ++i)
            if (i < tickCount - 1) {
                int y = -(axis->startValue(axis->categoriesLabels().at(i)) - axis->min()) * scale + m_rect.bottom();
                points[i] = y;
            } else {
                int y = -(axis->endValue(axis->categoriesLabels().at(i - 1)) - axis->min())  * scale + m_rect.bottom();
                points[i] = y;
            }
    }

    return points;
}

void ChartCategoryAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();
    m_minWidth = 0;
    m_minHeight = 0;

    if(layout.isEmpty()) {
        return;
    }

    QCategoryAxis *categoryAxis = qobject_cast<QCategoryAxis *>(m_chartAxis);
    QStringList ticksList = categoryAxis->categoriesLabels();

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    for (int i = 0; i < labels.count(); i++) {
        labels.at(i)->setVisible(false);
    }

    // axis base line
    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine(m_rect.left() , m_rect.top(), m_rect.left(), m_rect.bottom());

    for (int i = 0; i < layout.size(); ++i) {

        // label items
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
        if (i < ticksList.count()) {
            labelItem->setText(ticksList.at(i));
        }
        const QRectF& rect = labelItem->boundingRect();

        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        if (i < layout.size() - 1)
            labelItem->setPos(m_rect.left() - rect.width() - label_padding , layout[i] + (layout[i + 1] - layout[i]) / 2 - center.y());
        else
            labelItem->setPos(m_rect.left() - rect.width() - label_padding , layout[i]-center.y());

        // check if the label should be shown
        if (labelItem->pos().y() + center.y() < m_rect.top() || labelItem->pos().y() + center.y() > m_rect.bottom())
            labelItem->setVisible(false);
        else
            labelItem->setVisible(true);

        m_minWidth=qMax(rect.width()+label_padding,m_minWidth);
        m_minHeight+=rect.height();

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(m_rect.left(),layout[i],m_rect.width(),layout[i-1]-layout[i]);
        }

        // grid lines and axis line ticks
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setPos(m_rect.left(), layout[i]);
        lineItem->setLine(0, 0, m_rect.width(), 0);

        QGraphicsLineItem *tickLineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        tickLineItem->setPos(m_rect.left(), layout[i]);
        tickLineItem->setLine(-5, 0, 0, 0);

        // check if the grid line and the axis tick should be shown
        if (lineItem->pos().y() < m_rect.top() || lineItem->pos().y() > m_rect.bottom()) {
            lineItem->setVisible(false);
            tickLineItem->setVisible(false);
        } else {
            lineItem->setVisible(true);
            tickLineItem->setVisible(true);
        }
    }

}

void ChartCategoryAxisY::handleAxisUpdated()
{
    updateGeometry();
    ChartAxis::handleAxisUpdated();
}

QTCOMMERCIALCHART_END_NAMESPACE
