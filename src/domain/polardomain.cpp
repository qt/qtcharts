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

#include "polardomain_p.h"
#include "qabstractaxis_p.h"
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PolarDomain::PolarDomain(QObject *parent)
    : AbstractDomain(parent)
{
}

PolarDomain::~PolarDomain()
{
}

void PolarDomain::setSize(const QSizeF &size)
{
    Q_ASSERT(size.width() == size.height());
    m_radius = size.height() / 2;
    m_center = QPointF(m_radius, m_radius);
    AbstractDomain::setSize(size);
}

QPointF PolarDomain::calculateGeometryPoint(const QPointF &point, bool &ok) const
{
    qreal r;
    qreal a = toAngularCoordinate(point.x(), ok);
    if (ok)
        r = toRadialCoordinate(point.y(), ok);
    if (ok) {
        return m_center + polarCoordinateToPoint(a, r);
    } else {
        qWarning() << "Logarithm of negative value is undefined. Empty layout returned.";
        return QPointF();
    }
}

QVector<QPointF> PolarDomain::calculateGeometryPoints(const QList<QPointF> &vector) const
{
    QVector<QPointF> result;
    result.resize(vector.count());
    bool ok;
    qreal r;
    qreal a;

    for (int i = 0; i < vector.count(); ++i) {
        a = toAngularCoordinate(vector[i].x(), ok);
        if (ok)
            r = toRadialCoordinate(vector[i].y(), ok);
        if (ok) {
            result[i] = m_center + polarCoordinateToPoint(a, r);
        } else {
            qWarning() << "Logarithm of negative value is undefined. Empty layout returned.";
            return QVector<QPointF>();
        }
    }

    return result;
}

QPointF PolarDomain::polarCoordinateToPoint(qreal angularCoordinate, qreal radialCoordinate) const
{
    qreal dx = qSin(angularCoordinate * (M_PI / 180)) * radialCoordinate;
    qreal dy = qCos(angularCoordinate * (M_PI / 180)) * radialCoordinate;

    return QPointF(dx, -dy);
}

#include "moc_polardomain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
