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

#ifndef QBARSET_H
#define QBARSET_H

#include <qchartglobal.h>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QBarSetPrivate;

class QTCOMMERCIALCHART_EXPORT QBarSet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QPen pen READ pen WRITE setPen)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
    Q_PROPERTY(QBrush labelBrush READ labelBrush WRITE setLabelBrush)
    Q_PROPERTY(QFont labelFont READ labelFont WRITE setLabelFont)

public:
    explicit QBarSet(const QString name, QObject *parent = 0);
    virtual ~QBarSet();

    void setName(const QString name);
    QString name() const;

    void append(const QPointF value);
    void append(const QList<QPointF> values);
    void append(const qreal value);
    void append(const QList<qreal> values);

    QBarSet& operator << (const qreal &value);
    QBarSet& operator << (const QPointF &value);

    void insert(const int index, const qreal value);
    void insert(const int index, const QPointF value);
    bool remove(const int index, const int count = 1);
    void replace(const int index, const qreal value);
    void replace(const int index, const QPointF value);
    QPointF at(const int index) const;
    QPointF operator [] (const int index) const;
    int count() const;
    qreal sum() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelFont(const QFont &font);
    QFont labelFont() const;

Q_SIGNALS:
    void nameChanged();
    void penChanged();
    void brushChanged();
    void labelChanged();
    void labelBrushChanged();
    void labelFontChanged();

    void valuesAdded(int index, int count);
    void valuesRemoved(int index, int count);
    void valueChanged(int index);

private:
    QScopedPointer<QBarSetPrivate> d_ptr;
    Q_DISABLE_COPY(QBarSet)
    friend class QBarSeries;
    friend class BarLegendMarker;
    friend class BarChartItem;
    friend class QBarSeriesPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
