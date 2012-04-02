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

#ifndef QAREASERIES_H_
#define QAREASERIES_H_

#include <qchartglobal.h>
#include <qseries.h>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QLineSeries;

class QTCOMMERCIALCHART_EXPORT QAreaSeries : public QSeries
{
    Q_OBJECT
public:
    QAreaSeries(QLineSeries *upperSeries, QLineSeries *lowerSeries = 0);
    virtual ~QAreaSeries();

public: // from QChartSeries
    virtual QSeriesType type() const { return QSeries::SeriesTypeArea; }

    QLineSeries* upperSeries() const { return m_upperSeries; }
    QLineSeries* lowerSeries() const { return m_lowerSeries; }

    void setPen(const QPen &pen);
    QPen pen() const { return m_pen;}

    void setBrush(const QBrush &brush);
    QBrush brush() const { return m_brush;}

    void setPointsVisible(bool visible);
    bool pointsVisible() const { return m_pointsVisible; }

//    bool setModel(QAbstractItemModel* model);
//    void setModelMappingUpper(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);
//    void setModelMappingLower(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);

Q_SIGNALS:
    void updated();
    void clicked(const QPointF &point);
    void selected();

private:
    QBrush m_brush;
    QPen m_pen;
    QLineSeries* m_upperSeries;
    QLineSeries* m_lowerSeries;
    bool m_pointsVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
