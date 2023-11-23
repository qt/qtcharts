// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTDATASET_P_H
#define CHARTDATASET_P_H

#include <QtCharts/QAbstractSeries>
#include <private/abstractdomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE

class QAbstractAxis;
class ChartPresenter;
class GLXYSeriesDataManager;

class Q_CHARTS_EXPORT ChartDataSet : public QObject
{
    Q_OBJECT
public:
    ChartDataSet(QChart *chart);
    virtual ~ChartDataSet();

    void addSeries(QAbstractSeries *series);
    void removeSeries(QAbstractSeries *series);
    QList<QAbstractSeries *> series() const;

    void addAxis(QAbstractAxis *axis,Qt::Alignment alignment);
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

    GLXYSeriesDataManager *glXYSeriesDataManager() { return m_glXYSeriesDataManager; }

    AbstractDomain* createDomain(AbstractDomain::DomainType type);
    AbstractDomain* domainForSeries(QAbstractSeries *series) const;

Q_SIGNALS:
    void axisAdded(QAbstractAxis* axis);
    void axisRemoved(QAbstractAxis* axis);
    void seriesAdded(QAbstractSeries* series);
    void seriesRemoved(QAbstractSeries* series);
public Q_SLOTS:
    void reverseChanged();
private:
    void createAxes(QAbstractAxis::AxisTypes type, Qt::Orientation orientation);
    QAbstractAxis *createAxis(QAbstractAxis::AxisType type, Qt::Orientation orientation);
    AbstractDomain::DomainType selectDomain(const QList<QAbstractAxis *> &axes);
    void deleteAllAxes();
    void deleteAllSeries();
    void findMinMaxForSeries(const QList<QAbstractSeries *> &series, Qt::Orientations orientation,
                             qreal &min, qreal &max);

private:
    QList<QAbstractSeries *> m_seriesList;
    QList<QAbstractAxis *> m_axisList;
    QChart* m_chart;
    GLXYSeriesDataManager *m_glXYSeriesDataManager;
};

QT_END_NAMESPACE

#endif /* CHARTENGINE_P_H */
