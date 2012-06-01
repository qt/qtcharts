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

#ifndef QLEGEND_P_H
#define QLEGEND_P_H

#include "qlegend.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class ChartPresenter;
class QAbstractSeries;

class QLegendPrivate : public QObject
{
    Q_OBJECT
public:
    QLegendPrivate(ChartPresenter *presenter, QChart *chart, QLegend *q);
    ~QLegendPrivate();

    void setOffset(qreal x, qreal y);
    void updateLayout();
    void attachToChart();

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries *series, Domain *domain);
    void handleSeriesRemoved(QAbstractSeries *series);
    void handleSeriesUpdated(QAbstractSeries *series);
    void handleUpdatePieSeries(); //TODO remove this function

private:
    QLegend *q_ptr;
    ChartPresenter *m_presenter;
    QChart* m_chart;
    QGraphicsItemGroup* m_markers;
    Qt::Alignment m_alignment;
    QBrush m_brush;
    QPen m_pen;
    QRectF m_rect;
    qreal m_offsetX;
    qreal m_offsetY;
    qreal m_minWidth;
    qreal m_minHeight;
    qreal m_width;
    qreal m_height;
    bool m_attachedToChart;
    bool m_backgroundVisible;

friend class QLegend;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
