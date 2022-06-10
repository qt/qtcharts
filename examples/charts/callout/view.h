// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef VIEW_H
#define VIEW_H
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QChart;
QT_END_NAMESPACE

class Callout;

QT_USE_NAMESPACE

class View: public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;
    QChart *m_chart;
    Callout *m_tooltip;
    QList<Callout *> m_callouts;
};

#endif
