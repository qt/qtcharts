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

#ifndef QSPLINESERIES_H
#define QSPLINESERIES_H

#include <qchartglobal.h>
#include <qlineseries.h>
#include <QList>
#include <QPointF>
#include <QtGlobal>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QSplineSeries : public QLineSeries
{
    Q_OBJECT
public:

    QSplineSeries(QObject *parent = 0);
    QSeriesType type() const {return QSeries::SeriesTypeSpline;}

//    int count() const { return m_x.size(); }
    QPointF controlPoint(int index) const {return m_controlPoints[index];}
    bool setModel(QAbstractItemModel *model);

    void setModelMapping(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);
    void setModelMappingShift(int first, int count);

    // TODO: allow the user to set custom control points
//    void setCustomControlPoints(QList<QPointsF> controlPoints);
//    bool calculateControlPointsAutomatically();
//    void setCalculateControlPointsAutomatically();


private:
    void calculateControlPoints();
    QList<qreal> getFirstControlPoints(QList<qreal> rhs);

private Q_SLOTS:
    void updateControlPoints();

private:
    QList<QPointF> m_controlPoints;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSPLINESERIES_H
