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

#ifndef XYPOLARDOMAIN_H
#define XYPOLARDOMAIN_H
#include <private/polardomain_p.h>
#include <QtCore/QRectF>

QT_CHARTS_BEGIN_NAMESPACE

class QT_CHARTS_AUTOTEST_EXPORT XYPolarDomain: public PolarDomain
{
    Q_OBJECT
public:
    explicit XYPolarDomain(QObject *object = 0);
    virtual ~XYPolarDomain();

    DomainType type(){ return AbstractDomain::XYPolarDomain;}

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY);

    friend bool QT_CHARTS_AUTOTEST_EXPORT operator== (const XYPolarDomain &Domain1, const XYPolarDomain &Domain2);
    friend bool QT_CHARTS_AUTOTEST_EXPORT operator!= (const XYPolarDomain &Domain1, const XYPolarDomain &Domain2);
    friend QDebug QT_CHARTS_AUTOTEST_EXPORT operator<<(QDebug dbg, const XYPolarDomain &AbstractDomain);

    void zoomIn(const QRectF &rect);
    void zoomOut(const QRectF &rect);
    void move(qreal dx, qreal dy);

    QPointF calculateDomainPoint(const QPointF &point) const;

protected:
    qreal toAngularCoordinate(qreal value, bool &ok) const;
    qreal toRadialCoordinate(qreal value, bool &ok) const;
};

QT_CHARTS_END_NAMESPACE

#endif // XYPOLARDOMAIN_H
