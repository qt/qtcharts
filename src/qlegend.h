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

    enum PreferredLayout {
        PreferredLayoutHorizontal,
        PreferredLayoutVertical
    };

    explicit QLegend(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void setBackgroundBrush(const QBrush& brush);
    QBrush backgroundBrush() const;

    void setPreferredLayout(QLegend::PreferredLayout preferred);

    QSizeF maximumSize() const;
    void setMaximumSize(const QSizeF size);

    void setSize(const QSizeF size);
    void setPos(const QPointF &pos);

signals:
    // for interactions.
    void clicked(QSeries* series, Qt::MouseButton button);
    void clicked(QBarSet* barset, Qt::MouseButton button);
    void clicked(QPieSlice* slice, Qt::MouseButton button);

public slots:
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);

private:
    // PIMPL --->
    void createMarkers(QSeries* series);
    void appendMarkers(QXYSeries* series);      // All line series are derived from QXYSeries, so this works for now
    void appendMarkers(QBarSeries* series);
    void appendMarkers(QPieSeries* series);
    void deleteMarkers(QSeries* series);
    void layoutChanged();    // TODO: rename this to layoutChanged and remove original layoutChanged, when ready
    // <--- PIMPL


//    QRectF mBoundingRect;
    QPointF mPos;
    QSizeF mSize;
    QSizeF mMinimumSize;
    QSizeF mMaximumSize;

    QList<QSeries*> mSeriesList;
    QList<LegendMarker*> mMarkers;

    QBrush mBackgroundBrush;
    QLegend::PreferredLayout mPreferredLayout;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
