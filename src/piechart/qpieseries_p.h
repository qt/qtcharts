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

#ifndef QPIESERIES_P_H
#define QPIESERIES_P_H

#include "qpieseries.h"
#include "qabstractseries_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QLegendPrivate;

class QPieSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QPieSeriesPrivate(QPieSeries *parent);
    ~QPieSeriesPrivate();

    void scaleDomain(Domain& domain);
    Chart* createGraphics(ChartPresenter *presenter);
    QList<LegendMarker*> createLegendMarker(QLegend *legend);

    void updateDerivativeData();

    static QPieSeriesPrivate* seriesData(QPieSeries &series);

Q_SIGNALS:
    void piePositionChanged();
    void pieSizeChanged();

public Q_SLOTS:
    void sliceChanged();
    void sliceClicked();
    void sliceHovered(bool state);
    bool setRealValue(qreal &value, qreal newValue, qreal max, qreal min = 0.0);

public:
    QList<QPieSlice*> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_sum;

private:
    friend class QLegendPrivate;
    Q_DECLARE_PUBLIC(QPieSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESERIES_P_H
