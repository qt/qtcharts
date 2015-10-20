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

#ifndef POLARCHARTAXIS_P_H
#define POLARCHARTAXIS_P_H

#include <private/chartaxiselement_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class PolarChartAxis : public ChartAxisElement
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsLayoutItem)
public:
    PolarChartAxis(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~PolarChartAxis();

    void setGeometry(const QRectF &axis, const QRectF &grid);
    virtual qreal preferredAxisRadius(const QSizeF &maxSize) = 0;
    int tickWidth() { return 3; }

public: // from ChartAxisElement
    QRectF gridGeometry() const;
    bool isEmpty();

protected:
    void updateLayout(QVector<qreal> &layout);

protected: // virtual functions
    virtual void createItems(int count) = 0;
    virtual void createAxisLabels(const QVector<qreal> &layout) = 0;
    virtual void updateMinorTickItems() = 0;

public Q_SLOTS:
    virtual void handleShadesBrushChanged(const QBrush &brush);
    virtual void handleShadesPenChanged(const QPen &pen);

private:
    void deleteItems(int count);
};

QT_CHARTS_END_NAMESPACE

#endif // POLARCHARTAXIS_P_H
