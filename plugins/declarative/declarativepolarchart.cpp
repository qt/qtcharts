/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "declarativepolarchart.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#ifdef QDOC_QT5
/*!
    \qmltype PolarChartView
    \instantiates DeclarativePolarChart
    \inqmlmodule QtCommercial.Chart

    \include doc/src/declarativepolarchart.qdocinc
*/
#else
/*!
    \qmlclass PolarChartView DeclarativePolarChart

    \include ../doc/src/declarativepolarchart.qdocinc
*/
#endif

DeclarativePolarChart::DeclarativePolarChart(QDECLARATIVE_ITEM *parent)
    : DeclarativeChart(QChart::ChartTypePolar, parent)
{
}

DeclarativePolarChart::~DeclarativePolarChart()
{
}

#include "moc_declarativepolarchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
