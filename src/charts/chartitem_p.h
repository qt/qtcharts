/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
#include <QtWidgets/QGraphicsItem>

QT_CHARTS_BEGIN_NAMESPACE

class ChartItem : public ChartElement
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

QT_CHARTS_END_NAMESPACE

#endif /* CHARTITEM_H */
