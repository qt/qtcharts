#ifndef QCHARTAXIS_H_
#define QCHARTAXIS_H_

#include <qchartglobal.h>
#include <QPen>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool axisVisible READ isAxisVisible WRITE setAxisVisible NOTIFY axisVisibilityChanged);
    Q_PROPERTY(QPen axisPen READ axisPen WRITE setAxisPen NOTIFY axisPenChanged);
    Q_PROPERTY(QBrush axisBrush READ axisBrush WRITE setAxisBrush NOTIFY axisBurshChanged);

   // Q_PROPERTY(bool axisVisible READ isAxisVisible WRITE setAxisVisible NOTIFY axisVisibilityChanged);
public:
    enum LabelOrientation{ HORIZONTAL, VERTICAL , SLIDE };

    QChartAxis(QObject* parent = 0);
    virtual ~QChartAxis();

    //axis
    bool isAxisVisible() const { return m_axisVisible;};
    void setAxisVisible(bool visible);
    void setAxisPen(const QPen& pen);
    const QPen& axisPen() const { return m_axisPen;};
    void setAxisBrush(const QBrush& brush);
    const QBrush& axisBrush() const { return m_axisBrush;};

    //grid
    bool isGridVisible() const { return m_girdVisible;};
    void setGridVisible(bool visible);

    bool isLabelsVisible() const { return m_labelsVisible;};
    void setLabelsVisible(bool visible);

    bool isRowShadesVisible() const { return m_rowShadesVisible;};
    void setRowShadesVisible(bool visible);

    /*
    void setLabelFont(const QFont& font);
    const QFont& labelFont();

    void setLabelPen(const QPen& pen);
    const QPen& labelPen();

    void setGridPen(const QPen& pen);
    const QPen& gridPen();

    void setGridBrush(const QBrush& brush);
    const QBrush& gridBrush();
     */

signals:
    void axisVisibilityChanged();
    void axisPenChanged();
    void axisBurshChanged();


private:

    bool m_axisVisible;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_girdVisible;
    bool m_labelsVisible;
    bool m_rowShadesVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif /* QCHARTAXIS_H_ */
