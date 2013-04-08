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

#include "qboxplotseries.h"
#include "qboxplotseries_p.h"
#include "qboxplotlegendmarker.h"
#include "boxplotchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "qvalueaxis.h"
#include "charttheme_p.h"
#include "boxplotanimation_p.h"
#include "qchart_p.h"

#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBoxPlotSeries
    \brief Series for creating stacked bar chart
    \mainclass

    QBoxPlotSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as stacks, where bars in same category are stacked on top of each other.
    QBoxPlotSeries groups the data from sets to categories, which are defined by QStringList.

    See the \l {BoxPlotChart Example} {stacked bar chart example} to learn how to create a stacked bar chart.
    \image examples_boxplotchart.png

    \sa QBarSet, QPercentBarSeries, QAbstractBarSeries
*/

/*!
    \qmlclass BoxPlotSeries QBoxPlotSeries
    \inherits AbstractBarSeries

    The following QML shows how to create a simple stacked bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View7.qml 1
    \beginfloatleft
    \image demos_qmlchart7.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QBoxPlotSeries.
    QBoxPlotSeries is QObject which is a child of a \a parent.
*/
QBoxPlotSeries::QBoxPlotSeries(QObject *parent)
    : QAbstractBarSeries(*new QBoxPlotSeriesPrivate(this), parent)
{
}

/*!
    Destructor. Removes series from chart.
*/
QBoxPlotSeries::~QBoxPlotSeries()
{
    qDebug() << "QBoxPlotSeries::~QBoxPlotSeries";

    Q_D(QBoxPlotSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns QChartSeries::SeriesTypeBoxPlot.
*/
QAbstractSeries::SeriesType QBoxPlotSeries::type() const
{
    return QAbstractSeries::SeriesTypeBoxPlot;
}

void QBoxPlotSeries::setBrush(const QBrush &brush)
{
    Q_D(QBoxPlotSeries);

    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->updated();
    }
}

QBrush QBoxPlotSeries::brush() const
{
    Q_D(const QBoxPlotSeries);

    return d->m_brush;
}

void QBoxPlotSeries::setPen(const QPen &pen)
{
    Q_D(QBoxPlotSeries);

    if (d->m_pen != pen) {
        d->m_pen = pen;
        emit d->updated();
    }
}

QPen QBoxPlotSeries::pen() const
{
    Q_D(const QBoxPlotSeries);

    return d->m_pen;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxPlotSeriesPrivate::QBoxPlotSeriesPrivate(QBoxPlotSeries *q)
    : QAbstractBarSeriesPrivate(q),
      m_pen(QPen(Qt::NoPen)),
      m_brush(QBrush(Qt::NoBrush))
{
}

QBoxPlotSeriesPrivate::~QBoxPlotSeriesPrivate()
{
    qDebug() << "QBoxPlotSeriesPrivate::~QBoxPlotSeriesPrivate()";
    disconnect(this, 0, 0, 0);
}

void QBoxPlotSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal x = categoryCount();
    minX = qMin(minX, - (qreal)0.5);
    minY = qMin(minY, bottom());
    maxX = qMax(maxX, x - (qreal)0.5);
    //maxY = qMax(maxY, top());
    maxY = qMax(maxY, max());

    domain()->setRange(minX, maxX, minY, maxY);
}

void QBoxPlotSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QBoxPlotSeries);

    BoxPlotChartItem *boxPlot = new BoxPlotChartItem(q,parent);
    m_item.reset(boxPlot);
    QAbstractSeriesPrivate::initializeGraphics(parent);

    if (m_chart) {
        connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesAdded(QAbstractSeries*)), this, SLOT(handleSeriesChange(QAbstractSeries*)) );
        connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)), this, SLOT(handleSeriesRemove(QAbstractSeries*)) );

        QList<QAbstractSeries *> serieses = m_chart->series();
        boxPlot->m_seriesCount = serieses.count();

        // Tries to find this series from the Chart's list of serieses and deduce the index
        int index = 0;
        foreach (QAbstractSeries *s, serieses) {
            if (q == static_cast<QBoxPlotSeries *>(s)) {
                boxPlot->m_seriesIndex = index;
                m_index = index;
            }
            index++;
        }
    }

    // Make BoxPlotChartItem to instantiate box & whisker items
    boxPlot->handleDataStructureChanged();
}

void QBoxPlotSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QBoxPlotSeries);

    const QList<QGradient> gradients = theme->seriesGradients();

    if (forced || m_brush == QBrush(Qt::NoBrush)) {
        QColor brushColor = ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0.1);
        q->setBrush(brushColor);
    }

    if (forced || m_pen == QPen(Qt::NoPen)) {
        QPen pen;
        pen.setColor(ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 1.0));
        pen.setWidthF(1.0);
        pen.setCosmetic(true);
        q->setPen(pen);
    }
}

void QBoxPlotSeriesPrivate::initializeAnimations(QtCommercialChart::QChart::AnimationOptions options)
{
    BoxPlotChartItem *item = static_cast<BoxPlotChartItem *>(m_item.data());
    Q_ASSERT(item);
    if (options.testFlag(QChart::SeriesAnimations)) {
        item->setAnimation(new BoxPlotAnimation(item));
    }else{
        item->setAnimation((BoxPlotAnimation *)0);
    }
    QAbstractSeriesPrivate::initializeAnimations(options);
}

QList<QLegendMarker*> QBoxPlotSeriesPrivate::createLegendMarkers(QLegend *legend)
{
    Q_Q(QBoxPlotSeries);
    QList<QLegendMarker*> list;
    return list << new QBoxPlotLegendMarker(q, legend);
}

void QBoxPlotSeriesPrivate::handleSeriesRemove(QAbstractSeries *series)
{
    qDebug() << "QBoxPlotSeriesPrivate::handleSeriesRemove";
    Q_Q(QBoxPlotSeries);

    QBoxPlotSeries *removedSeries = static_cast<QBoxPlotSeries *>(series);
    QObject::disconnect(m_chart->d_ptr->m_dataset, 0, removedSeries->d_func(), 0);

    // Test if series removed is me, then don't do anything
    if (q != removedSeries) {
        BoxPlotChartItem *item = static_cast<BoxPlotChartItem *>(m_item.data());
        if (item) {
            item->m_seriesCount = item->m_seriesCount - 1;
            if (removedSeries->d_func()->m_index < m_index) {
                m_index--;
                item->m_seriesIndex = m_index;
            }

            item->handleDataStructureChanged();
        }
    }
}

void QBoxPlotSeriesPrivate::handleSeriesChange(QAbstractSeries *series)
{
    Q_UNUSED(series);

    Q_Q(QBoxPlotSeries);

    BoxPlotChartItem *boxPlot = static_cast<BoxPlotChartItem *>(m_item.data());

    if (m_chart) {
        QList<QAbstractSeries *> serieses = m_chart->series();
        boxPlot->m_seriesCount = serieses.count();

        // Tries to find this series from the Chart's list of serieses and deduce the index
        int index = 0;
        foreach (QAbstractSeries *s, serieses) {
            if (q == static_cast<QBoxPlotSeries *>(s)) {
                boxPlot->m_seriesIndex = index;
                m_index = index;
            }
            index++;
        }
    }

    boxPlot->handleDataStructureChanged();
}

#include "moc_qboxplotseries.cpp"
#include "moc_qboxplotseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

