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

#include "chartvalueaxisy_p.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "qvalueaxis.h"
#include "chartlayout_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartValueAxisY::ChartValueAxisY(QValueAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item),
      m_axis(axis)
{
	QObject::connect(m_axis,SIGNAL(tickCountChanged(int)),this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis,SIGNAL(labelFormatChanged(QString)),this, SLOT(handleLabelFormatChanged(QString)));
}

ChartValueAxisY::~ChartValueAxisY()
{
}

QVector<qreal> ChartValueAxisY::calculateLayout() const
{
	int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QVector<qreal> points;
    points.resize(tickCount);

    const QRectF &gridRect = gridGeometry();

    const qreal deltaY = gridRect.height() / (tickCount - 1);
    for (int i = 0; i < tickCount; ++i) {
        points[i] = i * -deltaY + gridRect.bottom();
    }

    return points;
}

void ChartValueAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createValueLabels(min(),max(),layout.size(),m_axis->labelFormat()));
    VerticalAxis::updateGeometry();
}

void ChartValueAxisY::handleTickCountChanged(int tick)
{
	Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
	if(presenter()) presenter()->layout()->invalidate();
}

void ChartValueAxisY::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartValueAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = createValueLabels(min(),max(),m_axis->tickCount(),m_axis->labelFormat());
    qreal width = 0;
    qreal height = 0;

    int count = 1;

    if(!ticksList.empty()){
        count = qMax(ticksList.last().count(),ticksList.first().count());
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
    case Qt::PreferredSize:
    {
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

#include "moc_chartvalueaxisy_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
