// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBOXPLOTSERIES_H
#define QBOXPLOTSERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QBoxSet>
#include <QtCharts/QAbstractSeries>

QT_BEGIN_NAMESPACE

class QBoxPlotSeriesPrivate;

class Q_CHARTS_EXPORT QBoxPlotSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(bool boxOutlineVisible READ boxOutlineVisible WRITE setBoxOutlineVisible NOTIFY boxOutlineVisibilityChanged)
    Q_PROPERTY(qreal boxWidth READ boxWidth WRITE setBoxWidth NOTIFY boxWidthChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged REVISION(2, 0))
public:
    explicit QBoxPlotSeries(QObject *parent = nullptr);
    ~QBoxPlotSeries();

    bool append(QBoxSet *box);
    bool remove(QBoxSet *box);
    bool take(QBoxSet *box);
    bool append(const QList<QBoxSet *> &boxes);
    bool insert(int index, QBoxSet *box);
    int count() const;
    QList<QBoxSet *> boxSets() const;
    void clear();

    QAbstractSeries::SeriesType type() const override;

    void setBoxOutlineVisible(bool visible);
    bool boxOutlineVisible();
    void setBoxWidth(qreal width);
    qreal boxWidth();
    void setBrush(const QBrush &brush);
    QBrush brush() const;
    void setPen(const QPen &pen);
    QPen pen() const;

Q_SIGNALS:
    void clicked(QBoxSet *boxset);
    void hovered(bool status, QBoxSet *boxset);
    void pressed(QBoxSet *boxset);
    void released(QBoxSet *boxset);
    void doubleClicked(QBoxSet *boxset);
    void countChanged();
    void penChanged();
    void brushChanged();
    void boxOutlineVisibilityChanged();
    void boxWidthChanged();

    void boxsetsAdded(const QList<QBoxSet *> &sets);
    void boxsetsRemoved(const QList<QBoxSet *> &sets);

private:
    Q_DECLARE_PRIVATE(QBoxPlotSeries)
    Q_DISABLE_COPY(QBoxPlotSeries)
    friend class BoxPlotChartItem;
    friend class QBoxPlotLegendMarkerPrivate;
};

QT_END_NAMESPACE

#endif // QBOXPLOTSERIES_H
