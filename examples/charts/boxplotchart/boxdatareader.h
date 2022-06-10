// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef BOXDATAREADER_H
#define BOXDATAREADER_H

#include <QtCore/QTextStream>
#include <QtCharts/QBoxSet>

QT_USE_NAMESPACE

class BoxDataReader : public QTextStream
{
public:
    explicit BoxDataReader(QIODevice *device);
    QBoxSet *readBox();
    void readFile(QIODevice *device);

protected:
    qreal findMedian(int begin, int end);

private:
    QList<qreal> sortedList;
};

#endif // BOXDATAREADER_H
