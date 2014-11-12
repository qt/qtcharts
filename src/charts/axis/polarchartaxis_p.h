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

public Q_SLOTS:
    virtual void handleShadesBrushChanged(const QBrush &brush);
    virtual void handleShadesPenChanged(const QPen &pen);

private:
    void deleteItems(int count);
};

QT_CHARTS_END_NAMESPACE

#endif // POLARCHARTAXIS_P_H
