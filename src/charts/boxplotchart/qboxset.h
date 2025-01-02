// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QBOXSET_H
#define QBOXSET_H

#include <QtCharts/qchartglobal.h>
#include <QtGui/qpen.h>
#include <QtGui/qbrush.h>
#include <QtGui/qfont.h>
#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE
class QBoxSetPrivate;

class Q_CHARTS_EXPORT QBoxSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)

public:
    enum ValuePositions {
        LowerExtreme,
        LowerQuartile,
        Median,
        UpperQuartile,
        UpperExtreme
    };

public:
    explicit QBoxSet(const QString label = QString(), QObject *parent = nullptr);
    explicit QBoxSet(const qreal le, const qreal lq, const qreal m, const qreal uq, const qreal ue, const QString label = QString(), QObject *parent = nullptr);
    virtual ~QBoxSet();

    void append(const qreal value);
    void append(const QList<qreal> &values);

    void clear();

    void setLabel(const QString label);
    QString label() const;

    QBoxSet &operator << (const qreal &value);

    void setValue(const int index, const qreal value);
    qreal at(const int index) const;
    qreal operator [](const int index) const;
    int count() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

Q_SIGNALS:
    void clicked();
    void hovered(bool status);
    void pressed();
    void released();
    void doubleClicked();
    void penChanged();
    void brushChanged();

    void valuesChanged();
    void valueChanged(int index);
    void cleared();

private:
    QScopedPointer<QBoxSetPrivate> d_ptr;
    Q_DISABLE_COPY(QBoxSet)
    friend class BarLegendMarker;
    friend class BarChartItem;
    friend class BoxPlotChartItem;
    friend class QBoxPlotSeriesPrivate;
};

QT_END_NAMESPACE

#endif // QBOXSET_H
