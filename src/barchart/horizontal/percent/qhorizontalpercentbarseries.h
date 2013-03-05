/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef QHORIZONTALPERCENTBARSERIES_H
#define QHORIZONTALPERCENTBARSERIES_H

#include <qabstractbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QHorizontalPercentBarSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QHorizontalPercentBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalPercentBarSeries(QObject *parent = 0);
    ~QHorizontalPercentBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QHorizontalPercentBarSeries)
    Q_DISABLE_COPY(QHorizontalPercentBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHORIZONTALPERCENTBARSERIES_H
