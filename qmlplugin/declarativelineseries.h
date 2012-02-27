#ifndef DECLARATIVELINESERIES_H
#define DECLARATIVELINESERIES_H

#include "qchartglobal.h"
#include "scatterelement.h" // TODO: rename header
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QLineSeries;

class DeclarativeLineSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<ScatterElement> data READ data)

public:
    explicit DeclarativeLineSeries(QDeclarativeItem *parent = 0);
    QDeclarativeListProperty<ScatterElement> data();

signals:

public slots:
    static void appendData(QDeclarativeListProperty<ScatterElement> *list,
                           ScatterElement *element);

private slots:
    void setParentForSeries();

private:
    QChart *m_chart;
    QLineSeries *m_series;
    QList<ScatterElement *> m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVELINESERIES_H
