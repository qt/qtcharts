// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QCANDLESTICKSERIES_H
#define QCANDLESTICKSERIES_H

#include <QtCharts/QAbstractSeries>

QT_BEGIN_NAMESPACE

class QCandlestickSeriesPrivate;
class QCandlestickSet;

class Q_CHARTS_EXPORT QCandlestickSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(qreal maximumColumnWidth READ maximumColumnWidth WRITE setMaximumColumnWidth NOTIFY maximumColumnWidthChanged)
    Q_PROPERTY(qreal minimumColumnWidth READ minimumColumnWidth WRITE setMinimumColumnWidth NOTIFY minimumColumnWidthChanged)
    Q_PROPERTY(qreal bodyWidth READ bodyWidth WRITE setBodyWidth NOTIFY bodyWidthChanged)
    Q_PROPERTY(bool bodyOutlineVisible READ bodyOutlineVisible WRITE setBodyOutlineVisible NOTIFY bodyOutlineVisibilityChanged)
    Q_PROPERTY(qreal capsWidth READ capsWidth WRITE setCapsWidth NOTIFY capsWidthChanged)
    Q_PROPERTY(bool capsVisible READ capsVisible WRITE setCapsVisible NOTIFY capsVisibilityChanged)
    Q_PROPERTY(QColor increasingColor READ increasingColor WRITE setIncreasingColor NOTIFY increasingColorChanged)
    Q_PROPERTY(QColor decreasingColor READ decreasingColor WRITE setDecreasingColor NOTIFY decreasingColorChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)

public:
    explicit QCandlestickSeries(QObject *parent = nullptr);
    ~QCandlestickSeries();

    bool append(QCandlestickSet *set);
    bool remove(QCandlestickSet *set);
    bool append(const QList<QCandlestickSet *> &sets);
    bool remove(const QList<QCandlestickSet *> &sets);
    bool insert(int index, QCandlestickSet *set);
    bool take(QCandlestickSet *set);
    void clear();

    QList<QCandlestickSet *> sets() const;
    int count() const;

    QAbstractSeries::SeriesType type() const override;

    void setMaximumColumnWidth(qreal maximumColumnWidth);
    qreal maximumColumnWidth() const;

    void setMinimumColumnWidth(qreal minimumColumnWidth);
    qreal minimumColumnWidth() const;

    void setBodyWidth(qreal bodyWidth);
    qreal bodyWidth() const;

    void setBodyOutlineVisible(bool bodyOutlineVisible);
    bool bodyOutlineVisible() const;

    void setCapsWidth(qreal capsWidth);
    qreal capsWidth() const;

    void setCapsVisible(bool capsVisible);
    bool capsVisible() const;

    void setIncreasingColor(const QColor &increasingColor);
    QColor increasingColor() const;

    void setDecreasingColor(const QColor &decreasingColor);
    QColor decreasingColor() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setPen(const QPen &pen);
    QPen pen() const;

Q_SIGNALS:
    void clicked(QCandlestickSet *set);
    void hovered(bool status, QCandlestickSet *set);
    void pressed(QCandlestickSet *set);
    void released(QCandlestickSet *set);
    void doubleClicked(QCandlestickSet *set);
    void candlestickSetsAdded(const QList<QCandlestickSet *> &sets);
    void candlestickSetsRemoved(const QList<QCandlestickSet *> &sets);
    void countChanged();
    void maximumColumnWidthChanged();
    void minimumColumnWidthChanged();
    void bodyWidthChanged();
    void bodyOutlineVisibilityChanged();
    void capsWidthChanged();
    void capsVisibilityChanged();
    void increasingColorChanged();
    void decreasingColorChanged();
    void brushChanged();
    void penChanged();

private:
    Q_DISABLE_COPY(QCandlestickSeries)
    Q_DECLARE_PRIVATE(QCandlestickSeries)
    friend class CandlestickChartItem;
    friend class QCandlestickLegendMarkerPrivate;
};

QT_END_NAMESPACE

#endif // QCANDLESTICKSERIES_H
