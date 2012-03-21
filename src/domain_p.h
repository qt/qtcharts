#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "qchartglobal.h"
#include "qchartaxis.h"
#include <QRectF>
#include <QSizeF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain: public QObject {
    Q_OBJECT
public:
    explicit Domain(QObject* object=0);
    virtual ~Domain();

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY, int tickXCount, int tickYCount);
    void setRangeX(qreal min, qreal max);
    void setRangeX(qreal min, qreal max, int tickCount);
    void setRangeY(qreal min, qreal max);
    void setRangeY(qreal min, qreal max, int tickCount);
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
    void handleAxisXChanged(qreal min,qreal max,int tickXCount = 5,QChartAxis::LabelsSelection mode = QChartAxis::NativeLabelsSelection);
    void handleAxisYChanged(qreal min,qreal max,int tickYCount = 5,QChartAxis::LabelsSelection mode = QChartAxis::NativeLabelsSelection);

private:
    void niceNumbers(qreal &min, qreal &max, int &ticksCount);
    void looseNiceNumbers(qreal &min, qreal &max, int &ticksCount);
    qreal niceNumber(qreal x,bool celing);

private:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    int m_tickXCount;
    int m_tickYCount;
    QChartAxis::LabelsSelection m_selection;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
