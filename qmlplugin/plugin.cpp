#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include "declarativechart.h"
#include "declarativexypoint.h"
#include "declarativescatterseries.h"
#include "declarativelineseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartQmlPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtCommercial.Chart"));

        qmlRegisterType<DeclarativeChart>(uri, 1, 0, "Chart");
        qmlRegisterType<DeclarativeXyPoint>(uri, 1, 0, "XyPoint");
        qmlRegisterType<DeclarativeScatterSeries>(uri, 1, 0, "ScatterSeries");
        qmlRegisterType<DeclarativeLineSeries>(uri, 1, 0, "LineSeries");
        qmlRegisterType<DeclarativeBarSeries>(uri, 1, 0, "BarSeries");
        qmlRegisterType<DeclarativePieSeries>(uri, 1, 0, "PieSeries");
        qmlRegisterType<QPieSlice>(uri, 1, 0, "PieSlice");
    }
};

#include "plugin.moc"

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

Q_EXPORT_PLUGIN2(qtcommercialchartqml, QT_PREPEND_NAMESPACE(ChartQmlPlugin))
