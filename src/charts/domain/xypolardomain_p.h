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
