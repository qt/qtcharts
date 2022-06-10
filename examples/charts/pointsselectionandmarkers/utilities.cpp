// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "utilities.h"

#include <QBrush>
#include <QList>
#include <QPainter>
#include <QPainterPath>

namespace Utilities
{
    QImage redRectangle(qreal imageSize)
    {
        QImage image(imageSize, imageSize, QImage::Format_RGB32);
        QPainter painter;
        painter.begin(&image);
        painter.fillRect(0, 0, imageSize, imageSize, Qt::red);
        painter.end();
        return image;
    }

    QImage yellowRectangle(qreal imageSize)
    {
        QImage image(imageSize, imageSize, QImage::Format_RGB32);
        QPainter painter;
        painter.begin(&image);
        painter.fillRect(0, 0, imageSize, imageSize, Qt::yellow);
        painter.end();
        return image;
    }

    QImage blueTriangle(qreal imageSize)
    {
        return QImage(":/blue_triangle.png").scaled(imageSize, imageSize);
    }

    QImage greenTriangle(qreal imageSize)
    {
        return QImage(":/green_triangle.png").scaled(imageSize, imageSize);
    }

    QImage orangeCircle(qreal imageSize)
    {
        QImage image(imageSize, imageSize, QImage::Format_ARGB32);
        image.fill(QColor(0, 0, 0, 0));
        QPainter paint;
        paint.begin(&image);
        paint.setBrush(QColor(255,127,80));
        QPen pen = paint.pen();
        pen.setWidth(0);
        paint.setPen(pen);
        paint.drawEllipse(0, 0, imageSize * 0.9, imageSize * 0.9);
        paint.end();
        return image;
    }

    QImage lavenderCircle(qreal imageSize)
    {
        QImage image(imageSize, imageSize, QImage::Format_ARGB32);
        image.fill(QColor(0, 0, 0, 0));
        QPainter paint;
        paint.begin(&image);
        paint.setBrush(QColor(147,112,219));
        QPen pen = paint.pen();
        pen.setWidth(0);
        paint.setPen(pen);
        paint.drawEllipse(0, 0, imageSize * 0.9, imageSize * 0.9);
        paint.end();
        return image;
    }

    QImage getPointRepresentation(PointType pointType, int imageSize)
    {
        switch (pointType) {
        case Utilities::PointType::RedRectangle:
            return redRectangle(imageSize);
        case Utilities::PointType::GreenTriangle:
            return greenTriangle(imageSize);
        case Utilities::PointType::OrangeCircle:
            return orangeCircle(imageSize);
        default:
            return redRectangle(imageSize);
        }
    }

    QImage getSelectedPointRepresentation(SelectedPointType pointType, int imageSize)
    {
        switch (pointType) {
        case Utilities::SelectedPointType::BlueTriangle:
            return blueTriangle(imageSize);
        case Utilities::SelectedPointType::YellowRectangle:
            return yellowRectangle(imageSize);
        case Utilities::SelectedPointType::LavenderCircle:
            return lavenderCircle(imageSize);
        default:
            return blueTriangle(imageSize);
        }
    }

    QColor makeLineColor(LineColor lineColor)
    {
        switch (lineColor) {
        case Utilities::LineColor::Blue:
            return QColor(65, 105, 225);
        case Utilities::LineColor::Black:
            return QColor(0,0,0);
        case Utilities::LineColor::Mint:
            return QColor(70, 203, 155);
        default:
            return QColor(0, 0, 0);
        }
    }
}
