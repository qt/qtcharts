/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QPointF>
#include <QtCore/QTime>
#include <stdlib.h>

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;


class Model
{
private:
    Model() {}

public:
    static DataTable generateRandomData(int listCount, int valueMax, int valueCount)
    {
        DataTable dataTable;

        // set seed for random stuff
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

        // generate random data
        for (int i(0); i < listCount; i++) {
            DataList dataList;
            qreal yValue(0.1);
            for (int j(0); j < valueCount; j++) {
                yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
                QPointF value(
                    (j + (qreal) qrand() / (qreal) RAND_MAX)
                    * ((qreal) valueMax / (qreal) valueCount), yValue);
                QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
                dataList << Data(value, label);
            }
            dataTable << dataList;
        }
        return dataTable;
    }
};

#endif
