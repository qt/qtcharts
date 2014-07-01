/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QAREALEGENDMARKER_H
#define QAREALEGENDMARKER_H

#include <QtCharts/qchartglobal.h>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QAreaSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QAreaLegendMarkerPrivate;

class QT_CHARTS_EXPORT QAreaLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QAreaLegendMarker(QAreaSeries *series, QLegend *legend, QObject *parent = 0);
    virtual ~QAreaLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypeArea; }

    // Related series
    virtual QAreaSeries* series();

protected:
    QAreaLegendMarker(QAreaLegendMarkerPrivate &d, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QAreaLegendMarker)
    Q_DISABLE_COPY(QAreaLegendMarker)

};

QT_CHARTS_END_NAMESPACE

#endif // QAREALEGENDMARKER_H
