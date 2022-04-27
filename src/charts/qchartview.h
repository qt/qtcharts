/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QCHARTVIEW_H
#define QCHARTVIEW_H

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QGraphicsView>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QRubberBand;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QChartViewPrivate;

class Q_CHARTS_EXPORT QChartView : public QGraphicsView
{
    Q_OBJECT
    Q_ENUMS(RubberBand)
public:

    enum  RubberBand {
        NoRubberBand = 0x0,
        VerticalRubberBand = 0x1,
        HorizontalRubberBand = 0x2,
        RectangleRubberBand = 0x3,
        ClickThroughRubberBand = 0x80
    };

    Q_DECLARE_FLAGS(RubberBands, RubberBand)

    explicit QChartView(QWidget *parent = nullptr);
    explicit QChartView(QChart *chart, QWidget *parent = nullptr);
    ~QChartView();

    void setRubberBand(const RubberBands &rubberBands);
    RubberBands rubberBand() const;

    QChart *chart() const;
    void setChart(QChart *chart);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
#ifdef Q_OS_MACOS
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
#endif

    QScopedPointer<QChartViewPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QChartView)
};

QT_END_NAMESPACE

#endif // QCHARTVIEW_H
