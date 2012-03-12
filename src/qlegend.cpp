#include "qchartglobal.h"
#include "qlegend.h"
#include "qseries.h"
#include <QPainter>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: this to legendmarker_p.h header
class LegendMarker : public QGraphicsItem
{
public:
    LegendMarker(QGraphicsItem *parent = 0) : QGraphicsItem(parent)
      ,mBoundingRect(0,0,1,1)
    {}

    void setBoundingRect(const QRectF rect) { mBoundingRect = rect; }
    void setBrush(const QBrush brush) { mBrush = brush; }
    void setName(const QString name) { mName = name; }
    QString name() const { return mName; }
    QColor color() const { return mBrush.color(); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)
    {
        painter->setBrush(mBrush);
        painter->drawRect(mBoundingRect);
    }

    QRectF boundingRect() const { return mBoundingRect; }

private:
    QRectF mBoundingRect;
    QBrush mBrush;
    QString mName;
};

QLegend::QLegend(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mBackgroundBrush(Qt::darkGray)     // TODO: from theme?
{
}

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(mBackgroundBrush);
    painter->drawRect(mBoundingRect);

    foreach(LegendMarker* m, mMarkers) {
        QRectF r = m->boundingRect();
        painter->setPen(m->color());
        painter->drawText(r.x() + 20, r.y() + r.height(), m->name());
    }
}

QRectF QLegend::boundingRect() const
{
    return mBoundingRect;
}

void QLegend::setBackgroundBrush(const QBrush& brush)
{
    mBackgroundBrush = brush;
}

QBrush QLegend::backgroundBrush() const
{
    return mBackgroundBrush;
}

void QLegend::handleSeriesAdded(QSeries* series,Domain* domain)
{
    mSeriesList.append(series);
    dataChanged();
    layoutChanged();
}

void QLegend::handleSeriesRemoved(QSeries* series)
{
    mSeriesList.removeOne(series);
    dataChanged();
    layoutChanged();
}

void QLegend::handleGeometryChanged(const QRectF& size)
{
    mBoundingRect = size;
    layoutChanged();
}

void QLegend::dataChanged()
{
    foreach (QGraphicsItem* i, childItems()) {
        delete i;
    }

    mMarkers.clear();

    foreach (QSeries* s, mSeriesList) {
        for (int i=0; i<s->legendEntries().count(); i++) {
            LegendMarker *marker = new LegendMarker(this);
            marker->setBrush(s->legendEntries().at(i).mBrush);
            marker->setName(s->legendEntries().at(i).mName);
            mMarkers.append(marker);
//            childItems().append(marker);
        }
    }
}

void QLegend::layoutChanged()
{
    // Calculate layout for markers and text
    if (mMarkers.count() <= 0) {
        // Nothing to do
        return;
    }

    // TODO: marker defined by series.
    QSizeF markerSize(10,10);

    // TODO: better layout, this is just concept.
    // Leave some space around markers like this: | x x x x |
    qreal steps = mMarkers.count();

    qreal xStep = mBoundingRect.width() / steps;
    qreal yStep = mBoundingRect.height() / steps;
    qreal x = mBoundingRect.x() + 5;
    qreal y = mBoundingRect.y() + (mBoundingRect.height() - markerSize.height())/2;
    foreach (LegendMarker* m, mMarkers) {
        qDebug() << "marker x:" << x;
        qDebug() << "marker y:" << y;
        m->setBoundingRect(QRectF(x,y,markerSize.width(),markerSize.height()));
        x += xStep;
    }
}



#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
