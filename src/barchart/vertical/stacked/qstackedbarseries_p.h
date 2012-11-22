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

#ifndef QSTACKEDBARSERIES_P_H
#define QSTACKEDBARSERIES_P_H

#include "qabstractbarseries_p.h"
#include "abstractdomain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE


class QStackedBarSeriesPrivate: public QAbstractBarSeriesPrivate
{
public:
    QStackedBarSeriesPrivate(QStackedBarSeries *q);
    void initializeGraphics(QGraphicsItem* parent);
    void initializeAnimations(QtCommercialChart::QChart::AnimationOptions options);
    void initializeDomain();
private:
    Q_DECLARE_PUBLIC(QStackedBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
