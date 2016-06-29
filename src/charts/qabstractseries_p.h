/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE

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

class QAbstractSeriesPrivate : public QObject
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

    ChartItem* chartItem() { return m_item.data(); }

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
    QScopedPointer<ChartItem> m_item;
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

QT_CHARTS_END_NAMESPACE

#endif
