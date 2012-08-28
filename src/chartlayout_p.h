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

#ifndef CHARTLAYOUT_H_
#define CHARTLAYOUT_H_
#include <QGraphicsLayout>
#include <QMargins>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;

class ChartLayout : public QGraphicsLayout
{
public:

    ChartLayout(ChartPresenter* presenter);
    virtual ~ChartLayout();

    void setMinimumMargins(const QMargins& margins);
    QMargins minimumMargins() const;

    void setGeometry(const QRectF& rect);

protected:
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
    int count() const { return 0; }
    QGraphicsLayoutItem* itemAt(int) const { return 0; };
    void removeAt(int){};

private:
    ChartPresenter* m_presenter;
    int m_marginBig;
    int m_marginSmall;
    int m_marginTiny;
    QMargins m_chartMargins;
    QMargins m_legendMargins;
    bool m_intialized;


};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
