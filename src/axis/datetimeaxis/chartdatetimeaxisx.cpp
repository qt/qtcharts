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

#include "chartdatetimeaxisx_p.h"
#include "chartpresenter_p.h"
#include "qdatetimeaxis.h"
#include "chartlayout_p.h"
#include <QGraphicsLayout>
#include <QDateTime>
#include <QFontMetrics>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDateTimeAxisX::ChartDateTimeAxisX(QDateTimeAxis *axis, QGraphicsItem* item)
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis,SIGNAL(tickCountChanged(int)),this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis,SIGNAL(formatChanged(QString)),this, SLOT(handleFormatChanged(QString)));
}

ChartDateTimeAxisX::~ChartDateTimeAxisX()
{
}

QVector<qreal> ChartDateTimeAxisX::calculateLayout() const
{
    int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QVector<qreal> points;
    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / (tickCount - 1);
    for (int i = 0; i < tickCount; ++i) {
        int x = i * deltaX + gridRect.left();
        points[i] = x;
    }
    return points;
}

void ChartDateTimeAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createDateTimeLabels(min(),max(), layout.size(),m_axis->format()));
    HorizontalAxis::updateGeometry();
}

void ChartDateTimeAxisX::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick)
    if(presenter()) presenter()->layout()->invalidate();
}

void ChartDateTimeAxisX::handleFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartDateTimeAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = createDateTimeLabels(min(),max(),m_axis->tickCount(),m_axis->format());
    qreal width = 0;
    qreal height = 0;

    if(ticksList.empty()){
        return sh;
    }


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

#include "moc_chartdatetimeaxisx_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
