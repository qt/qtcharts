/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVECHARTGLOBAL_H
#define DECLARATIVECHARTGLOBAL_H

#include <QtCore/QtGlobal>
#include <qtcharts-config.h>

#ifndef QT_STATIC
#  if defined(QT_BUILD_QMLCHARTS_LIB)
#    define Q_QMLCHARTS_PRIVATE_EXPORT Q_DECL_EXPORT
#  else
#    define Q_QMLCHARTS_PRIVATE_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_QMLCHARTS_PRIVATE_EXPORT
#endif

void Q_QMLCHARTS_PRIVATE_EXPORT qml_register_types_QtCharts();

#endif // DECLARATIVECHARTGLOBAL_H
