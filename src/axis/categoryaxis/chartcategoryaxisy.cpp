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

#include "chartcategoryaxisy_p.h"
#include "qcategoryaxis.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartCategoryAxisY::ChartCategoryAxisY(QCategoryAxis *axis,ChartPresenter *presenter) : VerticalAxis(axis,presenter),
     m_axis(axis)
{
    setLabelBetweenTicks(true);
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

    const QRectF& gridRect = gridGeometry();
    qreal range = m_axis->max() - m_axis->min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = gridRect.height() / range;
        for (int i = 0; i < tickCount; ++i)
            if (i < tickCount - 1) {
                int y = -(m_axis->startValue(m_axis->categoriesLabels().at(i)) - m_axis->min()) * scale + gridRect.bottom();
                points[i] = y;
            } else {
                int y = -(m_axis->endValue(m_axis->categoriesLabels().at(i - 1)) - m_axis->min())  * scale + gridRect.bottom();
                points[i] = y;
            }
    }

    return points;
}

void ChartCategoryAxisY::updateGeometry()
{
    setLabels(m_axis->categoriesLabels()<<"");
    VerticalAxis::updateGeometry();
}

void ChartCategoryAxisY::handleAxisUpdated()
{
    updateGeometry();
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = ChartAxis::sizeHint(which, constraint);
    QStringList ticksList; //TODO::
    qreal width=0;
    qreal height=0;

      switch (which) {
        case Qt::MinimumSize:
            width = fn.boundingRect("...").width()+labelPadding();
            height = fn.height();
            width=qMax(width,base.width());
            height+=base.height();
            sh = QSizeF(width,height);
            break;
        case Qt::PreferredSize:{

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                height+=rect.height();
                width=qMax(rect.width()+labelPadding(),width);
            }
            height=qMax(height,base.height());
            width+=base.width();
            sh = QSizeF(width,height);
            break;
        }
        default:
          break;
      }

      return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
