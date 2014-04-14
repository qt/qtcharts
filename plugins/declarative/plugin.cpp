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

#include "qchart.h"
#include "qabstractaxis.h"
#include "qvalueaxis.h"
#include "qlogvalueaxis.h"
#include "declarativecategoryaxis.h"
#include "qbarcategoryaxis.h"
#include "declarativechart.h"
#include "declarativepolarchart.h"
#include "declarativexypoint.h"
#include "declarativelineseries.h"
#include "declarativesplineseries.h"
#include "declarativeareaseries.h"
#include "declarativescatterseries.h"
#include "declarativebarseries.h"
#include "declarativeboxplotseries.h"
#include "declarativepieseries.h"
#include "declarativeaxes.h"
#include "qvxymodelmapper.h"
#include "qhxymodelmapper.h"
#include "qhpiemodelmapper.h"
#include "qvpiemodelmapper.h"
#include "qhbarmodelmapper.h"
#include "qvbarmodelmapper.h"
#include "declarativemargins.h"
#include "qarealegendmarker.h"
#include "qbarlegendmarker.h"
#include "qpielegendmarker.h"
#include "qxylegendmarker.h"
#ifndef QT_ON_ARM
    #include "qdatetimeaxis.h"
#endif
#include "shared_defines.h"
#include <QAbstractItemModel>
#ifdef CHARTS_FOR_QUICK2
#include <QtQml/QQmlExtensionPlugin>
#else
#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#endif

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QList<QPieSlice *>)
Q_DECLARE_METATYPE(QList<QBarSet *>)
Q_DECLARE_METATYPE(QList<QAbstractAxis *>)

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

Q_DECLARE_METATYPE(DeclarativeChart *)
Q_DECLARE_METATYPE(DeclarativePolarChart *)
Q_DECLARE_METATYPE(DeclarativeMargins *)
Q_DECLARE_METATYPE(DeclarativeAreaSeries *)
Q_DECLARE_METATYPE(DeclarativeBarSeries *)
Q_DECLARE_METATYPE(DeclarativeBarSet *)
Q_DECLARE_METATYPE(DeclarativeBoxPlotSeries *)
Q_DECLARE_METATYPE(DeclarativeBoxSet *)
Q_DECLARE_METATYPE(DeclarativeLineSeries *)
Q_DECLARE_METATYPE(DeclarativePieSeries *)
Q_DECLARE_METATYPE(DeclarativePieSlice *)
Q_DECLARE_METATYPE(DeclarativeScatterSeries *)
Q_DECLARE_METATYPE(DeclarativeSplineSeries *)

Q_DECLARE_METATYPE(QAbstractAxis *)
Q_DECLARE_METATYPE(QValueAxis *)
Q_DECLARE_METATYPE(QBarCategoryAxis *)
Q_DECLARE_METATYPE(QCategoryAxis *)
Q_DECLARE_METATYPE(QDateTimeAxis *)
Q_DECLARE_METATYPE(QLogValueAxis *)

Q_DECLARE_METATYPE(QLegend *)
Q_DECLARE_METATYPE(QLegendMarker *)
Q_DECLARE_METATYPE(QAreaLegendMarker *)
Q_DECLARE_METATYPE(QBarLegendMarker *)
Q_DECLARE_METATYPE(QPieLegendMarker *)

Q_DECLARE_METATYPE(QHPieModelMapper *)
Q_DECLARE_METATYPE(QHXYModelMapper *)
Q_DECLARE_METATYPE(QPieModelMapper *)
Q_DECLARE_METATYPE(QHBarModelMapper *)
Q_DECLARE_METATYPE(QBarModelMapper *)
Q_DECLARE_METATYPE(QVBarModelMapper *)
Q_DECLARE_METATYPE(QVPieModelMapper *)
Q_DECLARE_METATYPE(QVXYModelMapper *)
Q_DECLARE_METATYPE(QXYLegendMarker *)
Q_DECLARE_METATYPE(QXYModelMapper *)

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QXYSeries *)
Q_DECLARE_METATYPE(QAbstractBarSeries *)
Q_DECLARE_METATYPE(QBarSeries *)
Q_DECLARE_METATYPE(QBarSet *)
Q_DECLARE_METATYPE(QAreaSeries *)
Q_DECLARE_METATYPE(QHorizontalBarSeries *)
Q_DECLARE_METATYPE(QHorizontalPercentBarSeries *)
Q_DECLARE_METATYPE(QHorizontalStackedBarSeries *)
Q_DECLARE_METATYPE(QLineSeries *)
Q_DECLARE_METATYPE(QPercentBarSeries *)
Q_DECLARE_METATYPE(QPieSeries *)
Q_DECLARE_METATYPE(QPieSlice *)
Q_DECLARE_METATYPE(QScatterSeries *)
Q_DECLARE_METATYPE(QSplineSeries *)
Q_DECLARE_METATYPE(QStackedBarSeries *)

