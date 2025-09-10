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

#ifndef CHARTBACKGROUND_H
#define CHARTBACKGROUND_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsRectItem>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QGraphicsDropShadowEffect;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ChartBackground: public QGraphicsRectItem
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


