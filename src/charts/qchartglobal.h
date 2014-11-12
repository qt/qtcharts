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

#ifndef QCHARTGLOBAL_H
#define QCHARTGLOBAL_H

#include <QtCore/QtGlobal>

#define QT_CHARTS_VERSION_STR   "2.0.0"
/*
   QT_CHARTS_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QT_CHARTS_VERSION       0x020000
/*
   can be used like #if (QT_CHARTS_VERSION >= QT_CHARTS_VERSION_CHECK(1, 1, 0))
*/
#define QT_CHARTS_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#if defined(QT_CHARTS_LIBRARY)
#  define QT_CHARTS_EXPORT Q_DECL_EXPORT
#else
#  define QT_CHARTS_EXPORT Q_DECL_IMPORT
#endif

#if defined(BUILD_PRIVATE_UNIT_TESTS) && defined(QT_CHARTS_LIBRARY)
#  define QT_CHARTS_AUTOTEST_EXPORT Q_DECL_EXPORT
#elif defined(BUILD_PRIVATE_UNIT_TESTS) && !defined(QT_CHARTS_LIBRARY)
#  define QT_CHARTS_AUTOTEST_EXPORT Q_DECL_IMPORT
#else
#  define QT_CHARTS_AUTOTEST_EXPORT
#endif

#ifdef QT_CHARTS_STATICLIB
#  undef QT_CHARTS_EXPORT
#  undef QT_CHARTS_AUTOTEST_EXPORT
#  define QT_CHARTS_EXPORT
#  define QT_CHARTS_AUTOTEST_EXPORT
#endif

#define QT_CHARTS_NAMESPACE QtCharts

#ifdef QT_CHARTS_NAMESPACE
#  define QT_CHARTS_BEGIN_NAMESPACE namespace QT_CHARTS_NAMESPACE {
#  define QT_CHARTS_END_NAMESPACE }
#  define QT_CHARTS_USE_NAMESPACE using namespace QT_CHARTS_NAMESPACE;
#else
#  define QT_CHARTS_BEGIN_NAMESPACE
#  define QT_CHARTS_END_NAMESPACE
#  define QT_CHARTS_USE_NAMESPACE
#endif

/*
    On Windows min and max conflict with standard macros
*/
#ifdef Q_OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#endif // QCHARTGLOBAL_H
