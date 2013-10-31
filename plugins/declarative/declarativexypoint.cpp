/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "declarativexypoint.h"
#include <QDataStream>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#ifdef QDOC_QT5
/*!
    \qmltype XYPoint
    \inqmlmodule QtCommercial.Chart

    \include doc/src/declarativexypoint.qdocinc
*/
#else
/*!
    \qmlclass XYPoint QPointF

    \include ../doc/src/declarativexypoint.qdocinc
*/
#endif

/*!
    \qmlproperty real XYPoint::x
    The x-coordinate of the point.
*/

/*!
    \qmlproperty real XYPoint::y
    The y-coordinate of the point.
*/

DeclarativeXYPoint::DeclarativeXYPoint(QObject *parent) :
    QObject(parent)
{
    setX(0.0);
    setY(0.0);
}

#include "moc_declarativexypoint.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
