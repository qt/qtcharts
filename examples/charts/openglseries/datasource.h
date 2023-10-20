// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QElapsedTimer>
#include <QObject>
#include <QPointF>
#include <QTimer>

QT_FORWARD_DECLARE_CLASS(QAbstractSeries)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QXYSeries)

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);

    void startUpdates(const QList<QXYSeries *> &seriesList, QLabel *fpsLabel);

public slots:
    void generateData(int seriesCount, int rowCount, int colCount);
    void update(QAbstractSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();

private:
    QList<QList<QList<QPointF>>> m_data;
    int m_index = -1;
    QList<QXYSeries *> m_seriesList;
    QLabel *m_fpsLabel = nullptr;
    QElapsedTimer m_fpsTimer;
    QTimer m_dataUpdater;
};

#endif
