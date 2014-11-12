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

#ifndef QAREASERIES_P_H
#define QAREASERIES_P_H

#include <private/qabstractseries_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QAreaSeries;
class QLineSeries;

class QAreaSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QAreaSeriesPrivate(QLineSeries *upperSeries, QLineSeries *lowerSeries, QAreaSeries *q);

    void initializeDomain();
    void initializeAxes();
    void initializeGraphics(QGraphicsItem* parent);
    void initializeTheme(int index, ChartTheme* theme, bool forced = false);
    void initializeAnimations(QChart::AnimationOptions options);

    QList<QLegendMarker *> createLegendMarkers(QLegend *legend);

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation) const;

Q_SIGNALS:
    void updated();

protected:
    QBrush m_brush;
    QPen m_pen;
    QLineSeries *m_upperSeries;
    QLineSeries *m_lowerSeries;
    bool m_pointsVisible;
    QString m_pointLabelsFormat;
    bool m_pointLabelsVisible;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
private:
    Q_DECLARE_PUBLIC(QAreaSeries);
};

QT_CHARTS_END_NAMESPACE

#endif
