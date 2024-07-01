// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVEFOREIGNTYPES_H
#define DECLARATIVEFOREIGNTYPES_H

#include <private/declarativechartglobal_p.h>
#include <QtQml/qqml.h>

#if QT_CONFIG(charts_bar_chart)
#include <QtCharts/qbarset.h>
#include <QtCharts/qbarmodelmapper.h>
#include <QtCharts/qhbarmodelmapper.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qabstractbarseries.h>
#endif

#if QT_CONFIG(charts_pie_chart)
#include <QtCharts/qpiemodelmapper.h>
#include <QtCharts/qhpiemodelmapper.h>
#include <QtCharts/qvpiemodelmapper.h>
#include <QtCharts/qpieslice.h>
#endif

#if QT_CONFIG(charts_boxplot_chart)
#include <QtCharts/qboxplotmodelmapper.h>
#include <QtCharts/qhboxplotmodelmapper.h>
#include <QtCharts/qvboxplotmodelmapper.h>
#include <QtCharts/qboxset.h>
#endif

#if QT_CONFIG(charts_candlestick_chart)
#include <QtCharts/qcandlestickmodelmapper.h>
#include <QtCharts/qhcandlestickmodelmapper.h>
#include <QtCharts/qvcandlestickmodelmapper.h>
#include <QtCharts/qcandlestickset.h>
#endif

#if QT_CONFIG(charts_datetime_axis)
#include <QtCharts/qdatetimeaxis.h>
#endif

#include <QtCharts/qxymodelmapper.h>
#include <QtCharts/qhxymodelmapper.h>
#include <QtCharts/qvxymodelmapper.h>

#include <QtCharts/qabstractaxis.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/qlogvalueaxis.h>

#include <QtCharts/qabstractseries.h>
#include <QtCharts/qxyseries.h>

#include <QtCharts/qlegend.h>

QT_BEGIN_NAMESPACE

// These structs specify types for Charts C++ types that need to be exposed in QML

