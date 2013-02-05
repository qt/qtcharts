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

#include "chartlayout_p.h"
#include "chartpresenter_p.h"
#include "qlegend_p.h"
#include "chartaxis_p.h"
#include "charttitle_p.h"
#include "chartbackground_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

static const qreal maxAxisPortion = 0.4;

ChartLayout::ChartLayout(ChartPresenter *presenter)
    : m_presenter(presenter),
      m_margins(20, 20, 20, 20),
      m_minChartRect(0, 0, 200, 200)
{

}

ChartLayout::~ChartLayout()
{

}

void ChartLayout::setGeometry(const QRectF &rect)
{
    if (!rect.isValid())
        return;

    QList<ChartAxis *> axes = m_presenter->axisItems();
    ChartTitle *title = m_presenter->titleElement();
    QLegend *legend = m_presenter->legend();
    ChartBackground *background = m_presenter->backgroundElement();

    QRectF contentGeometry = calculateBackgroundGeometry(rect, background);

    contentGeometry = calculateContentGeometry(contentGeometry);

    if (title && title->isVisible())
        contentGeometry = calculateTitleGeometry(contentGeometry, title);

    if (legend->isAttachedToChart() && legend->isVisible())
        contentGeometry = calculateLegendGeometry(contentGeometry, legend);

    contentGeometry = calculateAxisGeometry(contentGeometry, axes);

    m_presenter->setGeometry(contentGeometry);

    QGraphicsLayout::setGeometry(rect);
}

QRectF ChartLayout::calculateContentGeometry(const QRectF &geometry) const
{
    return geometry.adjusted(m_margins.left(), m_margins.top(), -m_margins.right(), -m_margins.bottom());
}

QRectF ChartLayout::calculateContentMinimum(const QRectF &minimum) const
{
    return  minimum.adjusted(0, 0, m_margins.left() + m_margins.right(), m_margins.top() + m_margins.bottom());
}


QRectF ChartLayout::calculateBackgroundGeometry(const QRectF &geometry, ChartBackground *background) const
{
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRectF backgroundGeometry = geometry.adjusted(left, top, -right, -bottom);
    if (background)
        background->setRect(backgroundGeometry);
    return backgroundGeometry;
}

QRectF ChartLayout::calculateBackgroundMinimum(const QRectF &minimum) const
{
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    return minimum.adjusted(0, 0, left + right, top + bottom);
}


