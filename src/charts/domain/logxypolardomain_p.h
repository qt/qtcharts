/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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

class Q_CHARTS_PRIVATE_EXPORT LogXYPolarDomain: public PolarDomain
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
