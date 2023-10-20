// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef BOXPLOTDATAREADER_H
#define BOXPLOTDATAREADER_H

#include <QList>
#include <QTextStream>

QT_FORWARD_DECLARE_CLASS(QBoxSet)

class BoxPlotDataReader
{
public:
    explicit BoxPlotDataReader(QIODevice *device);

    QBoxSet *readBox();
    void readFile(QIODevice *device);
    bool atEnd() const;

protected:
    qreal findMedian(int begin, int end);

private:
    QList<qreal> m_sortedList;
    QTextStream m_textStream;
};

#endif
