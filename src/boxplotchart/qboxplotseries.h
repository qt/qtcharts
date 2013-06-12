/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QBOXPLOTSERIES_H
#define QBOXPLOTSERIES_H

#include <qchartglobal.h>
#include <qboxset.h>
#include <qabstractseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBoxPlotSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QBoxPlotSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(bool boxOutlineVisible READ boxOutlineVisible WRITE setBoxOutlineVisible NOTIFY boxOutlineVisibilityChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
public:
    explicit QBoxPlotSeries(QObject *parent = 0);
    ~QBoxPlotSeries();

    bool append(QBoxSet *box);
    bool remove(QBoxSet *box);
    bool take(QBoxSet *box);
    bool append(QList<QBoxSet *> boxes);
    bool insert(int index, QBoxSet *box);
    int count() const;
    QList<QBoxSet *> boxSets() const;
    void clear();

    QAbstractSeries::SeriesType type() const;

    void setBoxOutlineVisible(bool visible);
    bool boxOutlineVisible();
    void setBrush(const QBrush &brush);
    QBrush brush() const;
    void setPen(const QPen &pen);
    QPen pen() const;

Q_SIGNALS:
    void clicked(QBoxSet *boxset);
    void hovered(bool status, QBoxSet *boxset);
    void countChanged();
    void penChanged();
    void brushChanged();
    void boxOutlineVisibilityChanged();

    void boxsetsAdded(QList<QBoxSet *> sets);
    void boxsetsRemoved(QList<QBoxSet *> sets);

private:
    Q_DECLARE_PRIVATE(QBoxPlotSeries)
    Q_DISABLE_COPY(QBoxPlotSeries)
    friend class BoxPlotChartItem;
    friend class QBoxPlotLegendMarkerPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBOXPLOTSERIES_H
