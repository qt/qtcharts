#ifndef DECLARATIVEPIESERIES_H
#define DECLARATIVEPIESERIES_H

#include "qchartglobal.h"
#include "qpieslice.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSeries;
class QChart;

class DeclarativePieSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<QPieSlice> data READ data)

public:
    explicit DeclarativePieSeries(QDeclarativeItem *parent = 0);
    QDeclarativeListProperty<QPieSlice> data();

Q_SIGNALS:

public Q_SLOTS:
    static void appendData(QDeclarativeListProperty<QPieSlice> *list,
                           QPieSlice *element);

private Q_SLOTS:
    void setParentForSeries();

private:
    QChart *m_chart;
    QPieSeries *m_series;
    QList<QPieSlice *> m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
