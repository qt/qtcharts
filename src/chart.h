#ifndef CHART_H
#define CHART_H
#include <QColor>
#include <QPainter>
#include <QRect>

class QPainter;

class Chart
{
public:
    Chart();
    virtual ~Chart();

    QColor color() const;
    void setColor(const QColor &color);

    void drawChart(QPainter *painter, const QRectF& drawRect);

private:
    QColor m_color;
};

#endif
