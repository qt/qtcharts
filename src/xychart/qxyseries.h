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

#ifndef QXYSERIES_H
#define QXYSERIES_H

#include <qchartglobal.h>
#include <qabstractseries.h>
#include <QPen>
#include <QBrush>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYSeriesPrivate;
class QXYModelMapper;

class QTCOMMERCIALCHART_EXPORT QXYSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(bool pointsVisible READ pointsVisible WRITE setPointsVisible)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

protected:
    explicit QXYSeries(QXYSeriesPrivate &d, QObject *parent = 0);

public:
    ~QXYSeries();
    void append(qreal x, qreal y);
    void append(const QPointF &point);
    void append(const QList<QPointF> &points);
    void replace(qreal oldX, qreal oldY, qreal newX, qreal newY);
    void replace(const QPointF &oldPoint, const QPointF &newPoint);
    void remove(qreal x, qreal y);
    void remove(const QPointF &point);
    void insert(int index, const QPointF &point);
    void clear();

    int count() const;
    QList<QPointF> points() const;

    QXYSeries &operator << (const QPointF &point);
    QXYSeries &operator << (const QList<QPointF> &points);

    virtual void setPen(const QPen &pen);
    QPen pen() const;

    virtual void setBrush(const QBrush &brush);
    QBrush brush() const;

    virtual void setColor(const QColor &color);
    virtual QColor color() const;

    void setPointsVisible(bool visible = true);
    bool pointsVisible() const;

    void replace(QList<QPointF> points);

Q_SIGNALS:
    void clicked(const QPointF &point);
    void pointReplaced(int index);
    void pointRemoved(int index);
    void pointAdded(int index);
    void colorChanged(QColor color);
    void pointsReplaced();

private:
    Q_DECLARE_PRIVATE(QXYSeries)
    Q_DISABLE_COPY(QXYSeries)
    friend class XYLegendMarker;
    friend class XYChart;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QXYSERIES_H
