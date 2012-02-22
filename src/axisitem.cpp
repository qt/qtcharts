#include "axisitem_p.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QDebug>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AxisItem::AxisItem(AxisType type,QGraphicsItem* parent) :
ChartItem(parent),
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
}

AxisItem::~AxisItem()
{
}

QRectF AxisItem::boundingRect() const
{
    return m_rect;
}

void AxisItem::createItems(int count)
{
    m_axis.addToGroup(new QGraphicsLineItem(this));
    for (int i = 0; i < count; ++i) {
           m_grid.addToGroup(new QGraphicsLineItem(this));
           m_labels.addToGroup(new QGraphicsSimpleTextItem(this));
           if(i%2) m_shades.addToGroup(new QGraphicsRectItem(this));
           m_axis.addToGroup(new QGraphicsLineItem(this));
       }
}

void AxisItem::clear()
{
    foreach(QGraphicsItem* item , m_shades.childItems()) {
        delete item;
    }

    foreach(QGraphicsItem* item , m_grid.childItems()) {
        delete item;
    }

    foreach(QGraphicsItem* item , m_labels.childItems()) {
        delete item;
    }

    foreach(QGraphicsItem* item , m_axis.childItems()) {
            delete item;
    }

    m_thicksList.clear();

}

void AxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void AxisItem::updateItem(int count)
{
    if(count ==0) return;

    QList<QGraphicsItem *> lines = m_grid.childItems();
    QList<QGraphicsItem *> labels = m_labels.childItems();
    QList<QGraphicsItem *> shades = m_shades.childItems();
    QList<QGraphicsItem *> axis = m_axis.childItems();

    switch (m_type)
      {
          case X_AXIS:
          {
              const qreal deltaX = m_rect.width() / (count-1);

              QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(axis.at(0));
              lineItem->setLine(m_rect.left(), m_rect.bottom(), m_rect.right(), m_rect.bottom());

              for (int i = 0; i < count; ++i) {
                  int x = i * deltaX + m_rect.left();
                  QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(lines.at(i));
                  lineItem->setLine(x, m_rect.top(), x, m_rect.bottom());
                  QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                  labelItem->setText(m_thicksList.at(i));
                  QPointF center = labelItem->boundingRect().center();
                  labelItem->setTransformOriginPoint(center.x(), center.y());
                  labelItem->setPos(x - center.x(), m_rect.bottom() + label_padding);
                  if(i%2){
                      QGraphicsRectItem *rectItem =  static_cast<QGraphicsRectItem*>(shades.at(i/2));
                      rectItem->setRect(x,m_rect.top(),deltaX,m_rect.height());
                  }
                  lineItem =  static_cast<QGraphicsLineItem*>(axis.at(i+1));
                  lineItem->setLine(x,m_rect.bottom(),x,m_rect.bottom()+5);
              }
          }
          break;

          case Y_AXIS:
          {
              const qreal deltaY = m_rect.height()/ (count-1);

              QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(axis.at(0));
              lineItem->setLine(m_rect.left() , m_rect.top(), m_rect.left(), m_rect.bottom());

              for (int i = 0; i < count; ++i) {
                  int y = i * -deltaY + m_rect.bottom();
                  QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(lines.at(i));
                  lineItem->setLine(m_rect.left() , y, m_rect.right(), y);
                  QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                  labelItem->setText(m_thicksList.at(i));
                  QPointF center = labelItem->boundingRect().center();
                  labelItem->setTransformOriginPoint(center.x(), center.y());
                  labelItem->setPos(m_rect.left() -  labelItem->boundingRect().width() - label_padding , y-center.y());
                  if(i%2){
                      QGraphicsRectItem *rectItem =  static_cast<QGraphicsRectItem*>(shades.at(i/2));
                      rectItem->setRect(m_rect.left(),y,m_rect.width(),deltaY);
                  }
                  lineItem =  static_cast<QGraphicsLineItem*>(axis.at(i+1));
                  lineItem->setLine(m_rect.left()-5,y,m_rect.left(),y);
              }
          }
          break;
          default:
          qDebug()<<"Unknown axis type";
          break;
      }
}

void AxisItem::handleAxisUpdate(QChartAxis* axis)
{
    if(axis->isAxisVisible()) {
        setAxisOpacity(100);
    }
    else {
        setAxisOpacity(0);
    }

    if(axis->isGridVisible()) {
        setGridOpacity(100);
    }
    else {
        setGridOpacity(0);
    }

    if(axis->isLabelsVisible())
    {
        setLabelsOpacity(100);
    }
    else {
        setLabelsOpacity(0);
    }

    if(axis->isShadesVisible()) {
        setShadesOpacity(axis->shadesOpacity());
    }
    else {
        setShadesOpacity(0);
    }

    setLabelsAngle(axis->labelsAngle());
    setAxisPen(axis->axisPen());
    setLabelsPen(axis->labelsPen());
    setLabelsBrush(axis->labelsBrush());
    setLabelsFont(axis->labelFont());
    setGridPen(axis->gridPen());
    setShadesPen(axis->shadesPen());
    setShadesBrush(axis->shadesBrush());
}

void AxisItem::handleLabelsChanged(QChartAxis* axis,const QStringList& labels)
{
    m_thicksList=labels;
    QList<QGraphicsItem*> items = m_labels.childItems();
    //if(items.size()!=m_thicksList.size()){
       clear();
       m_thicksList=labels;
       createItems(m_thicksList.size());
       updateItem(m_thicksList.size());
       items = m_labels.childItems();
       handleAxisUpdate(axis);
    // }

    Q_ASSERT(items.size()==m_thicksList.size());

    int i=0;
    foreach(QGraphicsItem* item, items){
        static_cast<QGraphicsSimpleTextItem*>(item)->setText(m_thicksList.at(i));
        i++;
    }
    update();
}

void AxisItem::handleGeometryChanged(const QRectF& rect)
{
    m_rect = rect;
    updateItem(m_thicksList.size());
    update();
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


//TODO "nice numbers algorithm"
#include "moc_axisitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
