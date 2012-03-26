#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QScatterSeries;

class DeclarativeScatterSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)

public:
    explicit DeclarativeScatterSeries(QDeclarativeItem *parent = 0);
    ~DeclarativeScatterSeries();

public: // from QDeclarativeParserStatus
    void componentComplete();

public:
    QDeclarativeListProperty<DeclarativeXyPoint> points();

signals:

public slots:
    static void appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                           DeclarativeXyPoint *element);

private slots:

public:
    QChart *m_chart; // not owned
    QScatterSeries *m_series; // not owned
    QList<DeclarativeXyPoint *> m_points; // not owned
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
