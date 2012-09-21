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

#include "qlegendmarker.h"
//#include "qlegendmarker_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QLegendMarker::QLegendMarker(QObject *parent) :
    QObject(parent)//,
//    d_ptr(new QLegendMarkerPrivate(this))
{
}

QLegendMarker::~QLegendMarker()
{
}

QString QLegendMarker::label() const
{
    return m_label;
}

void QLegendMarker::setLabel(const QString &label)
{
    m_label = label;
}

QPen QLegendMarker::pen() const
{
    return m_pen;
}

void QLegendMarker::setPen(const QPen &pen)
{
    m_pen = pen;
}

QBrush QLegendMarker::brush() const
{
    return m_brush;
}

void QLegendMarker::setBrush(const QBrush &brush)
{
    m_brush = brush;
}

bool QLegendMarker::isVisible() const
{
    return m_visible;
}

void QLegendMarker::setVisible(bool visible)
{
    m_visible = visible;
}

#include "moc_qlegendmarker.cpp"
//#include "moc_qlegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
