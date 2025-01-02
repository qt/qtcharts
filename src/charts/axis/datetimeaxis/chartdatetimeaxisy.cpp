// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartdatetimeaxisy_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/QDateTimeAxis>
#include <private/abstractchartlayout_p.h>
#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QDateTime>
#include <QtCore/QtMath>

QT_BEGIN_NAMESPACE

ChartDateTimeAxisY::ChartDateTimeAxisY(QDateTimeAxis *axis, QGraphicsItem *item)
    : VerticalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(tickCountChanged(int)), this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis, SIGNAL(formatChanged(QString)), this, SLOT(handleFormatChanged(QString)));
}

ChartDateTimeAxisY::~ChartDateTimeAxisY()
{
}

QList<qreal> ChartDateTimeAxisY::calculateLayout() const
{
    const int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QList<qreal> points;
    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaY = gridRect.height() / (qreal(tickCount) - 1.0);
    for (int i = 0; i < tickCount; ++i)
        points[i] =  qreal(i) * -deltaY + gridRect.bottom();

    return points;
}

void ChartDateTimeAxisY::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;
    setLabels(createDateTimeLabels(min(), max(), layout.size(), m_axis->format()));
    VerticalAxis::updateGeometry();
    updateLabelsDateTimes();
}

void ChartDateTimeAxisY::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

void ChartDateTimeAxisY::handleFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if (presenter())
        presenter()->layout()->invalidate();
}

QSizeF ChartDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;

    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = createDateTimeLabels(min(), max(), m_axis->tickCount(), m_axis->format());
    qreal width = 0;
    // Height of vertical axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base height is irrelevant.
    qreal height = 0;

    if (ticksList.empty())
        return sh;

    switch (which) {
    case Qt::MinimumSize: {
        if (labelsVisible()) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            width = boundingRect.width() + labelPadding() + base.width() + 1.0;
            height = boundingRect.height() / 2.0;
        } else {
            width = base.width() + 1.0;
            height = 0;
        }
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        if (labelsVisible()) {
            qreal labelWidth = 0.0;
            qreal firstHeight = -1.0;
            foreach (const QString& s, ticksList) {
                QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                labelWidth = qMax(rect.width(), labelWidth);
                height = rect.height();
                if (firstHeight < 0.0)
                    firstHeight = height;
            }
            width = labelWidth + labelPadding() + base.width() + 2.0; //two pixels of tolerance
            height = qMax(height, firstHeight) / 2.0;
        } else {
            width = base.width() + 2.0;
            height = 0;
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

#include "moc_chartdatetimeaxisy_p.cpp"
