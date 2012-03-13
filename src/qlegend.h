#ifndef QLEGEND_H
#define QLEGEND_H

#include "qchartglobal.h"
#include "qseries.h"
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;
class LegendMarker;

class QTCOMMERCIALCHART_EXPORT QLegend : public QGraphicsObject
{
    Q_OBJECT
public:

    explicit QLegend(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void setBackgroundBrush(const QBrush& brush);
    QBrush backgroundBrush() const;

signals:
    // for interactions.
    void clicked(QSeries* series, QString name);
    void rightClicked(QSeries* series, QString name);

public slots:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);
    void handleGeometryChanged(const QRectF& size);

private:
    void dataChanged();
    void layoutChanged();

    QRectF mBoundingRect;
    QList<QSeries*> mSeriesList;
    QList<LegendMarker*> mMarkers;

    QBrush mBackgroundBrush;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
