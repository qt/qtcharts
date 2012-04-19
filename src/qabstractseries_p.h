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

#ifndef QABSTRACTSERIES_P_H
#define QABSTRACTSERIES_P_H

#include "qabstractseries.h"

class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;
class ChartPresenter;
class Chart;
class LegendMarker;
class QLegend;
class ChartDataSet;

class QAbstractSeriesPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractSeriesPrivate(QAbstractSeries *q);
    ~QAbstractSeriesPrivate();

    virtual void scaleDomain(Domain& domain) = 0;
    virtual Chart* createGraphics(ChartPresenter* presenter) = 0;
    virtual QList<LegendMarker*> createLegendMarker(QLegend* legend) = 0;

protected:
    QAbstractSeries *q_ptr;
    QAbstractItemModel *m_model;
    ChartDataSet *m_dataset;
    int m_mapFirst;
    int m_mapCount;
    Qt::Orientation m_mapOrientation;
    QString m_name;

    friend class QAbstractSeries;
    friend class ChartDataSet;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
