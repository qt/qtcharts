#ifndef QXYSERIES_H_
#define QXYSERIES_H_

#include "qchartglobal.h"
#include "qseries.h"
#include <QDebug>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QXYSeries : public QSeries
{
    Q_OBJECT
protected:
    QXYSeries(QObject* parent=0);
    virtual ~QXYSeries();

public:
    void add(qreal x, qreal y);
    void add(const QPointF& point);
    void add(const QList<QPointF> points);
    void replace(qreal x,qreal y);
    void replace(const QPointF& point);
    void remove(qreal x, qreal y);
    void remove(const QPointF& point);
    void removeAll();

    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    QList<QPointF> data();

    QXYSeries& operator << (const QPointF &point);
    QXYSeries& operator << (const QList<QPointF> points);

    void setPen(const QPen& pen);
    QPen pen() const {return m_pen;}
    void setBrush(const QBrush& pen);
    QBrush brush() const {return m_brush;}

    bool setModel(QAbstractItemModel* model);
    QAbstractItemModel* model() {return m_model;}

    void setModelMapping(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);
//    void setModelMappingY(int modelLineIndex, Qt::Orientation orientation = Qt::Vertical);

    private slots:
        void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);

signals:
    void updated();
    void pointReplaced(int index);
    void pointRemoved(int index);
    void pointAdded(int index);

protected:
    QVector<qreal> m_x;
    QVector<qreal> m_y;

    QPen m_pen;
    QBrush m_brush;

    QAbstractItemModel* m_model;
    int m_mapX;
    Qt::Orientation m_mapOrientation;
    int m_mapY;
//    Qt::Orientation m_mapYOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
