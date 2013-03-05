/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "chartbackground_p.h"
#include "chartconfig_p.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBackground::ChartBackground(QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
      m_diameter(15),
      m_dropShadow(0)
{
}

ChartBackground::~ChartBackground()
{

}

void ChartBackground::setDropShadowEnabled(bool enabled)
{
    if (enabled) {
        if (!m_dropShadow) {
            m_dropShadow = new QGraphicsDropShadowEffect();
#ifdef Q_OS_MAC
            m_dropShadow->setBlurRadius(15);
            m_dropShadow->setOffset(0, 0);
#elif defined(Q_OS_WIN)
            m_dropShadow->setBlurRadius(10);
            m_dropShadow->setOffset(0, 0);
#else
            m_dropShadow->setBlurRadius(10);
            m_dropShadow->setOffset(5, 5);
#endif
            setGraphicsEffect(m_dropShadow);
        }
    } else {
        delete m_dropShadow;
        m_dropShadow = 0;
    }
}

void ChartBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRoundRect(rect(), roundness(rect().width()), roundness(rect().height()));
#ifndef QT_NO_DEBUG
    painter->setPen(Qt::black);
    QFont font;
    QString build("build %1");
    font.setPointSize(6);
    painter->setFont(font);
    painter->drawText(rect().bottomLeft(), build.arg(ChartConfig::instance()->compilationTime()));
#endif
    painter->restore();
}

int ChartBackground::roundness(qreal size) const
{
    if (qFuzzyCompare(size, 0))
        return 0;
    return 100 * m_diameter / int(size);
}

int ChartBackground::diameter() const
{
    return m_diameter;
}

void ChartBackground::setDiameter(int diameter)
{
    m_diameter = diameter;
}

QTCOMMERCIALCHART_END_NAMESPACE
