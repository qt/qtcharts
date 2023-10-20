// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QList>
#include <QObject>
#include <QPointF>

QT_FORWARD_DECLARE_CLASS(QAbstractSeries)
QT_FORWARD_DECLARE_CLASS(QQuickView)

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QQuickView *appViewer, QObject *parent = nullptr);

public slots:
    void generateData(int type, int rowCount, int colCount);
    void update(QAbstractSeries *series);

private:
    QQuickView *m_appViewer = nullptr;
    QList<QList<QPointF>> m_data;
    int m_index = -1;
};

#endif
