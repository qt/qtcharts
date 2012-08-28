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
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartLayout::ChartLayout(ChartPresenter* presenter):
m_presenter(presenter),
m_marginBig(60),
m_marginSmall(20),
m_marginTiny(10),
m_chartMargins(m_marginBig,m_marginBig,m_marginBig,m_marginBig),
m_intialized(false)
{

}

ChartLayout::~ChartLayout()
{

}

void ChartLayout::setGeometry(const QRectF& rect)
{

    if (!rect.isValid()) return;

    QGraphicsLayout::setGeometry(rect);

    if(!m_intialized){
        m_presenter->setGeometry(rect);
        m_intialized=true;
    }

    // check title size

    QSize titleSize = QSize(0,0);

    if (m_presenter->titleItem()) {
        titleSize= m_presenter->titleItem()->boundingRect().size().toSize();
    }

    qreal axisHeight = 0;
    qreal axisWidth = 0;

    // check axis size

    foreach (ChartAxis* axis,m_presenter->axisItems()){
        if(axis->axisType() ==  ChartAxis::X_AXIS)
        axisHeight = qMax(axis->minimumHeight(),axisHeight);
        else
        axisWidth = qMax(axis->minimumWidth(),axisWidth);
    }

    QLegend* legend = m_presenter->legend();
    Q_ASSERT(legend);

    qreal titlePadding = m_chartMargins.top()/2;

    QMargins chartMargins = m_chartMargins;

    //TODO multiple axis handling;
    chartMargins.setLeft(qMax(m_chartMargins.left(),int(axisWidth + 2*m_marginTiny)));
    chartMargins.setBottom(qMax(m_chartMargins.bottom(),int(axisHeight + 2* m_marginTiny)));


    // recalculate legend position
    if ((legend->isAttachedToChart() && legend->isVisible())) {

        // Reserve some space for legend
        switch (legend->alignment()) {

        case Qt::AlignTop: {

        	QSizeF legendSize = legend->effectiveSizeHint(Qt::PreferredSize,QSizeF(rect.width(),-1));
            int topMargin = 2*m_marginTiny + titleSize.height() + legendSize.height() + m_marginTiny;
            chartMargins = QMargins(chartMargins.left(),topMargin,chartMargins.right(),chartMargins.bottom());
            m_legendMargins = QMargins(chartMargins.left(),topMargin - (legendSize.height() + m_marginTiny),chartMargins.right(),rect.height()-topMargin + m_marginTiny);
            titlePadding = m_marginTiny + m_marginTiny;
            break;
        }
        case Qt::AlignBottom: {
        	QSizeF legendSize = legend->effectiveSizeHint(Qt::PreferredSize,QSizeF(rect.width(),-1));
            int bottomMargin = m_marginTiny + legendSize.height() + m_marginTiny + axisHeight;
            chartMargins = QMargins(chartMargins.left(),chartMargins.top(),chartMargins.right(),bottomMargin);
            m_legendMargins = QMargins(chartMargins.left(),rect.height()-bottomMargin + m_marginTiny + axisHeight,chartMargins.right(),m_marginTiny + m_marginSmall);
            titlePadding = chartMargins.top()/2;
            break;
        }
        case Qt::AlignLeft: {
        	QSizeF legendSize = legend->effectiveSizeHint(Qt::PreferredSize,QSizeF(-1,rect.height()));
            int leftPadding = m_marginTiny + legendSize.width() + m_marginTiny + axisWidth;
            chartMargins = QMargins(leftPadding,chartMargins.top(),chartMargins.right(),chartMargins.bottom());
            m_legendMargins = QMargins(m_marginTiny + m_marginSmall,chartMargins.top(),rect.width()-leftPadding + m_marginTiny + axisWidth,chartMargins.bottom());
            titlePadding = chartMargins.top()/2;
            break;
        }
        case Qt::AlignRight: {
        	QSizeF legendSize = legend->effectiveSizeHint(Qt::PreferredSize,QSizeF(-1,rect.height()));
            int rightPadding = m_marginTiny + legendSize.width() + m_marginTiny;
            chartMargins = QMargins(chartMargins.left(),chartMargins.top(),rightPadding,chartMargins.bottom());
            m_legendMargins = QMargins(rect.width()- rightPadding+ m_marginTiny ,chartMargins.top(),m_marginTiny + m_marginSmall,chartMargins.bottom());
            titlePadding = chartMargins.top()/2;
            break;
        }
        default: {
            break;
        }
        }

        legend->setGeometry(rect.adjusted(m_legendMargins.left(),m_legendMargins.top(),-m_legendMargins.right(),-m_legendMargins.bottom()));
    }

    // recalculate title position
    if (m_presenter->titleItem()) {
        QPointF center = rect.center() - m_presenter->titleItem()->boundingRect().center();
        m_presenter->titleItem()->setPos(center.x(),titlePadding);
    }

    //recalculate background gradient
    if (m_presenter->backgroundItem()) {
        m_presenter->backgroundItem()->setRect(rect.adjusted(m_marginTiny,m_marginTiny, -m_marginTiny, -m_marginTiny));
    }

    QRectF chartRect = rect.adjusted(chartMargins.left(),chartMargins.top(),-chartMargins.right(),-chartMargins.bottom());

    if(m_presenter->geometry()!=chartRect && chartRect.isValid()){
        m_presenter->setGeometry(chartRect);
    }else if(chartRect.size().isEmpty()){
        m_presenter->setGeometry(QRect(rect.width()/2,rect.height()/2,1,1));
    }
}


QSizeF ChartLayout::sizeHint ( Qt::SizeHint which, const QSizeF & constraint) const
{
    Q_UNUSED(constraint);
    if(which == Qt::MinimumSize)
        return QSize(2*(m_chartMargins.top()+m_chartMargins.bottom()),2*(m_chartMargins.top() + m_chartMargins.bottom()));
    else
        return QSize(-1,-1);
}

void ChartLayout::setMinimumMargins(const QMargins& margins)
{

    if(m_chartMargins != margins){
        m_chartMargins = margins;
        updateGeometry();
    }
}

QMargins ChartLayout::minimumMargins() const
{
    return m_chartMargins;
}

QTCOMMERCIALCHART_END_NAMESPACE
