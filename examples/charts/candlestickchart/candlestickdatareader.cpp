// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "candlestickdatareader.h"

CandlestickDataReader::CandlestickDataReader(QIODevice *device)
    : QTextStream(device)
{
}

CandlestickDataReader::~CandlestickDataReader()
{
}

void CandlestickDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QCandlestickSet *CandlestickDataReader::readCandlestickSet()
{
    //! [1]
    QString line = readLine();
    if (line.startsWith("#") || line.isEmpty())
        return 0;
    //! [1]

    //! [2]
    QStringList strList = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (strList.count() != 5)
        return 0;
    //! [2]

    //! [3]
    const qreal timestamp = strList.at(0).toDouble();
    const qreal open = strList.at(1).toDouble();
    const qreal high = strList.at(2).toDouble();
    const qreal low = strList.at(3).toDouble();
    const qreal close = strList.at(4).toDouble();
    //! [3]

    //! [4]
    QCandlestickSet *candlestickSet = new QCandlestickSet(timestamp);
    candlestickSet->setOpen(open);
    candlestickSet->setHigh(high);
    candlestickSet->setLow(low);
    candlestickSet->setClose(close);
    //! [4]

    return candlestickSet;
}
