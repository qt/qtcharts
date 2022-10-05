// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/qabstractaxis.h>
#include <QtCharts/qlogvalueaxis.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCore/qmath.h>
#include <QtGui/qtextdocument.h>
#include <QtWidgets/qgraphicslayout.h>
#include <private/abstractchartlayout_p.h>
#include <private/abstractdomain_p.h>
#include <private/cartesianchartaxis_p.h>
#include <private/chartpresenter_p.h>
#include <private/linearrowitem_p.h>
#include <private/qabstractaxis_p.h>

QT_BEGIN_NAMESPACE

CartesianChartAxis::CartesianChartAxis(QAbstractAxis *axis, QGraphicsItem *item , bool intervalAxis)
    : ChartAxisElement(axis, item, intervalAxis)
{
    Q_ASSERT(item);
}


CartesianChartAxis::~CartesianChartAxis()
{
}

void CartesianChartAxis::createItems(int count)
{
    if (arrowItems().size() == 0) {
        QGraphicsLineItem *arrow = new LineArrowItem(this, this);
        arrow->setAcceptedMouseButtons({});
        arrow->setPen(axis()->linePen());
        arrowGroup()->addToGroup(arrow);
    }

    if (intervalAxis() && gridItems().size() == 0) {
        for (int i = 0 ; i < 2 ; i  ++){
            QGraphicsLineItem *item = new QGraphicsLineItem(this);
            item->setAcceptedMouseButtons({});
            item->setPen(axis()->gridLinePen());
            gridGroup()->addToGroup(item);
            QGraphicsRectItem *shades = new QGraphicsRectItem(this);
            shades->setAcceptedMouseButtons({});
            shades->setPen(axis()->shadesPen());
            shades->setBrush(axis()->shadesBrush());
            shadeGroup()->addToGroup(shades);
        }
    }

    QGraphicsTextItem *title = titleItem();
    title->setFont(axis()->titleFont());
    title->setDefaultTextColor(axis()->titleBrush().color());
    title->setHtml(axis()->titleText());

    for (int i = 0; i < count; ++i) {
        QGraphicsLineItem *arrow = new QGraphicsLineItem(this);
        arrow->setAcceptedMouseButtons({});
        QGraphicsLineItem *grid = new QGraphicsLineItem(this);
        grid->setAcceptedMouseButtons({});
        QGraphicsTextItem *label;
        if (axis()->type() == QAbstractAxis::AxisTypeValue) {
            label = new ValueAxisLabel(this);
            connect(static_cast<ValueAxisLabel *>(label), &ValueAxisLabel::valueChanged,
                    this, &ChartAxisElement::valueLabelEdited);
            if (labelsEditable())
                static_cast<ValueAxisLabel *>(label)->setEditable(true);
#if QT_CONFIG(charts_datetime_axis)
        } else if (axis()->type() == QAbstractAxis::AxisTypeDateTime) {
            DateTimeAxisLabel *dateTimeLabel = new DateTimeAxisLabel(this);
            label = dateTimeLabel;
            connect(dateTimeLabel, &DateTimeAxisLabel::dateTimeChanged,
                    this, &ChartAxisElement::dateTimeLabelEdited);
            if (labelsEditable())
                dateTimeLabel->setEditable(true);
            dateTimeLabel->setFormat(static_cast<QDateTimeAxis*>(axis())->format());
#endif
        } else {
            label = new QGraphicsTextItem(this);
        }

        label->setAcceptedMouseButtons({});
        label->document()->setDocumentMargin(ChartPresenter::textMargin());
        arrow->setPen(axis()->linePen());
        grid->setPen(axis()->gridLinePen());
        label->setFont(axis()->labelsFont());
        label->setDefaultTextColor(axis()->labelsBrush().color());
        label->setRotation(axis()->labelsAngle());
        arrowGroup()->addToGroup(arrow);
        gridGroup()->addToGroup(grid);
        labelGroup()->addToGroup(label);

        if (gridItems().size() == 1 || (((gridItems().size() + 1) % 2) && gridItems().size() > 0)) {
            QGraphicsRectItem *shades = new QGraphicsRectItem(this);
            shades->setPen(axis()->shadesPen());
            shades->setBrush(axis()->shadesBrush());
            shadeGroup()->addToGroup(shades);
        }
    }
}

