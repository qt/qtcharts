// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
