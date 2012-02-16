#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qchartglobal.h"
#include "scatterelement.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QScatterSeries;

class DeclarativeScatterSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<ScatterElement> data READ data)

public:
    explicit DeclarativeScatterSeries(QDeclarativeItem *parent = 0);
    QDeclarativeListProperty<ScatterElement> data();

signals:

public slots:
    static void appendData(QDeclarativeListProperty<ScatterElement> *list,
                           ScatterElement *element);
//    void append(ScatterElement element);

private slots:
    void setParentForSeries();

public:
    void initSeries();

    QChart *m_chart;
    QScatterSeries *m_series;
    QList<ScatterElement *> m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
