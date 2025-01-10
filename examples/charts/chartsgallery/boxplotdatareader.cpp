// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "boxplotdatareader.h"

#include <QBoxSet>

#include <algorithm>

BoxPlotDataReader::BoxPlotDataReader(QIODevice *device)
    : m_textStream(device)
{
}

void BoxPlotDataReader::readFile(QIODevice *device)
{
    m_textStream.setDevice(device);
}

bool BoxPlotDataReader::atEnd() const
{
    return m_textStream.atEnd();
}

QBoxSet *BoxPlotDataReader::readBox()
{
    //! [1]
    QString line = m_textStream.readLine();
    if (line.startsWith("#"))
        return nullptr;
    //! [1]

    //! [2]
    QStringList strList = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    //! [2]

    //! [3]
    m_sortedList.clear();
    for (int i = 1; i < strList.count(); i++)
        m_sortedList.append(strList.at(i).toDouble());

    std::sort(m_sortedList.begin(), m_sortedList.end());
    //! [3]

    int count = m_sortedList.count();

    //! [4]
    auto box = new QBoxSet(strList.first());
    box->setValue(QBoxSet::LowerExtreme, m_sortedList.first());
    box->setValue(QBoxSet::UpperExtreme, m_sortedList.last());
    box->setValue(QBoxSet::Median, findMedian(0, count));
    box->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
    box->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + (count % 2), count));
    //! [4]

    return box;
}

qreal BoxPlotDataReader::findMedian(int begin, int end)
{
    //! [5]
    int count = end - begin;
    if (count % 2) {
        return m_sortedList.at(count / 2 + begin);
    } else {
        qreal right = m_sortedList.at(count / 2 + begin);
        qreal left = m_sortedList.at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
    }
    //! [5]
}
