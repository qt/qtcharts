/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
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
