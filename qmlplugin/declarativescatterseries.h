#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include <QDeclarativeItem>
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QScatterSeries;

class DeclarativeScatterSeries : public QDeclarativeItem//, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> data READ data)

public:
    explicit DeclarativeScatterSeries(QDeclarativeItem *parent = 0);
    ~DeclarativeScatterSeries();

public: // from QDeclarativeParserStatus
    void componentComplete();

public:
    QDeclarativeListProperty<DeclarativeXyPoint> data();

signals:

public slots:
    static void appendData(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                           DeclarativeXyPoint *element);

private slots:

public:
    QChart *m_chart; // not owned
    QScatterSeries *m_series; // not owned
    QList<DeclarativeXyPoint *> m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
