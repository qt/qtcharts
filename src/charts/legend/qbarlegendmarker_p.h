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

#ifndef QBARLEGENDMARKER_P_H
#define QBARLEGENDMARKER_P_H

#include <QtCharts/QChartGlobal>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarSet>

QT_CHARTS_BEGIN_NAMESPACE

class QBarLegendMarker;

class QBarLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QBarLegendMarkerPrivate(QBarLegendMarker *q, QAbstractBarSeries *series, QBarSet *barset, QLegend *legend);
    virtual ~QBarLegendMarkerPrivate();

    virtual QAbstractBarSeries* series();
    virtual QObject* relatedObject();

public Q_SLOTS:
    virtual void updated();

private:
    QBarLegendMarker *q_ptr;
    QAbstractBarSeries *m_series;
    QBarSet *m_barset;

    Q_DECLARE_PUBLIC(QBarLegendMarker)
};

QT_CHARTS_END_NAMESPACE

#endif // QBARLEGENDMARKER_P_H
