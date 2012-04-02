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

#include "axisitem_p.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QPainter>
#include <QDebug>
#include <cmath>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Axis::Axis(QChartAxis *axis,ChartPresenter *presenter,AxisType type) : Chart(presenter),
    m_chartAxis(axis),
    m_type(type),
    m_labelsAngle(0),
    m_grid(new QGraphicsItemGroup(presenter->rootItem())),
    m_shades(new QGraphicsItemGroup(presenter->rootItem())),
    m_labels(new QGraphicsItemGroup(presenter->rootItem())),
    m_axis(new QGraphicsItemGroup(presenter->rootItem())),
    m_min(0),
    m_max(0),
    m_ticksCount(0)
{
    //initial initialization
    m_axis->setZValue(ChartPresenter::AxisZValue);
    m_axis->setHandlesChildEvents(false);

    m_shades->setZValue(ChartPresenter::ShadesZValue);
    m_grid->setZValue(ChartPresenter::GridZValue);

    connect(m_chartAxis,SIGNAL(updated()),this,SLOT(handleAxisUpdated()));
    connect(m_chartAxis->categories(),SIGNAL(updated()),this,SLOT(handleAxisCategoriesUpdated()));

    handleAxisUpdated();
}

Axis::~Axis()
{
}

void Axis::createItems(int count)
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

void Axis::deleteItems(int count)
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

void Axis::updateLayout(QVector<qreal> &layout)
{
    if (animator()) {
        animator()->updateLayout(this,layout);
    } else {
        setLayout(layout);
    }
}

bool Axis::createLabels(QStringList &labels,qreal min, qreal max,int ticks) const
{
    Q_ASSERT(max>=min);
    Q_ASSERT(ticks>1);

    QChartAxisCategories* categories = m_chartAxis->categories();

    bool category = categories->count()>0;

    if (!category) {
        int n = qMax(int(-floor(log10((max-min)/(ticks-1)))),0);
        n++;
        for (int i=0; i< ticks; i++) {
            qreal value = min + (i * (max - min)/ (ticks-1));
            labels << QString::number(value,'f',n);
        }
    } else {
        QList<qreal> values = categories->values();
        for (int i=0; i< ticks; i++) {
            qreal value = (min + (i * (max - min)/ (ticks-1)));
            int j=0;
            for (; j<values.count(); j++) {
                if (values.at(j) > value) break;
            }
            if (j!=0) value=values.at(j-1);

            QString label = categories->label(value);
            labels << label;
        }
    }

    return category;
}

void Axis::setAxisOpacity(qreal opacity)
{
    m_axis->setOpacity(opacity);
}

qreal Axis::axisOpacity() const
{
    return m_axis->opacity();
}

void Axis::setGridOpacity(qreal opacity)
{
    m_grid->setOpacity(opacity);
}

qreal Axis::gridOpacity() const
{
    return m_grid->opacity();
}

void Axis::setLabelsOpacity(qreal opacity)
{
    m_labels->setOpacity(opacity);
}

qreal Axis::labelsOpacity() const
{
    return m_labels->opacity();
}

void Axis::setShadesOpacity(qreal opacity)
{
    m_shades->setOpacity(opacity);
}

qreal Axis::shadesOpacity() const
{
    return m_shades->opacity();
}

void Axis::setLabelsAngle(int angle)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
          item->setRotation(angle);
    }

    m_labelsAngle=angle;
}

void Axis::setLabelsPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setPen(pen);
    }
}

void Axis::setLabelsBrush(const QBrush &brush)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setBrush(brush);
    }
}

void Axis::setLabelsFont(const QFont &font)
{
    foreach(QGraphicsItem* item , m_labels->childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setFont(font);
    }
}

void Axis::setShadesBrush(const QBrush &brush)
{
    foreach(QGraphicsItem* item , m_shades->childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setBrush(brush);
    }
}

void Axis::setShadesPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_shades->childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setPen(pen);
    }
}

