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

#ifndef QVBARMODELMAPPER_H
#define QVBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarSetColumn READ firstBarSetColumn WRITE setFirstBarSetColumn)
    Q_PROPERTY(int lastBarSetColumn READ lastBarSetColumn WRITE setLastBarSetColumn)

public:
    explicit QVBarModelMapper(QObject *parent = 0);

    int firstBarSetColumn() const;
    void setFirstBarSetColumn(int firstBarSetColumn);

    int lastBarSetColumn() const;
    void setLastBarSetColumn(int lastBarSetColumn);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVBARMODELMAPPER_H
