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

#include <private/polarchartvalueaxisangular_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>

QT_BEGIN_NAMESPACE

PolarChartValueAxisAngular::PolarChartValueAxisAngular(QValueAxis *axis, QGraphicsItem *item)
    : PolarChartAxisAngular(axis, item)
{
    QObject::connect(axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(axis, SIGNAL(minorTickCountChanged(int)),
                     this, SLOT(handleMinorTickCountChanged(int)));
    QObject::connect(axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
}

PolarChartValueAxisAngular::~PolarChartValueAxisAngular()
{
}

QList<qreal> PolarChartValueAxisAngular::calculateLayout() const
{
    int tickCount = static_cast<QValueAxis *>(axis())->tickCount();
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

void PolarChartValueAxisAngular::createAxisLabels(const QList<qreal> &layout)
{
    QStringList labelList = createValueLabels(min(), max(), layout.size(), 0.0, 0.0,
                                              QValueAxis::TicksFixed,
                                              static_cast<QValueAxis *>(axis())->labelFormat());
    setLabels(labelList);
}

void PolarChartValueAxisAngular::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartValueAxisAngular::handleMinorTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartValueAxisAngular::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_polarchartvalueaxisangular_p.cpp"
