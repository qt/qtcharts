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

#ifndef QCHART_P_H
#define QCHART_P_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class ChartThemeManager;
class ChartPresenter;
class QLegend;
class ChartDataSet;

class Q_CHARTS_EXPORT QChartPrivate
{

public:
    QChartPrivate(QChart *q, QChart::ChartType type);
    ~QChartPrivate();
    QChart *q_ptr;
    QLegend *m_legend;
    ChartDataSet *m_dataset;
    ChartPresenter *m_presenter;
    ChartThemeManager *m_themeManager;
    QChart::ChartType m_type;

    static QPen &defaultPen();
    static QBrush &defaultBrush();
    static QFont &defaultFont();

    void init();
    void zoomIn(qreal factor);
    void zoomOut(qreal factor);
    void zoomIn(const QRectF &rect);
    void zoomReset();
    bool isZoomed();
    void scroll(qreal dx, qreal dy);
};

QT_END_NAMESPACE
#endif
