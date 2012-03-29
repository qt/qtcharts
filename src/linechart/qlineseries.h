/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QLINESERIES_H_
#define QLINESERIES_H_

#include <qchartglobal.h>
#include <qxyseries.h>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QLineSeries : public QXYSeries
{
public:
    QLineSeries(QObject *parent=0);
	virtual ~QLineSeries();

	void setPointsVisible(bool visible);
	bool pointsVisible() const {return m_pointsVisible;}

public: // from QChartSeries
	virtual QSeriesType type() const {return QSeries::SeriesTypeLine;}
    friend QDebug operator<< (QDebug d, const QLineSeries series);
private:
    bool m_pointsVisible;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
