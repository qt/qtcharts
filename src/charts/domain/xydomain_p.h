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

#ifndef XYDOMAIN_H
#define XYDOMAIN_H
#include <private/abstractdomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT XYDomain: public AbstractDomain
{
    Q_OBJECT
public:
    explicit XYDomain(QObject *object = 0);
    virtual ~XYDomain();

    DomainType type() override { return AbstractDomain::XYDomain; }

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) override;

    friend bool Q_AUTOTEST_EXPORT operator== (const XYDomain &Domain1, const XYDomain &Domain2);
    friend bool Q_AUTOTEST_EXPORT operator!= (const XYDomain &Domain1, const XYDomain &Domain2);
    friend QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const XYDomain &AbstractDomain);

    void zoomIn(const QRectF &rect) override;
    void zoomOut(const QRectF &rect) override;
    void move(qreal dx, qreal dy) override;

    QPointF calculateGeometryPoint(const QPointF &point, bool &ok) const override;
    QPointF calculateDomainPoint(const QPointF &point) const override;
    QList<QPointF> calculateGeometryPoints(const QList<QPointF> &list) const override;
};

QT_END_NAMESPACE

#endif // XYDOMAIN_H
