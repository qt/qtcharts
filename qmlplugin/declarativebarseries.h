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
    Q_PROPERTY(QStringList barCategories READ barCategories WRITE setBarCategories)

public:
    explicit DeclarativeBarSeries(QDeclarativeItem *parent = 0);

public: // from QDeclarativeParserStatus
    void componentComplete();

public:
    void setBarCategories(QStringList categories);
    QStringList barCategories();

signals:

public slots:

public:
    QChart *m_chart;
    QBarSeries *m_series;
    QStringList m_categories;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBARSERIES_H
