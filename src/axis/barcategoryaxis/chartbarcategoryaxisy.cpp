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

ChartBarCategoryAxisY::ChartBarCategoryAxisY(QBarCategoryAxis *axis, ChartPresenter *presenter)
    : VerticalAxis(axis, presenter, true),
      m_categoriesAxis(axis)
{
}

ChartBarCategoryAxisY::~ChartBarCategoryAxisY()
{
}

QVector<qreal> ChartBarCategoryAxisY::calculateLayout() const
{
    int count = m_categoriesAxis->d_ptr->count();

    Q_ASSERT(count >= 1);

    QVector<qreal> points;
    points.resize(count + 2);

    const QRectF &gridRect = gridGeometry();

    const qreal delta = gridRect.height() / (count);
    qreal offset = - min() - 0.5;

    if (delta < 1)
        return points;

    if (offset < 0)
        offset = int(offset * gridRect.height() / (max() - min())) % int(delta) + delta;
    else
        offset = int(offset * gridRect.height() / (max() - min())) % int(delta);

    for (int i = -1; i < count + 1; ++i) {
        int y = gridRect.bottom() - i * delta - offset;
        points[i + 1] = y;
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

    if (m_categoriesAxis->categories() != m_categories) {
        m_categories = m_categoriesAxis->categories();
        if (ChartAxis::layout().count() == m_categoriesAxis->d_ptr->count() + 2)
            updateGeometry();
    }
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartBarCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = ChartAxis::sizeHint(which, constraint);
    QStringList ticksList = createCategoryLabels(ChartAxis::layout());

    qreal width=0;
    qreal height=0;

      switch (which) {
        case Qt::MinimumSize:
            width = fn.boundingRect("...").width() + labelPadding();
            height = fn.height();
            width+=base.width();
            height=qMax(height,base.height());
            sh = QSizeF(width,height);
            break;
        case Qt::PreferredSize:{

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                height+=rect.height();
                width=qMax(rect.width()+labelPadding() + 1 ,width); //one pixel torelance
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
