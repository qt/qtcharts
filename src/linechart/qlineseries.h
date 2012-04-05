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

class QLineSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QLineSeries : public QXYSeries
{
public:
    explicit QLineSeries(QObject *parent=0);
	~QLineSeries();

	QSeries::QSeriesType type() const;

protected:
	QLineSeries(QLineSeriesPrivate &d,QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QLineSeries);
    Q_DISABLE_COPY(QLineSeries);
    friend class LineChartItem;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
