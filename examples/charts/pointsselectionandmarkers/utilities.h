// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef UTILITIES_H
#define UTILITIES_H

#include <QImage>

namespace Utilities
{
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

    QImage redRectangle(qreal imageSize);
    QImage yellowRectangle(qreal imageSize);
    QImage blueTriangle(qreal imageSize);
    QImage greenTriangle(qreal imageSize);
    QImage orangeCircle(qreal imageSize);
    QImage lavenderCircle(qreal imageSize);
    QImage getPointRepresentation(PointType pointType, int imageSize);
    QImage getSelectedPointRepresentation(SelectedPointType pointType, int imageSize);
    QColor makeLineColor(LineColor lineColor);
}

#endif // UTILITIES_H
