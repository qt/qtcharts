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

#ifndef DECLARATIVEBARSERIES_H
#define DECLARATIVEBARSERIES_H

#include "qchartglobal.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QBarSeries;

class DeclarativeBarSeries : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QStringList barCategories READ barCategories WRITE setBarCategories)

public:
    explicit DeclarativeBarSeries(QDeclarativeItem *parent = 0);

public: // from QDeclarativeParserStatus
    void componentComplete();

public:
    void setBarCategories(QStringList categories);
    QStringList barCategories();

Q_SIGNALS:

public Q_SLOTS:

public:
    QChart *m_chart;
    QBarSeries *m_series;
    QStringList m_categories;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBARSERIES_H
