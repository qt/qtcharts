#ifndef LEGENDMARKER_P_H
#define LEGENDMARKER_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QSeries;
class QBarSet;
class QPieSlice;

// TODO: split this to 3 different markers for series, barset and pieslice. Current implementation is easier to misuse...
class LegendMarker : public QGraphicsObject
{
    Q_OBJECT

    enum LegendMarkerType {
        LegendMarkerTypeSeries,
        LegendMarkerTypeBarset,
        LegendMarkerTypePieslice
    };

public:
    LegendMarker(QSeries* series, QGraphicsItem *parent = 0);
    LegendMarker(QSeries* series, QBarSet* barset, QGraphicsItem *parent = 0);
    LegendMarker(QSeries* series, QPieSlice* pieslice, QGraphicsItem *parent = 0);
    void setBoundingRect(const QRectF rect);

    void setBrush(const QBrush brush);
    QBrush brush() const;

    void setName(const QString name);
    QString name() const;

    QSeries* series() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    QRectF boundingRect() const;

public:
    // From QGraphicsObject
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked(QSeries* series, Qt::MouseButton button);
    void clicked(QBarSet* barset, Qt::MouseButton button);
    void clicked(QPieSlice* pieslice, Qt::MouseButton button);

private:
    QRectF mBoundingRect;
    QBrush mBrush;
    QString mName;
    QSeries* mSeries;
    QBarSet* mBarset;
    QPieSlice* mPieslice;

    LegendMarkerType mType;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif // LEGENDMARKER_P_H
