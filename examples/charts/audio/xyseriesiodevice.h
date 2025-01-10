// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QIODevice>
#include <QList>
#include <QPointF>

QT_FORWARD_DECLARE_CLASS(QXYSeries)

class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit XYSeriesIODevice(QXYSeries *series, QObject *parent = nullptr);

    static const int sampleCount = 2000;

protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;

private:
    QXYSeries *m_series = nullptr;
    QList<QPointF> m_buffer;
};

#endif // XYSERIESIODEVICE_H
