#ifndef QLEGEND_H
#define QLEGEND_H

#include <qchartglobal.h>
#include <qseries.h>
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;
class LegendMarker;
class QPieSlice;
class QXYSeries;
class QBarSet;
class QBarSeries;
class QPieSeries;
class LegendScrollButton;

class QTCOMMERCIALCHART_EXPORT QLegend : public QGraphicsObject
{
    Q_OBJECT
public:

    enum PreferredLayout {
        PreferredLayoutTop,
        PreferredLayoutBottom,
        PreferredLayoutLeft,
        PreferredLayoutRight,
    };

    explicit QLegend(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void setBrush(const QBrush& brush);
    QBrush brush() const;

    void setPen(const QPen& pen);
    QPen pen() const;

    void setPreferredLayout(QLegend::PreferredLayout preferred);
    QLegend::PreferredLayout preferredLayout() const;

    QSizeF maximumSize() const;
    void setMaximumSize(const QSizeF size);

    QSizeF size() const;
    void setSize(const QSizeF size);
    void setPos(const QPointF &pos);

signals:
    // for interactions.
    void clicked(QSeries* series, Qt::MouseButton button);
    void clicked(QBarSet* barset, Qt::MouseButton button);
    void clicked(QPieSlice* slice, Qt::MouseButton button);

public slots:
    // PIMPL --->
    void handleSeriesAdded(QSeries* series,Domain* domain);
    void handleSeriesRemoved(QSeries* series);
    void handleAdded(QList<QPieSlice*> slices);
    void handleRemoved(QList<QPieSlice*> slices);
    void handleMarkerDestroyed();
    void handleScrollButtonClicked(QGraphicsSceneMouseEvent* event);
    // PIMPL <---

private:
    // PIMPL --->
    void connectSeries(QSeries* series);
    void disconnectSeries(QSeries* series);
    void createMarkers(QSeries* series);
    void appendMarkers(QXYSeries* series);      // All line series are derived from QXYSeries, so this works for now
    void appendMarkers(QBarSeries* series);
    void appendMarkers(QPieSeries* series);
    void deleteMarkers(QSeries* series);
    void updateLayout();
    void rescaleScrollButtons(const QSize& size);
    QSizeF maximumMarkerSize();
    void checkFirstMarkerBounds();
    bool scrollButtonsVisible();

    QPointF mPos;
    QSizeF mSize;
    QSizeF mMinimumSize;
    QSizeF mMaximumSize;

    QList<LegendMarker*> mMarkers;

    QBrush m_brush;
    QPen m_pen;
    QLegend::PreferredLayout mPreferredLayout;

    int mFirstMarker;

    LegendScrollButton* mScrollButtonLeft;
    LegendScrollButton* mScrollButtonRight;
    LegendScrollButton* mScrollButtonUp;
    LegendScrollButton* mScrollButtonDown;

    qreal mMargin;
    // <--- PIMPL
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
