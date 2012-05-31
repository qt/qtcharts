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
#include "qaxiscategories.h"
#include "declarativechart.h"
#include "declarativexypoint.h"
#include "declarativelineseries.h"
#include "declarativesplineseries.h"
#include "declarativeareaseries.h"
#include "declarativescatterseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"
#include <QVXYModelMapper>
#include <QHXYModelMapper>
#include <QHPieModelMapper>
#include <QVPieModelMapper>
#include <QHBarModelMapper>
#include <QVBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartQmlPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtCommercial.Chart"));

        qmlRegisterType<DeclarativeChart>(uri, 1, 0, "ChartView");
        qmlRegisterType<DeclarativeXyPoint>(uri, 1, 0, "XyPoint");
        qmlRegisterType<DeclarativeScatterSeries>(uri, 1, 0, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries>(uri, 1, 0, "LineSeries");
        qmlRegisterType<DeclarativeSplineSeries>(uri, 1, 0, "SplineSeries");
        qmlRegisterType<DeclarativeAreaSeries>(uri, 1, 0, "AreaSeries");
        qmlRegisterType<DeclarativeBarSeries>(uri, 1, 0, "BarSeries");
        qmlRegisterType<DeclarativeGroupedBarSeries>(uri, 1, 0, "GroupedBarSeries");
        qmlRegisterType<DeclarativePieSeries>(uri, 1, 0, "PieSeries");
        qmlRegisterType<DeclarativePieSlice>(uri, 1, 0, "PieSlice");
        qmlRegisterType<DeclarativeBarSet>(uri, 1, 0, "BarSet");
        qmlRegisterType<QHXYModelMapper>(uri, 1, 0, "HXYModelMapper");
        qmlRegisterType<QVXYModelMapper>(uri, 1, 0, "VXYModelMapper");
        qmlRegisterType<QHPieModelMapper>(uri, 1, 0, "HPieModelMapper");
        qmlRegisterType<QVPieModelMapper>(uri, 1, 0, "VPieModelMapper");
        qmlRegisterType<QHBarModelMapper>(uri, 1, 0, "HBarModelMapper");
        qmlRegisterType<QVBarModelMapper>(uri, 1, 0, "VBarModelMapper");


        qmlRegisterUncreatableType<QScatterSeries>(uri, 1, 0, "QScatterSeries",
                                          QLatin1String("Trying to create uncreatable: QScatterSeries."));
        qmlRegisterUncreatableType<QPieSeries>(uri, 1, 0, "QPieSeries",
                                          QLatin1String("Trying to create uncreatable: QPieSeries."));
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
        qmlRegisterUncreatableType<QAxis>(uri, 1, 0, "Axis",
                                          QLatin1String("Trying to create uncreatable: Axis."));
        qmlRegisterUncreatableType<QPieModelMapper>(uri, 1, 0, "PieModelMapper",
                                                    QLatin1String("Trying to create uncreatable: PieModelMapper."));
        qmlRegisterUncreatableType<QXYModelMapper>(uri, 1, 0, "XYModelMapper",
                                                    QLatin1String("Trying to create uncreatable: XYModelMapper."));
    }
};

#include "plugin.moc"

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

Q_EXPORT_PLUGIN2(qtcommercialchartqml, QT_PREPEND_NAMESPACE(ChartQmlPlugin))
