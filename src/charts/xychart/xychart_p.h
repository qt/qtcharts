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

#ifndef XYCHART_H
#define XYCHART_H

#include <QtCharts/QChartGlobal>
#include <private/chartitem_p.h>
#include <private/xyanimation_p.h>
#include <QtCharts/QValueAxis>
#include <QtGui/QPen>

QT_CHARTS_BEGIN_NAMESPACE

class ChartPresenter;
class QXYSeries;

class XYChart :  public ChartItem
{
    Q_OBJECT
public:
    explicit XYChart(QXYSeries *series,QGraphicsItem *item = 0);
    ~XYChart() {}

    void setGeometryPoints(const QVector<QPointF> &points);
    QVector<QPointF> geometryPoints() const { return m_points; }

    void setAnimation(XYAnimation *animation);
    ChartAnimation *animation() const { return m_animation; }
    virtual void updateGeometry() = 0;

    bool isDirty() const { return m_dirty; }
    void setDirty(bool dirty);

    void getSeriesRanges(qreal &minX, qreal &maxX, qreal &minY, qreal &maxY);
    QVector<bool> offGridStatusVector();

public Q_SLOTS:
    void handlePointAdded(int index);
    void handlePointRemoved(int index);
    void handlePointReplaced(int index);
    void handlePointsReplaced();
    void handleDomainUpdated();

Q_SIGNALS:
    void clicked(const QPointF &point);
    void hovered(const QPointF &point, bool state);
    void pressed(const QPointF &point);
    void released(const QPointF &point);
    void doubleClicked(const QPointF &point);

protected:
    virtual void updateChart(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, int index = -1);

private:
    inline bool isEmpty();

protected:
    QXYSeries *m_series;
    QVector<QPointF> m_points;
    XYAnimation *m_animation;
    bool m_dirty;

    friend class AreaChartItem;
};

QT_CHARTS_END_NAMESPACE

#endif