QRectF ChartLayout::calculateAxisGeometry(const QRectF &geometry, const QList<ChartAxis *>& axes) const
{
    QSizeF left(0,0);
    QSizeF minLeft(0,0);
    QSizeF right(0,0);
    QSizeF minRight(0,0);
    QSizeF bottom(0,0);
    QSizeF minBottom(0,0);
    QSizeF top(0,0);
    QSizeF minTop(0,0);
    int leftCount = 0;
    int rightCount = 0;
    int topCount = 0;
    int bottomCount = 0;

    foreach (ChartAxis *axis , axes) {

        if (!axis->isVisible())
            continue;


        QSizeF size = axis->effectiveSizeHint(Qt::PreferredSize);
        //this is used to get single thick font size
        QSizeF minSize = axis->effectiveSizeHint(Qt::MinimumSize);

        switch (axis->alignment()) {
        case Qt::AlignLeft:
           left.setWidth(left.width()+size.width());
           left.setHeight(qMax(left.height(),size.height()));
           minLeft.setWidth(minLeft.width()+minSize.width());
           minLeft.setHeight(qMax(minLeft.height(),minSize.height()));
           leftCount++;
           break;
        case Qt::AlignRight:
            right.setWidth(right.width()+size.width());
            right.setHeight(qMax(right.height(),size.height()));
            minRight.setWidth(minRight.width()+minSize.width());
            minRight.setHeight(qMax(minRight.height(),minSize.height()));
            rightCount++;
            break;
        case Qt::AlignTop:
            top.setWidth(qMax(top.width(),size.width()));
            top.setHeight(top.height()+size.height());
            minTop.setWidth(qMax(minTop.width(),minSize.width()));
            minTop.setHeight(minTop.height()+minSize.height());
            topCount++;
            break;
        case Qt::AlignBottom:
            bottom.setWidth(qMax(bottom.width(), size.width()));
            bottom.setHeight(bottom.height() + size.height());
            minBottom.setWidth(qMax(minBottom.width(),minSize.width()));
            minBottom.setHeight(minBottom.height() + minSize.height());
            bottomCount++;
            break;
        default:
            qWarning()<<"Axis is without alignment !";
            break;
        }
    }

    int totalVerticalAxes = leftCount + rightCount;
    qreal leftSqueezeRatio = 1.0;
    qreal rightSqueezeRatio = 1.0;
    qreal vratio = 0;

    if (totalVerticalAxes > 0)
        vratio = (maxAxisPortion * geometry.width()) / totalVerticalAxes;

    if (leftCount > 0) {
        int maxWidth = vratio * leftCount;
        if (left.width() > maxWidth) {
            leftSqueezeRatio = maxWidth / left.width();
            left.setWidth(maxWidth);
        }
    }
    if (rightCount > 0) {
        int maxWidth = vratio * rightCount;
        if (right.width() > maxWidth) {
            rightSqueezeRatio = maxWidth / right.width();
            right.setWidth(maxWidth);
        }
    }

    int totalHorizontalAxes = topCount + bottomCount;
    qreal topSqueezeRatio = 1.0;
    qreal bottomSqueezeRatio = 1.0;
    qreal hratio = 0;

    if (totalHorizontalAxes > 0)
        hratio = (maxAxisPortion * geometry.height()) / totalHorizontalAxes;

    if (topCount > 0) {
        int maxHeight = hratio * topCount;
        if (top.height() > maxHeight) {
            topSqueezeRatio = maxHeight / top.height();
            top.setHeight(maxHeight);
        }
    }
    if (bottomCount > 0) {
        int maxHeight = hratio * bottomCount;
        if (bottom.height() > maxHeight) {
            bottomSqueezeRatio = maxHeight / bottom.height();
            bottom.setHeight(maxHeight);
        }
    }

    qreal minHeight = qMax(minLeft.height(),minRight.height()) + 1;
    qreal minWidth = qMax(minTop.width(),minBottom.width()) + 1;

    QRectF chartRect = geometry.adjusted(qMax(left.width(),minWidth/2), qMax(top.height(), minHeight/2),-qMax(right.width(),minWidth/2),-qMax(bottom.height(),minHeight/2));

    qreal leftOffset = 0;
    qreal rightOffset = 0;
    qreal topOffset = 0;
    qreal bottomOffset = 0;

    foreach(ChartElement *axisElement , axes) {

        //TODO fixme
        ChartAxis* axis = qobject_cast<ChartAxis*>(axisElement);

        if (!axis->isVisible())
            continue;

        QSizeF size = axis->effectiveSizeHint(Qt::PreferredSize);

        switch(axis->alignment()){
        case Qt::AlignLeft:{
            qreal width = size.width();
            if (leftSqueezeRatio < 1.0)
                width *= leftSqueezeRatio;
            leftOffset+=width;
            axis->setGeometry(QRect(chartRect.left()-leftOffset, geometry.top(),width, geometry.bottom()),chartRect);
            break;
        }
        case Qt::AlignRight:{
            qreal width = size.width();
            if (rightSqueezeRatio < 1.0)
                width *= rightSqueezeRatio;
            axis->setGeometry(QRect(chartRect.right()+rightOffset,geometry.top(),width,geometry.bottom()),chartRect);
            rightOffset+=width;
            break;
        }
        case Qt::AlignTop: {
            qreal height = size.height();
            if (topSqueezeRatio < 1.0)
                height *= topSqueezeRatio;
            axis->setGeometry(QRect(geometry.left(), chartRect.top() - topOffset - height, geometry.width(), height), chartRect);
            topOffset += height;
            break;
        }
        case Qt::AlignBottom:
            qreal height = size.height();
            if (bottomSqueezeRatio < 1.0)
                height *= bottomSqueezeRatio;
            axis->setGeometry(QRect(geometry.left(), chartRect.bottom() + bottomOffset, geometry.width(), height), chartRect);
            bottomOffset += height;
            break;
        }
    }

    return chartRect;
}

