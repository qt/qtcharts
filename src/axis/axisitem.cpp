#include "axisitem_p.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QDebug>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AxisItem::AxisItem(QChartAxis* axis,AxisType type,QGraphicsItem* parent) :
ChartItem(parent),
m_chartAxis(axis),
m_type(type),
m_labelsAngle(0),
m_grid(parent),
m_shades(parent),
m_labels(parent),
m_axis(parent),
m_min(0),
m_max(0),
m_ticksCount(0)
{
    //initial initialization
    m_axis.setZValue(ChartPresenter::AxisZValue);
    m_shades.setZValue(ChartPresenter::ShadesZValue);
    m_grid.setZValue(ChartPresenter::GridZValue);
    setFlags(QGraphicsItem::ItemHasNoContents);

    QObject::connect(m_chartAxis,SIGNAL(updated()),this,SLOT(handleAxisUpdated()));
    QObject::connect(m_chartAxis->categories(),SIGNAL(updated()),this,SLOT(handleAxisCategoriesUpdated()));

    handleAxisUpdated();
}

AxisItem::~AxisItem()
{
}

QRectF AxisItem::boundingRect() const
{
    return QRectF();
}

void AxisItem::createItems(int count)
{
    if(m_axis.children().size()==0)
           m_axis.addToGroup(new QGraphicsLineItem());
    for (int i = 0; i < count; ++i) {
           m_grid.addToGroup(new QGraphicsLineItem());
           m_labels.addToGroup(new QGraphicsSimpleTextItem());
           if(m_grid.childItems().size()%2) m_shades.addToGroup(new QGraphicsRectItem());
           m_axis.addToGroup(new QGraphicsLineItem());
       }
}

void AxisItem::deleteItems(int count)
{
    QList<QGraphicsItem *> lines = m_grid.childItems();
    QList<QGraphicsItem *> labels = m_labels.childItems();
    QList<QGraphicsItem *> shades = m_shades.childItems();
    QList<QGraphicsItem *> axis = m_axis.childItems();

    for (int i = 0; i < count; ++i) {
        delete(lines.takeLast());
        delete(labels.takeLast());
        if(lines.size()%2) delete(shades.takeLast());
        delete(axis.takeLast());
    }
}

void AxisItem::updateLayout(QVector<qreal>& layout)
{
    setLayout(layout);
}

QStringList AxisItem::createLabels(int ticks, qreal min, qreal max) const
{
    Q_ASSERT(max>=min);
    Q_ASSERT(ticks>0);

    QStringList labels;

    QChartAxisCategories* categories = m_chartAxis->categories();

    for(int i=0; i< ticks; i++) {
        qreal value = min + (i * (max - min)/ (ticks-1));
        if(categories->count()==0) {
            labels << QString::number(value);
        }
        else {
            QString label = categories->label(value);
            labels << label;
        }
    }


    return labels;
}

void AxisItem::setAxisOpacity(qreal opacity)
{
    m_axis.setOpacity(opacity);
}

qreal AxisItem::axisOpacity() const
{
    return m_axis.opacity();
}

void AxisItem::setGridOpacity(qreal opacity)
{
    m_grid.setOpacity(opacity);
}

qreal AxisItem::gridOpacity() const
{
    return m_grid.opacity();
}

void AxisItem::setLabelsOpacity(qreal opacity)
{
    m_labels.setOpacity(opacity);
}

qreal AxisItem::labelsOpacity() const
{
    return m_labels.opacity();
}

void AxisItem::setShadesOpacity(qreal opacity)
{
    m_shades.setOpacity(opacity);
}

qreal AxisItem::shadesOpacity() const
{
    return m_shades.opacity();
}

void AxisItem::setLabelsAngle(int angle)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
          QPointF center = item->boundingRect().center();
          item->setRotation(angle);
    }

    m_labelsAngle=angle;
}

void AxisItem::setLabelsPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setPen(pen);
    }
}

void AxisItem::setLabelsBrush(const QBrush& brush)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setBrush(brush);
    }
}

void AxisItem::setLabelsFont(const QFont& font)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setFont(font);
    }
}

void AxisItem::setShadesBrush(const QBrush& brush)
{
    foreach(QGraphicsItem* item , m_shades.childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setBrush(brush);
    }
}

void AxisItem::setShadesPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_shades.childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setPen(pen);
    }
}

