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
public:
	QXYSeries(QObject* parent=0);
	virtual ~QXYSeries();

public:
	void add(qreal x, qreal y);
	void add(const QPointF& point);
	void replace(qreal x,qreal y);
	void replace(const QPointF& point);
	void remove(qreal x);
	void remove(const QPointF& point);
	void clear();

	int count() const;
	qreal x(int pos) const;
	qreal y(int pos) const;

	QXYSeries& operator << (const QPointF &point);

signals:
	void updated();
	void pointReplaced(int index);
	void pointRemoved(int index);
	void pointAdded(int index);


protected:
	QVector<qreal> m_x;
	QVector<qreal> m_y;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
