/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "declarativeaxes.h"
#include "qabstractaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeAxes::DeclarativeAxes(QObject *parent) :
    QObject(parent),
    m_axisX(0),
    m_axisY(0),
    m_axisXTop(0),
    m_axisYRight(0)
{
}

void DeclarativeAxes::setAxisX(QAbstractAxis *axis)
{
    m_axisX = axis;
    emit axisXChanged(axis);
}

void DeclarativeAxes::setAxisY(QAbstractAxis *axis)
{
    m_axisY = axis;
    emit axisYChanged(axis);
}

void DeclarativeAxes::setAxisXTop(QAbstractAxis *axis)
{
    m_axisXTop = axis;
    emit axisXTopChanged(axis);
}

void DeclarativeAxes::setAxisYRight(QAbstractAxis *axis)
{
    m_axisYRight = axis;
    emit axisYRightChanged(axis);
}

#include "moc_declarativeaxes.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
