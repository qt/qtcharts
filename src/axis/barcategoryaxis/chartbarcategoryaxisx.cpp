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

#include "chartbarcategoryaxisx_p.h"
#include "chartpresenter_p.h"
#include "qbarcategoryaxis_p.h"
#include <QFontMetrics>
#include <QDebug>
#include <qmath.h>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBarCategoryAxisX::ChartBarCategoryAxisX(QBarCategoryAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter),
m_categoriesAxis(axis)
{

}

ChartBarCategoryAxisX::~ChartBarCategoryAxisX()
{
}

QVector<qreal> ChartBarCategoryAxisX::calculateLayout() const
{
    int count = m_categoriesAxis->d_ptr->count();

    Q_ASSERT(count>=1);

    QVector<qreal> points;
    points.resize(count+2);

    QRectF rect = presenter()->chartsGeometry();

    const qreal delta = rect.width()/(count);
    qreal offset =-m_min-0.5;

    if(delta<1) return points;

    if(offset<=0) {
        offset = int(offset * rect.width()/(m_max - m_min))%int(delta) + delta;
    }
    else {
        offset = int(offset * rect.width()/(m_max - m_min))%int(delta);
    }

    points[0] = rect.left();
    points[count+1] = rect.right();

    for (int i = 0; i < count; ++i) {
        qreal x = offset + i * delta + rect.left();
        points[i+1] = x;
    }
    return points;
}

QStringList ChartBarCategoryAxisX::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result;
    QRectF rect = presenter()->chartsGeometry();
    qreal d = (m_max - m_min)/rect.width();
    for (int i = 0;i < layout.count()-1; ++i) {
        qreal x = qFloor((((layout[i+1] + layout[i])/2-rect.left())*d + m_min+0.5));
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


void ChartBarCategoryAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    if(layout.isEmpty()) return;

    QStringList ticksList = createCategoryLabels(layout);

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    QRectF chartRect = presenter()->chartsGeometry();

    const qreal delta =  chartRect.width()/(m_categoriesAxis->d_ptr->count());

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine( chartRect.left(),  chartRect.bottom(),  chartRect.right(),  chartRect.bottom());

    qreal width =  chartRect.left();
    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(layout[i],  chartRect.top(), layout[i],  chartRect.bottom());
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
        labelItem->setText(ticksList.at(i));
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        if(i==0){
            labelItem->setPos(layout[i+1] - (delta)/2 - center.x(),  chartRect.bottom() + label_padding);
        }else{
            labelItem->setPos(layout[i] + (delta)/2 - center.x(),  chartRect.bottom() + label_padding);
        }

        if(labelItem->pos().x()<=width || labelItem->pos().x()+ rect.width()> chartRect.right()) {
            labelItem->setVisible(false);
        }
        else {
            labelItem->setVisible(true);
            width=rect.width()+labelItem->pos().x();
        }

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(layout[i-1], chartRect.top(),layout[i]-layout[i-1], chartRect.height());
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        lineItem->setLine(layout[i], chartRect.bottom(),layout[i], chartRect.bottom()+5);
    }
}

void ChartBarCategoryAxisX::handleAxisUpdated()
{
    if(m_categoriesAxis->categories()!=m_categories)
    {
        m_categories=m_categoriesAxis->categories();
        if(ChartAxis::layout().count()==m_categoriesAxis->d_ptr->count()+2) updateGeometry();
    }
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartBarCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_font);
    QSizeF sh;
    QSizeF base = ChartAxis::sizeHint(which, constraint);
    QStringList ticksList = createCategoryLabels(ChartAxis::layout());
    qreal width=0;
    qreal height=0;

      switch (which) {
        case Qt::MinimumSize:
            width = fn.boundingRect("...").width();
            height = fn.height()+label_padding;
            width=qMax(width,base.width());
            height+=base.height();
            sh = QSizeF(width,height);
            break;
        case Qt::PreferredSize:{

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                width+=rect.width();
                height=qMax(rect.height()+label_padding,height);
            }
            width=qMax(width,base.width());
            height+=base.height();
            sh = QSizeF(width,height);
            break;
        }
        default:
          break;
      }

      return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