void CartesianChartAxis::updateMinorTickItems()
{
    int currentCount = minorArrowItems().size();
    int expectedCount = 0;
    if (axis()->type() == QAbstractAxis::AxisTypeValue) {
        QValueAxis *valueAxis = qobject_cast<QValueAxis *>(axis());
        if (valueAxis->tickType() == QValueAxis::TicksFixed) {
            expectedCount = valueAxis->minorTickCount() * (valueAxis->tickCount() - 1);
            expectedCount = qMax(expectedCount, 0);
        } else {
            const qreal interval = valueAxis->tickInterval();
            const qreal anchor = valueAxis->tickAnchor();
            const qreal max = valueAxis->max();
            const qreal min = valueAxis->min();
            const int _minorTickCount = valueAxis->minorTickCount();

            // Find the closest major tick <= the min of the range, even if it's not drawn!
            // This is where we'll start counting minor ticks from, because minor ticks
            // might need to be drawn even before the first major tick.
            const qreal ticksFromAnchor = (anchor - min) / interval;
            const qreal firstMajorTick = anchor - std::ceil(ticksFromAnchor) * interval;

            const qreal deltaMinor = interval / qreal(_minorTickCount + 1);
            qreal minorTick = firstMajorTick + deltaMinor;
            int minorCounter = 0;

            while (minorTick < min) {
                minorTick += deltaMinor;
                minorCounter++;
            }

            QList<qreal> points;

            // Calculate the points on axis value space. Conversion to graphical points
            // will be done on axis specific geometry update function
            while (minorTick <= max) {
                if (minorCounter < _minorTickCount) {
                    expectedCount++;
                    minorCounter++;
                    points << (minorTick - min);
                } else {
                    minorCounter = 0;
                }
                minorTick += deltaMinor;
            }

            setDynamicMinorTickLayout(points);
        }
    } else if (axis()->type() == QAbstractAxis::AxisTypeLogValue) {
        QLogValueAxis *logValueAxis = qobject_cast<QLogValueAxis *>(axis());

        int minorTickCount = logValueAxis->minorTickCount();
        if (minorTickCount < 0)
            minorTickCount = qMax(qFloor(logValueAxis->base()) - 2, 0);

        expectedCount = minorTickCount * (logValueAxis->tickCount() + 1);
        expectedCount = qMax(expectedCount, logValueAxis->minorTickCount());
    } else {
        // minor ticks are not supported
        return;
    }

    int diff = expectedCount - currentCount;
    if (diff > 0) {
        for (int i = 0; i < diff; ++i) {
            QGraphicsLineItem *minorGridLineItem = new QGraphicsLineItem(this);
            minorGridLineItem->setPen(axis()->minorGridLinePen());
            minorGridGroup()->addToGroup(minorGridLineItem);

            QGraphicsLineItem *minorArrowLineItem = new QGraphicsLineItem(this);
            minorArrowLineItem->setPen(axis()->linePen());
            minorArrowGroup()->addToGroup(minorArrowLineItem);
        }
    } else {
        QList<QGraphicsItem *> minorGridItemsList = minorGridItems();
        QList<QGraphicsItem *> minorArrowItemsList = minorArrowItems();
        for (int i = 0; i > diff; --i) {
            if (!minorGridItemsList.isEmpty())
                delete minorGridItemsList.takeLast();

            if (!minorArrowItemsList.isEmpty())
                delete minorArrowItemsList.takeLast();
        }
    }
}

void CartesianChartAxis::deleteItems(int count)
{
    QList<QGraphicsItem *> lines = gridItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> axis = arrowItems();

    for (int i = 0; i < count; ++i) {
        if (lines.size() == 1 || (((lines.size() + 1) % 2) && lines.size() > 0))
            delete(shades.takeLast());
        delete(lines.takeLast());
        delete(labels.takeLast());
        delete(axis.takeLast());
    }
}

void CartesianChartAxis::updateLayout(const QList<qreal> &layout)
{
    int diff = ChartAxisElement::layout().size() - layout.size();

    if (diff > 0)
        deleteItems(diff);
    else if (diff <= 0)
        createItems(-diff);

    updateMinorTickItems();

    if (animation()) {
        switch (presenter()->state()) {
        case ChartPresenter::ZoomInState:
            animation()->setAnimationType(AxisAnimation::ZoomInAnimation);
            animation()->setAnimationPoint(presenter()->statePoint());
            break;
        case ChartPresenter::ZoomOutState:
            animation()->setAnimationType(AxisAnimation::ZoomOutAnimation);
            animation()->setAnimationPoint(presenter()->statePoint());
            break;
        case ChartPresenter::ScrollUpState:
        case ChartPresenter::ScrollLeftState:
            animation()->setAnimationType(AxisAnimation::MoveBackwordAnimation);
            break;
        case ChartPresenter::ScrollDownState:
        case ChartPresenter::ScrollRightState:
            animation()->setAnimationType(AxisAnimation::MoveForwardAnimation);
            break;
        case ChartPresenter::ShowState:
            animation()->setAnimationType(AxisAnimation::DefaultAnimation);
            break;
        }
        animation()->setValues(ChartAxisElement::layout(), layout);
        presenter()->startAnimation(animation());
    } else {
        setLayout(layout);
        updateGeometry();
    }
}

