#ifndef CHARTBACKGROUND_H_
#define CHARTBACKGROUND_H_

#include "qchartglobal.h"
#include <QGraphicsRectItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartBackground: public QGraphicsRectItem
{
public:
    ChartBackground(QGraphicsItem *parent =0);
    ~ChartBackground();

    void setDimeter(int dimater);
    int diameter() const;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    int roundness(qreal size) const;

private:
     int m_diameter;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTBACKGROUND_H_ */


