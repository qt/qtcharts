// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/polarchartaxis_p.h>
#include <private/qabstractaxis_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE

PolarChartAxis::PolarChartAxis(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : ChartAxisElement(axis, item, intervalAxis)
{
}

PolarChartAxis::~PolarChartAxis()
{

}

void PolarChartAxis::setGeometry(const QRectF &axis, const QRectF &grid)
{
    Q_UNUSED(grid);
    setAxisGeometry(axis);

    if (emptyAxis()) {
        prepareGeometryChange();
        return;
    }

    const QList<qreal> layout = calculateLayout();
    updateLayout(layout);
}

QRectF PolarChartAxis::gridGeometry() const
{
    return QRectF();
}

void PolarChartAxis::updateLayout(const QList<qreal> &layout)
{
    int diff = ChartAxisElement::layout().size() - layout.size();

    if (animation()) {
        switch (presenter()->state()) {
        case ChartPresenter::ZoomInState:
        case ChartPresenter::ZoomOutState:
        case ChartPresenter::ScrollUpState:
        case ChartPresenter::ScrollLeftState:
        case ChartPresenter::ScrollDownState:
        case ChartPresenter::ScrollRightState:
        case ChartPresenter::ShowState:
            animation()->setAnimationType(AxisAnimation::DefaultAnimation);
            break;
        }
        // Update to "old" geometry before starting animation to avoid incorrectly sized
        // axes lingering in wrong position compared to series plot before animation can kick in.
        // Note that the position mismatch still exists even with this update, but it will be
        // far less ugly.
        if (ChartAxisElement::layout().size() != 0)
            updateGeometry();
    }

    if (diff > 0)
        deleteItems(diff);
    else if (diff <= 0)
        createItems(-diff);

    updateMinorTickItems();

    if (animation()) {
        animation()->setValues(ChartAxisElement::layout(), layout);
        presenter()->startAnimation(animation());
    } else {
        setLayout(layout);
        updateGeometry();
    }
}

bool PolarChartAxis::emptyAxis() const
{
    return !axisGeometry().isValid() || qFuzzyIsNull(min() - max());
}

void PolarChartAxis::deleteItems(int count)
{
    QList<QGraphicsItem *> gridLines = gridItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> axis = arrowItems();

    for (int i = 0; i < count; ++i) {
        if (gridItems().size() == 1 || (((gridLines.size() + 1) % 2) && gridLines.size() > 0))
            delete(shades.takeLast());
        delete(gridLines.takeLast());
        delete(labels.takeLast());
        delete(axis.takeLast());
    }
}

void PolarChartAxis::handleShadesBrushChanged(const QBrush &brush)
{
    const auto items = shadeItems();
    for (QGraphicsItem *item : items)
        static_cast<QGraphicsPathItem *>(item)->setBrush(brush);
}

void PolarChartAxis::handleShadesPenChanged(const QPen &pen)
{
    const auto items = shadeItems();
    for (QGraphicsItem *item : items)
        static_cast<QGraphicsPathItem *>(item)->setPen(pen);
}

QT_END_NAMESPACE

#include "moc_polarchartaxis_p.cpp"
