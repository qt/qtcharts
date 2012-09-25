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

#include "chartvalueaxisy_p.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "qvalueaxis.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartValueAxisY::ChartValueAxisY(QAbstractAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter),
    m_tickCount(0)
{
}

ChartValueAxisY::~ChartValueAxisY()
{
}

QVector<qreal> ChartValueAxisY::calculateLayout() const
{
    Q_ASSERT(m_tickCount>=2);

    QVector<qreal> points;
    points.resize(m_tickCount);

    const qreal deltaY = m_gridRect.height()/(m_tickCount-1);
    for (int i = 0; i < m_tickCount; ++i) {
        int y = i * -deltaY + m_gridRect.bottom();
        points[i] = y;
    }

    return points;
}

void ChartValueAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();

    if(layout.isEmpty()) return;

    QStringList ticksList = createNumberLabels(m_min,m_max,layout.size());

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    qreal height = m_axisRect.bottom();

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    //lineItem->setLine( m_gridRect.left() ,  m_gridRect.top(),  m_gridRect.left(),  m_gridRect.bottom());

    if (m_chartAxis->alignment()==Qt::AlignLeft)
        lineItem->setLine( m_axisRect.right() ,  m_gridRect.top(),  m_axisRect.right(),  m_gridRect.bottom());
    else if(m_chartAxis->alignment()==Qt::AlignRight)
        lineItem->setLine( m_axisRect.left() ,   m_gridRect.top(),  m_axisRect.left(),  m_gridRect.bottom());

    QFontMetrics fn(m_font);

    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine( m_gridRect.left() , layout[i],  m_gridRect.right(), layout[i]);
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));

        QString text = ticksList.at(i);

        if (fn.boundingRect(text).width() >  m_axisRect.right() - m_axisRect.left() - labelPadding() )
        {
            QString label = text + "...";
            while (fn.boundingRect(label).width() > m_axisRect.right() - m_axisRect.left() - labelPadding() && label.length() > 3)
                label.remove(label.length() - 4, 1);
            labelItem->setText(label);
        }else{
            labelItem->setText(text);
        }

        const QRectF& rect = labelItem->boundingRect();

        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        //labelItem->setPos( m_gridRect.left() - rect.width() - labelPadding() , layout[i]-center.y());

        if (m_chartAxis->alignment()==Qt::AlignLeft)
            labelItem->setPos( m_axisRect.right() - rect.width() - labelPadding() , layout[i]-center.y());
        else if(m_chartAxis->alignment()==Qt::AlignRight)
            labelItem->setPos( m_axisRect.left() + labelPadding() , layout[i]-center.y());

        if(labelItem->pos().y() + rect.height() > height ||
                labelItem->pos().y() < m_axisRect.top()) {
            labelItem->setVisible(false);
            lineItem->setVisible(false);
        }else{
            labelItem->setVisible(true);
            lineItem->setVisible(true);
            height=labelItem->pos().y();
        }

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect( m_gridRect.left(),layout[i], m_gridRect.width(),layout[i-1]-layout[i]);
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        // lineItem->setLine( m_gridRect.left()-5,layout[i], m_gridRect.left(),layout[i]);

        if (m_chartAxis->alignment()==Qt::AlignLeft)
            lineItem->setLine( m_axisRect.right()- labelPadding(),layout[i], m_axisRect.right(),layout[i]);
        else if(m_chartAxis->alignment()==Qt::AlignRight)
            lineItem->setLine( m_axisRect.left(),layout[i], m_axisRect.left()+ labelPadding(),layout[i]);

    }
}

void ChartValueAxisY::handleAxisUpdated()
{
    //TODO:: fix this
    QValueAxis* axis = qobject_cast<QValueAxis*>(m_chartAxis);
    m_tickCount = axis->tickCount();
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartValueAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_font);
    QSizeF sh;
    QSizeF base = ChartAxis::sizeHint(which, constraint);
    QStringList ticksList = createNumberLabels(m_min,m_max,m_tickCount);
    qreal width=0;
    qreal height=0;

    switch (which) {
    case Qt::MinimumSize: {
        int count = qMax(ticksList.first().count() , ticksList.last().count());
        width=fn.averageCharWidth()*count+labelPadding();
        height=fn.height();
        height=qMax(height,base.height());
        width+=base.width();
        sh = QSizeF(width,height);
        break;
    }
    case Qt::PreferredSize:
    {
        for (int i = 0; i < ticksList.size(); ++i)
        {
            width=qMax(qreal(fn.averageCharWidth()*ticksList.at(i).count())+labelPadding(),width);
            height+=fn.height();
        }
        height=qMax(height,base.height());
        width+=base.width();
        sh = QSizeF(width,height);
        break;
    }
    default:
        break;
    }
    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
