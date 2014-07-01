/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QTimer>

QT_CHARTS_USE_NAMESPACE

//![1]
class ChartView: public QChartView
{
    Q_OBJECT
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    virtual ~ChartView();

public slots:
    void handleTimeout();

private:
    QTimer m_timer;
    QList<QAbstractSeries *> m_series;
    QStringList m_titles;
    int m_index;
    QChart *m_chart;
};
//![1]

#endif /* CHARTVIEW_H */
