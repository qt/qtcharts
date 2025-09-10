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

#ifndef LOGXYPOLARDOMAIN_H
#define LOGXYPOLARDOMAIN_H
#include <private/polardomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT LogXYPolarDomain: public PolarDomain
{
    Q_OBJECT
public:
    explicit LogXYPolarDomain(QObject *object = 0);
    virtual ~LogXYPolarDomain();

    DomainType type() override { return AbstractDomain::LogXYPolarDomain; }

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) override;

    friend bool Q_AUTOTEST_EXPORT operator== (const LogXYPolarDomain &domain1, const LogXYPolarDomain &domain2);
    friend bool Q_AUTOTEST_EXPORT operator!= (const LogXYPolarDomain &domain1, const LogXYPolarDomain &domain2);
    friend QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXYPolarDomain &domain);

    void zoomIn(const QRectF &rect) override;
    void zoomOut(const QRectF &rect) override;
    void move(qreal dx, qreal dy) override;

    QPointF calculateDomainPoint(const QPointF &point) const override;

    bool attachAxis(QAbstractAxis *axis) override;
    bool detachAxis(QAbstractAxis *axis) override;

public Q_SLOTS:
    void handleHorizontalAxisBaseChanged(qreal baseX);

protected:
    qreal toAngularCoordinate(qreal value, bool &ok) const override;
    qreal toRadialCoordinate(qreal value, bool &ok) const override;

private:
    qreal m_logLeftX;
    qreal m_logRightX;
    qreal m_logBaseX;
};

QT_END_NAMESPACE

#endif // LOGXYPOLARDOMAIN_H
