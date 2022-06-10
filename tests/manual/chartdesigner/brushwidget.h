// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef BRUSHWIDGET_H
#define BRUSHWIDGET_H

#include <QtWidgets/QWidget>

class BrushWidget: public QWidget
{
public:
    explicit BrushWidget(QWidget *parent = 0);
    ~BrushWidget();

    QBrush brush() const { return m_brush; }
    void setBrush(const QBrush &brush);

private:
    QBrush m_brush;
};

#endif /* BRUSHWIDGET_H */