void AxisItem::setAxisPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_axis.childItems()) {
           static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void AxisItem::setGridPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_grid.childItems()) {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

QVector<qreal> AxisItem::calculateLayout() const
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

void AxisItem::setLayout(QVector<qreal>& layout)
{
	int diff = m_layoutVector.size() - layout.size();

	if(diff>0) {
		deleteItems(diff);
	}
	else if(diff<0) {
		createItems(-diff);
	}

	QList<QGraphicsItem *> lines = m_grid.childItems();
	QList<QGraphicsItem *> labels = m_labels.childItems();
	QList<QGraphicsItem *> shades = m_shades.childItems();
	QList<QGraphicsItem *> axis = m_axis.childItems();

	Q_ASSERT(labels.size() == m_ticksList.size());
	Q_ASSERT(layout.size() == m_ticksList.size());

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
				labelItem->setText(m_ticksList.at(i));
				QPointF center = labelItem->boundingRect().center();
				labelItem->setTransformOriginPoint(center.x(), center.y());
				labelItem->setPos(layout[i] - center.x(), m_rect.bottom() + label_padding);
				if(i%2 && i+1 < layout.size()) {
					QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2));
					rectItem->setRect(layout[i],m_rect.top(),layout[i+1]-layout[i],m_rect.height());
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
				labelItem->setText(m_ticksList.at(i));
				QPointF center = labelItem->boundingRect().center();
				labelItem->setTransformOriginPoint(center.x(), center.y());
				labelItem->setPos(m_rect.left() - labelItem->boundingRect().width() - label_padding , layout[i]-center.y());
				if(i%2 && i+1 < layout.size()) {
					QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2));
					rectItem->setRect(m_rect.left(),layout[i],m_rect.width(),layout[i]-layout[i+1]);
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

	if(diff!=0) handleAxisUpdated();
	m_layoutVector=layout;
}

bool AxisItem::isEmpty()
{
    return m_rect.isEmpty() || m_min==m_max || m_ticksCount==0;
}

//handlers

void AxisItem::handleAxisCategoriesUpdated()
{
	if(isEmpty()) return;
	m_ticksList = createLabels(m_ticksCount,m_min,m_max);
	updateLayout(m_layoutVector);
}

void AxisItem::handleAxisUpdated()
{

    int count = m_chartAxis->ticksCount();

    if(m_ticksCount!=count){
    	handleTicksCountChanged(count);
    }

    if(isEmpty()) return;

    if(m_chartAxis->isAxisVisible()) {
        setAxisOpacity(100);
    }
    else {
        setAxisOpacity(0);
    }

    if(m_chartAxis->isGridVisible()) {
        setGridOpacity(100);
    }
    else {
        setGridOpacity(0);
    }

    if(m_chartAxis->labelsVisible())
    {
        setLabelsOpacity(100);
    }
    else {
        setLabelsOpacity(0);
    }

    if(m_chartAxis->shadesVisible()) {
        setShadesOpacity(m_chartAxis->shadesOpacity());
    }
    else {
        setShadesOpacity(0);
    }

    setLabelsAngle(m_chartAxis->labelsAngle());
    setAxisPen(m_chartAxis->axisPen());
    setLabelsPen(m_chartAxis->labelsPen());
    setLabelsBrush(m_chartAxis->labelsBrush());
    setLabelsFont(m_chartAxis->labelsFont());
    setGridPen(m_chartAxis->gridPen());
    setShadesPen(m_chartAxis->shadesPen());
    setShadesBrush(m_chartAxis->shadesBrush());

}

void AxisItem::handleTicksCountChanged(int count)
{
	m_ticksCount=count;

	if(isEmpty()) return;
	m_ticksList = createLabels(m_ticksCount,m_min,m_max);
	QVector<qreal> layout = calculateLayout();
	updateLayout(layout);
}

void AxisItem::handleRangeChanged(qreal min, qreal max)
{

    m_min = min;
    m_max = max;

    if(isEmpty()) return;
    m_ticksList = createLabels(m_ticksCount,m_min,m_max);
    QVector<qreal> layout = calculateLayout();
    updateLayout(layout);

}

void AxisItem::handleGeometryChanged(const QRectF& rect)
{

    m_rect = rect;
    if(isEmpty()) return;
    m_ticksList = createLabels(m_ticksCount,m_min,m_max);
    QVector<qreal> layout = calculateLayout();
    updateLayout(layout);
}

//painter

void AxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//TODO "nice numbers algorithm"
#include "moc_axisitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