QRectF ChartLayout::calculateAxisMinimum(const QRectF &minimum, const QList<ChartAxis *>& axes) const
{
    QSizeF left;
    QSizeF right;
    QSizeF bottom;
    QSizeF top;

    foreach (ChartAxis *axis, axes) {

        QSizeF size = axis->effectiveSizeHint(Qt::MinimumSize);

        if (!axis->isVisible())
            continue;

        switch (axis->alignment()) {
        case Qt::AlignLeft:
            left.setWidth(left.width() + size.width());
            left.setHeight(qMax(left.height() * 2, size.height()));
            break;
        case Qt::AlignRight:
            right.setWidth(right.width() + size.width());
            right.setHeight(qMax(right.height() * 2, size.height()));
            break;
        case Qt::AlignTop:
            top.setWidth(qMax(top.width(), size.width()));
            top.setHeight(top.height() + size.height());
            break;
        case Qt::AlignBottom:
            bottom.setWidth(qMax(bottom.width(), size.width()));
            bottom.setHeight(bottom.height() + size.height());
            break;
        }
    }
    return minimum.adjusted(0, 0, left.width() + right.width() + qMax(top.width(), bottom.width()), top.height() + bottom.height() + qMax(left.height(), right.height()));
}

QRectF ChartLayout::calculateLegendGeometry(const QRectF &geometry, QLegend *legend) const
{
    QSizeF size = legend->effectiveSizeHint(Qt::PreferredSize, QSizeF(-1, -1));
    QRectF legendRect;
    QRectF result;

    switch (legend->alignment()) {
    case Qt::AlignTop: {
        legendRect = QRectF(geometry.topLeft(), QSizeF(geometry.width(), size.height()));
        result = geometry.adjusted(0, legendRect.height(), 0, 0);
        break;
    }
    case Qt::AlignBottom: {
        legendRect = QRectF(QPointF(geometry.left(), geometry.bottom() - size.height()), QSizeF(geometry.width(), size.height()));
        result = geometry.adjusted(0, 0, 0, -legendRect.height());
        break;
    }
    case Qt::AlignLeft: {
        qreal width = qMin(size.width(), geometry.width() * maxAxisPortion);
        legendRect = QRectF(geometry.topLeft(), QSizeF(width, geometry.height()));
        result = geometry.adjusted(width, 0, 0, 0);
        break;
    }
    case Qt::AlignRight: {
        qreal width = qMin(size.width(), geometry.width() * maxAxisPortion);
        legendRect = QRectF(QPointF(geometry.right() - width, geometry.top()), QSizeF(width, geometry.height()));
        result = geometry.adjusted(0, 0, -width, 0);
        break;
    }
    default: {
        legendRect = QRectF(0, 0, 0, 0);
        result = geometry;
        break;
    }
    }

    legend->setGeometry(legendRect);

    return result;
}

QRectF ChartLayout::calculateLegendMinimum(const QRectF &geometry, QLegend *legend) const
{
    QSizeF minSize = legend->effectiveSizeHint(Qt::MinimumSize, QSizeF(-1, -1));
    return geometry.adjusted(0, 0, minSize.width(), minSize.height());
}

QRectF ChartLayout::calculateTitleGeometry(const QRectF &geometry, ChartTitle *title) const
{
    title->setGeometry(geometry);
    QPointF center = geometry.center() - title->boundingRect().center();
    title->setPos(center.x(),title->pos().y());
    return geometry.adjusted(0,title->boundingRect().height()+1,0,0);
}

QRectF ChartLayout::calculateTitleMinimum(const QRectF &minimum, ChartTitle *title) const
{
    QSizeF min = title->sizeHint(Qt::MinimumSize);
    return  minimum.adjusted(0, 0, min.width(), min.height());
}

QSizeF ChartLayout::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);
    if (which == Qt::MinimumSize) {
        QList<ChartAxis *> axes = m_presenter->axisItems();
        ChartTitle *title = m_presenter->titleElement();
        QLegend *legend = m_presenter->legend();
        QRectF minimumRect(0, 0, 0, 0);
        minimumRect = calculateBackgroundMinimum(minimumRect);
        minimumRect = calculateContentMinimum(minimumRect);
        minimumRect = calculateTitleMinimum(minimumRect, title);
        minimumRect = calculateLegendMinimum(minimumRect, legend);
        minimumRect = calculateAxisMinimum(minimumRect, axes);
        return  minimumRect.united(m_minChartRect).size().toSize();
    }
    return QSize(-1, -1);
}

void ChartLayout::setMargins(const QMargins &margins)
{
    if (m_margins != margins) {
        m_margins = margins;
        updateGeometry();
    }
}

QMargins ChartLayout::margins() const
{
    return m_margins;
}

QTCOMMERCIALCHART_END_NAMESPACE
