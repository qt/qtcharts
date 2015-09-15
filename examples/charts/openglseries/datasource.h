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

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

QT_CHARTS_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);

    void startUpdates(const QList<QXYSeries *> &seriesList, QLabel *fpsLabel);

public slots:
    void generateData(int seriesCount, int rowCount, int colCount);
    void update(QAbstractSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();

private:
    QVector<QVector<QVector<QPointF> > > m_data;
    int m_index;
    QList<QXYSeries *> m_seriesList;
    QLabel *m_fpsLabel;
    QElapsedTimer m_fpsTimer;
    QTimer m_dataUpdater;
};

#endif // DATASOURCE_H
