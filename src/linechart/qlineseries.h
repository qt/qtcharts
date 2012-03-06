#ifndef QLINESERIES_H_
#define QLINESERIES_H_

#include "qchartglobal.h"
#include "qxyseries.h"
#include <QDebug>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QLineSeries : public QXYSeries
{
	Q_OBJECT
public:
	QLineSeries(QObject* parent=0);
	virtual ~QLineSeries();

public: // from QChartSeries
	virtual QSeriesType type() const {return QSeries::SeriesTypeLine;}
    friend QDebug operator<< (QDebug d, const QLineSeries series);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
