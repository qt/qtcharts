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

#ifndef QXYSERIES_P_H
#define QXYSERIES_P_H

#include "qabstractseries_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYSeries;
class QXYModelMapper;

class QXYSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QXYSeriesPrivate(QXYSeries* q);

    void scaleDomain(Domain& domain);
    QList<LegendMarker*> createLegendMarker(QLegend* legend);

protected Q_SLOTS:
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    virtual void modelRowsAdded(QModelIndex parent, int start, int end);
    virtual void modelRowsRemoved(QModelIndex parent, int start, int end);
    virtual void modelColumnsAdded(QModelIndex parent, int start, int end);
    virtual void modelColumnsRemoved(QModelIndex parent, int start, int end);
    virtual void mappingUpdated();

private:
    void setMapping();
    void insertData(int start, int end);
    void removeData(int start, int end);

Q_SIGNALS:
    void updated();
    void pointReplaced(int index);
    void pointRemoved(int index);
    void pointsRemoved(int start, int end);
    void pointAdded(int index);
    void pointsAdded(int start, int end);
    void reinitialized();

protected:
    QVector<QPointF> m_points;

    QPen m_pen;
    QBrush m_brush;
    QXYModelMapper* m_mapper;
    bool m_pointsVisible;

private:
    Q_DECLARE_PUBLIC(QXYSeries);
    friend class QScatterSeries;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
