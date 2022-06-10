// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
