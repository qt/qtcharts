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

#ifndef CHARTDATASET_P_H_
#define CHARTDATASET_P_H_

#include "qseries.h"
#include "domain_p.h"
#include <QVector>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis;
class QBarSeries;

class ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QObject* parent=0);
    virtual ~ChartDataSet();

    void addSeries(QSeries* series,QChartAxis *axisY = 0);
    void removeSeries(QSeries* series);
    void removeAllSeries();

    void zoomInDomain(const QRectF& rect, const QSizeF& size);
    void zoomOutDomain(const QRectF& rect, const QSizeF& size);
    void scrollDomain(int dx,int dy,const QSizeF& size);

    int seriesCount(QSeries::QSeriesType type);
    int seriesIndex(QSeries *series);

    Domain* domain(QSeries* series) const;
    Domain* domain(QChartAxis* axis) const;

    QChartAxis* axisX() const { return m_axisX; }
    QChartAxis* axisY(QSeries* series = 0) const;

Q_SIGNALS:
    void seriesAdded(QSeries* series,Domain* domain);
    void seriesRemoved(QSeries* series);
    void axisAdded(QChartAxis* axis,Domain* domain);
    void axisRemoved(QChartAxis* axis);

private:
    QStringList createLabels(QChartAxis* axis,qreal min, qreal max);
    void calculateDomain(QSeries* series,Domain* domain);
    void setupCategories(QBarSeries* series);

private:
    QMap<QSeries*, QChartAxis*> m_seriesAxisMap;
    QMap<QChartAxis*, Domain*> m_axisDomainMap;
    QChartAxis* m_axisX;
    QChartAxis* m_axisY;

    int m_domainIndex;
    bool m_axisXInitialized;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H_ */
