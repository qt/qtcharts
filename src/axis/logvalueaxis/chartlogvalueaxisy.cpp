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

#include "chartlogvalueaxisy_p.h"
#include "chartpresenter_p.h"
#include "qlogvalueaxis.h"
#include "chartlayout_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartLogValueAxisY::ChartLogValueAxisY(QLogValueAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(baseChanged(qreal)),this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(m_axis,SIGNAL(labelFormatChanged(QString)),this, SLOT(handleLabelFormatChanged(QString)));
}

ChartLogValueAxisY::~ChartLogValueAxisY()
{
}

QVector<qreal> ChartLogValueAxisY::calculateLayout() const
{
    QVector<qreal> points;
    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    qreal leftEdge = logMin < logMax ? logMin : logMax;
    qreal ceilEdge = ceil(leftEdge);
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));

    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaY = gridRect.height() / qAbs(logMax - logMin);
    for (int i = 0; i < tickCount; ++i)
        points[i] = (ceilEdge + i) * -deltaY - leftEdge * -deltaY + gridRect.bottom();

    return points;
}


void ChartLogValueAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), layout.size(), m_axis->labelFormat()));
    VerticalAxis::updateGeometry();
}

void ChartLogValueAxisY::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

void ChartLogValueAxisY::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartLogValueAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList;
    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));
    if (m_axis->max() > m_axis->min() && tickCount > 1)
        ticksList = createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), tickCount, m_axis->labelFormat());
    else
        ticksList.append(QString(" "));
    qreal width = 0;
    // Height of vertical axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base height is irrelevant.
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF boundingRect = labelBoundingRect(fn, "...");
        width = boundingRect.width() + labelPadding();
        width += base.width();
        height = boundingRect.height() / 2.0;
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        int labelWidth = 0;
        int firstHeight = -1;
        foreach (const QString& s, ticksList) {
            QRect rect = labelBoundingRect(fn, s);
            labelWidth = qMax(rect.width(), labelWidth);
            height = rect.height();
            if (firstHeight < 0)
                firstHeight = height;
        }
        width = labelWidth + labelPadding() + 2; //two pixels of tolerance
        width += base.width();
        height = qMax(height, qreal(firstHeight)) / 2.0;
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }

    return sh;
}

#include "moc_chartlogvalueaxisy_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
