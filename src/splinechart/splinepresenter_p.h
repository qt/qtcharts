#ifndef SPLINEPRESENTER_P_H
#define SPLINEPRESENTER_P_H

#include "chartitem_p.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplinePresenter : public QObject, public ChartItem
{
    Q_OBJECT
public:
    SplinePresenter(QObject *parent = 0);

    void handleGeometryChanged(const QRectF&);
    void handleDomainChanged(const Domain& domain);
    
signals:
    
public slots:
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINEPRESENTER_P_H
