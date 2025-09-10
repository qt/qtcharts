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

#ifndef CARTESIANCHARTAXIS_H
#define CARTESIANCHARTAXIS_H

#include <QtCharts/QChartGlobal>
#include <private/chartaxiselement_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QAbstractAxis;

class Q_CHARTS_EXPORT CartesianChartAxis : public ChartAxisElement
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsLayoutItem)
public:

    CartesianChartAxis(QAbstractAxis *axis, QGraphicsItem *item = 0, bool intervalAxis = false);
    ~CartesianChartAxis();

    void setGeometry(const QRectF &axis, const QRectF &grid) override;
    QRectF gridGeometry() const override { return m_gridRect; }
    bool emptyAxis() const override;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

    void setDateTimeLabelsFormat(const QString &format);

protected:
    void setGeometry(const QRectF &size) override { Q_UNUSED(size);}
    void updateGeometry() override = 0;
    void updateLayout(const QList<qreal> &layout) override;

public Q_SLOTS:
    void handleArrowPenChanged(const QPen &pen) override;
    void handleGridPenChanged(const QPen &pen) override;
    void handleShadesBrushChanged(const QBrush &brush) override;
    void handleShadesPenChanged(const QPen &pen) override;
    void handleMinorArrowPenChanged(const QPen &pen) override;
    void handleMinorGridPenChanged(const QPen &pen) override;
    void handleGridLineColorChanged(const QColor &color) override;
    void handleMinorGridLineColorChanged(const QColor &color) override;

protected:
    void updateLabelsValues(QValueAxis *axis);
    void updateLabelsDateTimes();

private:
    void createItems(int count);
    void deleteItems(int count);
    void updateMinorTickItems();

private:
    QRectF m_gridRect;

    friend class AxisAnimation;
    friend class LineArrowItem;
};

QT_END_NAMESPACE

#endif /* CARTESIANCHARTAXIS_H */