#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartQmlPlugin : public QDECLARATIVE_EXTENSION_PLUGIN
{
    Q_OBJECT

#ifdef CHARTS_FOR_QUICK2
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
#else
# if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDeclarativeExtensionInterface")
# endif
#endif

public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtCommercial.Chart"));

        qRegisterMetaType<QList<QPieSlice *> >();
        qRegisterMetaType<QList<QBarSet *> >();
        qRegisterMetaType<QList<QAbstractAxis *> >();

        // QtCommercial.Chart 1.0
        qmlRegisterType<DeclarativeChart>(uri, 1, 0, "ChartView");
        qmlRegisterType<DeclarativeXYPoint>(uri, 1, 0, "XYPoint");
        qmlRegisterType<DeclarativeScatterSeries>(uri, 1, 0, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries>(uri, 1, 0, "LineSeries");
        qmlRegisterType<DeclarativeSplineSeries>(uri, 1, 0, "SplineSeries");
        qmlRegisterType<DeclarativeAreaSeries>(uri, 1, 0, "AreaSeries");
        qmlRegisterType<DeclarativeBarSeries>(uri, 1, 0, "BarSeries");
        qmlRegisterType<DeclarativeStackedBarSeries>(uri, 1, 0, "StackedBarSeries");
        qmlRegisterType<DeclarativePercentBarSeries>(uri, 1, 0, "PercentBarSeries");
        qmlRegisterType<DeclarativePieSeries>(uri, 1, 0, "PieSeries");
        qmlRegisterType<QPieSlice>(uri, 1, 0, "PieSlice");
        qmlRegisterType<DeclarativeBarSet>(uri, 1, 0, "BarSet");
        qmlRegisterType<QHXYModelMapper>(uri, 1, 0, "HXYModelMapper");
        qmlRegisterType<QVXYModelMapper>(uri, 1, 0, "VXYModelMapper");
        qmlRegisterType<QHPieModelMapper>(uri, 1, 0, "HPieModelMapper");
        qmlRegisterType<QVPieModelMapper>(uri, 1, 0, "VPieModelMapper");
        qmlRegisterType<QHBarModelMapper>(uri, 1, 0, "HBarModelMapper");
        qmlRegisterType<QVBarModelMapper>(uri, 1, 0, "VBarModelMapper");
        qmlRegisterType<QValueAxis>(uri, 1, 0, "ValuesAxis");
        qmlRegisterType<QBarCategoryAxis>(uri, 1, 0, "BarCategoriesAxis");
        qmlRegisterUncreatableType<QLegend>(uri, 1, 0, "Legend",
                                            QLatin1String("Trying to create uncreatable: Legend."));
        qmlRegisterUncreatableType<QXYSeries>(uri, 1, 0, "XYSeries",
                                              QLatin1String("Trying to create uncreatable: XYSeries."));
        qmlRegisterUncreatableType<QAbstractItemModel>(uri, 1, 0, "AbstractItemModel",
                                                       QLatin1String("Trying to create uncreatable: AbstractItemModel."));
        qmlRegisterUncreatableType<QXYModelMapper>(uri, 1, 0, "XYModelMapper",
                                                   QLatin1String("Trying to create uncreatable: XYModelMapper."));
        qmlRegisterUncreatableType<QPieModelMapper>(uri, 1, 0, "PieModelMapper",
                                                    QLatin1String("Trying to create uncreatable: PieModelMapper."));
        qmlRegisterUncreatableType<QBarModelMapper>(uri, 1, 0, "BarModelMapper",
                                                    QLatin1String("Trying to create uncreatable: BarModelMapper."));
        qmlRegisterUncreatableType<QAbstractSeries>(uri, 1, 0, "AbstractSeries",
                                                    QLatin1String("Trying to create uncreatable: AbstractSeries."));
        qmlRegisterUncreatableType<QAbstractBarSeries>(uri, 1, 0, "AbstractBarSeries",
                                                       QLatin1String("Trying to create uncreatable: AbstractBarSeries."));
        qmlRegisterUncreatableType<QAbstractAxis>(uri, 1, 0, "AbstractAxis",
                                                  QLatin1String("Trying to create uncreatable: AbstractAxis. Use specific types of axis instead."));
        qmlRegisterUncreatableType<QBarSet>(uri, 1, 0, "BarSetBase",
                                            QLatin1String("Trying to create uncreatable: BarsetBase."));
        qmlRegisterUncreatableType<QPieSeries>(uri, 1, 0, "QPieSeries",
                                               QLatin1String("Trying to create uncreatable: QPieSeries. Use PieSeries instead."));
        qmlRegisterUncreatableType<DeclarativeAxes>(uri, 1, 0, "DeclarativeAxes",
                                               QLatin1String("Trying to create uncreatable: DeclarativeAxes."));

        // QtCommercial.Chart 1.1
        qmlRegisterType<DeclarativeChart, 1>(uri, 1, 1, "ChartView");
        qmlRegisterType<DeclarativeScatterSeries, 1>(uri, 1, 1, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries, 1>(uri, 1, 1, "LineSeries");
        qmlRegisterType<DeclarativeSplineSeries, 1>(uri, 1, 1, "SplineSeries");
        qmlRegisterType<DeclarativeAreaSeries, 1>(uri, 1, 1, "AreaSeries");
        qmlRegisterType<DeclarativeBarSeries, 1>(uri, 1, 1, "BarSeries");
        qmlRegisterType<DeclarativeStackedBarSeries, 1>(uri, 1, 1, "StackedBarSeries");
        qmlRegisterType<DeclarativePercentBarSeries, 1>(uri, 1, 1, "PercentBarSeries");
        qmlRegisterType<DeclarativeHorizontalBarSeries, 1>(uri, 1, 1, "HorizontalBarSeries");
        qmlRegisterType<DeclarativeHorizontalStackedBarSeries, 1>(uri, 1, 1, "HorizontalStackedBarSeries");
        qmlRegisterType<DeclarativeHorizontalPercentBarSeries, 1>(uri, 1, 1, "HorizontalPercentBarSeries");
        qmlRegisterType<DeclarativePieSeries>(uri, 1, 1, "PieSeries");
        qmlRegisterType<DeclarativeBarSet>(uri, 1, 1, "BarSet");
        qmlRegisterType<QValueAxis>(uri, 1, 1, "ValueAxis");
#ifndef QT_ON_ARM
        qmlRegisterType<QDateTimeAxis>(uri, 1, 1, "DateTimeAxis");
#endif
        qmlRegisterType<DeclarativeCategoryAxis>(uri, 1, 1, "CategoryAxis");
        qmlRegisterType<DeclarativeCategoryRange>(uri, 1, 1, "CategoryRange");
        qmlRegisterType<QBarCategoryAxis>(uri, 1, 1, "BarCategoryAxis");
        qmlRegisterUncreatableType<DeclarativeMargins>(uri, 1, 1, "Margins",
                                                       QLatin1String("Trying to create uncreatable: Margins."));

        // QtCommercial.Chart 1.2
        qmlRegisterType<DeclarativeChart, 2>(uri, 1, 2, "ChartView");
        qmlRegisterType<DeclarativeScatterSeries, 2>(uri, 1, 2, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries, 2>(uri, 1, 2, "LineSeries");
        qmlRegisterType<DeclarativeSplineSeries, 2>(uri, 1, 2, "SplineSeries");
        qmlRegisterType<DeclarativeAreaSeries, 2>(uri, 1, 2, "AreaSeries");
        qmlRegisterType<DeclarativeBarSeries, 2>(uri, 1, 2, "BarSeries");
        qmlRegisterType<DeclarativeStackedBarSeries, 2>(uri, 1, 2, "StackedBarSeries");
        qmlRegisterType<DeclarativePercentBarSeries, 2>(uri, 1, 2, "PercentBarSeries");
        qmlRegisterType<DeclarativeHorizontalBarSeries, 2>(uri, 1, 2, "HorizontalBarSeries");
        qmlRegisterType<DeclarativeHorizontalStackedBarSeries, 2>(uri, 1, 2, "HorizontalStackedBarSeries");
        qmlRegisterType<DeclarativeHorizontalPercentBarSeries, 2>(uri, 1, 2, "HorizontalPercentBarSeries");

        // QtCommercial.Chart 1.3
        qmlRegisterType<DeclarativeChart, 3>(uri, 1, 3, "ChartView");
        qmlRegisterType<DeclarativePolarChart, 1>(uri, 1, 3, "PolarChartView");
        qmlRegisterType<DeclarativeSplineSeries, 3>(uri, 1, 3, "SplineSeries");
        qmlRegisterType<DeclarativeScatterSeries, 3>(uri, 1, 3, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries, 3>(uri, 1, 3, "LineSeries");
        qmlRegisterType<DeclarativeAreaSeries, 3>(uri, 1, 3, "AreaSeries");
        qmlRegisterType<QLogValueAxis>(uri, 1, 3, "LogValueAxis");
        qmlRegisterType<DeclarativeBoxPlotSeries>(uri, 1, 3, "BoxPlotSeries");
        qmlRegisterType<DeclarativeBoxSet>(uri, 1, 3, "BoxSet");

        // QtCommercial.Chart 1.4
        qmlRegisterType<DeclarativeAreaSeries, 4>(uri, 1, 4, "AreaSeries");
        qmlRegisterType<DeclarativeBarSet, 2>(uri, 1, 4, "BarSet");
        qmlRegisterType<DeclarativeBoxPlotSeries, 1>(uri, 1, 4, "BoxPlotSeries");
        qmlRegisterType<DeclarativeBoxSet, 1>(uri, 1, 4, "BoxSet");
        qmlRegisterType<DeclarativePieSlice>(uri, 1, 4, "PieSlice");
        qmlRegisterType<DeclarativeScatterSeries, 4>(uri, 1, 4, "ScatterSeries");
    }
};

QTCOMMERCIALCHART_END_NAMESPACE

#include "plugin.moc"

QTCOMMERCIALCHART_USE_NAMESPACE

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    Q_EXPORT_PLUGIN2(qtcommercialchartqml, QT_PREPEND_NAMESPACE(ChartQmlPlugin))
#endif
