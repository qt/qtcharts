// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QCHARTGLOBAL_H
#define QCHARTGLOBAL_H

#if 0
#pragma qt_class(QChartGlobal)
#endif

#include <QtCore/qglobal.h>
#include <QtCharts/qtcharts-config.h>
#include <QtCharts/qtchartsexports.h>

#define Q_CHARTS_AUTOTEST_EXPORT Q_AUTOTEST_EXPORT

#define QT_CHARTS_VERSION_STR QT_VERSION_STR
/*
   QT_CHARTS_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QT_CHARTS_VERSION QT_VERSION
/*
   can be used like #if (QT_CHARTS_VERSION >= QT_CHARTS_VERSION_CHECK(1, 1, 0))
*/
#define QT_CHARTS_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#endif // QCHARTGLOBAL_H
