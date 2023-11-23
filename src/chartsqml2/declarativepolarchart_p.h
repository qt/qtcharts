// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVEPOLARCHART_H
#define DECLARATIVEPOLARCHART_H

#include <QtQml/qqmlregistration.h>
#include <QtCore/QtGlobal>
#include <QtQuick/QQuickItem>
#include <private/declarativechartglobal_p.h>
#include <private/declarativechart_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativePolarChart : public DeclarativeChart
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PolarChartView)
    QML_ADDED_IN_VERSION(1, 3)
    QML_EXTRA_VERSION(2, 0)
public:
    DeclarativePolarChart(QQuickItem *parent = 0);
    ~DeclarativePolarChart();
};

QT_END_NAMESPACE

#endif // DECLARATIVEPOLARCHART_H
