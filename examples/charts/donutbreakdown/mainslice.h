// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINSLICE_H
#define MAINSLICE_H

#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>

QT_USE_NAMESPACE

class MainSlice : public QPieSlice
{
    Q_OBJECT
public:
    MainSlice(QPieSeries *breakdownSeries, QObject *parent = 0);

    QPieSeries *breakdownSeries() const;

    void setName(QString name);
    QString name() const;

public Q_SLOTS:
    void updateLabel();

private:
    QPieSeries *m_breakdownSeries;
    QString m_name;
};

#endif // MAINSLICE_H
