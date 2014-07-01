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
#ifndef QBARLEGENDMARKER_H
#define QBARLEGENDMARKER_H

#include <QtCharts/qchartglobal.h>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QBarSet>

QT_CHARTS_BEGIN_NAMESPACE

class QLegend;
class QBarLegendMarkerPrivate;

class QT_CHARTS_EXPORT QBarLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QBarLegendMarker(QAbstractBarSeries *series, QBarSet *barset, QLegend *legend, QObject *parent = 0);
    virtual ~QBarLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypeBar; }

    // Related series and barset
    virtual QAbstractBarSeries* series();
    QBarSet* barset();

protected:
    QBarLegendMarker(QBarLegendMarkerPrivate &d, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QBarLegendMarker)
    Q_DISABLE_COPY(QBarLegendMarker)

};

QT_CHARTS_END_NAMESPACE

#endif // QBARLEGENDMARKER_H
