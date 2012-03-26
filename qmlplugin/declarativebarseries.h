#ifndef DECLARATIVEBARSERIES_H
#define DECLARATIVEBARSERIES_H

#include "qchartglobal.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QBarSeries;

class DeclarativeBarSeries : public QDeclarativeItem
{
    Q_OBJECT

public:
    explicit DeclarativeBarSeries(QDeclarativeItem *parent = 0);

signals:

public slots:

private slots:
    void setParentForSeries();

private:
    QChart *m_chart;
    QBarSeries *m_series;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBARSERIES_H
