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

#include <QtCharts/qlogvalueaxis.h>
#include <QtCore/qmath.h>
#include <private/abstractchartlayout_p.h>
#include <private/chartpresenter_p.h>
#include <private/polarchartlogvalueaxisangular_p.h>

QT_BEGIN_NAMESPACE

PolarChartLogValueAxisAngular::PolarChartLogValueAxisAngular(QLogValueAxis *axis,
                                                             QGraphicsItem *item)
    : PolarChartAxisAngular(axis, item)
{
    QObject::connect(axis, SIGNAL(baseChanged(qreal)), this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(axis, SIGNAL(labelFormatChanged(QString)),
                     this, SLOT(handleLabelFormatChanged(QString)));
}

PolarChartLogValueAxisAngular::~PolarChartLogValueAxisAngular()
{
}

QList<qreal> PolarChartLogValueAxisAngular::calculateLayout() const
{
    QLogValueAxis *logValueAxis = qobject_cast<QLogValueAxis *>(axis());

    QList<qreal> points;
    points.resize(logValueAxis->tickCount());

    const qreal logMax = std::log10(logValueAxis->max()) / std::log10(logValueAxis->base());
    const qreal logMin = std::log10(logValueAxis->min()) / std::log10(logValueAxis->base());
    const qreal startEdge = qMin(logMin, logMax);
    const qreal delta = 360.0 / qAbs(logMax - logMin);
    const qreal initialSpan = (std::ceil(startEdge) - startEdge) * delta;

    for (int i = 0; i < logValueAxis->tickCount(); ++i)
        points[i] = initialSpan + (delta * qreal(i));

    return points;
}

void PolarChartLogValueAxisAngular::createAxisLabels(const QList<qreal> &layout)
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

QT_END_NAMESPACE

#include "moc_polarchartlogvalueaxisangular_p.cpp"
