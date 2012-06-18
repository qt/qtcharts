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

#ifndef QHXYMODELMAPPER_H
#define QHXYMODELMAPPER_H

#include <QXYModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHXYModelMapper : public QXYModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int xRow READ xRow WRITE setXRow NOTIFY xRowChanged)
    Q_PROPERTY(int yRow READ yRow WRITE setYRow NOTIFY yRowChanged)

public:
    explicit QHXYModelMapper(QObject *parent = 0);
    
    int xRow() const;
    void setXRow(int xRow);

    int yRow() const;
    void setYRow(int yRow);

Q_SIGNALS:
    void xRowChanged();
    void yRowChanged();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHXYMODELMAPPER_H
