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
#include <QAreaSeries>
#include <QAbstractScrollArea>
#include <QGLWidget>
#include <QDebug>

QTCOMMERCIALCHART_USE_NAMESPACE

DataSource::DataSource(QAbstractScrollArea *appViewer, QObject *parent) :
    m_appViewer(appViewer),
    QObject(parent),
    m_index(-1)
{
    // generate
    generateData(0, 5, 1024);
}

void DataSource::update(QAbstractSeries *series)
{
    QXYSeries *xySeries = qobject_cast<QXYSeries *>(series);
    Q_ASSERT(xySeries);

    m_index++;
    if (m_index > m_data.count() - 1)
        m_index = 0;

    QList<QPointF> points = m_data.at(m_index);
    // Use replace instead of clear + append, it's optimized for performance
    xySeries->replace(points);
}

void DataSource::generateData(int type, int rowCount, int colCount)
{
    qDebug() << "DataSource::generateData:" << type << rowCount << colCount;

    // Remove previous data
    foreach (QList<QPointF> row, m_data)
        row.clear();
    m_data.clear();

    // Append the new data depending on the type
    for (int i(0); i < rowCount; i++) {
        QList<QPointF> points;
        for (int j(0); j < colCount; j++) {
            qreal x(0);
            qreal y(0);
            switch (type) {
            case 0:
                // data with sin + random component
                y = sin(3.14159265358979 / 50 * j) + 0.5 + (qreal) rand() / (qreal) RAND_MAX;
                x = j;
                break;
            case 1:
                // linear data
                x = j;
                y = (qreal) i / 10;
                break;
            default:
                // unknown, do nothing
                break;
            }
            points.append(QPointF(x, y));
        }
        m_data.append(points);
    }
}

void DataSource::setOpenGL(bool enabled)
{
    if (enabled)
        m_appViewer->setViewport(new QGLWidget());
    else
        m_appViewer->setViewport(0);
}
