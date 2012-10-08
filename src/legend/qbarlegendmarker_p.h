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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBARLEGENDMARKER_P_H
#define QBARLEGENDMARKER_P_H

#include "qchartglobal.h"
#include "qlegendmarker_p.h"
#include "legendmarkeritem_p.h"
#include <QAbstractBarSeries>
#include <QBarSet>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

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

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARLEGENDMARKER_P_H
