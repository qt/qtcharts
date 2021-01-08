/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
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
