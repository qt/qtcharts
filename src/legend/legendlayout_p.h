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

#ifndef LEGENDLAYOUT_H
#define LEGENDLAYOUT_H
#include <QGraphicsLayout>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLegend;

class LegendLayout : public QGraphicsLayout
{
public:

    LegendLayout(QLegend* legend);
    virtual ~LegendLayout();

    void setGeometry(const QRectF& rect);

    void setOffset(qreal x, qreal y);
    QPointF offset() const;

protected:
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
    int count() const { return 0; }
    QGraphicsLayoutItem* itemAt(int) const { return 0; };
    void removeAt(int){};

private:
    void setAttachedGeometry(const QRectF& rect);
    void setDettachedGeometry(const QRectF& rect);

private:
    QLegend* m_legend;
    qreal m_offsetX;
    qreal m_offsetY;
    qreal m_minOffsetX;
    qreal m_minOffsetY;
    qreal m_maxOffsetX;
    qreal m_maxOffsetY;
    qreal m_width;
    qreal m_height;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
