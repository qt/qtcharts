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

#include "chartcategoriesaxisx_p.h"
#include "chartpresenter_p.h"
#include "qbarcategoriesaxis_p.h"
#include <QDebug>
#include <qmath.h>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartCategoriesAxisX::ChartCategoriesAxisX(QBarCategoriesAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter),
m_categoriesAxis(axis)
{

}

ChartCategoriesAxisX::~ChartCategoriesAxisX()
{
}

QVector<qreal> ChartCategoriesAxisX::calculateLayout() const
{
    int count = m_categoriesAxis->d_ptr->count();

    Q_ASSERT(count>=1);

    QVector<qreal> points;
    points.resize(count+2);

    const qreal delta = m_rect.width()/(count);
    qreal offset =-m_min-0.5;

    if(offset<=0) {
        offset = int(offset * m_rect.width()/(m_max - m_min))%int(delta) + delta;
    }
    else {
        offset = int(offset * m_rect.width()/(m_max - m_min))%int(delta);
    }

    points[0] = m_rect.left();
    points[count+1] = m_rect.right();

    for (int i = 0; i < count; ++i) {
        qreal x = offset + i * delta + m_rect.left();
        points[i+1] = x;
    }
    return points;
}

QStringList ChartCategoriesAxisX::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result;
    qreal d = (m_max - m_min)/m_rect.width();
    for (int i = 0;i < layout.count()-1; ++i) {
        qreal x = qFloor((((layout[i+1] + layout[i])/2-m_rect.left())*d + m_min+0.5));
        if ((x < m_categoriesAxis->categories().count()) && (x >= 0)) {
            result << m_categoriesAxis->categories().at(x);
        }
        else {
            // No label for x coordinate
            result << "";
        }
    }
    result << "";
    return result;
}


void ChartCategoriesAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    m_minWidth = 0;
    m_minHeight = 0;

    if(layout.isEmpty()) return;

    QStringList ticksList = createCategoryLabels(layout);

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_axis->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    const qreal delta = m_rect.width()/(m_categoriesAxis->d_ptr->count());

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine(m_rect.left(), m_rect.bottom(), m_rect.right(), m_rect.bottom());

    qreal width = m_rect.left();
    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(layout[i], m_rect.top(), layout[i], m_rect.bottom());
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
        labelItem->setText(ticksList.at(i));
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        if(i==0){
            labelItem->setPos(layout[i+1] - (delta)/2 - center.x(), m_rect.bottom() + label_padding);
        }else{
            labelItem->setPos(layout[i] + (delta)/2 - center.x(), m_rect.bottom() + label_padding);
        }

        if(labelItem->pos().x()<=width || labelItem->pos().x()+ rect.width()>m_rect.right()) {
            labelItem->setVisible(false);
        }
        else {
            labelItem->setVisible(true);
            width=rect.width()+labelItem->pos().x();
        }

        m_minWidth+=rect.width();
        m_minHeight=qMax(rect.height()+label_padding,m_minHeight);

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(layout[i-1],m_rect.top(),layout[i]-layout[i-1],m_rect.height());
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        lineItem->setLine(layout[i],m_rect.bottom(),layout[i],m_rect.bottom()+5);
    }
}

void ChartCategoriesAxisX::handleAxisUpdated()
{
    if(m_categoriesAxis->categories()!=m_categories)
    {
        m_categories=m_categoriesAxis->categories();
        if(ChartAxis::layout().count()==m_categoriesAxis->d_ptr->count()+2) updateGeometry();
    }
    ChartAxis::handleAxisUpdated();
}

QTCOMMERCIALCHART_END_NAMESPACE
