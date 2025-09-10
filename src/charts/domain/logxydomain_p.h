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

#ifndef LOGXYDOMAIN_H
#define LOGXYDOMAIN_H
#include <private/abstractdomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT LogXYDomain: public AbstractDomain
{
    Q_OBJECT
public:
    explicit LogXYDomain(QObject *object = 0);
    virtual ~LogXYDomain();

    DomainType type() override { return AbstractDomain::LogXYDomain; }

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) override;

    friend bool Q_AUTOTEST_EXPORT operator== (const LogXYDomain &domain1, const LogXYDomain &domain2);
    friend bool Q_AUTOTEST_EXPORT operator!= (const LogXYDomain &domain1, const LogXYDomain &domain2);
    friend QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXYDomain &domain);

    void zoomIn(const QRectF &rect) override;
    void zoomOut(const QRectF &rect) override;
    void move(qreal dx, qreal dy) override;

    QPointF calculateGeometryPoint(const QPointF &point, bool &ok) const override;
    QPointF calculateDomainPoint(const QPointF &point) const override;
    QList<QPointF> calculateGeometryPoints(const QList<QPointF> &list) const override;

    bool attachAxis(QAbstractAxis *axis) override;
    bool detachAxis(QAbstractAxis *axis) override;

public Q_SLOTS:
    void handleHorizontalAxisBaseChanged(qreal baseX);

private:
    qreal m_logLeftX;
    qreal m_logRightX;
    qreal m_logBaseX;
};

QT_END_NAMESPACE

#endif // LOGXYDOMAIN_H
