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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
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
    QVector<QPointF> calculateGeometryPoints(const QList<QPointF> &vector) const;

    virtual qreal toAngularCoordinate(qreal value, bool &ok) const = 0;
    virtual qreal toRadialCoordinate(qreal value, bool &ok) const = 0;

protected:
    QPointF polarCoordinateToPoint(qreal angularCoordinate, qreal radialCoordinate) const;

    QPointF m_center;
    qreal m_radius;
};

QT_CHARTS_END_NAMESPACE

#endif // POLARDOMAIN_H
