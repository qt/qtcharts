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

#ifndef BOXDATAREADER_H
#define BOXDATAREADER_H

#include <QTextStream>
#include <QBoxSet>

QTCOMMERCIALCHART_USE_NAMESPACE

class BoxDataReader : public QTextStream
{
public:
    explicit BoxDataReader(QIODevice *fileHandle);
    QBoxSet* readBox();

protected:
    qreal findMedian(int begin, int end);

private:
};

#endif // BOXDATAREADER_H
