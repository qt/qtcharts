// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

QT_USE_NAMESPACE

const int maxSeriesCount = 10;

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);

    void startUpdates(QList<QXYSeries *> &seriesList, QLabel *fpsLabel, int interval);

public slots:
    void generateData(int seriesIndex, int rowCount, int colCount);
    void update(QXYSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();
    void setInterval(int interval);

private:
    QList<QList<QList<QPointF>>> m_data;
    int m_index;
    QList<QXYSeries *> *m_seriesList;
    QLabel *m_fpsLabel;
    QElapsedTimer m_fpsTimer;
    QTimer m_dataUpdater;
};

#endif // DATASOURCE_H
