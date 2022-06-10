// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CANDLESTICKDATAREADER_H
#define CANDLESTICKDATAREADER_H

#include <QtCharts/QCandlestickSet>
#include <QtCore/QTextStream>

QT_USE_NAMESPACE

class CandlestickDataReader : public QTextStream
{
public:
    explicit CandlestickDataReader(QIODevice *device);
    ~CandlestickDataReader();

    void readFile(QIODevice *device);
    QCandlestickSet *readCandlestickSet();
};

#endif // CANDLESTICKDATAREADER_H
