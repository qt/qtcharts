/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "datasource.h"
#include <QXYSeries>
#include <QDebug>

QTCOMMERCIALCHART_USE_NAMESPACE

DataSource::DataSource(QObject *parent) :
    QObject(parent),
    m_index(0)
{
    const int rowCount = 5;
    const int colCount = 1024;

    for (int i(0); i < rowCount; i++) {
        QList<QPointF> points;
        for (int j(0); j < colCount; j++) {
            qreal x = j;
            qreal y = sin(3.14159265358979 / 50 * x) + 0.5 + (qreal) rand() / (qreal) RAND_MAX;
            points.append(QPointF(x, y));
        }
        m_data.append(points);
    }
}

void DataSource::update(QAbstractSeries *series)
{
    QXYSeries *xySeries = qobject_cast<QXYSeries *>(series);
    Q_ASSERT(xySeries);

    QList<QPointF> points = m_data.at(m_index);
//xySeries->clear();
//xySeries->append(points);
    xySeries->replace(points);
    m_index = (m_index + 1) % m_data.count();
}
