/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#ifndef QPIELEGENDMARKER_H
#define QPIELEGENDMARKER_H

#include <QChartGlobal>
#include <QLegendMarker>
#include <QPieSeries>
#include <QPieSlice>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieLegendMarkerPrivate;

// TODO: No export? make this private. QLegendMarker should be enough for user of the api (why expose the details?)
class QTCOMMERCIALCHART_EXPORT QPieLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QPieLegendMarker(QPieSeries* series, QPieSlice* slice, QLegend *legend, QObject *parent = 0);
    virtual ~QPieLegendMarker();
    
    virtual LegendMarkerType type() { return LegendMarkerTypePie; }

    // Related series and slice
    QPieSeries* series();
    QPieSlice* slice();

protected:
    QPieLegendMarker(QPieLegendMarkerPrivate &d, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QPieLegendMarker)
    Q_DISABLE_COPY(QPieLegendMarker)

};

QTCOMMERCIALCHART_END_NAMESPACE
#endif // QPIELEGENDMARKER_H