void Axis::setAxisPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_axis->childItems()) {
           static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void Axis::setGridPen(const QPen &pen)
{
    foreach(QGraphicsItem* item , m_grid->childItems()) {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

QVector<qreal> Axis::calculateLayout() const
{
    Q_ASSERT(m_ticksCount>=2);

    QVector<qreal> points;
    points.resize(m_ticksCount);

    switch (m_type)
    {
        case X_AXIS:
        {
            const qreal deltaX = m_rect.width()/(m_ticksCount-1);
            for (int i = 0; i < m_ticksCount; ++i) {
                 int x = i * deltaX + m_rect.left();
                 points[i] = x;
            }
        }
        break;
        case Y_AXIS:
        {
            const qreal deltaY = m_rect.height()/(m_ticksCount-1);
            for (int i = 0; i < m_ticksCount; ++i) {
                 int y = i * -deltaY + m_rect.bottom();
                 points[i] = y;
            }
        }
        break;
    }
    return points;
}

void Axis::setLayout(QVector<qreal> &layout)
{
	int diff = m_layoutVector.size() - layout.size();

    if (diff>0) {
		deleteItems(diff);
    } else if (diff<0) {
		createItems(-diff);
	}

    if( diff!=0) handleAxisUpdated();

	QStringList ticksList;

    bool categories = createLabels(ticksList,m_min,m_max,layout.size());

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_axis->childItems();

	Q_ASSERT(labels.size() == ticksList.size());
	Q_ASSERT(layout.size() == ticksList.size());

	qreal minWidth = 0;
	qreal minHeight = 0;

	switch (m_type)
	{
		case X_AXIS:
		{
			QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
			lineItem->setLine(m_rect.left(), m_rect.bottom(), m_rect.right(), m_rect.bottom());

			for (int i = 0; i < layout.size(); ++i) {
				QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
				lineItem->setLine(layout[i], m_rect.top(), layout[i], m_rect.bottom());
				QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                if (!categories || i<1) {
				    labelItem->setText(ticksList.at(i));
				    const QRectF& rect = labelItem->boundingRect();
				    minWidth+=rect.width();
				    minHeight=qMax(rect.height(),minHeight);
				    QPointF center = rect.center();
				    labelItem->setTransformOriginPoint(center.x(), center.y());
				    labelItem->setPos(layout[i] - center.x(), m_rect.bottom() + label_padding);
                } else {
				    labelItem->setText(ticksList.at(i));
			        const QRectF& rect = labelItem->boundingRect();
			        minWidth+=rect.width();
			        minHeight=qMax(rect.height()+label_padding,minHeight);
				    QPointF center = rect.center();
				    labelItem->setTransformOriginPoint(center.x(), center.y());
				    labelItem->setPos(layout[i] - (layout[i] - layout[i-1])/2 - center.x(), m_rect.bottom() + label_padding);
				}

                if ((i+1)%2 && i>1) {
					QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
					rectItem->setRect(layout[i-1],m_rect.top(),layout[i]-layout[i-1],m_rect.height());
				}
				lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
				lineItem->setLine(layout[i],m_rect.bottom(),layout[i],m_rect.bottom()+5);
			}

		}
		break;

		case Y_AXIS:
		{
			QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
			lineItem->setLine(m_rect.left() , m_rect.top(), m_rect.left(), m_rect.bottom());

			for (int i = 0; i < layout.size(); ++i) {
				QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
				lineItem->setLine(m_rect.left() , layout[i], m_rect.right(), layout[i]);
				QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));

                if (!categories || i<1) {
				    labelItem->setText(ticksList.at(i));
				    const QRectF& rect = labelItem->boundingRect();
				    minWidth=qMax(rect.width()+label_padding,minWidth);
				    minHeight+=rect.height();
				    QPointF center = rect.center();
				    labelItem->setTransformOriginPoint(center.x(), center.y());
				    labelItem->setPos(m_rect.left() - rect.width() - label_padding , layout[i]-center.y());
                } else {
				    labelItem->setText(ticksList.at(i));
				    const QRectF& rect = labelItem->boundingRect();
				    minWidth=qMax(rect.width(),minWidth);
				    minHeight+=rect.height();
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
		break;
		default:
        qDebug()<<"Unknown axis type";
		break;
	}

    m_layoutVector=layout;

    presenter()->setMinimumMarginWidth(this,minWidth);
    presenter()->setMinimumMarginHeight(this,minHeight);

}

bool Axis::isEmpty()
{
    return m_rect.isEmpty() || qFuzzyIsNull(m_min - m_max) || m_ticksCount==0;
}

//handlers

void Axis::handleAxisCategoriesUpdated()
{
    if (isEmpty()) return;
	updateLayout(m_layoutVector);
}

void Axis::handleAxisUpdated()
{

    if (isEmpty()) return;

    if (m_chartAxis->isAxisVisible()) {
        setAxisOpacity(100);
    } else {
        setAxisOpacity(0);
    }

    if (m_chartAxis->isGridLineVisible()) {
        setGridOpacity(100);
    } else {
        setGridOpacity(0);
    }

    if (m_chartAxis->labelsVisible()) {
        setLabelsOpacity(100);
    } else {
        setLabelsOpacity(0);
    }

    if (m_chartAxis->shadesVisible()) {
        setShadesOpacity(m_chartAxis->shadesOpacity());
    } else {
        setShadesOpacity(0);
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

void Axis::handleRangeChanged(qreal min, qreal max,int tickCount)
{
    if (qFuzzyIsNull(min - max) || tickCount < 2)
        return;

    m_min = min;
    m_max = max;
    m_ticksCount= tickCount;

    if (isEmpty()) return;
    QVector<qreal> layout = calculateLayout();
    updateLayout(layout);

}

void Axis::handleGeometryChanged(const QRectF &rect)
{
    if(m_rect != rect)
    {
        m_rect = rect;
        if (isEmpty()) return;
        QVector<qreal> layout = calculateLayout();
        updateLayout(layout);
    }
}

void Axis::axisSelected()
{
    qDebug()<<"TODO axis clicked";
}

//TODO "nice numbers algorithm"
#include "moc_axisitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
