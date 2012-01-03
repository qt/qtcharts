#include "chart.h"

Chart::Chart()
{

}

Chart::~Chart()
{

}

QColor Chart::color() const
{
    return m_color;
}

void Chart::setColor(const QColor &color)
{
    m_color = color;
}

void Chart::drawChart(QPainter *painter, const QRectF& drawRect)
{
    QRectF r = drawRect;
    r.adjust(10, 10, -10, -10);

    QPen pen(m_color, 2);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawLine(r.topLeft(), r.bottomLeft());
    painter->drawLine(r.bottomLeft(), r.bottomRight());

    painter->drawText(drawRect, "Axis x", QTextOption(Qt::AlignBottom | Qt::AlignHCenter));
    QTransform transform;
    transform.translate(drawRect.width(), 0); // works badly if drawrect width != height :)
    transform.rotate(90);
    painter->setTransform(transform);
    painter->drawText(drawRect, "Axis y", QTextOption(Qt::AlignBottom | Qt::AlignHCenter));
    painter->resetTransform();

    painter->drawText(drawRect, QT_VERSION_STR, QTextOption(Qt::AlignTop | Qt::AlignRight));
    painter->drawText(drawRect, "Insert chart here", QTextOption(Qt::AlignCenter));

}
