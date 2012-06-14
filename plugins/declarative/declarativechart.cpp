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

#include "declarativechart.h"
#include <QPainter>
#include "declarativelineseries.h"
#include "declarativeareaseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"
#include "declarativesplineseries.h"
#include "declarativescatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \qmlclass ChartView DeclarativeChart

    ChartView element is the parent that is responsible for showing different chart series types.

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart1.png
    \endfloat
    \clearfloat
*/

DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      m_chart(new QChart(this))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
//    m_chart->axisX()->setNiceNumbersEnabled(false);
}

DeclarativeChart::~DeclarativeChart()
{
    delete m_chart;
}

void DeclarativeChart::childEvent(QChildEvent *event)
{
    if (event->type() == QEvent::ChildAdded) {
        if (qobject_cast<QAbstractSeries *>(event->child())) {
            m_chart->addSeries(qobject_cast<QAbstractSeries *>(event->child()));
        }
    }
}

void DeclarativeChart::componentComplete()
{
//    qDebug() << "DeclarativeChart::componentComplete(), maxX: " << axisX()->max();
    foreach(QObject *child, children()) {
        if (qobject_cast<QAbstractSeries *>(child)) {
//            qDebug() << "DeclarativeChart::componentComplete(), add: " << child;
            m_chart->addSeries(qobject_cast<QAbstractSeries *>(child));
        }
    }
//    qDebug() << "DeclarativeChart::componentComplete(), maxX: " << axisX()->max();

    QDeclarativeItem::componentComplete();
}

void DeclarativeChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
//    qDebug() << "DeclarativeChart::geometryChanged" << newGeometry.width() << newGeometry.height();
    if (newGeometry.isValid()) {
        if (newGeometry.width() > 0 && newGeometry.height() > 0) {
            m_chart->resize(newGeometry.width(), newGeometry.height());
        }
    }
    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
}

void DeclarativeChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // TODO: optimized?
    painter->setRenderHint(QPainter::Antialiasing, true);
}

void DeclarativeChart::setTheme(DeclarativeChart::Theme theme)
{
    QChart::ChartTheme chartTheme = (QChart::ChartTheme) theme;
    if (chartTheme != m_chart->theme()) {
        m_chart->setTheme(chartTheme);
        themeChanged();
    }
}

DeclarativeChart::Theme DeclarativeChart::theme()
{
    return (DeclarativeChart::Theme) m_chart->theme();
}

void DeclarativeChart::setAnimationOptions(DeclarativeChart::Animation animations)
{
    QChart::AnimationOption animationOptions = (QChart::AnimationOption) animations;
    if (animationOptions != m_chart->animationOptions()) {
        m_chart->setAnimationOptions(animationOptions);
        animationOptionsChanged();
    }
}

DeclarativeChart::Animation DeclarativeChart::animationOptions()
{
    if (m_chart->animationOptions().testFlag(QChart::AllAnimations))
        return DeclarativeChart::AllAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::GridAxisAnimations))
        return DeclarativeChart::GridAxisAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::SeriesAnimations))
        return DeclarativeChart::SeriesAnimations;
    else
        return DeclarativeChart::NoAnimation;
}

void DeclarativeChart::setTitle(QString title)
{
    if (title != m_chart->title()) {
        m_chart->setTitle(title);
        emit titleChanged();
    }
}
QString DeclarativeChart::title()
{
    return m_chart->title();
}

QAxis *DeclarativeChart::axisX()
{
    return m_chart->axisX();
}

QAxis *DeclarativeChart::axisY()
{
    return m_chart->axisY();
}

QLegend *DeclarativeChart::legend()
{
    return m_chart->legend();
}

QVariantList DeclarativeChart::axisXLabels()
{
    QVariantList labels;
    foreach (qreal value, m_chart->axisX()->categories()->values()) {
        labels.append(value);
        labels.append(m_chart->axisX()->categories()->label(value));
    }
    return labels;
}

void DeclarativeChart::setAxisXLabels(QVariantList list)
{
    QVariant value(QVariant::Invalid);
    foreach (QVariant element, list) {
        if (value.isValid() && element.type() == QVariant::String) {
            m_chart->axisX()->categories()->insert(value.toDouble(), element.toString());
            value = QVariant(QVariant::Invalid);
        } else {
            if (element.canConvert(QVariant::Double))
                value = element;
        }
    }
    emit axisLabelsChanged();
}

