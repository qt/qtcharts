/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTELEMENT_H
#define CHARTELEMENT_H

#include "qchartglobal.h"
#include <QObject>
#include <QRect>
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimator;
class ChartPresenter;
class ChartAnimation;
class ChartThemeManager;
class AbstractDomain;

class ChartElement: public QGraphicsObject
{

public:
    explicit ChartElement(QGraphicsItem* item = 0);

    virtual ChartAnimation *animation() const { return 0; }
    virtual void setPresenter(ChartPresenter *presenter);
    ChartPresenter *presenter() const;
    virtual void setThemeManager(ChartThemeManager *manager);
    ChartThemeManager* themeManager() const;

private:
    ChartPresenter *m_presenter;
    ChartThemeManager *m_themeManager;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
