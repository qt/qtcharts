#ifndef DECLARATIVELINESERIES_H
#define DECLARATIVELINESERIES_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QLineSeries;

class DeclarativeLineSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> data READ data)

public:
    explicit DeclarativeLineSeries(QDeclarativeItem *parent = 0);
    QDeclarativeListProperty<DeclarativeXyPoint> data();

signals:

public slots:
    static void appendData(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                           DeclarativeXyPoint *element);

private slots:
    void setParentForSeries();

private:
    QChart *m_chart;
    QLineSeries *m_series;
    QList<DeclarativeXyPoint *> m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVELINESERIES_H
