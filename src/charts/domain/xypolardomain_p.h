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

#ifndef XYPOLARDOMAIN_H
#define XYPOLARDOMAIN_H
#include <private/polardomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QRectF>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT XYPolarDomain: public PolarDomain
{
    Q_OBJECT
public:
    explicit XYPolarDomain(QObject *object = 0);
    virtual ~XYPolarDomain();

    DomainType type() override { return AbstractDomain::XYPolarDomain; }

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) override;

    friend bool Q_AUTOTEST_EXPORT operator== (const XYPolarDomain &Domain1, const XYPolarDomain &Domain2);
    friend bool Q_AUTOTEST_EXPORT operator!= (const XYPolarDomain &Domain1, const XYPolarDomain &Domain2);
    friend QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const XYPolarDomain &AbstractDomain);

    void zoomIn(const QRectF &rect) override;
    void zoomOut(const QRectF &rect) override;
    void move(qreal dx, qreal dy) override;

    QPointF calculateDomainPoint(const QPointF &point) const override;

protected:
    qreal toAngularCoordinate(qreal value, bool &ok) const override;
    qreal toRadialCoordinate(qreal value, bool &ok) const override;
};

QT_END_NAMESPACE

#endif // XYPOLARDOMAIN_H
