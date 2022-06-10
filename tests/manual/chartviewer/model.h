// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QPointF>
#include <QtCore/QRandomGenerator>
#include <QtCore/QTime>

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

        // generate random data
        for (int i(0); i < listCount; i++) {
            DataList dataList;
            qreal yValue(0.1);
            for (int j(0); j < valueCount; j++) {
                yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
                QPointF value(
                    (j + QRandomGenerator::global()->generateDouble())
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
