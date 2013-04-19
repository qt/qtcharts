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

#include "boxplotchartitem_p.h"
#include "qboxplotseries_p.h"
#include "bar_p.h"
#include "qboxset_p.h"
#include "qabstractbarseries_p.h"
#include "qboxset.h"
#include "boxwhiskers_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BoxPlotChartItem::BoxPlotChartItem(QBoxPlotSeries *series, QGraphicsItem* item) :
    ChartItem(series->d_func(), item),
    m_series(series),
    m_animation(0),
    m_animate(0)
{
    connect(series, SIGNAL(boxsetsRemoved(QList<QBoxSet*>)), this, SLOT(handleBoxsetRemove(QList<QBoxSet*>)));
    connect(series->d_func(), SIGNAL(restructuredBoxes()), this, SLOT(handleDataStructureChanged()));
    connect(series->d_func(), SIGNAL(updatedLayout()), this, SLOT(handleLayoutChanged()));
    connect(series->d_func(), SIGNAL(updatedBoxes()), this, SLOT(handleUpdatedBars()));
    connect(series->d_func(), SIGNAL(updated()), this, SLOT(handleUpdatedBars()));
    // QBoxPlotSeriesPrivate calls handleDataStructureChanged(), don't do it here
    setZValue(ChartPresenter::BoxPlotSeriesZValue);
}

BoxPlotChartItem::~BoxPlotChartItem()
{
    qDebug() << "BoxPlotChartItem::~BoxPlotChartItem() " << m_seriesIndex;
}

void BoxPlotChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //painter->setClipRect(QRectF(QPointF(0,0),domain()->size()));

    //qDebug() << "ALERT EMPTY: BoxPlotChartItem::paint";
}

void BoxPlotChartItem::setAnimation(BoxPlotAnimation *animation)
{
    //qDebug() << "BoxPlotChartItem::setAnimation :" << animation;

    m_animation = animation;
    if (m_animation) {
        foreach (BoxWhiskers *item, m_boxTable.values()) {
            m_animation->addBox(item);
        }
        handleDomainUpdated();
    }
}

void BoxPlotChartItem::handleDataStructureChanged()
{
    qDebug() << "BoxPlotChartItem::handleDataStructureChanged()";

    int setCount = m_series->count();

    for (int s = 0; s < setCount; s++) {
        QBoxSet *set = m_series->d_func()->boxsetAt(s);

        BoxWhiskers *boxWhiskersItem = m_boxTable.value(set);
        if (boxWhiskersItem == 0) {
            // Item is not yet created, make a box and add it to hash table
            boxWhiskersItem = new BoxWhiskers(domain(), this);
            m_boxTable.insert(set, boxWhiskersItem);

            // Set the decorative issues for the newly created box
            boxWhiskersItem->setBrush(m_series->brush());
            boxWhiskersItem->setPen(m_series->pen());
        }
        updateBoxGeometry(boxWhiskersItem, s);

        boxWhiskersItem->updateGeometry();

        if (m_animation)
            m_animation->addBox(boxWhiskersItem);
    }

    //
    handleDomainUpdated();
}

void BoxPlotChartItem::handleUpdatedBars()
{
    qDebug() << "BoxPlotChartItem::handleUpdatedBars()";

    foreach (BoxWhiskers *item, m_boxTable.values()) {
        item->setBrush(m_series->brush());
        item->setPen(m_series->pen());
    }
    // Override with QBoxSet specific settings
    foreach (QBoxSet *set, m_boxTable.keys()) {
        if (set->brush().style() != Qt::NoBrush)
            m_boxTable.value(set)->setBrush(set->brush());
        if (set->pen().style() != Qt::NoPen)
            m_boxTable.value(set)->setPen(set->pen());
    }
}

void BoxPlotChartItem::handleBoxsetRemove(QList<QBoxSet*> barSets)
{
    //qDebug() << "BoxPlotChartItem::handleBarsetRemove";

    foreach (QBoxSet *set, barSets) {
        BoxWhiskers *boxItem = m_boxTable.value(set);
        m_boxTable.remove(set);
        delete boxItem;
    }

    // We trust that series emits the restructuredBars, which handles restructuring
}

void BoxPlotChartItem::handleDomainUpdated()
{
    //qDebug() << "BoxPlotChartItem::handleDomainUpdated() domain()->size() = " << domain()->size();

    if ((domain()->size().width() <= 0) || (domain()->size().height() <= 0))
        return;

    // Set my bounding rect to same as domain size
    m_boundingRect.setRect(0.0, 0.0, domain()->size().width(), domain()->size().height());

    foreach (BoxWhiskers *item, m_boxTable.values()) {
        // Update the domain size for each BoxWhisker item
        item->setDomainSize(domain()->size());

        // If the animation is set, start the animation for each BoxWhisker item
        if (m_animation) {
            presenter()->startAnimation(m_animation->boxAnimation(item));
        }
    }
}

void BoxPlotChartItem::handleLayoutChanged()
{
    qDebug() << "BoxPlotChartItem::handleLayoutChanged";

    foreach (BoxWhiskers *item, m_boxTable.values()) {
        if (m_animation)
            m_animation->setAnimationStart(item);

        bool dirty = updateBoxGeometry(item, item->m_data.m_index);
        if (dirty && m_animation)
            presenter()->startAnimation(m_animation->boxChangeAnimation(item));
        else
            item->updateGeometry();
    }
}

QRectF BoxPlotChartItem::boundingRect() const
{
    return m_boundingRect;
}

void BoxPlotChartItem::initializeLayout()
{
    qDebug() << "ALERT EMPTY: BoxPlotChartItem::initializeLayout";
}

QVector<QRectF> BoxPlotChartItem::calculateLayout()
{
    qDebug() << "ALERT EMPTY: BoxPlotChartItem::calculateLayout()";

    return QVector<QRectF>();
}

bool BoxPlotChartItem::updateBoxGeometry(BoxWhiskers *box, int index)
{
    bool changed = false;

    QBoxSet *set = m_series->d_func()->boxsetAt(index);
    BoxWhiskersData &data = box->m_data;

    if ((data.m_lowerExtreme != set->at(0)) || (data.m_lowerQuartile != set->at(1)) ||
        (data.m_median != set->at(2)) || (data.m_upperQuartile != set->at(3)) || (data.m_upperExtreme != set->at(4)))
        changed = true;

    data.m_lowerExtreme = set->at(0);
    data.m_lowerQuartile = set->at(1);
    data.m_median = set->at(2);
    data.m_upperQuartile = set->at(3);
    data.m_upperExtreme = set->at(4);
    data.m_index = index;
    data.m_boxItems = m_series->count();

    data.m_maxX = domain()->maxX();
    data.m_minX = domain()->minX();
    data.m_maxY = domain()->maxY();
    data.m_minY = domain()->minY();

    data.m_seriesIndex = m_seriesIndex;
    data.m_seriesCount = m_seriesCount;

    return changed;
}

#include "moc_boxplotchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
