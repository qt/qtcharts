// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
