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

#ifndef CHARTBARCATEGORYAXISY_H
#define CHARTBARCATEGORYAXISY_H

#include <private/verticalaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QBarCategoryAxis;
class ChartPresenter;

class Q_CHARTS_EXPORT ChartBarCategoryAxisY : public VerticalAxis
{
    Q_OBJECT
public:
    ChartBarCategoryAxisY(QBarCategoryAxis *axis, QGraphicsItem* item = 0);
    ~ChartBarCategoryAxisY();

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;
protected:
    QList<qreal> calculateLayout() const override;
    void updateGeometry() override;
private:
    QStringList createCategoryLabels(const QList<qreal> &layout) const;
public Q_SLOTS:
    void handleCategoriesChanged();
private:
    QBarCategoryAxis *m_categoriesAxis;
};

QT_END_NAMESPACE

#endif /* CHARTBARCATEGORYAXISY_H */
