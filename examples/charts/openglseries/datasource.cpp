/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "datasource.h"
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE

DataSource::DataSource(QObject *parent) :
    QObject(parent),
    m_index(-1)
{
    generateData(0, 0, 0);
}

void DataSource::update(QAbstractSeries *series, int seriesIndex)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        const QVector<QVector<QPointF> > &seriesData = m_data.at(seriesIndex);
        if (seriesIndex == 0)
            m_index++;
        if (m_index > seriesData.count() - 1)
            m_index = 0;

        QVector<QPointF> points = seriesData.at(m_index);
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(points);
    }
}

void DataSource::handleSceneChanged()
{
    m_dataUpdater.start();
}

void DataSource::updateAllSeries()
{
    static int frameCount = 0;
    static QString labelText = QStringLiteral("FPS: %1");

    for (int i = 0; i < m_seriesList.size(); i++)
        update(m_seriesList[i], i);

    frameCount++;
    int elapsed = m_fpsTimer.elapsed();
    if (elapsed >= 1000) {
        elapsed = m_fpsTimer.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
        m_fpsLabel->setText(labelText.arg(QString::number(fps, 'f', 1)));
        frameCount = 0;
    }
}

void DataSource::startUpdates(const QList<QXYSeries *> &seriesList, QLabel *fpsLabel)
{
    m_seriesList = seriesList;
    m_fpsLabel = fpsLabel;

    m_dataUpdater.setInterval(0);
    m_dataUpdater.setSingleShot(true);
    QObject::connect(&m_dataUpdater, &QTimer::timeout,
                     this, &DataSource::updateAllSeries);

    m_fpsTimer.start();
    updateAllSeries();
}

void DataSource::generateData(int seriesCount, int rowCount, int colCount)
{
    // Remove previous data
    foreach (QVector<QVector<QPointF> > seriesData, m_data) {
        foreach (QVector<QPointF> row, seriesData)
            row.clear();
    }

    m_data.clear();

    qreal xAdjustment = 20.0 / (colCount * rowCount);
    qreal yMultiplier = 3.0 / qreal(seriesCount);

    // Append the new data depending on the type
    for (int k(0); k < seriesCount; k++) {
        QVector<QVector<QPointF> > seriesData;
        qreal height = qreal(k) * (10.0 / qreal(seriesCount)) + 0.3;
        for (int i(0); i < rowCount; i++) {
            QVector<QPointF> points;
            points.reserve(colCount);
            for (int j(0); j < colCount; j++) {
                qreal x(0);
                qreal y(0);
                // data with sin + random component
                y = height + (yMultiplier * qSin(3.14159265358979 / 50 * j)
                              + (yMultiplier * (qreal) rand() / (qreal) RAND_MAX));
                // 0.000001 added to make values logaxis compatible
                x = 0.000001 + 20.0 * (qreal(j) / qreal(colCount)) + (xAdjustment * qreal(i));
                points.append(QPointF(x, y));
            }
            seriesData.append(points);
        }
        m_data.append(seriesData);
    }
}
