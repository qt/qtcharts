// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef POLARDOMAIN_H
#define POLARDOMAIN_H
#include <private/abstractdomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT PolarDomain: public AbstractDomain
{
    Q_OBJECT
public:
    explicit PolarDomain(QObject *object = 0);
    virtual ~PolarDomain();

    void setSize(const QSizeF &size) override;

    QPointF calculateGeometryPoint(const QPointF &point, bool &ok) const override;
    QList<QPointF> calculateGeometryPoints(const QList<QPointF> &list) const override;

    virtual qreal toAngularCoordinate(qreal value, bool &ok) const = 0;
    virtual qreal toRadialCoordinate(qreal value, bool &ok) const = 0;

protected:
    QPointF polarCoordinateToPoint(qreal angularCoordinate, qreal radialCoordinate) const;

    QPointF m_center;
    qreal m_radius;
};

QT_END_NAMESPACE

#endif // POLARDOMAIN_H
