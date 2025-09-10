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

#ifndef CHARTCATEGORYAXISX_H
#define CHARTCATEGORYAXISX_H

#include <private/horizontalaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QCategoryAxis;

class Q_CHARTS_EXPORT ChartCategoryAxisX : public HorizontalAxis
{
    Q_OBJECT
public:
    ChartCategoryAxisX(QCategoryAxis *axis, QGraphicsItem* item = 0);
    ~ChartCategoryAxisX();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

public Q_SLOTS:
    void handleCategoriesChanged();

protected:
    QList<qreal> calculateLayout() const override;
    void updateGeometry() override;

private:
    QCategoryAxis *m_axis;
};

QT_END_NAMESPACE

#endif /* CHARTCATEGORYAXISX_H */
