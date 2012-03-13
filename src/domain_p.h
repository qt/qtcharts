#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "qchartglobal.h"
#include <QRectF>
#include <QSizeF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain: public QObject {
    Q_OBJECT
public:
    explicit Domain(QObject* object=0);
    virtual ~Domain();

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void setRangeX(qreal min, qreal max);
    void setRangeY(qreal min, qreal max);
    void setMinX(qreal min);
    void setMaxX(qreal max);
    void setMinY(qreal min);
    void setMaxY(qreal max);

    qreal minX() const {return m_minX;};
    qreal maxX() const {return m_maxX;};
    qreal minY() const {return m_minY;};
    qreal maxY() const {return m_maxY;};

    qreal spanX() const;
    qreal spanY() const;
    bool isEmpty() const;

    int tickXCount() const {return m_tickXCount;}
    int tickYCount() const {return m_tickYCount;}

    friend bool operator== (const Domain &domain1, const Domain &domain2);
    friend bool operator!= (const Domain &domain1, const Domain &domain2);
    friend QDebug operator<<(QDebug dbg, const Domain &domain);

    void zoomIn(const QRectF& rect, const QSizeF& size);
    void zoomOut(const QRectF& rect, const QSizeF& size);
    void move(int dx,int dy,const QSizeF& size);

signals:
    void domainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void rangeXChanged(qreal min, qreal max, int tickXCount);
    void rangeYChanged(qreal min, qreal max, int tickYCount);


public slots:
    void handleAxisRangeXChanged(qreal min,qreal max);
    void handleAxisRangeYChanged(qreal min,qreal max);
    void handleAxisXTicksCountChanged(int tickCount);
    void handleAxisYTicksCountChanged(int tickCount);

private:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    int m_tickXCount;
    int m_tickYCount;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
