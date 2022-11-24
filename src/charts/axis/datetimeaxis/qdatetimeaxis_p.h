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

#ifndef QDATETIMEAXIS_P_H
#define QDATETIMEAXIS_P_H

#include <QtCharts/QDateTimeAxis>
#include <QtCharts/private/qchartglobal_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCore/QDateTime>

QT_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT QDateTimeAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
public:
    QDateTimeAxisPrivate(QDateTimeAxis *q);
    ~QDateTimeAxisPrivate();

public:
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(AbstractDomain *domain) override;

    //interface for manipulating range form base class
    void setMin(const QVariant &min) override;
    void setMax(const QVariant &max) override;
    void setRange(const QVariant &min, const QVariant &max) override;

    //interface manipulating range form domain
    qreal min() override { return m_min; }
    qreal max() override { return m_max; }
    void setRange(qreal min,qreal max) override;

protected:
    int tickCount() const;

protected:
    qreal m_min;
    qreal m_max;
    int m_tickCount;
    QString m_format;
    Q_DECLARE_PUBLIC(QDateTimeAxis)
};

QT_END_NAMESPACE

#endif // QDATETIMEAXIS_P_H
