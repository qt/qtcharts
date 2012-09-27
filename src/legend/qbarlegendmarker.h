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
#ifndef QBARLEGENDMARKER_H
#define QBARLEGENDMARKER_H

#include <QChartGlobal>
#include <QLegendMarker>
#include <QAbstractBarSeries>
#include <QBarSet>
//#include "qbarlegendmarker_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegend;
class QBarLegendMarkerPrivate;

class QTCOMMERCIALCHART_EXPORT QBarLegendMarker : public QLegendMarker
{
    Q_OBJECT
public:
    explicit QBarLegendMarker(QAbstractBarSeries* series, QBarSet* barset, QLegend *legend, QObject *parent = 0);
    virtual ~QBarLegendMarker();

    virtual QAbstractBarSeries* series();
    virtual QBarSet* peerObject();    // TODO: rename to slice and remove these virtuals from base class?

protected:
    QBarLegendMarker(QBarLegendMarkerPrivate &d, QObject *parent = 0);

//Q_SIGNALS:

//public Q_SLOTS:

private:
    Q_DECLARE_PRIVATE(QBarLegendMarker)
    Q_DISABLE_COPY(QBarLegendMarker)

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARLEGENDMARKER_H
