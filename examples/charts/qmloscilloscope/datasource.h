// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QQuickView *appViewer, QObject *parent = 0);

Q_SIGNALS:

public slots:
    void generateData(int type, int rowCount, int colCount);
    void update(QAbstractSeries *series);

private:
    QQuickView *m_appViewer;
    QList<QList<QPointF>> m_data;
    int m_index;
};

#endif // DATASOURCE_H