bool CartesianChartAxis::emptyAxis() const
{
    return axisGeometry().isEmpty()
           || gridGeometry().isEmpty()
           || qFuzzyIsNull(max() - min());
}

void CartesianChartAxis::setGeometry(const QRectF &axis, const QRectF &grid)
{
    m_gridRect = grid;
    setAxisGeometry(axis);

    if (emptyAxis()) {
        prepareGeometryChange();
        return;
    }

    const QList<qreal> layout = calculateLayout();
    updateLayout(layout);
}

QSizeF CartesianChartAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return QSizeF();
}

void CartesianChartAxis::setDateTimeLabelsFormat(const QString &format)
{
    if (max() <= min()
            || layout().size() < 1
            || axis()->type() != QAbstractAxis::AxisTypeDateTime) {
        return;
    }
#if QT_CONFIG(charts_datetime_axis)
    for (int i = 0; i < layout().size(); i++)
        static_cast<DateTimeAxisLabel *>(labelItems().at(i))->setFormat(format);
#endif
}

void CartesianChartAxis::handleArrowPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, arrowItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void CartesianChartAxis::handleGridPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, gridItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void CartesianChartAxis::handleMinorArrowPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, minorArrowItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void CartesianChartAxis::handleMinorGridPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, minorGridItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void CartesianChartAxis::handleGridLineColorChanged(const QColor &color)
{
    foreach (QGraphicsItem *item, gridItems()) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem *>(item);
        QPen pen = lineItem->pen();
        pen.setColor(color);
        lineItem->setPen(pen);
    }
}

void CartesianChartAxis::handleMinorGridLineColorChanged(const QColor &color)
{
    foreach (QGraphicsItem *item, minorGridItems()) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem *>(item);
        QPen pen = lineItem->pen();
        pen.setColor(color);
        lineItem->setPen(pen);
    }
}

void CartesianChartAxis::handleShadesBrushChanged(const QBrush &brush)
{
    foreach (QGraphicsItem *item, shadeItems())
        static_cast<QGraphicsRectItem *>(item)->setBrush(brush);
}

void CartesianChartAxis::handleShadesPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item, shadeItems())
        static_cast<QGraphicsRectItem *>(item)->setPen(pen);
}

void CartesianChartAxis::updateLabelsValues(QValueAxis *axis)
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;

    if (axis->tickType() == QValueAxis::TicksFixed) {
        for (int i = 0; i < layout.size(); ++i) {
            qreal value = axis->isReverse()
                    ? min() + ((layout.size() - 1 - i) * (max() - min()) / (layout.size() - 1))
                    : min() + (i * (max() - min()) / (layout.size() - 1));
            static_cast<ValueAxisLabel *>(labelItems().at(i))->setValue(value);
        }
    } else {
        const qreal anchor = axis->tickAnchor();
        const qreal interval = axis->tickInterval();
        const qreal ticksFromAnchor = (anchor - min()) / interval;
        const qreal firstMajorTick = anchor - std::floor(ticksFromAnchor) * interval;

        int i = axis->isReverse() ? labelItems().size()-1 : 0;
        qreal value = firstMajorTick;
        while (value <= max()) {
            static_cast<ValueAxisLabel *>(labelItems().at(i))->setValue(value);
            value += interval;
            i += axis->isReverse() ? -1 : 1;
        }
    }
}

void CartesianChartAxis::updateLabelsDateTimes()
{
    if (max() <= min() || layout().size() < 1)
        return;
#if QT_CONFIG(charts_datetime_axis)
    for (int i = 0; i < layout().size(); i++) {
        qreal value = min() + (i * (max() - min()) / (layout().size() - 1));
        static_cast<DateTimeAxisLabel *>(labelItems().at(i))->setValue(
                    QDateTime::fromMSecsSinceEpoch(value));
    }
#endif
}

QT_END_NAMESPACE

#include "moc_cartesianchartaxis_p.cpp"
