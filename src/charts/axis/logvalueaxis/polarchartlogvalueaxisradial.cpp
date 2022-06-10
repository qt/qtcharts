// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/qlogvalueaxis.h>
#include <QtCore/qmath.h>
#include <private/abstractchartlayout_p.h>
#include <private/chartpresenter_p.h>
#include <private/polarchartlogvalueaxisradial_p.h>

QT_BEGIN_NAMESPACE

PolarChartLogValueAxisRadial::PolarChartLogValueAxisRadial(QLogValueAxis *axis, QGraphicsItem *item)
    : PolarChartAxisRadial(axis, item)
{
    QObject::connect(axis, SIGNAL(baseChanged(qreal)), this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(axis, SIGNAL(labelFormatChanged(QString)),
                     this, SLOT(handleLabelFormatChanged(QString)));
}

PolarChartLogValueAxisRadial::~PolarChartLogValueAxisRadial()
{
}

QList<qreal> PolarChartLogValueAxisRadial::calculateLayout() const
{
    QLogValueAxis *logValueAxis = qobject_cast<QLogValueAxis *>(axis());

    QList<qreal> points;
    points.resize(logValueAxis->tickCount());

    const qreal logMax = qLn(logValueAxis->max()) / qLn(logValueAxis->base());
    const qreal logMin = qLn(logValueAxis->min()) / qLn(logValueAxis->base());
    const qreal innerEdge = logMin < logMax ? logMin : logMax;
    const qreal delta = (axisGeometry().width() / 2.0) / qAbs(logMax - logMin);
    const qreal initialSpan = (std::ceil(innerEdge) - innerEdge) * delta;

    for (int i = 0; i < logValueAxis->tickCount(); ++i)
        points[i] = initialSpan + (delta * qreal(i));

    return points;
}

void PolarChartLogValueAxisRadial::createAxisLabels(const QList<qreal> &layout)
{
    QLogValueAxis *logValueAxis = static_cast<QLogValueAxis *>(axis());
    setLabels(createLogValueLabels(logValueAxis->min(),
                                   logValueAxis->max(),
                                   logValueAxis->base(),
                                   layout.size(),
                                   logValueAxis->labelFormat()));
}

void PolarChartLogValueAxisRadial::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void PolarChartLogValueAxisRadial::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_polarchartlogvalueaxisradial_p.cpp"
