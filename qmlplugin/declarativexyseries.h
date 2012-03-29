#ifndef DECLARATIVE_XY_SERIES_H
#define DECLARATIVE_XY_SERIES_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativeXySeries : public QDeclarativeParserStatus
{
    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit DeclarativeXySeries();
    ~DeclarativeXySeries();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public:
    QDeclarativeListProperty<DeclarativeXyPoint> points();

public Q_SLOTS:
    static void appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                             DeclarativeXyPoint *element);

protected:
    virtual void seriesComplete() = 0;
    virtual QObject *seriesObject() = 0;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_XY_SERIES_H
