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

#include "chartdatetimeaxisy_p.h"
#include "chartpresenter_p.h"
#include "qdatetimeaxis.h"
#include "chartlayout_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <QDateTime>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDateTimeAxisY::ChartDateTimeAxisY(QDateTimeAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis,SIGNAL(tickCountChanged(int)),this, SLOT(handleTickCountChanged(int)));
}

ChartDateTimeAxisY::~ChartDateTimeAxisY()
{
}

QVector<qreal> ChartDateTimeAxisY::calculateLayout() const
{
    int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QVector<qreal> points;
    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaY = gridRect.height() / (tickCount - 1);
    for (int i = 0; i < tickCount; ++i) {
        int y = i * -deltaY + gridRect.bottom();
        points[i] = y;
    }

    return points;
}

void ChartDateTimeAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createDateTimeLabels(min(),max(), layout.size(),m_axis->format()));
    VerticalAxis::updateGeometry();
}

void ChartDateTimeAxisY::handleTickCountChanged(int tick)
{
    Q_UNUSED(tick)
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = createDateTimeLabels(min(),max(),m_axis->tickCount(),m_axis->format());
    qreal width = 0;
    qreal height = 0;

    if(ticksList.empty()){
        return sh;
    }

    switch (which) {
        case Qt::MinimumSize: {
            width = fn.boundingRect("...").width() + labelPadding();
            width += base.width();
            height = fn.height();
            height = qMax(height,base.height());
            sh = QSizeF(width,height);
            break;
        }
        case Qt::PreferredSize: {
            int count = qMax(ticksList.first().count() , ticksList.last().count());
            width = count*fn.averageCharWidth() + labelPadding() + 2; //two pixels of tolerance
            width += base.width();
            height = fn.height() * ticksList.count();
            height = qMax(height,base.height());
            sh = QSizeF(width,height);
            break;
        }
        default:
        break;
    }

    return sh;
}

#include "moc_chartdatetimeaxisy_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
