// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartelement_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractdomain_p.h>
#include <private/chartdataset_p.h>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE
