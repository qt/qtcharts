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

#ifndef CHARTITEM_H
#define CHARTITEM_H

#include <private/chartelement_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtWidgets/QGraphicsItem>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartItem : public ChartElement
{
    Q_OBJECT
    enum ChartItemTypes { AXIS_ITEM = UserType + 1, XYLINE_ITEM };
public:
    ChartItem(QAbstractSeriesPrivate *series,QGraphicsItem* item);
    AbstractDomain*  domain() const;
    virtual void cleanup();

public Q_SLOTS:
    virtual void handleDomainUpdated();

    QAbstractSeriesPrivate* seriesPrivate() const {return m_series;}

protected:
    bool m_validData;
private:
    QAbstractSeriesPrivate* m_series;
};

QT_END_NAMESPACE

#endif /* CHARTITEM_H */
