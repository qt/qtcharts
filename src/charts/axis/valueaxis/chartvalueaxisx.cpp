// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartvalueaxisx_p.h>
#include <QtCharts/QAbstractAxis>
#include <private/chartpresenter_p.h>
#include <QtCharts/QValueAxis>
#include <private/abstractchartlayout_p.h>
#include <private/valueaxislabel_p.h>
#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QtMath>
#include <QtCore/QDebug>


QT_BEGIN_NAMESPACE

ChartValueAxisX::ChartValueAxisX(QValueAxis *axis, QGraphicsItem *item)
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis, SIGNAL(minorTickCountChanged(int)),
                     this, SLOT(handleMinorTickCountChanged(int)));
    QObject::connect(m_axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
    QObject::connect(m_axis, SIGNAL(tickIntervalChanged(qreal)), this, SLOT(handleTickIntervalChanged(qreal)));
    QObject::connect(m_axis, SIGNAL(tickAnchorChanged(qreal)), this, SLOT(handleTickAnchorChanged(qreal)));
    QObject::connect(m_axis, SIGNAL(tickTypeChanged(QValueAxis::TickType)), this,
                     SLOT(handleTickTypeChanged(QValueAxis::TickType)));
}

ChartValueAxisX::~ChartValueAxisX()
{
}

QList<qreal> ChartValueAxisX::calculateLayout() const
{
    if (m_axis->tickType() == QValueAxis::TicksFixed) {
        int tickCount = m_axis->tickCount();

        Q_ASSERT(tickCount >= 2);

        QList<qreal> points;
        points.resize(tickCount);

        const QRectF &gridRect = gridGeometry();
        const qreal deltaX = gridRect.width() / (qreal(tickCount) - 1.0);
        for (int i = 0; i < tickCount; ++i)
            points[i] = qreal(i) * deltaX + gridRect.left();
        return points;
    } else { // QValueAxis::TicksDynamic
        const qreal interval = m_axis->tickInterval();
        const qreal anchor = m_axis->tickAnchor();
        const qreal maxValue = max();
        const qreal minValue = min();

        // Find the first major tick right after the min of the range
        const qreal ticksFromAnchor = (anchor - minValue) / interval;
        const qreal firstMajorTick = anchor - std::floor(ticksFromAnchor) * interval;

        const QRectF &gridRect = gridGeometry();
        const qreal deltaX = gridRect.width() / (maxValue - minValue);

        QList<qreal> points;
        const qreal leftPos = gridRect.left();
        qreal value = firstMajorTick;
        while (value <= maxValue) {
            points << (value - minValue) * deltaX + leftPos;
            value += interval;
        }

        return points;
    }
}

void ChartValueAxisX::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    const QList<qreal> &dynamicMinorTicklayout = ChartAxisElement::dynamicMinorTicklayout();
    if (layout.isEmpty() && dynamicMinorTicklayout.isEmpty())
        return;
    setLabels(createValueLabels(min(), max(), layout.size(), m_axis->tickInterval(),
                                m_axis->tickAnchor(), m_axis->tickType(), m_axis->labelFormat()));
    HorizontalAxis::updateGeometry();
    updateLabelsValues(m_axis);
}

void ChartValueAxisX::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter()) presenter()->layout()->invalidate();
}

void ChartValueAxisX::handleMinorTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void ChartValueAxisX::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter()) presenter()->layout()->invalidate();
}

void ChartValueAxisX::handleTickIntervalChanged(qreal interval)
{
    Q_UNUSED(interval);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter()) presenter()->layout()->invalidate();
}

void ChartValueAxisX::handleTickAnchorChanged(qreal anchor)
{
    Q_UNUSED(anchor);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter()) presenter()->layout()->invalidate();
}

void ChartValueAxisX::handleTickTypeChanged(QValueAxis::TickType type)
{
    Q_UNUSED(type);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = createValueLabels(min(), max(), m_axis->tickCount(),
                                              m_axis->tickInterval(), m_axis->tickAnchor(),
                                              m_axis->tickType(), m_axis->labelFormat());
    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        if (labelsVisible()) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            width = boundingRect.width() / 2.0;
            height = boundingRect.height() + labelPadding() + base.height() + 1.0;
        } else {
            width = 0;
            height = base.height() + 1.0;
        }
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        if (labelsVisible()) {
            qreal labelHeight = 0.0;
            qreal firstWidth = -1.0;
            foreach (const QString& s, ticksList) {
                QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                labelHeight = qMax(rect.height(), labelHeight);
                width = rect.width();
                if (firstWidth < 0.0)
                    firstWidth = width;
            }
            height = labelHeight + labelPadding() + base.height() + 1.0;
            width = qMax(width, firstWidth) / 2.0;
        } else {
            height = base.height() + 1.0;
            width = 0;
        }
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }
    return sh;
}

QT_END_NAMESPACE

#include "moc_chartvalueaxisx_p.cpp"
