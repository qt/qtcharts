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

#ifndef DECLARATIVE_MARGINS_H
#define DECLARATIVE_MARGINS_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>
#include <QtCore/QMargins>
#include <private/declarativechartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeMargins : public QObject, public QMargins
{
    Q_OBJECT
    Q_PROPERTY(int top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(int bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(int left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(int right READ right WRITE setRight NOTIFY rightChanged)
    QML_NAMED_ELEMENT(Margins)
    QML_ADDED_IN_VERSION(1, 1)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Abstract base type")

public:
    explicit DeclarativeMargins(QObject *parent = 0);
    void setTop(int top);
    void setBottom(int bottom);
    void setLeft(int left);
    void setRight(int right);

Q_SIGNALS:
    void topChanged(int top, int bottom, int left, int right);
    void bottomChanged(int top, int bottom, int left, int right);
    void leftChanged(int top, int bottom, int left, int right);
    void rightChanged(int top, int bottom, int left, int right);
};

QT_END_NAMESPACE

#endif // DECLARATIVE_MARGINS_H
