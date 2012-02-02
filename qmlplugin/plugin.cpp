#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include "declarativechart.h"
#include "declarativeseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartQmlPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtCommercial.Chart"));
        qmlRegisterType<DeclarativeChart>(uri, 1, 0, "Chart");
        qmlRegisterType<DeclarativeSeries>(uri, 1, 0, "Series");
        //qmlRegisterUncreatableType<QChartSeries::SeriesTypeBar>(uri, 1, 0, "Series.Se", QLatin1String("Do not create objects of this type."));
    }
};

#include "plugin.moc"

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

Q_EXPORT_PLUGIN2(qtcommercialchartqml, QT_PREPEND_NAMESPACE(ChartQmlPlugin))
