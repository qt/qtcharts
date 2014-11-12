/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QPIESERIES_P_H
#define QPIESERIES_P_H

#include <QtCharts/QPieSeries>
#include <private/qabstractseries_p.h>

QT_CHARTS_BEGIN_NAMESPACE
class QLegendPrivate;

class QPieSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QPieSeriesPrivate(QPieSeries *parent);
    ~QPieSeriesPrivate();

    void initializeDomain();
    void initializeAxes();
    void initializeGraphics(QGraphicsItem* parent);
    void initializeAnimations(QtCharts::QChart::AnimationOptions options);
    void initializeTheme(int index, ChartTheme* theme, bool forced = false);

    QList<QLegendMarker *> createLegendMarkers(QLegend *legend);

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const;

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
    void slicePressed();
    void sliceReleased();
    void sliceDoubleClicked();

private:
    QList<QPieSlice *> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_sum;
    qreal m_holeRelativeSize;

public:
    friend class QLegendPrivate;
    Q_DECLARE_PUBLIC(QPieSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QPIESERIES_P_H
