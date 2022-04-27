/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include <private/polarchartdatetimeaxisradial_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCharts/QDateTimeAxis>

QT_BEGIN_NAMESPACE

PolarChartDateTimeAxisRadial::PolarChartDateTimeAxisRadial(QDateTimeAxis *axis, QGraphicsItem *item)
    : PolarChartAxisRadial(axis, item)
{
    QObject::connect(axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(axis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
}

PolarChartDateTimeAxisRadial::~PolarChartDateTimeAxisRadial()
{
}

QList<qreal> PolarChartDateTimeAxisRadial::calculateLayout() const
{
    int tickCount = static_cast<QDateTimeAxis *>(axis())->tickCount();
    Q_ASSERT(tickCount >= 2);

    QList<qreal> points;
    points.resize(tickCount);

    const qreal d = (axisGeometry().width() / 2) / qreal(tickCount - 1);

    for (int i = 0; i < tickCount; ++i) {
        qreal radialCoordinate = qreal(i) * d;
        points[i] = radialCoordinate;
    }

    return points;
}
void PolarChartDateTimeAxisRadial::createAxisLabels(const QList<qreal> &layout)
{
    setLabels(createDateTimeLabels(min(), max(), layout.size(), static_cast<QDateTimeAxis *>(axis())->format()));
}

void PolarChartDateTimeAxisRadial::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartDateTimeAxisRadial::handleFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_polarchartdatetimeaxisradial_p.cpp"
