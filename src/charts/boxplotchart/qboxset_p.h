/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBOXSET_P_H
#define QBOXSET_P_H

#include <QtCharts/QBoxSet>
#include <QtCore/QMap>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QFont>

QT_CHARTS_BEGIN_NAMESPACE

class QBoxPlotSeriesPrivate;

class QBoxSetPrivate : public QObject
{
    Q_OBJECT

public:
    QBoxSetPrivate(const QString label, QBoxSet *parent);
    ~QBoxSetPrivate();

    bool append(qreal value);
    bool append(QList<qreal> values);

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

QT_CHARTS_END_NAMESPACE

#endif // QBOXSET_P_H
