/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

QT_CHARTS_BEGIN_NAMESPACE

class QT_CHARTS_AUTOTEST_EXPORT PolarDomain: public AbstractDomain
{
    Q_OBJECT
public:
    explicit PolarDomain(QObject *object = 0);
    virtual ~PolarDomain();

    void setSize(const QSizeF &size);

    QPointF calculateGeometryPoint(const QPointF &point, bool &ok) const;
    QVector<QPointF> calculateGeometryPoints(const QVector<QPointF> &vector) const;

    virtual qreal toAngularCoordinate(qreal value, bool &ok) const = 0;
    virtual qreal toRadialCoordinate(qreal value, bool &ok) const = 0;

protected:
    QPointF polarCoordinateToPoint(qreal angularCoordinate, qreal radialCoordinate) const;

    QPointF m_center;
    qreal m_radius;
};

QT_CHARTS_END_NAMESPACE

#endif // POLARDOMAIN_H
