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

#include <private/polarchartlogvalueaxisangular_p.h>
#include <private/abstractchartlayout_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

PolarChartLogValueAxisAngular::PolarChartLogValueAxisAngular(QLogValueAxis *axis, QGraphicsItem *item)
    : PolarChartAxisAngular(axis, item)
{
    QObject::connect(axis, SIGNAL(baseChanged(qreal)), this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
}

PolarChartLogValueAxisAngular::~PolarChartLogValueAxisAngular()
{
}

QVector<qreal> PolarChartLogValueAxisAngular::calculateLayout() const
{
    QLogValueAxis *logValueAxis = static_cast<QLogValueAxis *>(axis());
    const qreal logMax = log10(logValueAxis->max()) / log10(logValueAxis->base());
    const qreal logMin = log10(logValueAxis->min()) / log10(logValueAxis->base());
    const qreal startEdge = logMin < logMax ? logMin : logMax;
    const qreal delta = 360.0 / qAbs(logMax - logMin);
    const qreal initialSpan = (ceil(startEdge) - startEdge) * delta;
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));

    QVector<qreal> points;
    points.resize(tickCount);

    for (int i = 0; i < tickCount; ++i) {
        qreal angularCoordinate = initialSpan + (delta * qreal(i));
        points[i] = angularCoordinate;
    }

    return points;
}

void PolarChartLogValueAxisAngular::createAxisLabels(const QVector<qreal> &layout)
{
    QLogValueAxis *logValueAxis = static_cast<QLogValueAxis *>(axis());
    setLabels(createLogValueLabels(logValueAxis->min(),
                                   logValueAxis->max(),
                                   logValueAxis->base(),
                                   layout.size(),
                                   logValueAxis->labelFormat()));
}

void PolarChartLogValueAxisAngular::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartLogValueAxisAngular::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

#include "moc_polarchartlogvalueaxisangular_p.cpp"

QT_CHARTS_END_NAMESPACE
