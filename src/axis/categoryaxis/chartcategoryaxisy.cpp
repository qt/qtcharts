/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "chartcategoryaxisy_p.h"
#include "qcategoryaxis.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartCategoryAxisY::ChartCategoryAxisY(QCategoryAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item, true),
      m_axis(axis)
{
}

ChartCategoryAxisY::~ChartCategoryAxisY()
{
}

QVector<qreal> ChartCategoryAxisY::calculateLayout() const
{
    int tickCount = m_axis->categoriesLabels().count() + 1;
    QVector<qreal> points;

    if (tickCount < 2)
        return points;

    const QRectF &gridRect = gridGeometry();
    qreal range = max() - min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = gridRect.height() / range;
        for (int i = 0; i < tickCount; ++i) {
            if (i < tickCount - 1) {
                qreal y = -(m_axis->startValue(m_axis->categoriesLabels().at(i)) - min()) * scale + gridRect.bottom();
                points[i] = y;
            } else {
                qreal y = -(m_axis->endValue(m_axis->categoriesLabels().at(i - 1)) - min())  * scale + gridRect.bottom();
                points[i] = y;
            }
        }
    }

    return points;
}

void ChartCategoryAxisY::updateGeometry()
{
    setLabels(m_axis->categoriesLabels() << "");
    VerticalAxis::updateGeometry();
}

void ChartCategoryAxisY::handleAxisUpdated()
{
    updateGeometry();
}

QSizeF ChartCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_axis->categoriesLabels();
    qreal width = 0;
    qreal height = 0; // Height is irrelevant for Y axes with interval labels

    switch (which) {
    case Qt::MinimumSize: {
        QRectF boundingRect = labelBoundingRect(fn, "...");
        width = boundingRect.width() + labelPadding();
        width += base.width();
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        int labelWidth = 0;
        foreach (const QString& s, ticksList) {
            QRect rect = labelBoundingRect(fn, s);
            labelWidth = qMax(rect.width(), labelWidth);
        }
        width = labelWidth + labelPadding() + 1;
        width += base.width();
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }
    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
