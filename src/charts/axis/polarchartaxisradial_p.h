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

#ifndef POLARCHARTAXISRADIAL_P_H
#define POLARCHARTAXISRADIAL_P_H

#include <QtCharts/qvalueaxis.h>
#include <private/polarchartaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT PolarChartAxisRadial : public PolarChartAxis
{
    Q_OBJECT

public:
    PolarChartAxisRadial(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~PolarChartAxisRadial();

    Qt::Orientation orientation() const;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

    void updateGeometry() override;
    void createItems(int count) override;
    void updateMinorTickItems() override;

    qreal preferredAxisRadius(const QSizeF &maxSize) override;

public Q_SLOTS:
    void handleArrowPenChanged(const QPen &pen) override;
    void handleGridPenChanged(const QPen &pen) override;
    void handleMinorArrowPenChanged(const QPen &pen) override;
    void handleMinorGridPenChanged(const QPen &pen) override;
    void handleGridLineColorChanged(const QColor &color) override;
    void handleMinorGridLineColorChanged(const QColor &color) override;

private:
    void updateMinorTickGeometry();
};

QT_END_NAMESPACE

#endif // POLARCHARTAXISRADIAL_P_H
