/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#ifndef QCOLORAXIS_H
#define QCOLORAXIS_H

#include <QtCharts/QAbstractAxis>

QT_BEGIN_NAMESPACE

class QColorAxisPrivate;

class Q_CHARTS_EXPORT QColorAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(int tickCount READ tickCount WRITE setTickCount NOTIFY tickCountChanged)
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(qreal size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(bool autoRange READ autoRange WRITE setAutoRange NOTIFY autoRangeChanged)

public:
    explicit QColorAxis(QObject *parent = nullptr);
    ~QColorAxis();

    AxisType type() const override;

    void setMin(qreal min);
    qreal min() const;
    void setMax(qreal max);
    qreal max() const;
    void setRange(qreal min, qreal max);

    void setTickCount(int count);
    int tickCount() const;

    void setSize(const qreal size);
    qreal size() const;

    void setGradient(const QLinearGradient &gradient);
    QLinearGradient gradient() const;

    void setAutoRange(bool autoRange);
    bool autoRange() const;

Q_SIGNALS:
    void minChanged(qreal min);
    void maxChanged(qreal max);
    void rangeChanged(qreal min, qreal max);
    void tickCountChanged(int tickCount);
    void gradientChanged(const QLinearGradient &gradient);
    void sizeChanged(const qreal size);
    void autoRangeChanged(bool autoRange);

protected:
    explicit QColorAxis(QColorAxisPrivate &d, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QColorAxis)
    Q_DISABLE_COPY(QColorAxis)
};

QT_END_NAMESPACE

#endif // QCOLORAXIS_H
