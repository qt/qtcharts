// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVALUEAXIS_H
#define QVALUEAXIS_H

#include <QtCharts/QAbstractAxis>

QT_BEGIN_NAMESPACE

class QValueAxisPrivate;

class Q_CHARTS_EXPORT QValueAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(int tickCount READ tickCount WRITE setTickCount NOTIFY tickCountChanged)
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString labelFormat READ labelFormat WRITE setLabelFormat NOTIFY labelFormatChanged)
    Q_PROPERTY(int minorTickCount READ minorTickCount WRITE setMinorTickCount NOTIFY minorTickCountChanged)
    Q_PROPERTY(qreal tickAnchor READ tickAnchor WRITE setTickAnchor NOTIFY tickAnchorChanged
                       REVISION(2, 3))
    Q_PROPERTY(qreal tickInterval READ tickInterval WRITE setTickInterval NOTIFY tickIntervalChanged
                       REVISION(2, 3))
    Q_PROPERTY(TickType tickType READ tickType WRITE setTickType NOTIFY tickTypeChanged REVISION(2,
                                                                                                 3))
    Q_ENUMS(TickType)

public:
    enum TickType {
        TicksDynamic = 0,
        TicksFixed
    };

public:
    explicit QValueAxis(QObject *parent = nullptr);
    ~QValueAxis();

protected:
    QValueAxis(QValueAxisPrivate &d, QObject *parent = nullptr);

public:
    AxisType type() const override;

    //range handling
    void setMin(qreal min);
    qreal min() const;
    void setMax(qreal max);
    qreal max() const;
    void setRange(qreal min, qreal max);

    //ticks handling
    void setTickCount(int count);
    int tickCount() const;
    void setMinorTickCount(int count);
    int minorTickCount() const;
    void setTickAnchor(qreal anchor);
    qreal tickAnchor() const;
    void setTickInterval(qreal insterval);
    qreal tickInterval() const;
    void setTickType(QValueAxis::TickType type);
    QValueAxis::TickType tickType() const;

    void setLabelFormat(const QString &format);
    QString labelFormat() const;

public Q_SLOTS:
    void applyNiceNumbers();

Q_SIGNALS:
    void minChanged(qreal min);
    void maxChanged(qreal max);
    void rangeChanged(qreal min, qreal max);
    void tickCountChanged(int tickCount);
    void minorTickCountChanged(int tickCount);
    void labelFormatChanged(const QString &format);
    Q_REVISION(2, 3) void tickIntervalChanged(qreal interval);
    Q_REVISION(2, 3) void tickAnchorChanged(qreal anchor);
    Q_REVISION(2, 3) void tickTypeChanged(QValueAxis::TickType type);

private:
    Q_DECLARE_PRIVATE(QValueAxis)
    Q_DISABLE_COPY(QValueAxis)
};

QT_END_NAMESPACE

#endif // QVALUEAXIS_H
