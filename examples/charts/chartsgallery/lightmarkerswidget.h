// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef LIGHTMARKERSWIDGET_H
#define LIGHTMARKERSWIDGET_H

#include "contentwidget.h"

#include <QColor>
#include <QImage>

QT_FORWARD_DECLARE_CLASS(QChartView)

class LightMarkersWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit LightMarkersWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;

private:
    enum class PointType {
        RedRectangle,
        GreenTriangle,
        OrangeCircle
    };

    enum class SelectedPointType {
        BlueTriangle,
        YellowRectangle,
        LavenderCircle
    };

    enum class LineColor {
        Blue,
        Black,
        Mint
    };

    QImage rectangle(qreal imageSize, const QColor &color);
    QImage circle(qreal imageSize, const QColor &color);
    QImage blueTriangle(qreal imageSize);
    QImage greenTriangle(qreal imageSize);
    QImage getPointRepresentation(PointType pointType, int imageSize);
    QImage getSelectedPointRepresentation(SelectedPointType pointType, int imageSize);
    QColor makeLineColor(LineColor lineColor);

    QWidget *m_mainWidget = nullptr;
};

#endif
