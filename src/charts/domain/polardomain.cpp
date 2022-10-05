// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/polardomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCore/QtMath>

QT_BEGIN_NAMESPACE

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
    m_radius = size.height() / 2.0;
    m_center = QPointF(m_radius, m_radius);
    AbstractDomain::setSize(size);
}

QPointF PolarDomain::calculateGeometryPoint(const QPointF &point, bool &ok) const
{
    qreal r = 0.0;
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

QList<QPointF> PolarDomain::calculateGeometryPoints(const QList<QPointF> &list) const
{
    QList<QPointF> result;
    result.resize(list.size());
    bool ok;
    qreal r = 0.0;
    qreal a = 0.0;

    for (int i = 0; i < list.size(); ++i) {
        a = toAngularCoordinate(list[i].x(), ok);
        if (ok)
            r = toRadialCoordinate(list[i].y(), ok);
        if (ok) {
            result[i] = m_center + polarCoordinateToPoint(a, r);
        } else {
            qWarning() << "Logarithm of negative value is undefined. Empty layout returned.";
            return QList<QPointF>();
        }
    }

    return result;
}

QPointF PolarDomain::polarCoordinateToPoint(qreal angularCoordinate, qreal radialCoordinate) const
{
    qreal dx = qSin(qDegreesToRadians(angularCoordinate)) * radialCoordinate;
    qreal dy = qCos(qDegreesToRadians(angularCoordinate)) * radialCoordinate;

    return QPointF(dx, -dy);
}

QT_END_NAMESPACE

#include "moc_polardomain_p.cpp"
