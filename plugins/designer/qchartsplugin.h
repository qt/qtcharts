#ifndef QCHARTSPLUGIN_H_
#define QCHARTSPLUGIN_H_

#include <QDesignerCustomWidgetInterface>

class QChartsPlugin: public QObject,public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QChartsPlugin(QObject *parent = 0);
    ~QChartsPlugin();

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
};

#endif /* QCHARTSPLUGIN_H_ */
