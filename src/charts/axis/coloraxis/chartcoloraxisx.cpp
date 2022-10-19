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

#include "chartcoloraxisx_p.h"
#include <QtCharts/QColorAxis>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtWidgets/QGraphicsLayout>

QT_BEGIN_NAMESPACE

ChartColorAxisX::ChartColorAxisX(QColorAxis *axis, QGraphicsItem *item)
    : HorizontalAxis(axis, item, true)
    , m_axis(axis)
{

}

ChartColorAxisX::~ChartColorAxisX()
{
}

QSizeF ChartColorAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    const QStringList &ticksList = createColorLabels(min(), max(), m_axis->tickCount());
    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF boundingRect = ChartPresenter::textBoundingRect(
                axis()->labelsFont(), QStringLiteral("..."), axis()->labelsAngle());
        width = boundingRect.width() / 2.0;
        height = boundingRect.height() + labelPadding() + base.height() + m_axis->size()
                + colorScalePadding() + 1.0;
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        qreal labelHeight = 0.0;
        qreal firstWidth = -1.0;
        for (const QString &s : ticksList) {
            QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s,
                                                           axis()->labelsAngle());
            labelHeight = qMax(rect.height(), labelHeight);
            width = rect.width();
            if (firstWidth < 0.0)
                firstWidth = width;
        }
        height = labelHeight + labelPadding() + base.height() + m_axis->size() + colorScalePadding()
                + 1.0;
        width = qMax(width, firstWidth) / 2.0;
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }
    return sh;
}

QList<qreal> ChartColorAxisX::calculateLayout() const
{
    int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QList<qreal> points;
    points.resize(tickCount);

    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / (qreal(tickCount) - 1.0);
    for (int i = 0; i < tickCount; ++i)
        points[i] = qreal(i) * deltaX + gridRect.left();
    return points;
}

void ChartColorAxisX::updateGeometry()
{
    setLabels(createColorLabels(min(), max(), m_axis->tickCount()));
    HorizontalAxis::updateGeometry();
}


QT_END_NAMESPACE

#include "moc_chartcoloraxisx_p.cpp"
