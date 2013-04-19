/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef QBOXSET_H
#define QBOXSET_H

#include <qchartglobal.h>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QBoxSetPrivate;

class QTCOMMERCIALCHART_EXPORT QBoxSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)

public:
    explicit QBoxSet(QObject *parent = 0);
    explicit QBoxSet(qreal value1, qreal value2, qreal value3, qreal value4, qreal value5, QObject *parent = 0);
    virtual ~QBoxSet();

    void append(const qreal value);
    void append(const QList<qreal> &values);

    void setLowerExtreme(const qreal value);
    qreal lowerExtreme();
    void setLowerQuartile(const qreal value);
    qreal lowerQuartile();
    void setMedian(const qreal value);
    qreal median();
    void setUpperQuartile(const qreal value);
    qreal upperQuartile();
    void setUpperExtreme(const qreal value);
    qreal upperExtreme();

    QBoxSet &operator << (const qreal &value);

    void insert(const int index, const qreal value);
    void remove(const int index, const int count = 1);
    void replace(const int index, const qreal value);
    qreal at(const int index) const;
    qreal operator [](const int index) const;
    int count() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    QColor color();
    void setColor(QColor color);

    QColor borderColor();
    void setBorderColor(QColor color);


Q_SIGNALS:
    void clicked(int index);
    void hovered(bool status);
    void penChanged();
    void brushChanged();
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);

    void valuesAdded(int index, int count);
    void valuesRemoved(int index, int count);
    void valueChanged(int index);

private:
    QScopedPointer<QBoxSetPrivate> d_ptr;
    Q_DISABLE_COPY(QBoxSet)
    friend class BarLegendMarker;
    friend class BarChartItem;
    friend class BoxPlotChartItem;
    friend class QBoxPlotSeriesPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBOXSET_H
