#ifndef LEGENDMARKER_P_H
#define LEGENDMARKER_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSeries;


class LegendMarker : public QGraphicsObject
{
    Q_OBJECT
public:
    LegendMarker(QSeries* series, QGraphicsItem *parent = 0);
    void setBoundingRect(const QRectF rect);
    void setBrush(const QBrush brush);
    void setName(const QString name);
    QString name() const;
    QColor color() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    QRectF boundingRect() const;

public:
    // From QGraphicsObject
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked(QSeries* series, QString name);
    void rightClicked(QSeries* series, QString name);

private:
    QRectF mBoundingRect;
    QBrush mBrush;
    QString mName;
    QSeries* mSeries;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif // LEGENDMARKER_P_H
