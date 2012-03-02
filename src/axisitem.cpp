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
m_axis(parent)
{
    //initial initialization
    m_axis.setZValue(ChartPresenter::AxisZValue);
    m_shades.setZValue(ChartPresenter::ShadesZValue);
    m_grid.setZValue(ChartPresenter::GridZValue);
    setFlags(QGraphicsItem::ItemHasNoContents);

    QObject::connect(m_chartAxis,SIGNAL(updated()),this,SLOT(handleAxisUpdated()));
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

void AxisItem::clear(int count)
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

void AxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void AxisItem::updateItems(QVector<qreal>& oldLayout,QVector<qreal>& newLayout)
{
    if(newLayout.count()==0) return;
    applyLayout(newLayout);
    oldLayout=newLayout;
}

QStringList AxisItem::createLabels(int ticks, qreal min, qreal max)
{


    Q_ASSERT(max>=min);

    QStringList labels;

    //int ticks = axis->ticksCount()-1;

    for(int i=0; i<= ticks; i++) {
        qreal value = min + (i * (max - min)/ ticks);
        QString label ;//= axis->axisTickLabel(value);
        if(label.isEmpty()) {
            labels << QString::number(value);
        }
        else {
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
    QVector<qreal> points;
    points.resize(m_thicksList.size());

    switch (m_type)
    {
        case X_AXIS:
        {
            const qreal deltaX = m_rect.width()/(m_thicksList.size()-1);
            for (int i = 0; i < m_thicksList.size(); ++i) {
                 int x = i * deltaX + m_rect.left();
                 points[i] = x;
            }
        }
        break;
        case Y_AXIS:
        {
            const qreal deltaY = m_rect.height()/(m_thicksList.size()-1);
            for (int i = 0; i < m_thicksList.size(); ++i) {
                 int y = i * -deltaY + m_rect.bottom();
                 points[i] = y;
            }
        }
        break;
    }
    return points;
}

void AxisItem::applyLayout(const QVector<qreal>& points)
{
    Q_ASSERT(points.size() == m_thicksList.size());

    QList<QGraphicsItem *> lines = m_grid.childItems();
    QList<QGraphicsItem *> labels = m_labels.childItems();
    QList<QGraphicsItem *> shades = m_shades.childItems();
    QList<QGraphicsItem *> axis = m_axis.childItems();

    Q_ASSERT(labels.size() == m_thicksList.size());

    switch (m_type)
         {
             case X_AXIS:
             {
                 QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(axis.at(0));
                 lineItem->setLine(m_rect.left(), m_rect.bottom(), m_rect.right(), m_rect.bottom());

                 for (int i = 0; i < points.size(); ++i) {
                     QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(lines.at(i));
                     lineItem->setLine(points[i], m_rect.top(), points[i], m_rect.bottom());
                     QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                     labelItem->setText(m_thicksList.at(i));
                     QPointF center = labelItem->boundingRect().center();
                     labelItem->setTransformOriginPoint(center.x(), center.y());
                     labelItem->setPos(points[i] - center.x(), m_rect.bottom() + label_padding);
                     if(i%2){
                         QGraphicsRectItem *rectItem =  static_cast<QGraphicsRectItem*>(shades.at(i/2));
                         rectItem->setRect(points[i],m_rect.top(),points[i+1]-points[i],m_rect.height());
                     }
                     lineItem =  static_cast<QGraphicsLineItem*>(axis.at(i+1));
                     lineItem->setLine(points[i],m_rect.bottom(),points[i],m_rect.bottom()+5);
                 }
             }
             break;

             case Y_AXIS:
             {
                 QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(axis.at(0));
                 lineItem->setLine(m_rect.left() , m_rect.top(), m_rect.left(), m_rect.bottom());

                 for (int i = 0; i < points.size(); ++i) {
                     QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(lines.at(i));
                     lineItem->setLine(m_rect.left() , points[i], m_rect.right(), points[i]);
                     QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                     labelItem->setText(m_thicksList.at(i));
                     QPointF center = labelItem->boundingRect().center();
                     labelItem->setTransformOriginPoint(center.x(), center.y());
                     labelItem->setPos(m_rect.left() -  labelItem->boundingRect().width() - label_padding , points[i]-center.y());
                     if(i%2){
                         QGraphicsRectItem *rectItem =  static_cast<QGraphicsRectItem*>(shades.at(i/2));
                         rectItem->setRect(m_rect.left(),points[i],m_rect.width(),points[i]-points[i+1]);
                     }
                     lineItem =  static_cast<QGraphicsLineItem*>(axis.at(i+1));
                     lineItem->setLine(m_rect.left()-5,points[i],m_rect.left(),points[i]);
                 }
             }
             break;
             default:
             qDebug()<<"Unknown axis type";
             break;
         }
}

//handlers

void AxisItem::handleAxisUpdated()
{
    if(m_layoutVector.count()==0) return;

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

void AxisItem::handleRangeChanged(qreal min, qreal max)
{
    if(min == max) return;

    QStringList labels = createLabels(4,min,max);

    int diff = m_thicksList.size() - labels.size();

    if(diff>0){
        clear(diff);
    }else if(diff<0){
        createItems(-diff);
    }
    m_thicksList=labels;

    if(m_rect.isEmpty()) return;

    QVector<qreal>  vector = calculateLayout();

    updateItems(m_layoutVector,vector);

    if(diff!=0) handleAxisUpdated();
}

void AxisItem::handleGeometryChanged(const QRectF& rect)
{
    m_rect = rect;

    if(m_thicksList.size()==0) return;

    QVector<qreal>  vector = calculateLayout();
    updateItems(m_layoutVector,vector);
}

//TODO "nice numbers algorithm"
#include "moc_axisitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
