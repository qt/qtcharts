#ifndef QLEGEND_H
#define QLEGEND_H

#include "qchartglobal.h"
#include "qseries.h"
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;
class LegendMarker;
class QPieSlice;
class QXYSeries;
class QBarSet;
class QBarSeries;
class QPieSeries;

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
    void clicked(QSeries* series);
    void rightClicked(QSeries* series);
    void clicked(QBarSet* barset);
    void rightClicked(QBarSet* series);
    void clicked(QPieSlice* slice);
    void rightClicked(QPieSlice* series);

public slots:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);
    void handleGeometryChanged(const QRectF& size);

private:
    // PIMPL --->
    void createMarker(QXYSeries* series);
    void createMarkers(QBarSeries* series);
    void createMarkers(QPieSeries* series);
    void layoutChanged();
    // <--- PIMPL


    QRectF mBoundingRect;
    QList<QSeries*> mSeriesList;
    QList<LegendMarker*> mMarkers;

    QBrush mBackgroundBrush;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
