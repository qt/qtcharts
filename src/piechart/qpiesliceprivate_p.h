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

#ifndef QPIESLICEPRIVATE_P_H
#define QPIESLICEPRIVATE_P_H

#include "qpieslice.h"
#include "pieslicedata_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSlicePrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(QPieSlice)

public:
    QPieSlicePrivate(QPieSlice *parent)
        :QObject(parent),
        q_ptr(parent)
    {
        connect(this, SIGNAL(changed()), q_ptr, SIGNAL(changed()));
    }

    ~QPieSlicePrivate() {}

Q_SIGNALS:
    void changed();

public:
    friend class QPieSeriesPrivate;
    friend class ChartTheme;
    QPieSlice * const q_ptr;
    PieSliceData m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICEPRIVATE_P_H
