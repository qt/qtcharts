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

#include "chartlogvalueaxisx_p.h"
#include "chartpresenter_p.h"
#include "qlogvalueaxis.h"
#include "chartlayout_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartLogValueAxisX::ChartLogValueAxisX(QLogValueAxis *axis, QGraphicsItem* item)
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis,SIGNAL(baseChanged(qreal)),this, SLOT(handleBaseChanged(qreal)));
}

ChartLogValueAxisX::~ChartLogValueAxisX()
{
}

QVector<qreal> ChartLogValueAxisX::calculateLayout() const
{
    QVector<qreal> points;

    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    qreal leftEdge = logMin < logMax ? logMin : logMax;
    qreal ceilEdge = ceil(leftEdge);
    int tickCount = qAbs(qRound(logMax - logMin));
    tickCount++;

    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / qAbs(logMax - logMin);
    for (int i = 0; i < tickCount; ++i)
        points[i] = (ceilEdge + i) * deltaX - leftEdge * deltaX + gridRect.left();

    return points;
}

void ChartLogValueAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), layout.size(), m_axis->labelFormat()));
    HorizontalAxis::updateGeometry();
}

void ChartLogValueAxisX::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartLogValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList;
    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    int tickCount = qAbs(qRound(logMax - logMin));
    tickCount++;

    if (m_axis->max() > m_axis->min() && tickCount > 1)
        ticksList = createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), tickCount, m_axis->labelFormat());
    else
        ticksList.append(QString(" "));
    qreal width = 0;
    qreal height = 0;


    switch (which) {
    case Qt::MinimumSize:{
        int count = qMax(ticksList.last().count(),ticksList.first().count());
        width = fn.averageCharWidth() * count;
        height = fn.height() + labelPadding();
        width = qMax(width,base.width());
        height += base.height();
        sh = QSizeF(width,height);
        break;
    }
    case Qt::PreferredSize: {
        int count = qMax(ticksList.last().count(),ticksList.first().count());
        width=fn.averageCharWidth() * count;
        height=fn.height()+labelPadding();
        width=qMax(width,base.width());
        height+=base.height();
        sh = QSizeF(width,height);
        break;
    }
    default:
        break;
    }

    return sh;
}

#include "moc_chartlogvalueaxisx_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
