#include "axisitem_p.h"
#include "qchartaxis.h"
#include <QPainter>
#include <QDebug>

#define LABEL_PADDING 5

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AxisItem::AxisItem(QChartAxis* axis,AxisType type,QGraphicsItem* parent) :
    ChartItem(parent),
    m_axis(axis),
    m_ticks(4),
    m_type(type)
{
    //initial initialization
    handleAxisChanged();
}

AxisItem::~AxisItem()
{
}

QRectF AxisItem::boundingRect() const
{
    return m_rect;
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

    if(!m_rect.isValid()) return;

    switch (m_type)
    {
        case X_AXIS:
        {
            const qreal deltaX = m_rect.width() / m_ticks;

            for (int i = 0; i <= m_ticks; ++i) {

                int x = i * deltaX + m_rect.left();

                qreal label = m_domain.m_minX + (i * m_domain.spanX()/ m_ticks);

                m_grid<<new QGraphicsLineItem(x, m_rect.top(), x, m_rect.bottom(),this);

                QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(label),this);
                QPointF center = text->boundingRect().center();
                text->setPos(x - center.x(), m_rect.bottom() + LABEL_PADDING);
                //text->rotate(-45);
                m_labels<<text;
            }
        }
        break;

        case Y_AXIS:
        {
            const qreal deltaY = m_rect.height()/ m_ticks;

            for (int j = 0; j <= m_ticks; ++j) {

                int y = j * -deltaY + m_rect.bottom();

                qreal label = m_domain.m_minY + (j * m_domain.spanY()
                    / m_ticks);

                m_grid<<new QGraphicsLineItem(m_rect.left() , y, m_rect.right(), y,this);
                QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(label),this);
                QPointF center = text->boundingRect().center();
                text->setPos(m_rect.left() - text->boundingRect().width() - LABEL_PADDING , y-center.y());

                m_labels<<text;

            }
        }
        break;
        default:
        qDebug()<<"Unknown axis type";
        break;
    }
}

void AxisItem::clear()
{
     qDeleteAll(m_shades);
     m_shades.clear();
     qDeleteAll(m_grid);
     m_grid.clear();
     qDeleteAll(m_labels);
     m_labels.clear();
}

void AxisItem::updateDomain()
{
    clear();
    createItems();
}

void AxisItem::handleAxisChanged()
{
    //m_axis->
}

void AxisItem::handleDomainChanged(const Domain& domain)
{
    m_domain = domain;
    clear();
    createItems();
}

void AxisItem::handleGeometryChanged(const QRectF& rect)
{
    Q_ASSERT(rect.isValid());
    m_rect = rect;
    clear();
    createItems();
}

//TODO "nice numbers algorithm"
#include "moc_axisitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
