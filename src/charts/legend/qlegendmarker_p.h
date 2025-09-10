// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QLEGENDMARKERPRIVATE_H
#define QLEGENDMARKERPRIVATE_H

#include <QtCharts/QChartGlobal>
#include <QGraphicsObject>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsLayoutItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QAbstractSeries;
class QLegend;

class QLegendMarker;
class LegendMarkerItem;

class Q_CHARTS_EXPORT QLegendMarkerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QLegendMarkerPrivate(QLegendMarker *q, QLegend *legend);
    virtual ~QLegendMarkerPrivate();

    // Helper for now. (or declare LegendLayout as friend)
    LegendMarkerItem* item() const { return m_item; }

    virtual QAbstractSeries* series() = 0;
    virtual QObject* relatedObject() = 0;

    void invalidateLegend();
    void invalidateAllItems();

public Q_SLOTS:
    virtual void updated() = 0;
    void handleShapeChange();

protected:
    LegendMarkerItem *m_item;
    QLegend *m_legend;
    bool m_customLabel;
    bool m_customBrush;
    bool m_customPen;

private:
    QLegendMarker *q_ptr;

    friend class QLegendPrivate;
    friend class LegendMarkerItem;
    Q_DECLARE_PUBLIC(QLegendMarker)
};

QT_END_NAMESPACE

#endif // QLEGENDMARKERPRIVATE_H
