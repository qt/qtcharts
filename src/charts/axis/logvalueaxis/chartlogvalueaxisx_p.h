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

#ifndef CHARTLOGVALUEAXISX_H
#define CHARTLOGVALUEAXISX_H

#include <private/horizontalaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QLogValueAxis;

class Q_CHARTS_EXPORT ChartLogValueAxisX : public HorizontalAxis
{
    Q_OBJECT

public:
    ChartLogValueAxisX(QLogValueAxis *axis, QGraphicsItem *item);
    ~ChartLogValueAxisX();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

protected:
    QList<qreal> calculateLayout() const override;
    void updateGeometry() override;

private Q_SLOTS:
    void handleBaseChanged(qreal base);
    void handleLabelFormatChanged(const QString &format);

private:
    QLogValueAxis *m_axis;
};

QT_END_NAMESPACE

#endif /* CHARTLOGVALUEAXISX_H */
