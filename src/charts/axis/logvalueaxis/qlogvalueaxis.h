// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QLOGVALUEAXIS_H
#define QLOGVALUEAXIS_H

#include <QtCharts/QAbstractAxis>

QT_BEGIN_NAMESPACE
class QDateTime;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QLogValueAxisPrivate;

class Q_CHARTS_EXPORT QLogValueAxis : public QAbstractAxis
{
    Q_OBJECT
    Q_PROPERTY(qreal min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qreal max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString labelFormat READ labelFormat WRITE setLabelFormat NOTIFY labelFormatChanged)
    Q_PROPERTY(qreal base READ base WRITE setBase NOTIFY baseChanged)
    Q_PROPERTY(int tickCount READ tickCount NOTIFY tickCountChanged)
    Q_PROPERTY(int minorTickCount READ minorTickCount WRITE setMinorTickCount NOTIFY minorTickCountChanged)

public:
    explicit QLogValueAxis(QObject *parent = nullptr);
    ~QLogValueAxis();

protected:
    QLogValueAxis(QLogValueAxisPrivate &d, QObject *parent = nullptr);

public:
    AxisType type() const override;

    //range handling
    void setMin(qreal min);
    qreal min() const;
    void setMax(qreal max);
    qreal max() const;
    void setRange(qreal min, qreal max);

    void setLabelFormat(const QString &format);
    QString labelFormat() const;

    void setBase(qreal base);
    qreal base() const;

    int tickCount() const;

    void setMinorTickCount(int minorTickCount);
    int minorTickCount() const;

Q_SIGNALS:
    void minChanged(qreal min);
    void maxChanged(qreal max);
    void rangeChanged(qreal min, qreal max);
    void labelFormatChanged(const QString &format);
    void baseChanged(qreal base);
    void tickCountChanged(int tickCount);
    void minorTickCountChanged(int minorTickCount);

private:
    Q_DECLARE_PRIVATE(QLogValueAxis)
    Q_DISABLE_COPY(QLogValueAxis)
};

QT_END_NAMESPACE

#endif // QLOGVALUEAXIS_H
