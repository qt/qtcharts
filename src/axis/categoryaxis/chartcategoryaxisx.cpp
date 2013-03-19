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

#include "chartcategoryaxisx_p.h"
#include "qcategoryaxis.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartCategoryAxisX::ChartCategoryAxisX(QCategoryAxis *axis, QGraphicsItem* item)
    : HorizontalAxis(axis, item, true),
      m_axis(axis)
{
}

ChartCategoryAxisX::~ChartCategoryAxisX()
{
}

QVector<qreal> ChartCategoryAxisX::calculateLayout() const
{
    int tickCount = m_axis->categoriesLabels().count() + 1;
    QVector<qreal> points;

    if (tickCount < 2)
        return points;

    const QRectF &gridRect = gridGeometry();
    qreal range  = max() - min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = gridRect.width() / range;
        for (int i = 0; i < tickCount; ++i) {
            if (i < tickCount - 1) {
                qreal x = (m_axis->startValue(m_axis->categoriesLabels().at(i)) - min()) * scale + gridRect.left();
                points[i] = x;
            } else {
                qreal x = (m_axis->endValue(m_axis->categoriesLabels().at(i - 1)) - min())  * scale + gridRect.left();
                points[i] = x;
            }
        }
    }

    return points;
}

void ChartCategoryAxisX::updateGeometry()
{
    setLabels(m_axis->categoriesLabels() << "");
    HorizontalAxis::updateGeometry();
}

void ChartCategoryAxisX::handleAxisUpdated()
{
    updateGeometry();
}

QSizeF ChartCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_axis->categoriesLabels();
    qreal width = 0; // Width is irrelevant for X axes with interval labels
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF boundingRect = labelBoundingRect(fn, "...");
        height = boundingRect.height() + labelPadding();
        height += base.height();
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        int labelHeight = 0;
        foreach (const QString& s, ticksList) {
            QRect rect = labelBoundingRect(fn, s);
            labelHeight = qMax(rect.height(), labelHeight);
        }
        height = labelHeight + labelPadding();
        height += base.height();
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
