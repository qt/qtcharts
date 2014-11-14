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
