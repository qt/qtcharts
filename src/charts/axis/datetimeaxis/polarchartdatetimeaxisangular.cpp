// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/polarchartdatetimeaxisangular_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCharts/QDateTimeAxis>

QT_BEGIN_NAMESPACE

PolarChartDateTimeAxisAngular::PolarChartDateTimeAxisAngular(QDateTimeAxis *axis, QGraphicsItem *item)
    : PolarChartAxisAngular(axis, item)
{
    QObject::connect(axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(axis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
}

PolarChartDateTimeAxisAngular::~PolarChartDateTimeAxisAngular()
{
}

QList<qreal> PolarChartDateTimeAxisAngular::calculateLayout() const
{
    int tickCount = static_cast<QDateTimeAxis *>(axis())->tickCount();
    Q_ASSERT(tickCount >= 2);

    QList<qreal> points;
    points.resize(tickCount);

    const qreal d = 360.0 / qreal(tickCount - 1);

    for (int i = 0; i < tickCount; ++i) {
        qreal angularCoordinate = qreal(i) * d;
        points[i] = angularCoordinate;
    }

    return points;
}
void PolarChartDateTimeAxisAngular::createAxisLabels(const QList<qreal> &layout)
{
    QStringList labelList = createDateTimeLabels(min(), max(), layout.size(), static_cast<QDateTimeAxis *>(axis())->format());
    setLabels(labelList);
}

void PolarChartDateTimeAxisAngular::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartDateTimeAxisAngular::handleFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_polarchartdatetimeaxisangular_p.cpp"
