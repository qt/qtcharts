// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CANDLESTICKDATAREADER_H
#define CANDLESTICKDATAREADER_H

#include <QTextStream>

QT_FORWARD_DECLARE_CLASS(QCandlestickSet)

class CandlestickDataReader
{
public:
    explicit CandlestickDataReader(QIODevice *device);
    ~CandlestickDataReader();

    void readFile(QIODevice *device);
    QCandlestickSet *readCandlestickSet();
    bool atEnd() const;

private:
    QTextStream m_textStream;
};

#endif
