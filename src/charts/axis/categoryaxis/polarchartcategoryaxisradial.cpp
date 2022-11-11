// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/polarchartcategoryaxisradial_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCharts/QCategoryAxis>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

PolarChartCategoryAxisRadial::PolarChartCategoryAxisRadial(QCategoryAxis *axis, QGraphicsItem *item)
    : PolarChartAxisRadial(axis, item, true)
{
    QObject::connect(axis, SIGNAL(categoriesChanged()), this, SLOT(handleCategoriesChanged()));
}

PolarChartCategoryAxisRadial::~PolarChartCategoryAxisRadial()
{
}

QList<qreal> PolarChartCategoryAxisRadial::calculateLayout() const
{
    QCategoryAxis *catAxis = static_cast<QCategoryAxis *>(axis());
    int tickCount = catAxis->categoriesLabels().size() + 1;
    QList<qreal> points;

    if (tickCount < 2)
        return points;

    qreal range = max() - min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = (axisGeometry().width() / 2) / range;
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

void PolarChartCategoryAxisRadial::createAxisLabels(const QList<qreal> &layout)
{
    Q_UNUSED(layout);
    setLabels(static_cast<QCategoryAxis *>(axis())->categoriesLabels() << QString());
}

void PolarChartCategoryAxisRadial::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_polarchartcategoryaxisradial_p.cpp"
