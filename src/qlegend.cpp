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
        qDebug() << "LegendMarker::paint" << mBoundingRect;
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
{
}

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // TODO: layout for text. using marker layout + magic for now.
    foreach(LegendMarker* m, mMarkers) {
        QRectF r = m->boundingRect();
        painter->setPen(m->color());
        // TODO: r.y + r.height is incorrect. should be r.y. Find the bug, and remove the hack
        painter->drawText(r.x() + 20, r.y()+r.height(), m->name());
    }
}

QRectF QLegend::boundingRect() const
{
    return mBoundingRect;
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
            childItems().append(marker);
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
    qreal steps = mMarkers.count() * 2 + 1;

    qreal yStep = mBoundingRect.height() / steps;
    qreal x = 0;
    qreal y = yStep;    // first step is empty
    foreach (LegendMarker* m, mMarkers) {
        m->setBoundingRect(QRectF(x,y,markerSize.width(),markerSize.height()));
        y += yStep*2;   // 2 steps per marker (marker and empty space)
    }
}



#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
