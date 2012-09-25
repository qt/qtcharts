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

#include "chartvalueaxisx_p.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "qvalueaxis.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>
#include <QDebug>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartValueAxisX::ChartValueAxisX(QAbstractAxis *axis, ChartPresenter *presenter)
    : ChartAxis(axis, presenter),
      m_tickCount(0)
{
}

ChartValueAxisX::~ChartValueAxisX()
{
}

QVector<qreal> ChartValueAxisX::calculateLayout() const
{
    Q_ASSERT(m_tickCount >= 2);

    QVector<qreal> points;
    points.resize(m_tickCount);

    QRectF rect = presenter()->chartsGeometry();

    const qreal deltaX = rect.width() / (m_tickCount - 1);
    for (int i = 0; i < m_tickCount; ++i) {
        int x = i * deltaX + rect.left();
        points[i] = x;
    }
    return points;
}

void ChartValueAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    if (layout.isEmpty())
        return;

    QStringList ticksList = createNumberLabels(m_min, m_max, layout.size());

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    QRectF chartRrect = presenter()->chartsGeometry();

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    //    lineItem->setLine(chartRrect.left(), chartRrect.bottom(), chartRrect.right(), chartRrect.bottom());
    if (m_chartAxis->alternativePlacement())
        lineItem->setLine(chartRrect.left(), m_internalRect.top(), chartRrect.right(), m_internalRect.top());
    else
        lineItem->setLine(chartRrect.left(), m_internalRect.bottom(), chartRrect.right(), m_internalRect.bottom());

    qreal width = 0;
    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(layout[i], chartRrect.top(), layout[i], chartRrect.bottom());
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
        labelItem->setText(ticksList.at(i));
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        //            labelItem->setPos(layout[i] - center.x(), chartRrect.bottom() + label_padding);
        if (m_chartAxis->alternativePlacement())
            labelItem->setPos(layout[i] - center.x(), m_internalRect.top() - rect.height() - label_padding);
        else
            labelItem->setPos(layout[i] - center.x(), m_internalRect.bottom() + label_padding);
        if (labelItem->pos().x() <= width ||
            labelItem->pos().x() < m_rect.left() ||
            labelItem->pos().x() + rect.width() > m_rect.right()){
            labelItem->setVisible(false);
            lineItem->setVisible(false);
        } else {
            labelItem->setVisible(true);
            lineItem->setVisible(true);
            width = rect.width() + labelItem->pos().x();
        }

        if ((i + 1) % 2 && i > 1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i / 2 - 1));
            rectItem->setRect(layout[i - 1], chartRrect.top(), layout[i] - layout[i - 1], chartRrect.height());
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i + 1));
        //        lineItem->setLine(layout[i],chartRrect.bottom(),layout[i],chartRrect.bottom()+5);
        if (m_chartAxis->alternativePlacement())
            lineItem->setLine(layout[i], m_internalRect.top(), layout[i], m_internalRect.top() - 5);
        else
            lineItem->setLine(layout[i], m_internalRect.bottom(), layout[i], m_internalRect.bottom() + 5);
    }
}

void ChartValueAxisX::handleAxisUpdated()
{
    //TODO:: fix this
    QValueAxis* axis = qobject_cast<QValueAxis*>(m_chartAxis);
    if (m_tickCount != axis->tickCount()) {
        m_tickCount = axis->tickCount();
        presenter()->layout()->invalidate();
    }
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_font);
    QSizeF sh;

    QSizeF base = ChartAxis::sizeHint(which, constraint);
    QStringList ticksList = createNumberLabels(m_min, m_max, m_tickCount);
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        int count = qMax(ticksList.last().count(), ticksList.first().count());
        width = fn.averageCharWidth() * count;
        height = fn.height() + label_padding;
        width = qMax(width, base.width());
        height += base.height();
        sh = QSizeF(width, height);
        break;
        }
    case Qt::PreferredSize:
        for (int i = 0; i < ticksList.size(); ++i)
            width += fn.averageCharWidth() * ticksList.at(i).count();
        height = fn.height() + label_padding;
        width = qMax(width, base.width());
        height += base.height();
        sh = QSizeF(width, height);
        break;
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
