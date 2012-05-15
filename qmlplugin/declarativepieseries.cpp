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

#include "declarativepieseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include <qdeclarativelist.h>
#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativePieSeries::DeclarativePieSeries(QObject *parent) :
    QPieSeries(parent)
{
}

QPieSlice *DeclarativePieSeries::slice(int index)
{
    QList<QPieSlice*> sliceList = slices();
    if (index < sliceList.count())
        return sliceList[index];

    return 0;
}


void DeclarativePieSeries::setPieModel(DeclarativePieModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    if (m) {
        QPieSeries::setModel(m);
        QPieModelMapper *mapper = new QPieModelMapper;
        mapper->setMapValues(0);
        mapper->setMapLabels(1);
        QPieSeries::setModelMapper(mapper);
    } else {
        qWarning("DeclarativePieSeries: Illegal model");
    }
}

DeclarativePieModel *DeclarativePieSeries::pieModel()
{
    return qobject_cast<DeclarativePieModel *>(model());
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
