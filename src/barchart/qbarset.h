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

public:
    QBarSet(QString name, QObject *parent = 0);
    virtual ~QBarSet();

    void setName(QString name);
    QString name() const;
    QBarSet& operator << (const qreal &value);  // appends new value to set
    void insertValue(int i, qreal value);
    void removeValue(int i);
    int count() const;                          // count of values in set
    qreal valueAt(int index) const;             // for modifying individual values
    void setValue(int index, qreal value);      // setter for individual value
    qreal sum() const;                          // sum of all values in the set

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
    void clicked(QString category, Qt::MouseButtons button);                         // Clicked and hover signals exposed to user

private:
    QScopedPointer<QBarSetPrivate> d_ptr;
    Q_DISABLE_COPY(QBarSet)
    friend class QBarSeries;
    friend class BarLegendMarker;
    friend class BarChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
