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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBARSET_P_H
#define QBARSET_P_H

#include "qbarset.h"
#include <QMap>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSetPrivate : public QObject
{
    Q_OBJECT

public:
    QBarSetPrivate(const QString label, QBarSet *parent);
    ~QBarSetPrivate();

    void append(QPointF value);
    void append(QList<QPointF> values);
    void append(QList<qreal> values);

    void insert(const int index, const qreal value);
    void insert(const int index, const QPointF value);
    bool remove(const int index, const int count);

    void replace(const int index, const qreal value);
    void replace(const int index, const QPointF value);

Q_SIGNALS:
    void restructuredBars();
    void updatedBars();

public:
    QBarSet * const q_ptr;
    QString m_label;
    QList<QPointF> m_values;
    QPen m_pen;
    QBrush m_brush;
    QBrush m_labelBrush;
    QFont m_labelFont;

    friend class QBarSet;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSETPRIVATE_P_H
