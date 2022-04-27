/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "declarativeaxes_p.h"
#include <QtCharts/QAbstractAxis>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE

#include "moc_declarativeaxes_p.cpp"
