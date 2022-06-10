// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "boxdatareader.h"

#include <algorithm>

BoxDataReader::BoxDataReader(QIODevice *device) :
    QTextStream(device)
{
}

void BoxDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QBoxSet *BoxDataReader::readBox()
{
    //! [1]
    QString line = readLine();
    if (line.startsWith("#"))
        return 0;
    //! [1]

    //! [2]
    QStringList strList = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    //! [2]

    //! [3]
    sortedList.clear();
    for (int i = 1; i < strList.count(); i++)
        sortedList.append(strList.at(i).toDouble());

    std::sort(sortedList.begin(), sortedList.end());
    //! [3]

    int count = sortedList.count();

    //! [4]
    QBoxSet *box = new QBoxSet(strList.first());
    box->setValue(QBoxSet::LowerExtreme, sortedList.first());
    box->setValue(QBoxSet::UpperExtreme, sortedList.last());
    box->setValue(QBoxSet::Median, findMedian(0, count));
    box->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
    box->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + (count % 2), count));
    //! [4]

    return box;
}

qreal BoxDataReader::findMedian(int begin, int end)
{
    //! [5]
    int count = end - begin;
    if (count % 2) {
        return sortedList.at(count / 2 + begin);
    } else {
        qreal right = sortedList.at(count / 2 + begin);
        qreal left = sortedList.at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
    }
    //! [5]
}
