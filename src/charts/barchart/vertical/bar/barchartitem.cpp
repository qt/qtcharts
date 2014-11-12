/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/barchartitem_p.h>
#include <private/bar_p.h>
#include <private/qabstractbarseries_p.h>
#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>

QT_CHARTS_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    AbstractBarChartItem(series, item)
{
    connect(series, SIGNAL(labelsPositionChanged(QAbstractBarSeries::LabelsPosition)),
            this, SLOT(handleLabelsPositionChanged()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(positionLabels()));
}

void BarChartItem::initializeLayout()
{
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
    qreal barWidth = m_series->d_func()->barWidth();

    m_layout.clear();
    for(int category = 0; category < categoryCount; category++) {
        for (int set = 0; set < setCount; set++) {
            QRectF rect;
            QPointF topLeft;
            QPointF bottomRight;

            if (domain()->type() == AbstractDomain::XLogYDomain || domain()->type() == AbstractDomain::LogXLogYDomain) {
                topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + set/setCount * barWidth, domain()->minY()), m_validData);
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set + 1)/setCount * barWidth, domain()->minY()), m_validData);
            } else {
                topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + set/setCount * barWidth, 0), m_validData);
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set + 1)/setCount * barWidth, 0), m_validData);
            }

            if (!m_validData)
                 return;
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            m_layout.append(rect.normalized());
        }
    }
}

QVector<QRectF> BarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
    qreal barWidth = m_series->d_func()->barWidth();

    for(int category = 0; category < categoryCount; category++) {
        for (int set = 0; set < setCount; set++) {
            qreal value = m_series->barSets().at(set)->at(category);
            QRectF rect;
            QPointF topLeft = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set)/(setCount) * barWidth, value), m_validData);
            QPointF bottomRight;
            if (domain()->type() == AbstractDomain::XLogYDomain || domain()->type() == AbstractDomain::LogXLogYDomain)
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set + 1)/(setCount) * barWidth, domain()->minY()), m_validData);
            else
                bottomRight = domain()->calculateGeometryPoint(QPointF(category - barWidth / 2 + (set + 1)/(setCount) * barWidth, 0), m_validData);

            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect.normalized());
        }
    }

    return layout;
}

void BarChartItem::handleLabelsPositionChanged()
{
    positionLabels();
}

void BarChartItem::positionLabels()
{
    for (int i = 0; i < m_layout.count(); i++) {
        QGraphicsTextItem *label = m_labels.at(i);
        qreal xPos = m_layout.at(i).center().x() - label->boundingRect().center().x();
        qreal yPos = 0;

        int offset = m_bars.at(i)->pen().width() / 2 + 2;
        if (m_series->labelsPosition() == QAbstractBarSeries::LabelsCenter)
            yPos = m_layout.at(i).center().y() - label->boundingRect().center().y();
        else if (m_series->labelsPosition() == QAbstractBarSeries::LabelsInsideEnd)
            yPos = m_layout.at(i).top() - offset;
        else if (m_series->labelsPosition() == QAbstractBarSeries::LabelsInsideBase)
            yPos = m_layout.at(i).bottom() - label->boundingRect().height() + offset;
        else if (m_series->labelsPosition() == QAbstractBarSeries::LabelsOutsideEnd)
            yPos = m_layout.at(i).top() - label->boundingRect().height() + offset;

        label->setPos(xPos, yPos);
        label->setZValue(zValue() + 1);
    }
}

#include "moc_barchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
