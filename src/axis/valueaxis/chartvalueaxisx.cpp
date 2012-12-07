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
#include <QDebug>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartValueAxisX::ChartValueAxisX(QValueAxis *axis, QGraphicsItem* item )
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
	QObject::connect(m_axis,SIGNAL(tickCountChanged(int)),this, SLOT(handleTickCountChanged(int)));
    QObject::connect(m_axis,SIGNAL(labelFormatChanged(QString)),this, SLOT(handleLabelFormatChanged(QString)));
}

ChartValueAxisX::~ChartValueAxisX()
{
}

QVector<qreal> ChartValueAxisX::calculateLayout() const
{
	int tickCount = m_axis->tickCount();

    Q_ASSERT(tickCount >= 2);

    QVector<qreal> points;
    points.resize(tickCount);

    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / (tickCount - 1);
    for (int i = 0; i < tickCount; ++i) {
        points[i] = i * deltaX + gridRect.left();
    }
    return points;
}

void ChartValueAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createValueLabels(min(),max(),layout.size(),m_axis->labelFormat()));
    HorizontalAxis::updateGeometry();
}

void ChartValueAxisX::handleTickCountChanged(int tick)
{
	Q_UNUSED(tick);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

void ChartValueAxisX::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = createValueLabels(min(),max(),m_axis->tickCount(),m_axis->labelFormat());
    qreal width = 0;
    qreal height = 0;


    switch (which) {
        case Qt::MinimumSize: {
            if(!ticksList.empty()) {
                foreach(QString label,ticksList) {
                    width = qMax(qreal(fn.boundingRect(label).width()),width);
                }
            }
            height = fn.height() + labelPadding();
            width = qMax(width,base.width());
            height += base.height();
            sh = QSizeF(width,height);
            break;
        }
        case Qt::PreferredSize: {
            if(!ticksList.empty()) {
                foreach(QString label,ticksList) {
                    width+=fn.boundingRect(label).width();
                }
            }
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

#include "moc_chartvalueaxisx_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
