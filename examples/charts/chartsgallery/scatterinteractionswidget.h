// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef SCATTERINTERACTIONSWIDGET_H
#define SCATTERINTERACTIONSWIDGET_H

#include "contentwidget.h"

QT_FORWARD_DECLARE_CLASS(QScatterSeries)

class ScatterInteractionsWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit ScatterInteractionsWidget(QWidget *parent = nullptr);

private slots:
    void handleClickedPoint(const QPointF &point);

private:
    QScatterSeries *m_scatter = nullptr;
    QScatterSeries *m_scatter2 = nullptr;
};

#endif
