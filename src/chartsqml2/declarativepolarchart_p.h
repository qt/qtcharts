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

class Q_QMLCHARTS_PRIVATE_EXPORT DeclarativePolarChart : public DeclarativeChart
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
