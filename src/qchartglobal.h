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

#ifndef QCHARTGLOBAL_H
#define QCHARTGLOBAL_H

#include <qglobal.h>

#define QTCOMMERCIALCHART_VERSION_STR   "1.2.1"
/*
   QTCOMMERCIALCHART_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QTCOMMERCIALCHART_VERSION       0x010201
/*
   can be used like #if (QTCOMMERCIALCHART_VERSION >= QTCOMMERCIALCHART_VERSION_CHECK(1, 1, 0))
*/
#define QTCOMMERCIALCHART_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#if defined(QTCOMMERCIALCHART_LIBRARY)
#  define QTCOMMERCIALCHART_EXPORT Q_DECL_EXPORT
#else
#  define QTCOMMERCIALCHART_EXPORT Q_DECL_IMPORT
#endif

#if defined(BUILD_PRIVATE_UNIT_TESTS) && defined(QTCOMMERCIALCHART_LIBRARY)
#  define QTCOMMERCIALCHART_AUTOTEST_EXPORT Q_DECL_EXPORT
#elif defined(BUILD_PRIVATE_UNIT_TESTS) && !defined(QTCOMMERCIALCHART_LIBRARY)
#  define QTCOMMERCIALCHART_AUTOTEST_EXPORT Q_DECL_IMPORT
#else
#  define QTCOMMERCIALCHART_AUTOTEST_EXPORT
#endif

#ifdef QTCOMMERCIALCHART_STATICLIB
#  undef QTCOMMERCIALCHART_EXPORT
#  undef QTCOMMERCIALCHART_AUTOTEST_EXPORT
#  define QTCOMMERCIALCHART_EXPORT
#  define QTCOMMERCIALCHART_AUTOTEST_EXPORT
#endif

#define QTCOMMERCIALCHART_NAMESPACE QtCommercialChart

#ifdef QTCOMMERCIALCHART_NAMESPACE
#  define QTCOMMERCIALCHART_BEGIN_NAMESPACE namespace QTCOMMERCIALCHART_NAMESPACE {
#  define QTCOMMERCIALCHART_END_NAMESPACE }
#  define QTCOMMERCIALCHART_USE_NAMESPACE using namespace QTCOMMERCIALCHART_NAMESPACE;
#else
#  define QTCOMMERCIALCHART_BEGIN_NAMESPACE
#  define QTCOMMERCIALCHART_END_NAMESPACE
#  define QTCOMMERCIALCHART_USE_NAMESPACE
#endif

#if defined(DEVELOPMENT_BUILD) && !defined(QT_NO_DEBUG)
#include <stdarg.h>
#include <QDebug>

#define CHART_DEBUG chartDebug(3,__LINE__,__FILE__,__FUNCTION__)

static inline QDebug chartDebug(int numargs,...)
{
    va_list valist;
    va_start(valist, numargs);
    //for( int i = 0 ; i < numargs; i++ )
    int line = va_arg(valist, int);
    char *file = va_arg(valist, char *);
    char *function = va_arg(valist, char *);
    va_end(valist);
    return qDebug() << QString().append(function).append("(").append(file).append(":%1)").arg(line);
}
#endif

#endif // QCHARTGLOBAL_H
