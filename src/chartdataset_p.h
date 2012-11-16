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
#include "qabstractaxis_p.h"
#include <QVector>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractAxis;
class ChartPresenter;

class QTCOMMERCIALCHART_AUTOTEST_EXPORT ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QChart *chart);
    virtual ~ChartDataSet();

    void addSeries(QAbstractSeries *series);
    void removeSeries(QAbstractSeries *series);
    QList<QAbstractSeries *> series() const;
    void removeAllSeries();

    void addAxis(QAbstractAxis *axis,Qt::Alignment aligment);
    void removeAxis(QAbstractAxis *axis);
    QList<QAbstractAxis*> axes() const;
    void removeAllAxes();

    bool attachAxis(QAbstractSeries* series,QAbstractAxis *axis);
    bool detachAxis(QAbstractSeries* series,QAbstractAxis *axis);

    void createDefaultAxes();

    void zoomInDomain(const QRectF &rect);
    void zoomOutDomain(const QRectF &rect);
    void scrollDomain(qreal dx, qreal dy);

Q_SIGNALS:
    void axisAdded(QAbstractAxis* axis);
    void axisRemoved(QAbstractAxis* axis);
    void seriesAdded(QAbstractSeries* series);
    void seriesRemoved(QAbstractSeries* series);

private:
    void createAxes(QAbstractAxis::AxisTypes type, Qt::Orientation orientation);
    QAbstractAxis *createAxis(QAbstractAxis::AxisType type, Qt::Orientation orientation);

private:
    QList<QAbstractSeries *> m_seriesList;
    QList<QAbstractAxis *> m_axisList;
    QChart* m_chart;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTENGINE_P_H */
