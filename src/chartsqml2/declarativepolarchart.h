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

#ifndef DECLARATIVEPOLARCHART_H
#define DECLARATIVEPOLARCHART_H

#include <QtCore/QtGlobal>
#include <QtQuick/QQuickItem>

#include "declarativechart.h"

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativePolarChart : public DeclarativeChart
{
    Q_OBJECT
public:
    DeclarativePolarChart(QQuickItem *parent = 0);
    ~DeclarativePolarChart();
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVEPOLARCHART_H
