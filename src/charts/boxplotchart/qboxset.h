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

#ifndef QBOXSET_H
#define QBOXSET_H

#include <QtCharts/QChartGlobal>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QFont>

QT_CHARTS_BEGIN_NAMESPACE
class QBoxSetPrivate;

class QT_CHARTS_EXPORT QBoxSet : public QObject
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
    explicit QBoxSet(const QString label = QString(), QObject *parent = 0);
    explicit QBoxSet(const qreal le, const qreal lq, const qreal m, const qreal uq, const qreal ue, const QString label = QString(), QObject *parent = 0);
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

QT_CHARTS_END_NAMESPACE

#endif // QBOXSET_H
