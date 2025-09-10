// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTELEMENT_H
#define CHARTELEMENT_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>
#include <QtCore/QRect>
#include <QGraphicsObject>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class ChartAnimator;
class ChartPresenter;
class ChartAnimation;
class ChartThemeManager;
class AbstractDomain;
class ChartDataSet;

class Q_CHARTS_EXPORT ChartElement: public QGraphicsObject
{

public:
    explicit ChartElement(QGraphicsItem* item = 0);

    virtual ChartAnimation *animation() const { return 0; }
    virtual void setPresenter(ChartPresenter *presenter);
    ChartPresenter *presenter() const;
    virtual void setThemeManager(ChartThemeManager *manager);
    ChartThemeManager* themeManager() const;
    virtual void setDataSet(ChartDataSet *dataSet);
    ChartDataSet *dataSet() const;

private:
    ChartPresenter *m_presenter;
    ChartThemeManager *m_themeManager;
    ChartDataSet *m_dataSet;
};

QT_END_NAMESPACE

#endif
