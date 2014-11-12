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

#ifndef QLEGENDMARKERPRIVATE_H
#define QLEGENDMARKERPRIVATE_H

#include <QtCharts/QChartGlobal>
#include <QGraphicsObject>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsLayoutItem>

QT_CHARTS_BEGIN_NAMESPACE

class QAbstractSeries;
class QLegend;

class QLegendMarker;
class LegendMarkerItem;

class QLegendMarkerPrivate : public QObject
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

public Q_SLOTS:
    virtual void updated() = 0;

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

QT_CHARTS_END_NAMESPACE

#endif // QLEGENDMARKERPRIVATE_H
