/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTDATASET_P_H
#define CHARTDATASET_P_H

#include <QtCharts/QAbstractSeries>
#include <private/abstractdomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCore/QVector>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractAxis;
class ChartPresenter;

class QT_CHARTS_AUTOTEST_EXPORT ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QChart *chart);
    virtual ~ChartDataSet();

    void addSeries(QAbstractSeries *series);
    void removeSeries(QAbstractSeries *series);
    QList<QAbstractSeries *> series() const;

    void addAxis(QAbstractAxis *axis,Qt::Alignment aligment);
    void removeAxis(QAbstractAxis *axis);
    QList<QAbstractAxis*> axes() const;

    bool attachAxis(QAbstractSeries* series,QAbstractAxis *axis);
    bool detachAxis(QAbstractSeries* series,QAbstractAxis *axis);

    void createDefaultAxes();

    void zoomInDomain(const QRectF &rect);
    void zoomOutDomain(const QRectF &rect);
    void zoomResetDomain();
    bool isZoomedDomain();
    void scrollDomain(qreal dx, qreal dy);

    QPointF mapToValue(const QPointF &position, QAbstractSeries *series = 0);
    QPointF mapToPosition(const QPointF &value, QAbstractSeries *series = 0);

Q_SIGNALS:
    void axisAdded(QAbstractAxis* axis);
    void axisRemoved(QAbstractAxis* axis);
    void seriesAdded(QAbstractSeries* series);
    void seriesRemoved(QAbstractSeries* series);

private:
    void createAxes(QAbstractAxis::AxisTypes type, Qt::Orientation orientation);
    QAbstractAxis *createAxis(QAbstractAxis::AxisType type, Qt::Orientation orientation);
    AbstractDomain::DomainType selectDomain(QList<QAbstractAxis* > axes);
    AbstractDomain* createDomain(AbstractDomain::DomainType type);
    void deleteAllAxes();
    void deleteAllSeries();
    void findMinMaxForSeries(QList<QAbstractSeries *> series,Qt::Orientations orientation, qreal &min, qreal &max);
private:
    QList<QAbstractSeries *> m_seriesList;
    QList<QAbstractAxis *> m_axisList;
    QChart* m_chart;
};

QT_CHARTS_END_NAMESPACE

#endif /* CHARTENGINE_P_H */
