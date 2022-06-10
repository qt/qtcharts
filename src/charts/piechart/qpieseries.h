// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QPIESERIES_H
#define QPIESERIES_H

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QPieSlice>

QT_BEGIN_NAMESPACE
class QPieSeriesPrivate;

class Q_CHARTS_EXPORT QPieSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(qreal horizontalPosition READ horizontalPosition WRITE setHorizontalPosition)
    Q_PROPERTY(qreal verticalPosition READ verticalPosition WRITE setVerticalPosition)
    Q_PROPERTY(qreal size READ pieSize WRITE setPieSize)
    Q_PROPERTY(qreal startAngle READ pieStartAngle WRITE setPieStartAngle)
    Q_PROPERTY(qreal endAngle READ pieEndAngle WRITE setPieEndAngle)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(qreal sum READ sum NOTIFY sumChanged)
    Q_PROPERTY(qreal holeSize READ holeSize WRITE setHoleSize)

public:
    explicit QPieSeries(QObject *parent = nullptr);
    virtual ~QPieSeries();

    QAbstractSeries::SeriesType type() const override;

    bool append(QPieSlice *slice);
    bool append(const QList<QPieSlice *> &slices);
    QPieSeries &operator << (QPieSlice *slice);
    QPieSlice *append(const QString &label, qreal value);

    bool insert(int index, QPieSlice *slice);

    bool remove(QPieSlice *slice);
    bool take(QPieSlice *slice);
    void clear();

    QList<QPieSlice *> slices() const;
    int count() const;

    bool isEmpty() const;

    qreal sum() const;

    void setHoleSize(qreal holeSize);
    qreal holeSize() const;

    void setHorizontalPosition(qreal relativePosition);
    qreal horizontalPosition() const;

    void setVerticalPosition(qreal relativePosition);
    qreal verticalPosition() const;

    void setPieSize(qreal relativeSize);
    qreal pieSize() const;

    void setPieStartAngle(qreal startAngle);
    qreal pieStartAngle() const;

    void setPieEndAngle(qreal endAngle);
    qreal pieEndAngle() const;

    void setLabelsVisible(bool visible = true);
    void setLabelsPosition(QPieSlice::LabelPosition position);

Q_SIGNALS:
    void added(const QList<QPieSlice *> &slices);
    void removed(const QList<QPieSlice *> &slices);
    void clicked(QPieSlice *slice);
    void hovered(QPieSlice *slice, bool state);
    void pressed(QPieSlice *slice);
    void released(QPieSlice *slice);
    void doubleClicked(QPieSlice *slice);
    void countChanged();
    void sumChanged();

private:
    Q_DECLARE_PRIVATE(QPieSeries)
    Q_DISABLE_COPY(QPieSeries)
    friend class PieChartItem;
};

QT_END_NAMESPACE

#endif // QPIESERIES_H
