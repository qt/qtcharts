/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTBACKGROUND_H
#define CHARTBACKGROUND_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsRectItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QGraphicsDropShadowEffect;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT ChartBackground: public QGraphicsRectItem
{
public:
    ChartBackground(QGraphicsItem *parent = 0);
    ~ChartBackground();

    void setDiameter(qreal diameter);
    qreal diameter() const;
    void setDropShadowEnabled(bool enabled);
    bool isDropShadowEnabled() { return m_dropShadow != 0; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_diameter;
    QGraphicsDropShadowEffect *m_dropShadow;
};

QT_END_NAMESPACE

#endif /* CHARTBACKGROUND_H */


