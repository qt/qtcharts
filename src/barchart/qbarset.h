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

public:
    explicit QBarSet(const QString name, QObject *parent = 0);
    virtual ~QBarSet();

    void setName(const QString name);
    QString name() const;

// TODO:
//    void append(const QPointF value);         // Appends bar with x-value
//    void append(const QList<QPointF> value);  // Same with list
    void append(const qreal value);             // TODO: change so, that count becomes x-value

// TODO:
//    void append(const QList<qreal> values);   // Append list of values. Using index as x-value

    QBarSet& operator << (const qreal &value);  // TODO: change implementations so, that count becomes x-value
// TODO:
//    QBarSet& operator << (const QPointF &value);  // Appends bar with x-value

    void insert(const int index, const qreal value); // TODO: internal reindexing (what happens, if there are points with real x values?)
    void remove(const int index);                    // TODO: internal reindexing (what happens, if there are points with real x values?)
    void replace(const int index, const qreal value);
    qreal at(const int index) const;
    qreal operator [] (int index) const;
    int count() const;
    qreal sum() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setLabelPen(const QPen &pen);
    QPen labelPen() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelFont(const QFont &font);
    QFont labelFont() const;

    void setLabelsVisible(bool visible = true);
    bool labelsVisible() const;

Q_SIGNALS:
    void clicked(QString category);
    void hovered(bool status);

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
