// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBOXSET_P_H
#define QBOXSET_P_H

#include <QtCharts/QBoxSet>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QMap>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QFont>

QT_BEGIN_NAMESPACE

class QBoxPlotSeriesPrivate;

class Q_CHARTS_EXPORT QBoxSetPrivate : public QObject
{
    Q_OBJECT

public:
    QBoxSetPrivate(const QString label, QBoxSet *parent);
    ~QBoxSetPrivate();

    bool append(qreal value);
    bool append(const QList<qreal> &values);

    int remove(const int index, const int count);
    void clear();

    void setValue(const int index, const qreal value);

    qreal value(const int index);

Q_SIGNALS:
    void restructuredBox();
    void updatedBox();
    void updatedLayout();

private:
    const QBoxSet *q_ptr;
    QString m_label;
    const int m_valuesCount;
    qreal *m_values;
    int m_appendCount;
    QPen m_pen;
    QBrush m_brush;
    QBrush m_labelBrush;
    QFont m_labelFont;
    QBoxPlotSeriesPrivate *m_series;

    friend class QBoxSet;
    friend class QBoxPlotSeriesPrivate;
};

QT_END_NAMESPACE

#endif // QBOXSET_P_H
