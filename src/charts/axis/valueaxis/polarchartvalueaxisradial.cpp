/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/polarchartvalueaxisradial_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>

QT_CHARTS_BEGIN_NAMESPACE

PolarChartValueAxisRadial::PolarChartValueAxisRadial(QValueAxis *axis, QGraphicsItem *item)
    : PolarChartAxisRadial(axis, item)
{
    QObject::connect(axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
}

PolarChartValueAxisRadial::~PolarChartValueAxisRadial()
{
}

QVector<qreal> PolarChartValueAxisRadial::calculateLayout() const
{
    int tickCount = static_cast<QValueAxis *>(axis())->tickCount();
    Q_ASSERT(tickCount >= 2);

    QVector<qreal> points;
    points.resize(tickCount);

    const qreal d = (axisGeometry().width() / 2) / qreal(tickCount - 1);

    for (int i = 0; i < tickCount; ++i) {
        qreal radialCoordinate = qreal(i) * d;
        points[i] = radialCoordinate;
    }

    return points;
}

void PolarChartValueAxisRadial::createAxisLabels(const QVector<qreal> &layout)
{
    setLabels(createValueLabels(min(), max(), layout.size(), static_cast<QValueAxis *>(axis())->labelFormat()));
}

void PolarChartValueAxisRadial::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartValueAxisRadial::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

#include "moc_polarchartvalueaxisradial_p.cpp"

QT_CHARTS_END_NAMESPACE
