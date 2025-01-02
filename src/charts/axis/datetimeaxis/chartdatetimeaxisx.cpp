// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartdatetimeaxisx_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/QDateTimeAxis>
#include <private/abstractchartlayout_p.h>
#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QDateTime>
#include <QtCore/QtMath>

QT_BEGIN_NAMESPACE

ChartDateTimeAxisX::ChartDateTimeAxisX(QDateTimeAxis *axis, QGraphicsItem *item)
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
}

ChartDateTimeAxisX::~ChartDateTimeAxisX()
{
}

QList<qreal> ChartDateTimeAxisX::calculateLayout() const
{
    int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QList<qreal> points;
    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / (qreal(tickCount) - 1.0);
    for (int i = 0; i < tickCount; ++i)
        points[i] =  qreal(i) * deltaX + gridRect.left();
    return points;
}

void ChartDateTimeAxisX::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;
    setLabels(createDateTimeLabels(min(), max(), layout.size(), m_axis->format()));
    HorizontalAxis::updateGeometry();
    updateLabelsDateTimes();
}

void ChartDateTimeAxisX::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void ChartDateTimeAxisX::handleFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QSizeF ChartDateTimeAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = createDateTimeLabels(min(), max(), m_axis->tickCount(), m_axis->format());
    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width = 0;
    qreal height = 0;

    if (ticksList.empty())
        return sh;

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

#include "moc_chartdatetimeaxisx_p.cpp"
