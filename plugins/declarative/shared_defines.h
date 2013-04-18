/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H

#ifdef CHARTS_FOR_QUICK2
#define QDECLARATIVE_ITEM QQuickItem
#define QDECLARATIVE_PAINTED_ITEM QQuickPaintedItem
#define QDECLARATIVE_LIST_PROPERTY QQmlListProperty
#define QDECLARATIVE_EXTENSION_PLUGIN QQmlExtensionPlugin
#define QDECLARATIVE_PARSER_STATUS QQmlParserStatus
#define LIST_PROPERTY_PARAM_DEFAULTS ,0,0,0

#else
#define QDECLARATIVE_ITEM QDeclarativeItem
#define QDECLARATIVE_PAINTED_ITEM QDeclarativeItem
#define QDECLARATIVE_LIST_PROPERTY QDeclarativeListProperty
#define QDECLARATIVE_EXTENSION_PLUGIN QDeclarativeExtensionPlugin
#define QDECLARATIVE_PARSER_STATUS QDeclarativeParserStatus
#define LIST_PROPERTY_PARAM_DEFAULTS ,0,0

#endif

#endif // SHARED_DEFINES_H
