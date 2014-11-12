/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/chartbackground_p.h>
#include <private/chartconfig_p.h>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QPainter>
#include <QGraphicsDropShadowEffect>

QT_CHARTS_BEGIN_NAMESPACE

ChartBackground::ChartBackground(QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
      m_diameter(5),
      m_dropShadow(0)
{
}

ChartBackground::~ChartBackground()
{

}

void ChartBackground::setDropShadowEnabled(bool enabled)
{
#ifdef QT_NO_GRAPHICSEFFECT
    Q_UNUSED(enabled)
#else
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
#endif
}

void ChartBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRoundedRect(rect(), m_diameter, m_diameter);
    painter->restore();
}

qreal ChartBackground::diameter() const
{
    return m_diameter;
}

void ChartBackground::setDiameter(qreal diameter)
{
    m_diameter = diameter;
    update();
}

QT_CHARTS_END_NAMESPACE
