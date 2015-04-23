/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "objectinspectorwidget.h"
#include <QtGui/QIcon>
#include <QtGui/QPainter>
#include <QtGui/QPixmapCache>

InspectorWidget::InspectorWidget()
{

}

InspectorWidget::~InspectorWidget()
{

}

QIcon InspectorWidget::getColorIcon(const QColor& color,const QSize &size) const
{

    QString key = QString("COLOR_ICON=%1:%2x%3").arg(color.name()).arg(size.width()).arg(size.height());

    QPixmap pixmap(size);

    if (!QPixmapCache::find(key, &pixmap)) {
        pixmap.fill(Qt::white);
        QPainter painter(&pixmap);
        painter.fillRect(2, 2, 46, 46, color);
        QPixmapCache::insert(key, pixmap);
    }

    return QIcon(pixmap);
}
