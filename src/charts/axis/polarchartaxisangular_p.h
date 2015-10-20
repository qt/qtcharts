/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef POLARCHARTAXISANGULAR_P_H
#define POLARCHARTAXISANGULAR_P_H

#include <private/polarchartaxis_p.h>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE

class PolarChartAxisAngular : public PolarChartAxis
{
    Q_OBJECT
public:
    PolarChartAxisAngular(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~PolarChartAxisAngular();

    Qt::Orientation orientation() const;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    virtual void updateGeometry();
    virtual void createItems(int count);
    virtual void updateMinorTickItems();

    qreal preferredAxisRadius(const QSizeF &maxSize);

public Q_SLOTS:
    virtual void handleArrowPenChanged(const QPen &pen);
    virtual void handleGridPenChanged(const QPen &pen);
    virtual void handleMinorArrowPenChanged(const QPen &pen);
    virtual void handleMinorGridPenChanged(const QPen &pen);
    virtual void handleGridLineColorChanged(const QColor &color);
    virtual void handleMinorGridLineColorChanged(const QColor &color);

private:
    QRectF moveLabelToPosition(qreal angularCoordinate, QPointF labelPoint, QRectF labelRect) const;
};

QT_CHARTS_END_NAMESPACE

#endif // POLARCHARTAXISANGULAR_P_H
