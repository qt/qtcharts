// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/abstractchartlayout_p.h>
#include <private/chartpresenter_p.h>
#include <private/qlegend_p.h>
#include <private/chartaxiselement_p.h>
#include <private/charttitle_p.h>
#include <private/chartbackground_p.h>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

static const qreal golden_ratio = 0.4;

AbstractChartLayout::AbstractChartLayout(ChartPresenter *presenter)
    : m_presenter(presenter),
      m_margins(20, 20, 20, 20)
{
}

AbstractChartLayout::~AbstractChartLayout()
{
}

void AbstractChartLayout::setGeometry(const QRectF &rect)
{
    if (!rect.isValid())
        return;

    // If the chart has a fixed geometry then don't update visually, unless plotbackground is
    // visible.
    const bool updateLayout = (!m_presenter->isFixedGeometry()
                               || m_presenter->isPlotAreaBackgroundVisible()
                               || m_presenter->geometry() == rect);
    if (m_presenter->chart()->isVisible()) {
        QList<ChartAxisElement *> axes = m_presenter->axisItems();
        ChartTitle *title = m_presenter->titleElement();
        QLegend *legend = m_presenter->legend();
        ChartBackground *background = m_presenter->backgroundElement();

        QRectF contentGeometry = calculateBackgroundGeometry(rect, background, updateLayout);

        contentGeometry = calculateContentGeometry(contentGeometry);

        if (title && title->isVisible())
            contentGeometry = calculateTitleGeometry(contentGeometry, title, updateLayout);

        if (legend->isAttachedToChart() && legend->isVisible())
            contentGeometry = calculateLegendGeometry(contentGeometry, legend, updateLayout);

        contentGeometry = calculateAxisGeometry(contentGeometry, axes, updateLayout);

        if (contentGeometry.isValid()) {
            m_presenter->setGeometry(contentGeometry);
            if (updateLayout) {
                if (m_presenter->chart()->chartType() == QChart::ChartTypeCartesian)
                    static_cast<QGraphicsRectItem *>(m_presenter->plotAreaElement())->setRect(contentGeometry);
                else
                    static_cast<QGraphicsEllipseItem *>(m_presenter->plotAreaElement())->setRect(contentGeometry);
            }
        }
    }

    QGraphicsLayout::setGeometry(rect);
}

QRectF AbstractChartLayout::calculateContentGeometry(const QRectF &geometry) const
{
    return geometry.adjusted(m_margins.left(), m_margins.top(), -m_margins.right(), -m_margins.bottom());
}

QRectF AbstractChartLayout::calculateContentMinimum(const QRectF &minimum) const
{
    return  minimum.adjusted(0, 0, m_margins.left() + m_margins.right(), m_margins.top() + m_margins.bottom());
}


QRectF AbstractChartLayout::calculateBackgroundGeometry(const QRectF &geometry,
                                                        ChartBackground *background,
                                                        bool update) const
{
    qreal left;
    qreal top;
    qreal right;
    qreal bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRectF backgroundGeometry = geometry.adjusted(left, top, -right, -bottom);
    if (background && update)
        background->setRect(backgroundGeometry);
    return backgroundGeometry;
}

QRectF AbstractChartLayout::calculateBackgroundMinimum(const QRectF &minimum) const
{
    qreal left;
    qreal top;
    qreal right;
    qreal bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    return minimum.adjusted(0, 0, left + right, top + bottom);
}

QRectF AbstractChartLayout::calculateLegendGeometry(const QRectF &geometry, QLegend *legend,
                                                    bool update) const
{
    QSizeF size = legend->effectiveSizeHint(Qt::PreferredSize, QSizeF(-1, -1));
    QRectF legendRect;
    QRectF result;

    switch (legend->alignment()) {
    case Qt::AlignTop: {
        legendRect = QRectF(geometry.topLeft(), QSizeF(geometry.width(), size.height()));
        result = geometry.adjusted(0, legendRect.height(), 0, 0);
        break;
    }
    case Qt::AlignBottom: {
        legendRect = QRectF(QPointF(geometry.left(), geometry.bottom() - size.height()), QSizeF(geometry.width(), size.height()));
        result = geometry.adjusted(0, 0, 0, -legendRect.height());
        break;
    }
    case Qt::AlignLeft: {
        qreal width = qMin(size.width(), geometry.width() * golden_ratio);
        legendRect = QRectF(geometry.topLeft(), QSizeF(width, geometry.height()));
        result = geometry.adjusted(width, 0, 0, 0);
        break;
    }
    case Qt::AlignRight: {
        qreal width = qMin(size.width(), geometry.width() * golden_ratio);
        legendRect = QRectF(QPointF(geometry.right() - width, geometry.top()), QSizeF(width, geometry.height()));
        result = geometry.adjusted(0, 0, -width, 0);
        break;
    }
    default: {
        legendRect = QRectF(0, 0, 0, 0);
        result = geometry;
        break;
    }
    }
    if (update)
        legend->setGeometry(legendRect);

    return result;
}

QRectF AbstractChartLayout::calculateLegendMinimum(const QRectF &geometry, QLegend *legend) const
{
    if (!legend->isAttachedToChart() || !legend->isVisible()) {
        return geometry;
    } else {
        QSizeF minSize = legend->effectiveSizeHint(Qt::MinimumSize, QSizeF(-1, -1));
        return geometry.adjusted(0, 0, minSize.width(), minSize.height());
    }
}

QRectF AbstractChartLayout::calculateTitleGeometry(const QRectF &geometry, ChartTitle *title,
                                                   bool update) const
{
    if (update)
        title->setGeometry(geometry);
    if (title->text().isEmpty()) {
        return geometry;
    } else {
        // Round to full pixel via QPoint to avoid one pixel clipping on the edge in some cases
        QPointF center((geometry.center() - title->boundingRect().center()).toPoint());
        if (update)
            title->setPos(center.x(), title->pos().y());
        return geometry.adjusted(0, title->boundingRect().height() + 1, 0, 0);
    }
}

QRectF AbstractChartLayout::calculateTitleMinimum(const QRectF &minimum, ChartTitle *title) const
{
    if (!title->isVisible() || title->text().isEmpty()) {
        return minimum;
    } else {
        QSizeF min = title->sizeHint(Qt::MinimumSize);
        return  minimum.adjusted(0, 0, min.width(), min.height());
    }
}

QSizeF AbstractChartLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    if (which == Qt::MinimumSize) {
        QList<ChartAxisElement *> axes = m_presenter->axisItems();
        ChartTitle *title = m_presenter->titleElement();
        QLegend *legend = m_presenter->legend();
        QRectF minimumRect(0, 0, 0, 0);
        minimumRect = calculateBackgroundMinimum(minimumRect);
        minimumRect = calculateContentMinimum(minimumRect);
        minimumRect = calculateTitleMinimum(minimumRect, title);
        minimumRect = calculateLegendMinimum(minimumRect, legend);
        minimumRect = calculateAxisMinimum(minimumRect, axes);
        return minimumRect.size().toSize();
    }
    return QSize(-1, -1);
}

void AbstractChartLayout::setMargins(const QMargins &margins)
{
    if (m_margins != margins) {
        m_margins = margins;
        updateGeometry();
    }
}

QMargins AbstractChartLayout::margins() const
{
    return m_margins;
}

QT_END_NAMESPACE
