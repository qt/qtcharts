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

#ifndef QHBARMODELMAPPER_H
#define QHBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarSetRow READ firstBarSetRow WRITE setFirstBarSetRow NOTIFY firstBarSetRowChanged)
    Q_PROPERTY(int lastBarSetRow READ lastBarSetRow WRITE setLastBarSetRow NOTIFY lastBarSetRowChanged)
    Q_PROPERTY(int firstColumn READ firstColumn WRITE setFirstColumn NOTIFY firstColumnChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)

public:
    explicit QHBarModelMapper(QObject *parent = 0);

    int firstBarSetRow() const;
    void setFirstBarSetRow(int firstBarSetRow);

    int lastBarSetRow() const;
    void setLastBarSetRow(int lastBarSetRow);

    int firstColumn() const;
    void setFirstColumn(int firstColumn);

    int columnCount() const;
    void setColumnCount(int columnCount);

Q_SIGNALS:
    void firstBarSetRowChanged();
    void lastBarSetRowChanged();
    void firstColumnChanged();
    void columnCountChanged();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHBARMODELMAPPER_H
