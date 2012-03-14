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

    QSizeF minimumSize() const;
    void setMinimumSize(const QSizeF size);

signals:
    // for interactions.
    void clicked(QSeries* series, Qt::MouseButton button);
    void clicked(QBarSet* barset, Qt::MouseButton button);
    void clicked(QPieSlice* slice, Qt::MouseButton button);

public slots:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);
    void handleGeometryChanged(const QRectF& size);

    // PIMPL --->
    // Internal slot. Legend needs to know when theme has changed (or color of some series, if user changes it)
    void handleThemeChanged();
    // <--- PIMPL

private:
    // PIMPL --->
    void createMarkers(QSeries* series);
    void appendMarkers(QXYSeries* series);
    void appendMarkers(QBarSeries* series);
    void appendMarkers(QPieSeries* series);
    void deleteMarkers(QSeries* series);
    void layoutChanged();
    // <--- PIMPL


    QRectF mBoundingRect;
    QList<QSeries*> mSeriesList;
    QList<LegendMarker*> mMarkers;

    QBrush mBackgroundBrush;
    QSizeF mMinimumSize;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
