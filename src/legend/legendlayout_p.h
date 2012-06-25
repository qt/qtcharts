#ifndef LEGENDLAYOUT_H_
#define LEGENDLAYOUT_H_
#include <QGraphicsLayout>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegend;

class LegendLayout : public QGraphicsLayout
{
public:

    LegendLayout(QLegend* legend);
    virtual ~LegendLayout();

    void setGeometry(const QRectF& rect);

    void setOffset(qreal x, qreal y);
    QPointF offset() const;

protected:
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
    int count() const { return 0; }
    QGraphicsLayoutItem* itemAt(int) const { return 0; };
    void removeAt(int){};

private:
    void setAttachedGeometry(const QRectF& rect);
    void setDettachedGeometry(const QRectF& rect);

private:
    QLegend* m_legend;
    int m_marginBig;
    int m_marginSmall;
    int m_marginTiny;
    qreal m_offsetX;
    qreal m_offsetY;
    qreal m_minOffsetX;
    qreal m_minOffsetY;
    qreal m_maxOffsetX;
    qreal m_maxOffsetY;
    qreal m_width;
    qreal m_height;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