void DeclarativeChart::setTitleColor(QColor color)
{
    QBrush b = m_chart->titleBrush();
    if (color != b.color()) {
        b.setColor(color);
        m_chart->setTitleBrush(b);
        emit titleColorChanged();
    }
}

QColor DeclarativeChart::titleColor()
{
    return m_chart->titleBrush().color();
}

void DeclarativeChart::setBackgroundColor(QColor color)
{
    QBrush b = m_chart->backgroundBrush();
    if (color != b.color()) {
        b.setColor(color);
        m_chart->setBackgroundBrush(b);
        emit backgroundColorChanged();
    }
}

QColor DeclarativeChart::backgroundColor()
{
    return m_chart->backgroundBrush().color();
}

int DeclarativeChart::count()
{
    return m_chart->series().count();
}

void DeclarativeChart::setDropShadowEnabled(bool enabled)
{
    if (enabled != m_chart->isBackgroundDropShadowEnabled()) {
        m_chart->setBackgroundDropShadowEnabled(enabled);
        dropShadowEnabledChanged(enabled);
    }
}

bool DeclarativeChart::dropShadowEnabled()
{
    return m_chart->isBackgroundDropShadowEnabled();
}

void DeclarativeChart::zoom(qreal factor)
{
    m_chart->zoom(factor);
}

void DeclarativeChart::scrollLeft(qreal pixels)
{
    m_chart->scroll(QPointF(pixels, 0));
}

void DeclarativeChart::scrollRight(qreal pixels)
{
    m_chart->scroll(QPointF(-pixels, 0));
}

void DeclarativeChart::scrollUp(qreal pixels)
{
    m_chart->scroll(QPointF(0, pixels));
}

void DeclarativeChart::scrollDown(qreal pixels)
{
    m_chart->scroll(QPointF(0, -pixels));
}

//void DeclarativeChart::scrollLeft(qreal ticks)
//{
//    m_chart->scroll(QPointF(ticksToPixels(m_chart->axisX(), ticks), 0));
//}

//void DeclarativeChart::scrollRight(qreal ticks)
//{
//    m_chart->scroll(QPointF(-ticksToPixels(m_chart->axisX(), ticks), 0));
//}

//void DeclarativeChart::scrollUp(qreal ticks)
//{
//    m_chart->scroll(QPointF(0, ticksToPixels(m_chart->axisY(), ticks)));
//}

//void DeclarativeChart::scrollDown(qreal ticks)
//{
//    m_chart->scroll(QPointF(0, -ticksToPixels(m_chart->axisY(), ticks)));
//}

//qreal DeclarativeChart::ticksToPixels(QAxis *axis, qreal ticks)
//{
//    qreal tickCount = axis->max() - axis->min();
//    qreal tickPixels = (m_chart->size().width() - m_chart->margins().width() * 2) / tickCount;
//    return tickPixels * ticks;
//}

QAbstractSeries *DeclarativeChart::series(int index)
{
    if (index < m_chart->series().count()) {
        return m_chart->series().at(index);
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::series(QString seriesName)
{
    foreach(QAbstractSeries *series, m_chart->series()) {
        if (series->name() == seriesName)
            return series;
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::createSeries(DeclarativeChart::SeriesType type, QString name)
{
    QAbstractSeries *series = 0;
    switch (type) {
    case DeclarativeChart::SeriesTypeLine:
        series = new DeclarativeLineSeries();
        break;
    case DeclarativeChart::SeriesTypeArea:
        series = new DeclarativeAreaSeries();
        break;
    case DeclarativeChart::SeriesTypeBar:
        series = new DeclarativeBarSeries();
        break;
    case DeclarativeChart::SeriesTypeStackedBar:
        // TODO
        break;
    case DeclarativeChart::SeriesTypePercentBar:
        // TODO
        break;
    case DeclarativeChart::SeriesTypeGroupedBar:
        series = new DeclarativeGroupedBarSeries();
        break;
    case DeclarativeChart::SeriesTypePie:
        series = new DeclarativePieSeries();
        break;
    case DeclarativeChart::SeriesTypeScatter:
        series = new DeclarativeScatterSeries();
        break;
    case DeclarativeChart::SeriesTypeSpline:
        series = new DeclarativeSplineSeries();
        break;
    default:
        qWarning() << "Illegal series type";
    }
    series->setName(name);
    m_chart->addSeries(series);
    return series;
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
