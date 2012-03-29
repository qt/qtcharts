#ifndef QLEGEND_H
#define QLEGEND_H

#include <qchartglobal.h>
#include <QGraphicsObject>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;
class LegendMarker;
class QPieSlice;
class QXYSeries;
class QBarSet;
class QBarSeries;
class QPieSeries;
class LegendScrollButton;
class QSeries;

// TODO: This as widget
class QTCOMMERCIALCHART_EXPORT QLegend : public QGraphicsObject
{
    Q_OBJECT
public:

    // We only support these alignments (for now)
    enum Layout {
        LayoutTop = Qt::AlignTop,
        LayoutBottom = Qt::AlignBottom,
        LayoutLeft = Qt::AlignLeft,
        LayoutRight = Qt::AlignRight
    };

    explicit QLegend(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setAlignmnent(QLegend::Layout alignment);
    QLegend::Layout alignment() const;

    QSizeF maximumSize() const;
    void setMaximumSize(const QSizeF size);

    QSizeF size() const;
    void setSize(const QSizeF size);
    void setPos(const QPointF &pos);

Q_SIGNALS:
    // for interactions.
    void clicked(QSeries *series, Qt::MouseButton button);
    void clicked(QBarSet *barset, Qt::MouseButton button);
    void clicked(QPieSlice *slice, Qt::MouseButton button);

public Q_SLOTS:
    // PIMPL --->
    void handleSeriesAdded(QSeries *series, Domain *domain);
    void handleSeriesRemoved(QSeries *series);
    void handleAdded(QList<QPieSlice *> slices);
    void handleRemoved(QList<QPieSlice *> slices);
    void handleMarkerDestroyed();
    void handleScrollButtonClicked(QGraphicsSceneMouseEvent *event);
    // PIMPL <---

private:
    // PIMPL --->
    void connectSeries(QSeries *series);
    void disconnectSeries(QSeries *series);
    void createMarkers(QSeries *series);
    void appendMarkers(QXYSeries *series);      // All line series are derived from QXYSeries, so this works for now
    void appendMarkers(QBarSeries *series);
    void appendMarkers(QPieSeries *series);
    void deleteMarkers(QSeries *series);
    void updateLayout();
    void rescaleScrollButtons(const QSize &size);
    QSizeF maximumMarkerSize();
    void checkFirstMarkerBounds();
    bool scrollButtonsVisible();

    qreal m_margin;
    QPointF m_pos;
    QSizeF m_minimumSize;
    QSizeF m_maximumSize;
    QSizeF m_size;

    QList<LegendMarker *> m_markers;

    QBrush m_brush;
    QPen m_pen;
    QLegend::Layout m_alignment;

    int mFirstMarker;

    LegendScrollButton *m_scrollButtonLeft;
    LegendScrollButton *m_scrollButtonRight;
    LegendScrollButton *m_scrollButtonUp;
    LegendScrollButton *m_scrollButtonDown;

    // <--- PIMPL
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
