#ifndef DECLARATIVE_XY_SERIES_H
#define DECLARATIVE_XY_SERIES_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include "qxyseries.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativeXySeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)

public:
    explicit DeclarativeXySeries(QSeries::QSeriesType type, QDeclarativeItem *parent = 0);
    ~DeclarativeXySeries();

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
    QSeries::QSeriesType m_seriesType;
    QChart *m_chart;
    QXYSeries *m_series;
    QList<DeclarativeXyPoint *> m_points;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_XY_SERIES_H
