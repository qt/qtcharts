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

#ifndef CHARTLAYOUT_H
#define CHARTLAYOUT_H
#include <QGraphicsLayout>
#include <QMargins>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class ChartTitle;
class QLegend;
class ChartAxis;
class ChartBackground;

class ChartLayout : public QGraphicsLayout
{
public:

    ChartLayout(ChartPresenter* presenter);
    virtual ~ChartLayout();

    void setMargins(const QMargins& margins);
    QMargins margins() const;

    void setGeometry(const QRectF& rect);
    void adjustChartGeometry();

protected:
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
    int count() const { return 0; }
    QGraphicsLayoutItem* itemAt(int) const { return 0; };
    void removeAt(int){};

private:
    QRectF calculateBackgroundGeometry(const QRectF& geometry,ChartBackground* background) const;
    QRectF calculateContentGeometry(const QRectF& geometry) const;
    QRectF calculateTitleGeometry(const QRectF& geometry, ChartTitle* title) const;
    QRectF calculateChartGeometry(const QRectF& geometry,const QList<ChartAxis*>& axes) const;
    QRectF calculateLegendGeometry(const QRectF& geometry, QLegend* legend) const;
    QRectF calculateBackgroundMinimum(const QRectF& minimum) const;
    QRectF calculateContentMinimum(const QRectF& minimum) const;
    QRectF calculateTitleMinimum(const QRectF& minimum,ChartTitle* title) const;
    QRectF calculateAxisMinimum(const QRectF& minimum,const QList<ChartAxis*>& axes) const;
    QRectF calculateLegendMinimum(const QRectF& minimum,QLegend* legend) const;

private:
    ChartPresenter* m_presenter;
    QMargins m_margins;
    QRectF m_minChartRect;
    QRectF m_minAxisRect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
