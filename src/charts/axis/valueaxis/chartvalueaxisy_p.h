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

#ifndef CHARTVALUEAXISY_H
#define CHARTVALUEAXISY_H

#include <private/verticalaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QValueAxis;

class Q_CHARTS_EXPORT ChartValueAxisY : public VerticalAxis
{
    Q_OBJECT
public:
    ChartValueAxisY(QValueAxis *axis, QGraphicsItem *item = 0);
    ~ChartValueAxisY();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;
protected:
    QList<qreal> calculateLayout() const override;
    void updateGeometry() override;
private Q_SLOTS:
    void handleTickCountChanged(int tick);
    void handleMinorTickCountChanged(int tick);
    void handleLabelFormatChanged(const QString &format);
    void handleTickIntervalChanged(qreal interval);
    void handleTickAnchorChanged(qreal anchor);
    void handleTickTypeChanged(QValueAxis::TickType type);

private:
    QValueAxis *m_axis;
};

QT_END_NAMESPACE

#endif /* CHARTVALUEAXISY_H */
