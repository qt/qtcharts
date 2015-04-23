/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef BOXDATAREADER_H
#define BOXDATAREADER_H

#include <QtCore/QTextStream>
#include <QtCharts/QBoxSet>

QT_CHARTS_USE_NAMESPACE

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
