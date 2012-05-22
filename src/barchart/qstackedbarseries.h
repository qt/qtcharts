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

#ifndef STACKEDBARSERIES_H
#define STACKEDBARSERIES_H

#include <QStringList>
#include <qbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QStackedBarSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QStackedBarSeries : public QBarSeries
{
    Q_OBJECT
public:
    explicit QStackedBarSeries(QObject *parent = 0);
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QStackedBarSeries)
    Q_DISABLE_COPY(QStackedBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARSERIES_H
