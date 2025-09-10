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

#ifndef DECLARATIVE_XY_POINT_H
#define DECLARATIVE_XY_POINT_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QChartGlobal>
#include <private/declarativechartglobal_p.h>
#include <QtCore/QObject>
#include <QtCore/QPointF>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeXYPoint : public QObject, public QPointF
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    QML_NAMED_ELEMENT(XYPoint)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeXYPoint(QObject *parent = 0);
};

QT_END_NAMESPACE

#endif // DECLARATIVE_XY_POINT_H
