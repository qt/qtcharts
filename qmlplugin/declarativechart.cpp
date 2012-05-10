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

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      m_chart(new QChart(this)),
      m_legend(LegendDisabled)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    m_chart->axisX()->setNiceNumbersEnabled(false);
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
            m_chart->addSeries(qobject_cast<QAbstractSeries *>(child));
        }
    }
//    qDebug() << "DeclarativeChart::componentComplete(), maxX: " << axisX()->max();

    QDeclarativeItem::componentComplete();
}

void DeclarativeChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
//    qDebug() << "DeclarativeChart::geometryChanged" << newGeometry.width() << newGeometry.height();
    Q_UNUSED(oldGeometry)

    if (newGeometry.isValid()) {
        if (newGeometry.width() > 0 && newGeometry.height() > 0) {
            m_chart->resize(newGeometry.width(), newGeometry.height());
        }
    }
}

void DeclarativeChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // TODO: optimized?
    painter->setRenderHint(QPainter::Antialiasing, true);
}

void DeclarativeChart::setAnimationOptions(QChart::AnimationOption animations)
{
    m_chart->setAnimationOptions(animations);
}

QChart::AnimationOption DeclarativeChart::animationOptions()
{
    if (m_chart->animationOptions().testFlag(QChart::AllAnimations))
        return QChart::AllAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::GridAxisAnimations))
        return QChart::GridAxisAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::SeriesAnimations))
        return QChart::SeriesAnimations;
    else
        return QChart::NoAnimation;
}

void DeclarativeChart::setLegend(ChartLegend legend)
{
    if (legend != m_legend) {
        m_legend = legend;
        switch (m_legend) {
        case LegendDisabled:
            m_chart->legend()->setVisible(false);
            break;
        case LegendTop:
            m_chart->legend()->setVisible(true);
            m_chart->legend()->setAlignment(QLegend::AlignmentTop);
            break;
        case LegendBottom:
            m_chart->legend()->setVisible(true);
            m_chart->legend()->setAlignment(QLegend::AlignmentBottom);
            break;
        case LegendLeft:
            m_chart->legend()->setVisible(true);
            m_chart->legend()->setAlignment(QLegend::AlignmentLeft);
            break;
        case LegendRight:
            m_chart->legend()->setVisible(true);
            m_chart->legend()->setAlignment(QLegend::AlignmentRight);
            break;
        default:
            m_chart->legend()->setVisible(false);
            break;
        }
    }
}

DeclarativeChart::ChartLegend DeclarativeChart::legend()
{
    return m_legend;
}

QAxis *DeclarativeChart::axisX()
{
    return m_chart->axisX();
}

QAxis *DeclarativeChart::axisY()
{
    return m_chart->axisY();
}

QVariantList DeclarativeChart::axisXLabels()
{
    QVariantList labels;
    foreach (qreal value, m_chart->axisX()->categories()->values()) {
//        qDebug() << "Label for" << value << "is" << m_chart->axisX()->categories()->label(value);
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
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
