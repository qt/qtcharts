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

#ifndef QXYSERIES_H_
#define QXYSERIES_H_

#include <qchartglobal.h>
#include <qseries.h>
#include <QPen>
#include <QBrush>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QXYSeries : public QSeries
{
    Q_OBJECT
protected:
    QXYSeries(QObject *parent = 0);
    virtual ~QXYSeries();

public:
    void append(qreal x, qreal y);
    void append(const QPointF &point);
    void append(const QList<QPointF> points);
    void replace(qreal x,qreal y);
    void replace(const QPointF &point);
    void remove(qreal x);
    void remove(qreal x, qreal y);
    void remove(const QPointF &point);
    void removeAll();

    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    QList<QPointF> data();

    QXYSeries& operator << (const QPointF &point);
    QXYSeries& operator << (const QList<QPointF> points);

    void setPen(const QPen &pen);
    QPen pen() const {return m_pen;}
    void setBrush(const QBrush &brush);
    QBrush brush() const {return m_brush;}

    bool setModel(QAbstractItemModel *model);

    virtual void setModelMapping(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);
    virtual void setModelMappingRange(int first, int count = 0);
    int mapFirst() const { return m_mapFirst; }

private Q_SLOTS:
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAboutToBeAdded(QModelIndex parent, int start, int end);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataAboutToBeRemoved(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);

Q_SIGNALS:
    void clicked(const QPointF &point);
    void selected();
    void updated();
    void pointReplaced(int index);
    void pointRemoved(int index);
    void pointAdded(int index);

protected:
    QVector<qreal> m_x;
    QVector<qreal> m_y;

    QPen m_pen;
    QBrush m_brush;

    int m_mapX;
    int m_mapY;
    int m_mapFirst;
    int m_mapCount;
    bool m_mapLimited;
    Qt::Orientation m_mapOrientation;
    int tempItemsRemoved;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
