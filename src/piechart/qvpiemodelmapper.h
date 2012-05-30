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

#ifndef QVPIEMODELMAPPER_H
#define QVPIEMODELMAPPER_H

#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int valuesColumn READ valuesColumn WRITE setValuesColumn)
    Q_PROPERTY(int labelsColumn READ labelsColumn WRITE setLabelsColumn)

public:
    explicit QVPieModelMapper(QObject *parent = 0);

    int valuesColumn() const;
    void setValuesColumn(int valuesColumn);

    int labelsColumn() const;
    void setLabelsColumn(int labelsColumn);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVPIEMODELMAPPER_H
