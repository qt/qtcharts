/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef BRUSHWIDGET_H
#define BRUSHWIDGET_H

#include <QWidget>

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
