/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QXYLEGENDMARKER_H
#define QXYLEGENDMARKER_H

#include <QChartGlobal>
#include <QLegendMarker>
#include <QXYSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYLegendMarkerPrivate;

class QTCOMMERCIALCHART_EXPORT QXYLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QXYLegendMarker(QXYSeries *series, QLegend *legend, QObject *parent = 0);
    virtual ~QXYLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypeXY; }

    // Related series
    virtual QXYSeries* series();

protected:
    QXYLegendMarker(QXYLegendMarkerPrivate &d, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QXYLegendMarker)
    Q_DISABLE_COPY(QXYLegendMarker)

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QXYLEGENDMARKER_H