#if QT_CONFIG(charts_bar_chart)
struct CppQBarModelMapper
{
    Q_GADGET
    QML_FOREIGN(QBarModelMapper)
    QML_NAMED_ELEMENT(BarModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQHBarModelMapper
{
    Q_GADGET
    QML_FOREIGN(QHBarModelMapper)
    QML_NAMED_ELEMENT(HBarModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQVBarModelMapper
{
    Q_GADGET
    QML_FOREIGN(QVBarModelMapper)
    QML_NAMED_ELEMENT(VBarModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct BarCategoriesAxis
{
    Q_GADGET
    QML_FOREIGN(QBarCategoryAxis)
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQBarCategoryAxis
{
    Q_GADGET
    QML_FOREIGN(QBarCategoryAxis)
    QML_NAMED_ELEMENT(BarCategoryAxis)
    QML_ADDED_IN_VERSION(1, 1)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQAbstractBarSeries
{
    Q_GADGET
    QML_FOREIGN(QAbstractBarSeries)
    QML_NAMED_ELEMENT(AbstractBarSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQListBarSet
{
    Q_GADGET
    QML_ANONYMOUS
    QML_FOREIGN(QList<QBarSet *>)
    QML_SEQUENTIAL_CONTAINER(QBarSet *)
};
#endif

#if QT_CONFIG(charts_pie_chart)
struct CppQPieModelMapper
{
    Q_GADGET
    QML_FOREIGN(QPieModelMapper)
    QML_NAMED_ELEMENT(PieModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQHPieModelMapper
{
    Q_GADGET
    QML_FOREIGN(QHPieModelMapper)
    QML_NAMED_ELEMENT(HPieModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQVPieModelMapper
{
    Q_GADGET
    QML_FOREIGN(QVPieModelMapper)
    QML_NAMED_ELEMENT(VPieModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQListPieSlice
{
    Q_GADGET
    QML_ANONYMOUS
    QML_FOREIGN(QList<QPieSlice *>)
    QML_SEQUENTIAL_CONTAINER(QPieSlice *)
};
#endif

#if QT_CONFIG(charts_boxplot_chart)
struct CppQBoxPlotModelMapper
{
    Q_GADGET
    QML_FOREIGN(QBoxPlotModelMapper)
    QML_NAMED_ELEMENT(BoxPlotModelMapper)
    QML_ADDED_IN_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQHBoxPlotModelMapper
{
    Q_GADGET
    QML_FOREIGN(QHBoxPlotModelMapper)
    QML_NAMED_ELEMENT(HBoxPlotModelMapper)
    QML_ADDED_IN_VERSION(2, 0)
};

struct CppQVBoxPlotModelMapper
{
    Q_GADGET
    QML_FOREIGN(QVBoxPlotModelMapper)
    QML_NAMED_ELEMENT(VBoxPlotModelMapper)
    QML_ADDED_IN_VERSION(2, 0)
};

struct CppQListBoxSet
{
    Q_GADGET
    QML_ANONYMOUS
    QML_FOREIGN(QList<QBoxSet *>)
    QML_SEQUENTIAL_CONTAINER(QBoxSet *)
};
#endif

#if QT_CONFIG(charts_candlestick_chart)
struct CppQCandlestickModelMapper
{
    Q_GADGET
    QML_FOREIGN(QCandlestickModelMapper)
    QML_NAMED_ELEMENT(CandlestickModelMapper)
    QML_ADDED_IN_VERSION(2, 2)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQHCandlestickModelMapper
{
    Q_GADGET
    QML_FOREIGN(QHCandlestickModelMapper)
    QML_NAMED_ELEMENT(HCandlestickModelMapper)
    QML_ADDED_IN_VERSION(2, 2)
};

struct CppQVCandlestickModelMapper
{
    Q_GADGET
    QML_FOREIGN(QVCandlestickModelMapper)
    QML_NAMED_ELEMENT(VCandlestickModelMapper)
    QML_ADDED_IN_VERSION(2, 2)
};

struct CppQListCandlestickSet
{
    Q_GADGET
    QML_ANONYMOUS
    QML_FOREIGN(QList<QCandlestickSet *>)
    QML_SEQUENTIAL_CONTAINER(QCandlestickSet *)
};
#endif

#if QT_CONFIG(charts_datetime_axis)
struct CppQDateTimeAxis
{
    Q_GADGET
    QML_FOREIGN(QDateTimeAxis)
    QML_NAMED_ELEMENT(DateTimeAxis)
    QML_ADDED_IN_VERSION(1, 1)
    QML_EXTRA_VERSION(2, 0)
};
#endif

struct CppQXYModelMapper
{
    Q_GADGET
    QML_FOREIGN(QXYModelMapper)
    QML_NAMED_ELEMENT(XYModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQHXYModelMapper
{
    Q_GADGET
    QML_FOREIGN(QHXYModelMapper)
    QML_NAMED_ELEMENT(HXYModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQVXYModelMapper
{
    Q_GADGET
    QML_FOREIGN(QVXYModelMapper)
    QML_NAMED_ELEMENT(VXYModelMapper)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQAbstractAxis
{
    Q_GADGET
    QML_FOREIGN(QAbstractAxis)
    QML_NAMED_ELEMENT(AbstractAxis)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct ValuesAxis
{
    Q_GADGET
    QML_FOREIGN(QValueAxis)
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
};

struct ValueAxis
{
    Q_GADGET
    QML_FOREIGN(QValueAxis)
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1, 1)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQLogValueAxis
{
    Q_GADGET
    QML_FOREIGN(QLogValueAxis)
    QML_NAMED_ELEMENT(LogValueAxis)
    QML_ADDED_IN_VERSION(1, 3)
    QML_EXTRA_VERSION(2, 0)
};

struct CppQAbstractSeries
{
    Q_GADGET
    QML_FOREIGN(QAbstractSeries)
    QML_NAMED_ELEMENT(AbstractSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQXYSeries
{
    Q_GADGET
    QML_FOREIGN(QXYSeries)
    QML_NAMED_ELEMENT(XYSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

struct CppQHashPointConfiguration
{
    Q_GADGET
    QML_ANONYMOUS
    QML_FOREIGN(QXYSeries::PointsConfigurationHash)
    QML_EXTENDED(CppQHashPointConfiguration)
};

struct CppQLegend
{
    Q_GADGET
    QML_FOREIGN(QLegend)
    QML_NAMED_ELEMENT(Legend)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)
    QML_UNCREATABLE("Uncreatable base type")
};

// You cannot do anything useful with a graphics layout here.
// Make it impossible to pass it around in QML.
struct CppQGraphicsLayout
{
    Q_GADGET
    QML_FOREIGN(QGraphicsLayout)
    QML_USING(void)
};

struct CppQPen
{
    Q_GADGET
    QML_FOREIGN(QPen)
    QML_EXTENDED(CppQPen)
    QML_ANONYMOUS
};

struct CppQBrush
{
    Q_GADGET
    QML_FOREIGN(QBrush)
    QML_EXTENDED(CppQBrush)
    QML_ANONYMOUS
};

QT_END_NAMESPACE

#endif // DECLARATIVEFOREIGNTYPES_H
