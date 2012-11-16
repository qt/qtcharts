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

#include "chartbarcategoryaxisy_p.h"
#include "chartpresenter_p.h"
#include "qbarcategoryaxis_p.h"
#include <qmath.h>
#include <QFontMetrics>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBarCategoryAxisY::ChartBarCategoryAxisY(QBarCategoryAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item, true),
      m_categoriesAxis(axis)
{
}

ChartBarCategoryAxisY::~ChartBarCategoryAxisY()
{
}

QVector<qreal> ChartBarCategoryAxisY::calculateLayout() const
{
    QVector<qreal> points;
    const QRectF& gridRect = gridGeometry();
    qreal range = max() - min();
    const qreal delta = gridRect.height()/range;

    if(delta<2) return points;

    qreal offset = - min() - 0.5;
    offset = int(offset * delta)%int(delta);

    int count = qFloor(range);
    if(count < 1 ) return points;

    points.resize(count+2);

    for (int i = 0; i < count+2; ++i) {
        points[i] =  gridRect.bottom() - i * delta -offset;
    }

    return points;
}

QStringList ChartBarCategoryAxisY::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result;
    const QRectF &gridRect = gridGeometry();
    qreal d = (max() - min()) / gridRect.height();

    for (int i = 0; i < layout.count() - 1; ++i) {
        qreal x = qFloor(((gridRect.height() - (layout[i + 1] + layout[i]) / 2 + gridRect.top()) * d + min() + 0.5));
        if ((x < m_categoriesAxis->categories().count()) && (x >= 0)) {
            result << m_categoriesAxis->categories().at(x);
        } else {
            // No label for x coordinate
            result << "";
        }
    }
    result << "";
    return result;
}

void ChartBarCategoryAxisY::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createCategoryLabels(layout));
    VerticalAxis::updateGeometry();
}

void ChartBarCategoryAxisY::handleAxisUpdated()
{
	//TODO:
	/*
    if (m_categoriesAxis->categories() != m_categories) {
        m_categories = m_categoriesAxis->categories();
        if (ChartAxis::layout().count() == m_categoriesAxis->d_ptr->count() + 2)
            updateGeometry();
    }*/
    //TODO :: ChartAxis::handleAxisUpdated();
}

QSizeF ChartBarCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = createCategoryLabels(ChartAxis::layout());

    qreal width=0;
    qreal height=0;

      switch (which) {
        case Qt::MinimumSize:
            width = fn.boundingRect("...").width() + labelPadding();
            height = fn.height();
            width+=base.width();
            if(base.width()>0) width+=labelPadding();
            height=qMax(height,base.height());
            sh = QSizeF(width,height);
            break;
        case Qt::PreferredSize:{

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                height+=rect.height();
                width=qMax(rect.width()+labelPadding(),width); //one pixel torelance
            }
            height=qMax(height,base.height());
            width+=base.width();
            if(base.width()>0) width+=labelPadding();
            sh = QSizeF(width,height);
            break;
        }
        default:
          break;
      }
      return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
