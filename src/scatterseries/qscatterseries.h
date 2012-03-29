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

#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <qchartglobal.h>
#include <qxyseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QXYSeries
{

public:
    enum MarkerShape {
        MarkerShapeCircle,
        MarkerShapeRectangle
    };

public:
    QScatterSeries(QObject *parent = 0);
    ~QScatterSeries();

public: // from QChartSeries
    QSeriesType type() const { return QSeries::SeriesTypeScatter; }

public:
    MarkerShape shape() const;
    void setShape(MarkerShape shape);
    qreal size() const;
    void setSize(qreal size);

private:
    MarkerShape m_shape;
    qreal m_size;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
