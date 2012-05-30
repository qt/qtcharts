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

#ifndef QHPIEMODELMAPPER_H
#define QHPIEMODELMAPPER_H

#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int valuesRow READ valuesRow WRITE setValuesRow)
    Q_PROPERTY(int labelsRow READ labelsRow WRITE setLabelsRow)

public:
    QHPieModelMapper(QObject *parent = 0);

    int valuesRow() const;
    void setValuesRow(int valuesRow);

    int labelsRow() const;
    void setLabelsRow(int labelsRow);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHPIEMODELMAPPER_H
