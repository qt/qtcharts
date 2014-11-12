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

#ifndef QBOXPLOTSERIES_P_H
#define QBOXPLOTSERIES_P_H

#include <QtCharts/QBoxPlotSeries>
#include <private/qabstractbarseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QBarSet>

QT_CHARTS_BEGIN_NAMESPACE

class BoxPlotAnimation;

class QBoxPlotSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QBoxPlotSeriesPrivate(QBoxPlotSeries *q);
    ~QBoxPlotSeriesPrivate();

    void initializeGraphics(QGraphicsItem *parent);
    void initializeDomain();
    void initializeAxes();
    void initializeAnimations(QChart::AnimationOptions options);
    void initializeTheme(int index, ChartTheme *theme, bool forced = false);

    QList<QLegendMarker*> createLegendMarkers(QLegend *legend);

    virtual QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis *createDefaultAxis(Qt::Orientation orientation) const;

    bool append(QBoxSet *set);
    bool remove(QBoxSet *set);
    bool append(QList<QBoxSet *> sets);
    bool remove(QList<QBoxSet *> sets);
    bool insert(int index, QBoxSet *set);
    QBoxSet *boxSetAt(int index);

    qreal max();
    qreal min();

private:
    void populateCategories(QBarCategoryAxis *axis);

Q_SIGNALS:
    void updated();
    void clicked(int index, QBoxSet *barset);
    void pressed(int index, QBoxSet *barset);
    void released(int index, QBoxSet *barset);
    void doubleClicked(int index, QBoxSet *barset);
    void updatedBoxes();
    void updatedLayout();
    void restructuredBoxes();

private slots:
    void handleSeriesChange(QAbstractSeries *series);
    void handleSeriesRemove(QAbstractSeries *series);

protected:
    QList<QBoxSet *> m_boxSets;
    QPen m_pen;
    QBrush m_brush;
    bool m_boxOutlineVisible;
    int m_index;
    BoxPlotAnimation *m_animation;
    qreal m_boxWidth;

private:
    Q_DECLARE_PUBLIC(QBoxPlotSeries)
};

QT_CHARTS_END_NAMESPACE

#endif
