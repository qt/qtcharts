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

#ifndef QCHARTVIEW_H
#define QCHARTVIEW_H

#include <QAbstractAxis>
#include <QAbstractSeries>
#include <QChart>
#include <QGraphicsView>

class QGraphicsScene;
class QRubberBand;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartViewPrivate;

class QTCOMMERCIALCHART_EXPORT QChartView : public QGraphicsView
{
    Q_OBJECT
    Q_ENUMS(RubberBand)
public:

    enum  RubberBand {
        NoRubberBand = 0x0,
        VerticalRubberBand = 0x1,
        HorizonalRubberBand = 0x2,
        RectangleRubberBand = 0x3
    };

    Q_DECLARE_FLAGS(RubberBands, RubberBand)

    explicit QChartView(QWidget *parent = 0);
    explicit QChartView(QChart *chart, QWidget *parent = 0);
    ~QChartView();

    void setRubberBand(const RubberBands& rubberBands);
    RubberBands rubberBand() const;

    QChart* chart() const;
    void setChart(QChart *chart);

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    QScopedPointer<QChartViewPrivate> d_ptr;
    Q_DISABLE_COPY(QChartView)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTVIEW_H
