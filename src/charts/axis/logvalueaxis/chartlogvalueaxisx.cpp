// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include <QtCharts/qlogvalueaxis.h>
#include <QtCore/qmath.h>
#include <QtWidgets/qgraphicslayout.h>
#include <private/abstractchartlayout_p.h>
#include <private/chartlogvalueaxisx_p.h>
#include <private/chartpresenter_p.h>

QT_BEGIN_NAMESPACE

ChartLogValueAxisX::ChartLogValueAxisX(QLogValueAxis *axis, QGraphicsItem *item)
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(baseChanged(qreal)), this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(m_axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
}

ChartLogValueAxisX::~ChartLogValueAxisX()
{
}

QList<qreal> ChartLogValueAxisX::calculateLayout() const
{
    QList<qreal> points;
    points.resize(m_axis->tickCount());

    const qreal logMax = qLn(m_axis->max()) / qLn(m_axis->base());
    const qreal logMin = qLn(m_axis->min()) / qLn(m_axis->base());
    const qreal leftEdge = qMin(logMin, logMax);
    const qreal ceilEdge = std::ceil(leftEdge);

    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / qAbs(logMax - logMin);
    for (int i = 0; i < m_axis->tickCount(); ++i)
        points[i] = (ceilEdge + qreal(i)) * deltaX - leftEdge * deltaX + gridRect.left();

    return points;
}

void ChartLogValueAxisX::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    setLabels(createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), layout.size(), m_axis->labelFormat()));
    HorizontalAxis::updateGeometry();
}

void ChartLogValueAxisX::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

void ChartLogValueAxisX::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartLogValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    const QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    const int tickCount = m_axis->tickCount();
    QStringList ticksList;
    QSizeF sh;

    if (m_axis->max() > m_axis->min() && tickCount > 0)
        ticksList = createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), tickCount, m_axis->labelFormat());
    else
        ticksList.append(QStringLiteral(" "));
    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize:{
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

#include "moc_chartlogvalueaxisx_p.cpp"
