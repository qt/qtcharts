// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTSERIES_P_H
#define QABSTRACTSERIES_P_H

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QChart>
#include <private/abstractdomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>

#include <memory>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class ChartPresenter;
class ChartElement;
class LegendMarker;
class QLegend;
class ChartDataSet;
class QAbstractAxis;
class QLegendMarker;
class ChartTheme;
class ChartAnimation;
class ChartItem;
class BoxPlotChartItem;

class Q_CHARTS_EXPORT QAbstractSeriesPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractSeriesPrivate(QAbstractSeries *q);
    ~QAbstractSeriesPrivate();

    virtual void initializeDomain() = 0;
    virtual void initializeAxes() = 0;
    virtual void initializeTheme(int index, ChartTheme* theme, bool forced = false) = 0;
    virtual void initializeGraphics(QGraphicsItem* parent) = 0;
    virtual void initializeAnimations(QChart::AnimationOptions options, int duration,
                                      QEasingCurve &curve) = 0;

    virtual QList<QLegendMarker*> createLegendMarkers(QLegend* legend) = 0;

    virtual QAbstractAxis::AxisType defaultAxisType(Qt::Orientation) const = 0;
    virtual QAbstractAxis* createDefaultAxis(Qt::Orientation) const = 0;

    ChartItem* chartItem() { return m_item.get(); }

    virtual void setDomain(AbstractDomain* domain);
    AbstractDomain* domain() { return m_domain.data(); }

    virtual void setPresenter(ChartPresenter *presenter);
    ChartPresenter *presenter() const;

    QChart* chart() { return m_chart; }

    void setBlockOpenGL(bool enable);

Q_SIGNALS:
    void countChanged();

protected:
    QAbstractSeries *q_ptr;
    QChart *m_chart;
    std::unique_ptr<ChartItem> m_item;
    QList<QAbstractAxis*> m_axes;

private:
    QScopedPointer<AbstractDomain> m_domain;
    QString m_name;
    bool m_visible;
    qreal m_opacity;
    ChartPresenter *m_presenter;
    bool m_useOpenGL;
    bool m_blockOpenGL;

    friend class QAbstractSeries;
    friend class ChartDataSet;
    friend class ChartPresenter;
    friend class QLegendPrivate;
    friend class BoxPlotChartItem;
};

QT_END_NAMESPACE

#endif
