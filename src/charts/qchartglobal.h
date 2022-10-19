/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCHARTGLOBAL_H
#define QCHARTGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCharts/qtcharts-config.h>

#define QT_CHARTS_VERSION_STR QT_VERSION_STR
/*
   QT_CHARTS_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QT_CHARTS_VERSION QT_VERSION
/*
   can be used like #if (QT_CHARTS_VERSION >= QT_CHARTS_VERSION_CHECK(1, 1, 0))
*/
#define QT_CHARTS_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#  if defined(QT_BUILD_CHARTS_LIB)
#    define Q_CHARTS_EXPORT Q_DECL_EXPORT
#  else
#    define Q_CHARTS_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_CHARTS_EXPORT
#endif

#define Q_CHARTS_AUTOTEST_EXPORT Q_AUTOTEST_EXPORT

QT_END_NAMESPACE
/*
    On Windows min and max conflict with standard macros
*/
#ifdef Q_OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#endif // QCHARTGLOBAL_H
