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

#ifndef QABSTRACTBARSERIES_P_H
#define QABSTRACTBARSERIES_P_H

#include <QtCharts/QAbstractBarSeries>
#include <private/qabstractseries_p.h>
#include <QtCore/QStringList>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QBarModelMapper;
class QBarCategoryAxis;
class QLegendMarker;

class Q_CHARTS_EXPORT QAbstractBarSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT
public:
    QAbstractBarSeriesPrivate(QAbstractBarSeries *parent);
    int categoryCount() const;

    void setBarWidth(qreal width);
    qreal barWidth() const;

    void setVisible(bool visible);
    void setLabelsVisible(bool visible);

    void initializeDomain() override;
    void initializeAxes() override;
    void initializeAnimations(QChart::AnimationOptions options, int duration, QEasingCurve &curve) override;
    void initializeTheme(int index, ChartTheme* theme, bool forced = false) override;

    QList<QLegendMarker*> createLegendMarkers(QLegend *legend) override;

    virtual QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const override;

    bool append(QBarSet *set);
    bool remove(QBarSet *set);
    bool append(const QList<QBarSet *> &sets);
    bool remove(const QList<QBarSet *> &sets);
    bool insert(int index, QBarSet *set);

    QBarSet *barsetAt(int index);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal absoluteCategorySum(int category);
    qreal maxCategorySum();
    qreal minX();
    qreal maxX();
    qreal categoryTop(int category);
    qreal categoryBottom(int category);
    qreal top();
    qreal bottom();

    bool blockBarUpdate();

    qreal labelsAngle() const;
    void setVisualsDirty(bool dirty) { m_visualsDirty = dirty; }
    bool visualsDirty() const { return m_visualsDirty; }
    void setLabelsDirty(bool dirty) { m_labelsDirty = dirty; }
    bool labelsDirty() const { return m_labelsDirty; }

Q_SIGNALS:
    void clicked(int index, QBarSet *barset);
    void pressed(int index, QBarSet *barset);
    void released(int index, QBarSet *barset);
    void doubleClicked(int index, QBarSet *barset);
    void updatedBars();
    void updatedLayout();
    void restructuredBars();
    void labelsVisibleChanged(bool visible);
    void visibleChanged();
    void setValueChanged(int index, QBarSet *barset);
    void setValueAdded(int index, int count, QBarSet *barset);
    void setValueRemoved(int index, int count, QBarSet *barset);

private Q_SLOTS:
    void handleSetValueChange(int index);
    void handleSetValueAdd(int index, int count);
    void handleSetValueRemove(int index, int count);

private:
    void populateCategories(QBarCategoryAxis *axis);

protected:
    QList<QBarSet *> m_barSets;
    qreal m_barWidth;
    bool m_labelsVisible;
    bool m_visible;
    bool m_blockBarUpdate;
    QString m_labelsFormat;
    QAbstractBarSeries::LabelsPosition m_labelsPosition;
    qreal m_labelsAngle;
    int m_labelsPrecision;
    bool m_visualsDirty;
    bool m_labelsDirty;

private:
    Q_DECLARE_PUBLIC(QAbstractBarSeries)
    friend class HorizontalBarChartItem;
    friend class BarChartItem;
};

QT_END_NAMESPACE

#endif // QABSTRACTBARSERIES_P_H
