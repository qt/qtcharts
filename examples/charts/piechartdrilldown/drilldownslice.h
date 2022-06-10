// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#ifndef DRILLDOWNSLICE_H
#define DRILLDOWNSLICE_H

#include <QtCharts/QPieSlice>

QT_BEGIN_NAMESPACE
class QAbstractSeries;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class DrilldownSlice : public QPieSlice
{
    Q_OBJECT

public:
    DrilldownSlice(qreal value, QString prefix, QAbstractSeries *drilldownSeries);
    virtual ~DrilldownSlice();
    QAbstractSeries *drilldownSeries() const;

public Q_SLOTS:
    void updateLabel();
    void showHighlight(bool show);

private:
    QAbstractSeries *m_drilldownSeries;
    QString m_prefix;
};

#endif // DRILLDOWNSLICE_H
