/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/chartelement_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractdomain_p.h>
#include <private/chartdataset_p.h>

QT_CHARTS_BEGIN_NAMESPACE

ChartElement::ChartElement(QGraphicsItem* item):
      QGraphicsObject(item),
      m_presenter(0),
      m_themeManager(0),
      m_dataSet(0)
{

}

void ChartElement::setPresenter(ChartPresenter *presenter)
{
    m_presenter = presenter;
}

ChartPresenter *ChartElement::presenter() const
{
    return m_presenter;
}

void ChartElement::setThemeManager(ChartThemeManager *manager)
{
    m_themeManager = manager;
}

ChartThemeManager* ChartElement::themeManager() const
{
    return m_themeManager;
}

void ChartElement::setDataSet(ChartDataSet *dataSet)
{
    m_dataSet = dataSet;
}

ChartDataSet *ChartElement::dataSet() const
{
    return m_dataSet;
}

QT_CHARTS_END_NAMESPACE
