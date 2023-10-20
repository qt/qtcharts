// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "candlestickdatareader.h"

#include <QCandlestickSet>

CandlestickDataReader::CandlestickDataReader(QIODevice *device)
    : m_textStream(device)
{
}

CandlestickDataReader::~CandlestickDataReader()
{
}

void CandlestickDataReader::readFile(QIODevice *device)
{
    m_textStream.setDevice(device);
}

QCandlestickSet *CandlestickDataReader::readCandlestickSet()
{
    //! [1]
    QString line = m_textStream.readLine();
    if (line.startsWith("#") || line.isEmpty())
        return nullptr;
    //! [1]

    //! [2]
    QStringList strList = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (strList.count() != 5)
        return nullptr;
    //! [2]

    //! [3]
    const qreal timestamp = strList.at(0).toDouble();
    const qreal open = strList.at(1).toDouble();
    const qreal high = strList.at(2).toDouble();
    const qreal low = strList.at(3).toDouble();
    const qreal close = strList.at(4).toDouble();
    //! [3]

    //! [4]
    auto candlestickSet = new QCandlestickSet(timestamp);
    candlestickSet->setOpen(open);
    candlestickSet->setHigh(high);
    candlestickSet->setLow(low);
    candlestickSet->setClose(close);
    //! [4]

    return candlestickSet;
}

bool CandlestickDataReader::atEnd() const
{
    return m_textStream.atEnd();
}
