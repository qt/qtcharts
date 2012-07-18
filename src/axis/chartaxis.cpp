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

#include "chartaxis_p.h"
#include "qabstractaxis.h"
#include "qabstractaxis_p.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include "domain_p.h"
#include <QPainter>
#include <QDebug>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAxis::ChartAxis(QAbstractAxis *axis,ChartPresenter *presenter) : Chart(presenter),
    m_chartAxis(axis),
    m_labelsAngle(0),
    m_grid(new QGraphicsItemGroup(presenter->rootItem())),
    m_shades(new QGraphicsItemGroup(presenter->rootItem())),
    m_labels(new QGraphicsItemGroup(presenter->rootItem())),
    m_axis(new QGraphicsItemGroup(presenter->rootItem())),
    m_min(0),
    m_max(0),
    m_animation(0),
    m_minWidth(0),
    m_minHeight(0)
{
    //initial initialization
    m_axis->setZValue(ChartPresenter::AxisZValue);
    m_axis->setHandlesChildEvents(false);

    m_shades->setZValue(ChartPresenter::ShadesZValue);
    m_grid->setZValue(ChartPresenter::GridZValue);

    QObject::connect(m_chartAxis->d_ptr.data(),SIGNAL(updated()),this,SLOT(handleAxisUpdated()));

    QGraphicsSimpleTextItem item;
    m_font = item.font();
}

ChartAxis::~ChartAxis()
{
}

void ChartAxis::setAnimation(AxisAnimation* animation)
{
    m_animation=animation;
}

void ChartAxis::setLayout(QVector<qreal> &layout)
{
    m_layoutVector=layout;
}

void ChartAxis::createItems(int count)
{
    if (m_axis->children().size() == 0)
    m_axis->addToGroup(new AxisItem(this));
    for (int i = 0; i < count; ++i) {
        m_grid->addToGroup(new QGraphicsLineItem());
        m_labels->addToGroup(new QGraphicsSimpleTextItem());
        m_axis->addToGroup(new QGraphicsLineItem());
        if ((m_grid->childItems().size())%2 && m_grid->childItems().size()>2) m_shades->addToGroup(new QGraphicsRectItem());
    }
}

void ChartAxis::deleteItems(int count)
{
    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_axis->childItems();

    for (int i = 0; i < count; ++i) {
        if (lines.size()%2 && lines.size() > 1) delete(shades.takeLast());
        delete(lines.takeLast());
        delete(labels.takeLast());
        delete(axis.takeLast());
    }
}

void ChartAxis::updateLayout(QVector<qreal> &layout)
{
    int diff = m_layoutVector.size() - layout.size();

    if (diff>0) {
        deleteItems(diff);
    }
    else if (diff<0) {
        createItems(-diff);
    }

    if(diff<0) handleAxisUpdated();

    if (m_animation) {
          switch(presenter()->state()){
              case ChartPresenter::ZoomInState:
                  m_animation->setAnimationType(AxisAnimation::ZoomInAnimation);
                  m_animation->setAnimationPoint(presenter()->statePoint());
                  break;
              case ChartPresenter::ZoomOutState:
                  m_animation->setAnimationType(AxisAnimation::ZoomOutAnimation);
                  m_animation->setAnimationPoint(presenter()->statePoint());
                  break;
              case ChartPresenter::ScrollUpState:
              case ChartPresenter::ScrollLeftState:
                  m_animation->setAnimationType(AxisAnimation::MoveBackwordAnimation);
                  break;
              case ChartPresenter::ScrollDownState:
              case ChartPresenter::ScrollRightState:
                  m_animation->setAnimationType(AxisAnimation::MoveForwardAnimation);
                  break;
              case ChartPresenter::ShowState:
                  m_animation->setAnimationType(AxisAnimation::DefaultAnimation);
                  break;
          }
          m_animation->setValues(m_layoutVector,layout);
          presenter()->startAnimation(m_animation);
    }
    else {
        setLayout(layout);
        updateGeometry();
    }
}

void ChartAxis::setAxisOpacity(qreal opacity)
{
    m_axis->setOpacity(opacity);
}

qreal ChartAxis::axisOpacity() const
{
    return m_axis->opacity();
}

void ChartAxis::setGridOpacity(qreal opacity)
{
    m_grid->setOpacity(opacity);
}

qreal ChartAxis::gridOpacity() const
{
    return m_grid->opacity();
}

void ChartAxis::setLabelsOpacity(qreal opacity)
{
    m_labels->setOpacity(opacity);
}

qreal ChartAxis::labelsOpacity() const
{
    return m_labels->opacity();
}

void ChartAxis::setShadesOpacity(qreal opacity)
{
    m_shades->setOpacity(opacity);
}

