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

#ifndef QPIESLICE_P_H
#define QPIESLICE_P_H

#include <QtCore/QObject>
#include <QtCharts/QPieSlice>
#include <private/pieslicedata_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QPieSeries;

class Q_CHARTS_EXPORT QPieSlicePrivate : public QObject
{
    Q_OBJECT

public:
    QPieSlicePrivate(QPieSlice *parent);
    ~QPieSlicePrivate();

    static QPieSlicePrivate *fromSlice(QPieSlice *slice);

    void setPen(const QPen &pen, bool themed);
    void setBrush(const QBrush &brush, bool themed);
    void setLabelBrush(const QBrush &brush, bool themed);
    void setLabelFont(const QFont &font, bool themed);

    void setPercentage(qreal percentage);
    void setStartAngle(qreal angle);
    void setAngleSpan(qreal span);

Q_SIGNALS:
    void labelPositionChanged();
    void explodedChanged();
    void labelArmLengthFactorChanged();
    void explodeDistanceFactorChanged();

private:
    friend class QPieSeries;
    friend class QPieSeriesPrivate;
    friend class ChartThemeManager;
    friend class PieChartItem;

    QPieSlice * const q_ptr;
    Q_DECLARE_PUBLIC(QPieSlice)

    PieSliceData m_data;
    QPieSeries *m_series;
};

QT_END_NAMESPACE

#endif // QPIESLICE_P_H
