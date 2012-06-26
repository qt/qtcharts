/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTDATASET_P_H
#define CHARTDATASET_P_H

#include "qabstractseries.h"
#include "domain_p.h"
#include <QVector>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractAxis;

class QTCOMMERCIALCHART_AUTOTEST_EXPORT ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QChart* parent=0);
    virtual ~ChartDataSet();

    void addSeries(QAbstractSeries* series);
    QAbstractAxis* removeSeries(QAbstractSeries* series);
    void removeAllSeries();
    void updateSeries(QAbstractSeries* series);

    void zoomInDomain(const QRectF& rect, const QSizeF& size);
    void zoomOutDomain(const QRectF& rect, const QSizeF& size);
    void scrollDomain(qreal dx,qreal dy,const QSizeF& size);

    int seriesCount(QAbstractSeries::SeriesType type);
    int seriesIndex(QAbstractSeries *series);

    Domain* domain(QAbstractSeries* series) const;
    Domain* domain(QAbstractAxis* axis) const;

    QAbstractAxis* axisX(QAbstractSeries *series) const;
    QAbstractAxis* axisY(QAbstractSeries *series) const;

    QList<QAbstractSeries*> series() const;

Q_SIGNALS:
    void seriesAdded(QAbstractSeries* series, Domain* domain);
    void seriesRemoved(QAbstractSeries* series);
    void seriesUpdated(QAbstractSeries* series);
    void axisAdded(QAbstractAxis* axis,Domain* domain);
    void axisRemoved(QAbstractAxis* axis);

private:
    QStringList createLabels(QAbstractAxis* axis,qreal min, qreal max);
    void calculateDomain(QAbstractSeries* series,Domain* domain);

private:
    QMap<QAbstractSeries*, QAbstractAxis*> m_seriesAxisMap;
    QMap<QAbstractAxis*, Domain*> m_axisDomainMap;
    QMap<int, QAbstractSeries*> m_indexSeriesMap;
    QAbstractAxis* m_axisX;
    QAbstractAxis* m_axisY;

    int m_domainIndex;
    bool m_axisXInitialized;
    bool m_axisYInitialized;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H_ */
