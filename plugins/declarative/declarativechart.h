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

#ifndef DECLARATIVECHART_H
#define DECLARATIVECHART_H

#include <QtCore/QtGlobal>
#include <QDeclarativeItem>
#include <qchart.h>
#include <QAxis>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: Derive from QChart for easier definition of properties?
class DeclarativeChart : public QDeclarativeItem
// TODO: for QTQUICK2: extend QQuickPainterItem instead
//class DeclarativeChart : public QQuickPaintedItem, public Chart
{
    Q_OBJECT
    Q_PROPERTY(QChart::ChartTheme theme READ theme WRITE setTheme)
    Q_PROPERTY(QChart::AnimationOption animationOptions READ animationOptions WRITE setAnimationOptions)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(ChartLegend legend READ legend WRITE setLegend)
    Q_PROPERTY(QAxis *axisX READ axisX)
    Q_PROPERTY(QAxis *axisY READ axisY)
    // TODO: how to define axis labels? This is not very convenient
    Q_PROPERTY(QVariantList axisXLabels READ axisXLabels WRITE setAxisXLabels)
    Q_ENUMS(ChartLegend)

public:
    enum ChartLegend {
        LegendDisabled = 0,
        LegendTop,
        LegendBottom,
        LegendLeft,
        LegendRight
    };

public:
    DeclarativeChart(QDeclarativeItem *parent = 0);
    ~DeclarativeChart();

public: // From QDeclarativeItem/QGraphicsItem
    void childEvent(QChildEvent *event);
    void componentComplete();
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    void setTheme(QChart::ChartTheme theme) {m_chart->setTheme(theme);}
    QChart::ChartTheme theme() {return m_chart->theme();}
    void setAnimationOptions(QChart::AnimationOption animations);
    QChart::AnimationOption animationOptions();
    void setTitle(QString title) {m_chart->setTitle(title);}
    QString title() { return m_chart->title();}
    void setLegend(ChartLegend legend);
    ChartLegend legend();
    QAxis *axisX();
    QAxis *axisY();
    QVariantList axisXLabels();
    void setAxisXLabels(QVariantList list);

public:
    // Extending QChart with DeclarativeChart is not possible because QObject does not support
    // multi inheritance, so we now have a QChart as a member instead
    QChart *m_chart;
    ChartLegend m_legend;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVECHART_H
