/****************************************************************************
 **
 ** Copyright (C) 2012 Digia Plc
 ** All rights reserved.
 ** For any questions to Digia, please use contact form at http://qt.digia.com
 **
 ** This file is part of the Qt Commercial Charts Add-on.
 **
 ** $QT_BEGIN_LICENSE$
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.
 **
 ** If you have questions regarding the use of this file, please use
 ** contact form at http://qt.digia.com
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "chartbarcategoryaxisy_p.h"
#include "chartpresenter_p.h"
#include "qbarcategoryaxis_p.h"
#include <qmath.h>
#include <QFontMetrics>
#include <QDebug>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBarCategoryAxisY::ChartBarCategoryAxisY(QBarCategoryAxis *axis, ChartPresenter *presenter)
    : ChartAxis(axis, presenter),
      m_categoriesAxis(axis)
{
}

ChartBarCategoryAxisY::~ChartBarCategoryAxisY()
{
}

QVector<qreal> ChartBarCategoryAxisY::calculateLayout() const
{
    int count = m_categoriesAxis->d_ptr->count();

    Q_ASSERT(count >= 1);

    QVector<qreal> points;
    points.resize(count + 2);

    QRectF rect = presenter()->chartsGeometry();

    const qreal delta = rect.height() / (count);
    qreal offset = - m_min - 0.5;

    if (delta < 1) return points;

    if (offset <= 0)
        offset = int(offset * rect.height() / (m_max - m_min)) % int(delta) + delta;
    else
        offset = int(offset * rect.height() / (m_max - m_min)) % int(delta);

    points[0] = rect.bottom();
    points[count + 1] = rect.top();

    for (int i = 0; i < count; ++i) {
        int y = rect.bottom() - i * delta - offset;
        points[i + 1] = y;
    }
    return points;
}

QStringList ChartBarCategoryAxisY::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result;
    QRectF rect = presenter()->chartsGeometry();
    qreal d = (m_max - m_min) / rect.height();
    for (int i = 0; i < layout.count() - 1; ++i) {
        qreal x = qFloor(((rect.height() - (layout[i + 1] + layout[i]) / 2 + rect.top()) * d + m_min + 0.5));
        if ((x < m_categoriesAxis->categories().count()) && (x >= 0))
            result << m_categoriesAxis->categories().at(x);
        else
            result << ""; // No label for x coordinate
    }
    result << "";
    return result;
}

void ChartBarCategoryAxisY::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();

    if (layout.isEmpty())
        return;

    QStringList ticksList = createCategoryLabels(layout);

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    QRectF chartRect = presenter()->chartsGeometry();

    const qreal delta = chartRect.height() / (m_categoriesAxis->d_ptr->count());

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine(chartRect.left() , chartRect.top(), chartRect.left(), chartRect.bottom());

    qreal height = chartRect.bottom();
    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(chartRect.left() , layout[i], chartRect.right(), layout[i]);
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
        labelItem->setText(ticksList.at(i));
        const QRectF& rect = labelItem->boundingRect();
        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());

        if (i == 0)
            labelItem->setPos(chartRect.left() - rect.width() - label_padding , layout[i + 1] + (delta) / 2 - center.y());
        else
            labelItem->setPos(chartRect.left() - rect.width() - label_padding , layout[i] - (delta) / 2 - center.y());

        if (labelItem->pos().y() + rect.height() >= height || labelItem->pos().y() < chartRect.top()) {
            labelItem->setVisible(false);
        } else {
            labelItem->setVisible(true);
            height = labelItem->pos().y();
        }

        if ((i + 1) % 2 && i > 1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i / 2 - 1));
            rectItem->setRect(chartRect.left(), layout[i], chartRect.width(), layout[i - 1] - layout[i]);
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i + 1));
        lineItem->setLine(chartRect.left() - 5, layout[i], chartRect.left(), layout[i]);
    }
}

void ChartBarCategoryAxisY::handleAxisUpdated()
{

    if (m_categoriesAxis->categories() != m_categories) {
        m_categories = m_categoriesAxis->categories();
        if (ChartAxis::layout().count() == m_categoriesAxis->d_ptr->count() + 2)
            updateGeometry();
    }
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartBarCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_font);
    QSizeF sh;
    QSizeF base = ChartAxis::sizeHint(which, constraint);
    QStringList ticksList = createCategoryLabels(ChartAxis::layout());
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize:
        width = fn.boundingRect("...").width() + label_padding;
        height = fn.height();
        width += base.width();
        height = qMax(height, base.height());
        sh = QSizeF(width, height);
        break;
    case Qt::PreferredSize:
        for (int i = 0; i < ticksList.size(); ++i) {
            QRectF rect = fn.boundingRect(ticksList.at(i));
            height += rect.height();
            width = qMax(rect.width() + label_padding, width);
        }
        height = qMax(height, base.height());
        width += base.width();
        sh = QSizeF(width, height);
        break;
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
