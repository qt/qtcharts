/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

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

QT_CHARTS_BEGIN_NAMESPACE

class ChartThemeManager;
class ChartPresenter;
class QLegend;
class ChartDataSet;

class Q_CHARTS_PRIVATE_EXPORT QChartPrivate
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

QT_CHARTS_END_NAMESPACE
#endif
