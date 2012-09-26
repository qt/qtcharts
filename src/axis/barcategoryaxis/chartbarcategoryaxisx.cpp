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

#include "chartbarcategoryaxisx_p.h"
#include "chartpresenter_p.h"
#include "qbarcategoryaxis_p.h"
#include <QFontMetrics>
#include <QDebug>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBarCategoryAxisX::ChartBarCategoryAxisX(QBarCategoryAxis *axis,ChartPresenter *presenter) : HorizontalAxis(axis,presenter),
m_categoriesAxis(axis)
{
    setLabelBetweenTicks(true);
}

ChartBarCategoryAxisX::~ChartBarCategoryAxisX()
{
}

QVector<qreal> ChartBarCategoryAxisX::calculateLayout() const
{
    int count = m_categoriesAxis->d_ptr->count();

    Q_ASSERT(count>=1);

    QVector<qreal> points;
    points.resize(count+2);

    const QRectF& gridRect = gridGeometry();

    const qreal delta = gridRect.width()/(count);
    qreal offset =-min()-0.5;

    if(delta<1) return points;

    if(offset<0) {
        offset = int(offset * gridRect.width()/(max() - min()))%int(delta) + delta;
    }
    else {
        offset = int(offset * gridRect.width()/(max() - min()))%int(delta);
    }

    for (int i = -1; i < count+1; ++i) {
        qreal x = offset + i * delta + gridRect.left();
        points[i+1] = x;
    }
    return points;
}

QStringList ChartBarCategoryAxisX::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result ;
    const QRectF& gridRect = gridGeometry();

    qreal d = (max() - min())/gridRect.width();
    for (int i = 0;i < layout.count()-1; ++i) {
        qreal x = qFloor((((layout[i] + layout[i+1])/2-gridRect.left())*d + min()+0.5));
        if ((x < m_categoriesAxis->categories().count()) && (x >= 0)) {
            result << m_categoriesAxis->categories().at(x);
        }
        else {
            // No label for x coordinate
            result << "";
        }
    }
    result << "";
    return result;
}


void ChartBarCategoryAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if(layout.isEmpty()) return;
    setLabels(createCategoryLabels(layout));
    HorizontalAxis::updateGeometry();
}

void ChartBarCategoryAxisX::handleAxisUpdated()
{
    if(m_categoriesAxis->categories()!=m_categories)
    {
        m_categories=m_categoriesAxis->categories();
        if(ChartAxis::layout().count()==m_categoriesAxis->d_ptr->count()+2) updateGeometry();
    }
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartBarCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
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
            width = fn.boundingRect("...").width();
            height = fn.height()+labelPadding();
            width=qMax(width,base.width());
            height+=base.height();
            sh = QSizeF(width,height);
            break;
        case Qt::PreferredSize:{

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                width+=rect.width();
                height=qMax(rect.height()+labelPadding(),height);
            }
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
