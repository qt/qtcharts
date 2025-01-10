// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DONUTBREAKDOWNMAINSLICE_H
#define DONUTBREAKDOWNMAINSLICE_H

#include <QPieSlice>

QT_FORWARD_DECLARE_CLASS(QPieSeries)

class DonutBreakdownMainSlice : public QPieSlice
{
    Q_OBJECT
public:
    DonutBreakdownMainSlice(QPieSeries *breakdownSeries, QObject *parent = nullptr);

    QPieSeries *breakdownSeries() const;

    void setName(const QString &name);
    QString name() const;

public slots:
    void updateLabel();

private:
    QPieSeries *m_breakdownSeries = nullptr;
    QString m_name;
};

#endif
