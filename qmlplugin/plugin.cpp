#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include "declarativechart.h"

QT_BEGIN_NAMESPACE

class QmlChartPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("com.digia.charts"));
        qmlRegisterType<DeclarativeChart>(uri, 1, 0, "Chart");
    }
};

QT_END_NAMESPACE

#include "plugin.moc"

Q_EXPORT_PLUGIN2(qmlchartplugin, QT_PREPEND_NAMESPACE(QmlChartPlugin));
