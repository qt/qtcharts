/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QSPLINESERIES_P_H
#define QSPLINESERIES_P_H

#include <private/qlineseries_p.h>

QT_CHARTS_BEGIN_NAMESPACE


class QSplineSeriesPrivate: public QLineSeriesPrivate
{
    Q_OBJECT
public:
    QSplineSeriesPrivate(QSplineSeries *q);

    void initializeTheme(int index, ChartTheme* theme, bool forced = false);
    void initializeGraphics(QGraphicsItem* parent);
    void initializeAnimations(QtCharts::QChart::AnimationOptions options);

private:
    Q_DECLARE_PUBLIC(QSplineSeries)
};

QT_CHARTS_END_NAMESPACE

#endif
