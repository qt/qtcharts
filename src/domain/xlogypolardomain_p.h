/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
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

#ifndef XLOGYPOLARDOMAIN_H
#define XLOGYPOLARDOMAIN_H
#include "polardomain_p.h"
#include <QRectF>
#include <QSizeF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_AUTOTEST_EXPORT XLogYPolarDomain: public PolarDomain
{
    Q_OBJECT
public:
    explicit XLogYPolarDomain(QObject *object = 0);
    virtual ~XLogYPolarDomain();

    DomainType type() { return AbstractDomain::XLogYPolarDomain; }

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY);

    friend bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const XLogYPolarDomain &domain1, const XLogYPolarDomain &domain2);
    friend bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const XLogYPolarDomain &domain1, const XLogYPolarDomain &domain2);
    friend QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const XLogYPolarDomain &domain);

    void zoomIn(const QRectF &rect);
    void zoomOut(const QRectF &rect);
    void move(qreal dx, qreal dy);

    QPointF calculateDomainPoint(const QPointF &point) const;

    bool attachAxis(QAbstractAxis *axis);
    bool detachAxis(QAbstractAxis *axis);

public Q_SLOTS:
    void handleVerticalAxisBaseChanged(qreal baseY);

protected:
    qreal toAngularCoordinate(qreal value, bool &ok) const;
    qreal toRadialCoordinate(qreal value, bool &ok) const;

private:
    qreal m_logInnerY;
    qreal m_logOuterY;
    qreal m_logBaseY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // XLOGYPOLARDOMAIN_H
