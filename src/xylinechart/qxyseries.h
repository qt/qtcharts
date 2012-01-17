#ifndef QXYSERIES_H_
#define QXYSERIES_H_

#include "qchartconfig.h"
#include <QDebug>
#include <QColor>

QCHART_BEGIN_NAMESPACE

class QCHART_EXPORT QXYSeries
{
public:
    QXYSeries();
    virtual ~QXYSeries();
    void add(qreal x, qreal y);
    void clear();
    void setColor(const QColor& color);
    const QColor& color() const { return m_color;}
    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    friend QDebug operator<< (QDebug d, const QXYSeries series);

private:
    QColor m_color;
    QList<qreal> m_x;
    QList<qreal> m_y;

};

QCHART_END_NAMESPACE

#endif
