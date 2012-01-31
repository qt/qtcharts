#include "axisitem_p.h"
#include <QPainter>
#include <QDebug>

#define LABEL_PADDING 5

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AxisItem::AxisItem(AxisType type,QGraphicsItem* parent) :
    QGraphicsItem(parent),
    m_ticks(4),
    m_type(type)
{
}

AxisItem::~AxisItem()
{
}

void AxisItem::setLength(int length)
{
    QPainterPath path;
    path.moveTo(QPointF(0,0));
    path.lineTo(length,0);
   // path.lineTo(length-4,0);
   // path.lineTo(length,3);
   // path.lineTo(length-4,6);
   // path.lineTo(length-4,4);
   // path.lineTo(0,4);
   // path.lineTo(0,2);
    m_path=path;
    update();
}

QRectF AxisItem::boundingRect() const
{
    return m_rect;
}

void AxisItem::setPlotDomain(const PlotDomain& plotDomain)
{
    m_plotDomain = plotDomain;
    createItems();
}

void AxisItem::setPos(const QPointF & pos)
{
    QGraphicsItem::setPos(pos);
}

void AxisItem::resize(const QSize &size)
{
    m_rect = QRectF(QPoint(0,0),size);
    createItems();
}

void AxisItem::setTheme(ChartTheme *theme)
{
    if (theme) {
        // TODO: add axis related properties to the theme class and use them here
    }
}

/*
void AxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    if (!m_rect.isValid())
    return;

    if(m_type==X_AXIS) {

        const qreal deltaX = m_rect.width() / m_ticks;

        for (int i = 0; i <= m_ticks; ++i) {

            int x = i * deltaX + m_rect.left();

            if(i==0) x--;
            if(i==m_ticks) x++;

            qreal label = m_plotDomain.m_minX + (i * m_plotDomain.spanX()
                / m_ticks);
            painter->drawLine(x, m_rect.top()-1, x, m_rect.bottom()+1);
           // painter->drawLine(x, m_rect.bottom()-1, x, m_rect.bottom()-1 + 5);

            painter->drawText(x - 50, m_rect.bottom() + 5, 100, 20,Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
        }
    }

    if(m_type==Y_AXIS) {

        const qreal deltaY = (m_rect.height()) / m_ticks;

        for (int j = 0; j <= m_ticks; ++j) {

            int y = j * -deltaY + m_rect.bottom();

            if(j==0) y++;
            if(j==m_ticks) y--;

            qreal label = m_plotDomain.m_minY + (j * m_plotDomain.spanY()
                / m_ticks);

            painter->drawLine(m_rect.left()-1, y, m_rect.right()+1, y);
            //painter->drawLine(m_rect.left() - 5, y, m_rect.left(), y);
            //TODO : margin = 50 ;
            painter->drawText(m_rect.left() - 50, y - 10, 50 - 5, 20,
                Qt::AlignRight | Qt::AlignVCenter,
                QString::number(label));
        }
    }

    //painter->drawRect(m_rect.adjusted(0, 0, -1, -1));
}
*/
void AxisItem::createItems()
{

    //TODO: this is very inefficient handling

        qDeleteAll(m_shades);
        m_shades.clear();
        qDeleteAll(m_grid);
        m_grid.clear();
        qDeleteAll(m_labels);
        m_labels.clear();


       if(m_type==X_AXIS) {

         const qreal deltaX = m_rect.width() / m_ticks;

         for (int i = 0; i <= m_ticks; ++i) {

             int x = i * deltaX + m_rect.left();

             qreal label = m_plotDomain.m_minX + (i * m_plotDomain.spanX()/ m_ticks);

             m_grid<<new QGraphicsLineItem(x, m_rect.top(), x, m_rect.bottom(),this);

             QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(label),this);
             QPointF center = text->boundingRect().center();
             text->setPos(x - center.x(), m_rect.bottom() + LABEL_PADDING);
             //text->rotate(-45);
             m_labels<<text;
         }
       }

       if(m_type==Y_AXIS) {

         const qreal deltaY = m_rect.height()/ m_ticks;

         for (int j = 0; j <= m_ticks; ++j) {

             int y = j * -deltaY + m_rect.bottom();

             qreal label = m_plotDomain.m_minY + (j * m_plotDomain.spanY()
                 / m_ticks);

             m_grid<<new QGraphicsLineItem(m_rect.left()  , y, m_rect.right(), y,this);
             QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(label),this);
             QPointF center = text->boundingRect().center();

             text->setPos(m_rect.left() - text->boundingRect().width() - LABEL_PADDING , y-center.y());
             //text->rotate(-45);
              m_labels<<text;

         }
       }

       //painter->drawRect(m_rect.adjusted(0, 0, -1, -1));
}

//TODO "nice numbers algorithm"

QTCOMMERCIALCHART_END_NAMESPACE