qreal ChartAxis::shadesOpacity() const
{
    return m_shades->opacity();
}

void ChartAxis::setLabelsAngle(int angle)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
          item->setRotation(angle);
    }

    m_labelsAngle=angle;
}

void ChartAxis::setLabelsPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setPen(pen);
    }
}

void ChartAxis::setLabelsBrush(const QBrush &brush)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setBrush(brush);
    }
}

void ChartAxis::setLabelsFont(const QFont &font)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setFont(font);
    }
    m_font = font;
}

void ChartAxis::setShadesBrush(const QBrush &brush)
{
    foreach(QGraphicsItem* item , m_shades->childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setBrush(brush);
    }
}

void ChartAxis::setShadesPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_shades->childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setPen(pen);
    }
}

void ChartAxis::setAxisPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_axis->childItems()) {
           static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void ChartAxis::setGridPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_grid->childItems()) {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

bool ChartAxis::isEmpty()
{
    return m_rect.isEmpty() || qFuzzyIsNull(m_min - m_max);
}

void ChartAxis::handleDomainUpdated()
{
    Domain* domain = qobject_cast<Domain*>(sender());
    qreal min(0);
    qreal max(0);

    if(m_chartAxis->orientation()==Qt::Horizontal) {
        min = domain->minX();
        max = domain->maxX();
    }
    else if (m_chartAxis->orientation()==Qt::Vertical)
    {
        min = domain->minY();
        max = domain->maxY();
    }

    if (!qFuzzyIsNull(m_min - min) || !qFuzzyIsNull(m_max - max))
    {
        m_min = min;
        m_max = max;

        if (!isEmpty()) {
            QVector<qreal> layout = calculateLayout();
            updateLayout(layout);
        }
    }
}

void ChartAxis::handleAxisUpdated()
{
    if(isEmpty()) return;

    if (!m_chartAxis->isVisible()) {
        setAxisOpacity(0);
        setGridOpacity(0);
        setLabelsOpacity(0);
        setShadesOpacity(0);
    }
    else {

        if (m_chartAxis->isArrowVisible()) {
            setAxisOpacity(100);
        }
        else {
            setAxisOpacity(0);
        }

        if (m_chartAxis->isGridLineVisible()) {
            setGridOpacity(100);
        }
        else {
            setGridOpacity(0);
        }

        if (m_chartAxis->labelsVisible()) {
            setLabelsOpacity(100);
        }
        else {
            setLabelsOpacity(0);
        }

        if (m_chartAxis->shadesVisible()) {
            setShadesOpacity(100);
        }
        else {
            setShadesOpacity(0);
        }
    }

    setLabelsAngle(m_chartAxis->labelsAngle());
    setAxisPen(m_chartAxis->axisPen());
    setLabelsPen(m_chartAxis->labelsPen());
    setLabelsBrush(m_chartAxis->labelsBrush());
    setLabelsFont(m_chartAxis->labelsFont());
    setGridPen(m_chartAxis->gridLinePen());
    setShadesPen(m_chartAxis->shadesPen());
    setShadesBrush(m_chartAxis->shadesBrush());

}

void ChartAxis::handleGeometryChanged(const QRectF &rect)
{
    if(m_rect != rect)
    {
        m_rect = rect;
        if (isEmpty()) return;
        QVector<qreal> layout = calculateLayout();
        updateLayout(layout);
    }
}


qreal ChartAxis::minimumWidth()
{
    if(m_minWidth == 0) updateGeometry();
    return m_minWidth;
}

qreal ChartAxis::minimumHeight()
{
    if(m_minHeight == 0) updateGeometry();
    return m_minHeight;
}


void ChartAxis::axisSelected()
{
    qDebug()<<"TODO: axis clicked";
}


void ChartAxis::createNumberLabels(QStringList &labels,qreal min, qreal max, int ticks) const
{
    Q_ASSERT(max>min);
    Q_ASSERT(ticks>1);

    int n = qMax(int(-floor(log10((max-min)/(ticks-1)))),0);
    n++;
    for (int i=0; i< ticks; i++) {
        qreal value = min + (i * (max - min)/ (ticks-1));
        labels << QString::number(value,'f',n);
    }
}

void ChartAxis::createCategoryLabels(QStringList &labels,qreal min, qreal max,const QStringList &categories) const
{
    Q_ASSERT(max>min);
    Q_UNUSED(max);

    int x = qFloor(min+0.5);
    int count = 0;

    // Try to find category for x coordinate
    while (count < categories.count()+1) {
        if ((x < categories.count()) && (x >= 0)) {
            labels << categories.at(x);
        } else {
            // No label for x coordinate
            labels << "";
        }
        x++;
        count++;
    }
}

#include "moc_chartaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
