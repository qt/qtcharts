/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
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
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DOMAIN_H
#define DOMAIN_H
#include "qchartglobal.h"
#include <QRectF>
#include <QSizeF>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_AUTOTEST_EXPORT Domain: public QObject
{
    Q_OBJECT
public:
    explicit Domain(QObject* object = 0);
    virtual ~Domain();

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void setRangeX(qreal min, qreal max);
    void setRangeY(qreal min, qreal max);
    void setMinX(qreal min);
    void setMaxX(qreal max);
    void setMinY(qreal min);
    void setMaxY(qreal max);

    qreal minX() const { return m_minX; }
    qreal maxX() const { return m_maxX; }
    qreal minY() const { return m_minY; }
    qreal maxY() const { return m_maxY; }

    qreal spanX() const;
    qreal spanY() const;
    bool isEmpty() const;

    friend bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const Domain &domain1, const Domain &domain2);
    friend bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const Domain &domain1, const Domain &domain2);
    friend QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const Domain &domain);

    void zoomIn(const QRectF& rect, const QSizeF& size);
    void zoomOut(const QRectF& rect, const QSizeF& size);
    void move(qreal dx, qreal dy, const QSizeF& size);
    void emitUpdated();

Q_SIGNALS:
    void updated();
    void rangeXChanged(qreal min, qreal max);
    void rangeYChanged(qreal min, qreal max);

public Q_SLOTS:
    void handleAxisUpdated();

private:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
