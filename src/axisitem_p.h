#ifndef AXISITEM_H_
#define AXISITEM_H_

#include "domain_p.h"
#include "chartitem_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis;

class AxisItem : public QObject, public ChartItem
{
    Q_OBJECT
public:
    enum AxisType{X_AXIS,Y_AXIS};

    AxisItem(AxisType type = X_AXIS,QGraphicsItem* parent = 0);
    ~AxisItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    AxisType axisType() const {return m_type;};

    void setAxisOpacity(qreal opacity);
    qreal axisOpacity() const;

    void setGridOpacity(qreal opacity);
    qreal gridOpacity() const;

    void setLabelsOpacity(qreal opacity);
    qreal labelsOpacity() const;

    void setShadesOpacity(qreal opacity);
    qreal shadesOpacity() const;

    void setLabelsAngle(int angle);
    int labelsAngle()const { return m_labelsAngle; }

    void setShadesBrush(const QBrush& brush);
    void setShadesPen(const QPen& pen);

    void setAxisPen(const QPen& pen);
    void setGridPen(const QPen& pen);

    void setLabelsPen(const QPen& pen);
    void setLabelsBrush(const QBrush& brush);
    void setLabelsFont(const QFont& font);

public slots:
    void handleAxisUpdate(QChartAxis* axis);
    void handleLabelsChanged(QChartAxis* axis,const QStringList& labels);
    void handleGeometryChanged(const QRectF& size);
protected:
    void updateItem(int count);
private:
    void clear();
    void createItems(int count);
private:
    AxisType m_type;
    QRectF m_rect;
    int m_labelsAngle;
    bool m_shadesEnabled;
    QGraphicsItemGroup m_grid;
    QGraphicsItemGroup m_shades;
    QGraphicsItemGroup m_labels;
    QGraphicsLineItem m_axis;
    QStringList m_thicksList;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXISITEM_H_ */
