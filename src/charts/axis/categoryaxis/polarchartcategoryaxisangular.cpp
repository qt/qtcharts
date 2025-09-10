// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/polarchartcategoryaxisangular_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCharts/QCategoryAxis>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

PolarChartCategoryAxisAngular::PolarChartCategoryAxisAngular(QCategoryAxis *axis, QGraphicsItem *item)
    : PolarChartAxisAngular(axis, item, true)
{
    QObject::connect(axis, SIGNAL(categoriesChanged()), this, SLOT(handleCategoriesChanged()));
}

PolarChartCategoryAxisAngular::~PolarChartCategoryAxisAngular()
{
}

QList<qreal> PolarChartCategoryAxisAngular::calculateLayout() const
{
    QCategoryAxis *catAxis = static_cast<QCategoryAxis *>(axis());
    int tickCount = catAxis->categoriesLabels().size() + 1;
    QList<qreal> points;

    if (tickCount < 2)
        return points;

    qreal range = max() - min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = 360.0 / range;
        qreal angle;
        for (int i = 0; i < tickCount; ++i) {
            if (i < tickCount - 1)
                angle = (catAxis->startValue(catAxis->categoriesLabels().at(i)) - min()) * scale;
            else
                angle = (catAxis->endValue(catAxis->categoriesLabels().at(i - 1)) - min()) * scale;
            points[i] = angle;
        }
    }

    return points;
}

void PolarChartCategoryAxisAngular::createAxisLabels(const QList<qreal> &layout)
{
    Q_UNUSED(layout);
    setLabels(static_cast<QCategoryAxis *>(axis())->categoriesLabels() << QString());
}

void PolarChartCategoryAxisAngular::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_polarchartcategoryaxisangular_p.cpp"
