/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "boxdatareader.h"

BoxDataReader::BoxDataReader(QIODevice *device) :
    QTextStream(device)
{
}

QBoxSet* BoxDataReader::readBox()
{
    QString line = readLine();
    if (line.startsWith("#"))
        return 0;

    QStringList strList = line.split(" ", QString::SkipEmptyParts);
    sortedList.clear();

    for (int i = 1; i < strList.count(); i++)
        sortedList.append(strList.at(i).toDouble());

    qSort(sortedList.begin(), sortedList.end());

    int count = sortedList.count();

    QBoxSet *box = new QBoxSet(strList.first());
    box->setValue(QBoxSet::LowerExtreme, sortedList.first());
    box->setValue(QBoxSet::UpperExtreme, sortedList.last());
    box->setValue(QBoxSet::Median, findMedian(0, count));
    box->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
    if (count % 2)
        box->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + 1, count));
    else // even amount of numbers
        box->setValue(QBoxSet::UpperQuartile, findMedian(count / 2, count));

    return box;
}

qreal BoxDataReader::findMedian(int begin, int end)
{
    int count = end - begin;
    if (count % 2 ) {
        return sortedList.at(int(count/2) + begin);
    } else {
        qreal right = sortedList.at(count / 2 + begin);
        qreal left = sortedList.at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
    }
}
