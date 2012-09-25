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

    void scaleDomain(Domain &domain);
    ChartElement *createGraphics(ChartPresenter *presenter);
    QList<LegendMarker *> createLegendMarker(QLegend *legend);
    void initializeAxis(QAbstractAxis *axis);
    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;

    void updateDerivativeData();
    void setSizes(qreal innerSize, qreal outerSize);

    static QPieSeriesPrivate *fromSeries(QPieSeries *series);

signals:
    void calculatedDataChanged();
    void pieSizeChanged();
    void pieStartAngleChanged();
    void pieEndAngleChanged();
    void horizontalPositionChanged();
    void verticalPositionChanged();

public Q_SLOTS:
    void sliceValueChanged();
    void sliceClicked();
    void sliceHovered(bool state);

private:
    QList<QPieSlice *> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_sum;
    qreal m_holeRelativeSize;

private:
    friend class QLegendPrivate;
    Q_DECLARE_PUBLIC(QPieSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESERIES_P_H
