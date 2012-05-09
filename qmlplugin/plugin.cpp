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
//#include "declarativepiemodel.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartQmlPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtCommercial.Chart"));

        qmlRegisterType<DeclarativeChart>(uri, 1, 0, "ChartView");
        qmlRegisterUncreatableType<QAxis>(uri, 1, 0, "Axis",
                                          QLatin1String("Trying to create uncreatable type: Axis."));
        //qmlRegisterType<DeclarativeAxisCategory>(uri, 1, 0, "AxisCategory");
        qmlRegisterType<DeclarativeXyPoint>(uri, 1, 0, "XyPoint");
        qmlRegisterType<DeclarativeScatterSeries>(uri, 1, 0, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries>(uri, 1, 0, "LineSeries");
        qmlRegisterType<DeclarativeSplineSeries>(uri, 1, 0, "SplineSeries");
        qmlRegisterType<DeclarativeAreaSeries>(uri, 1, 0, "AreaSeries");
        qmlRegisterType<DeclarativeBarSeries>(uri, 1, 0, "BarSeries");
        qmlRegisterType<DeclarativePieSeries>(uri, 1, 0, "PieSeries");
        qmlRegisterType<QPieSlice>(uri, 1, 0, "PieSlice");
        // TODO: a declarative model for each type
        qmlRegisterType<DeclarativePieModel>(uri, 1, 0, "PieModel");
        qmlRegisterType<DeclarativeXyModel>(uri, 1, 0, "XYModel");
    }
};

#include "plugin.moc"

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

Q_EXPORT_PLUGIN2(qtcommercialchartqml, QT_PREPEND_NAMESPACE(ChartQmlPlugin))
