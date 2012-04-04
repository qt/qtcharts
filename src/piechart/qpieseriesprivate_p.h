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

#ifndef QPIESERIESPRIVATE_P_H
#define QPIESERIESPRIVATE_P_H

#include "qpieseries.h"

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieSeriesPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(QPieSeries)

public:
    QPieSeriesPrivate(QPieSeries *parent);
    ~QPieSeriesPrivate();

    void updateDerivativeData();

public Q_SLOTS:
    void sliceChanged();
    void sliceClicked(Qt::MouseButtons buttons);
    void sliceHoverEnter();
    void sliceHoverLeave();
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);

public:
    QPieSeries * const q_ptr;

    QList<QPieSlice*> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_total;

    // model map
    int m_mapValues;
    int m_mapLabels;
    Qt::Orientation m_mapOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESERIESPRIVATE_P_H
