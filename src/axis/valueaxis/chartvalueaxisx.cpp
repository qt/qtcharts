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

#include "chartvalueaxisx_p.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "qvalueaxis.h"
#include "chartlayout_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartValueAxisX::ChartValueAxisX(QValueAxis *axis, ChartPresenter *presenter)
    : HorizontalAxis(axis, presenter),
      m_tickCount(0), m_axis(axis)
{
}

ChartValueAxisX::~ChartValueAxisX()
{
}

QVector<qreal> ChartValueAxisX::calculateLayout() const
{
    Q_ASSERT(m_tickCount >= 2);

    QVector<qreal> points;
    points.resize(m_tickCount);

    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / (m_tickCount - 1);
    for (int i = 0; i < m_tickCount; ++i) {
        points[i] = i * deltaX + gridRect.left();
    }
    return points;
}

void ChartValueAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createValueLabels(layout.size()));
    HorizontalAxis::updateGeometry();
}

void ChartValueAxisX::handleAxisUpdated()
{
    if (m_tickCount != m_axis->tickCount()) {
        m_tickCount = m_axis->tickCount();
        presenter()->layout()->invalidate();
    }

    ChartAxis::handleAxisUpdated();
}

QSizeF ChartValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = createValueLabels(m_tickCount);
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize:{
        int count = qMax(ticksList.last().count(),ticksList.first().count());
        count = qMin(count,5);
        width = fn.averageCharWidth() * count;
        height = fn.height() + labelPadding();
        width = qMax(width,base.width());
        height += base.height();
        sh = QSizeF(width,height);
        break;
    }
    case Qt::PreferredSize:{
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

QTCOMMERCIALCHART_END_NAMESPACE
