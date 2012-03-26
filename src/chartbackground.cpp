#include "chartbackground_p.h"
#include "chartconfig_p.h"
#include <QPen>
#include <QBrush>
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBackground::ChartBackground(QGraphicsItem* parent):QGraphicsRectItem(parent),
m_diameter(15)
{
}

ChartBackground::~ChartBackground()
{

}

void ChartBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   Q_UNUSED(option);
   Q_UNUSED(widget);
   painter->save();
   painter->setPen(pen());
   painter->setBrush(brush());
   painter->drawRoundRect(rect(),roundness(rect().width()),roundness(rect().height()));
#ifndef QT_NO_DEBUG
   painter->setPen(Qt::black);
   QFont font;
   QString build("build %1");
   font.setPointSize(6);
   painter->setFont(font);
   painter->drawText(rect().bottomLeft(),build.arg(ChartConfig::instance()->compilationTime()));
#endif
   painter->restore();
}

int ChartBackground::roundness(qreal size) const
{
    return 100*m_diameter/int(size);
}

int ChartBackground::diameter() const
{
    return m_diameter;
}

void ChartBackground::setDimeter(int dimater)
{
    m_diameter=dimater;
}

QTCOMMERCIALCHART_END_NAMESPACE
