/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#include <QDebug>

BoxDataReader::BoxDataReader(QIODevice *fileHandle) :
    QTextStream(fileHandle)
{
}

QBoxSet* BoxDataReader::readBox()
{
    QString line = readLine();
    if (line.startsWith("#"))
        return 0;

    QStringList strList = line.split(" ", QString::SkipEmptyParts);
    QList<qreal> sortedList;
    foreach (QString str, strList) {
        sortedList.append(str.toDouble());
    }

    qSort(sortedList.begin(), sortedList.end());
qDebug() << "sortedList = " << sortedList;

    int count = sortedList.count();
    int median = (int)(count / 2);
    int lowerQ = (int)(median / 2);
    int upperQ = median + lowerQ + 1;

    QBoxSet *box = new QBoxSet();
    box->setLowerExtreme(sortedList.at(0));
    box->setLowerQuartile(sortedList.at(lowerQ));
    box->setMedian(sortedList.at(median));
    box->setUpperQuartile(sortedList.at(upperQ));
    box->setUpperExtreme(sortedList.last());

    return box;
}

