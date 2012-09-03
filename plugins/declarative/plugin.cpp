/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include "qchart.h"
#include "qabstractaxis.h"
#include "qvalueaxis.h"
#include "declarativecategoryaxis.h"
#include "qbarcategoryaxis.h"
#include "declarativechart.h"
#include "declarativexypoint.h"
#include "declarativelineseries.h"
#include "declarativesplineseries.h"
#include "declarativeareaseries.h"
#include "declarativescatterseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"
#include "qvxymodelmapper.h"
#include "qhxymodelmapper.h"
#include "qhpiemodelmapper.h"
#include "qvpiemodelmapper.h"
#include "qhbarmodelmapper.h"
#include "qvbarmodelmapper.h"
#include "declarativemargins.h"
#include <QAbstractItemModel>

#ifndef QT_ON_ARM
#include "qdatetimeaxis.h"
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartQmlPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
    public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtCommercial.Chart"));

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

        // QtCommercial.Chart 1.1
        qmlRegisterType<DeclarativeChart, 1>(uri, 1, 1, "ChartView");
        qmlRegisterType<DeclarativeXYPoint>(uri, 1, 1, "XYPoint");
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
        qmlRegisterType<QPieSlice>(uri, 1, 1, "PieSlice");
        qmlRegisterType<DeclarativeBarSet>(uri, 1, 1, "BarSet");
        qmlRegisterType<QHXYModelMapper>(uri, 1, 1, "HXYModelMapper");
        qmlRegisterType<QVXYModelMapper>(uri, 1, 1, "VXYModelMapper");
        qmlRegisterType<QHPieModelMapper>(uri, 1, 1, "HPieModelMapper");
        qmlRegisterType<QVPieModelMapper>(uri, 1, 1, "VPieModelMapper");
        qmlRegisterType<QHBarModelMapper>(uri, 1, 1, "HBarModelMapper");
        qmlRegisterType<QVBarModelMapper>(uri, 1, 1, "VBarModelMapper");
        qmlRegisterType<QValueAxis>(uri, 1, 1, "ValueAxis");
#ifndef QT_ON_ARM
        qmlRegisterType<QDateTimeAxis>(uri, 1, 1, "DateTimeAxis");
#endif
        qmlRegisterType<DeclarativeCategoryAxis>(uri, 1, 1, "CategoryAxis");
        qmlRegisterType<DeclarativeCategoryRange>(uri, 1, 1, "CategoryRange");
        qmlRegisterType<QBarCategoryAxis>(uri, 1, 1, "BarCategoryAxis");
        qmlRegisterUncreatableType<QLegend>(uri, 1, 1, "Legend",
                                            QLatin1String("Trying to create uncreatable: Legend."));
        qmlRegisterUncreatableType<QXYSeries>(uri, 1, 1, "XYSeries",
                                              QLatin1String("Trying to create uncreatable: XYSeries."));
        qmlRegisterUncreatableType<QAbstractItemModel>(uri, 1, 1, "AbstractItemModel",
                                                       QLatin1String("Trying to create uncreatable: AbstractItemModel."));
        qmlRegisterUncreatableType<QXYModelMapper>(uri, 1, 1, "XYModelMapper",
                                                   QLatin1String("Trying to create uncreatable: XYModelMapper."));
        qmlRegisterUncreatableType<QPieModelMapper>(uri, 1, 1, "PieModelMapper",
                                                    QLatin1String("Trying to create uncreatable: PieModelMapper."));
        qmlRegisterUncreatableType<QBarModelMapper>(uri, 1, 1, "BarModelMapper",
                                                    QLatin1String("Trying to create uncreatable: BarModelMapper."));
        qmlRegisterUncreatableType<QAbstractSeries>(uri, 1, 1, "AbstractSeries",
                                                    QLatin1String("Trying to create uncreatable: AbstractSeries."));
        qmlRegisterUncreatableType<QAbstractBarSeries>(uri, 1, 1, "AbstractBarSeries",
                                                       QLatin1String("Trying to create uncreatable: AbstractBarSeries."));
        qmlRegisterUncreatableType<QAbstractAxis>(uri, 1, 1, "AbstractAxis",
                                                  QLatin1String("Trying to create uncreatable: AbstractAxis. Use specific types of axis instead."));
        qmlRegisterUncreatableType<QBarSet>(uri, 1, 1, "BarSetBase",
                                            QLatin1String("Trying to create uncreatable: BarsetBase."));
        qmlRegisterUncreatableType<QPieSeries>(uri, 1, 1, "QPieSeries",
                                               QLatin1String("Trying to create uncreatable: QPieSeries. Use PieSeries instead."));
        qmlRegisterUncreatableType<DeclarativeMargins>(uri, 1, 1, "Margins",
                                                       QLatin1String("Trying to create uncreatable: Margins."));
    }
};

#include "plugin.moc"

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

Q_EXPORT_PLUGIN2(qtcommercialchartqml, QT_PREPEND_NAMESPACE(ChartQmlPlugin))
