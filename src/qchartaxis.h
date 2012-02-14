#ifndef QCHARTAXIS_H_
#define QCHARTAXIS_H_

#include <qchartglobal.h>
#include <QPen>
#include <QFont>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis
{
public:
    enum LabelsOrientation{ LabelsOrientationHorizontal, LabelsOrientationVertical , LabelsOrientationSlide };

    QChartAxis();
    virtual ~QChartAxis();

    //axis
    bool isAxisVisible() const { return m_axisVisible;};
    void setAxisVisible(bool visible);
    void setAxisPen(const QPen& pen);
    QPen axisPen() const { return m_axisPen;};
    void setAxisBrush(const QBrush& brush);
    QBrush axisBrush() const { return m_axisBrush;};

    //grid
    bool isGridVisible() const { return m_gridVisible;};
    void setGridVisible(bool visible);
    void setGridPen(const QPen& pen);
    QPen gridPen() const {return m_gridPen;}

    //labels
    bool isLabelsVisible() const { return m_labelsVisible;};
    void setLabelsVisible(bool visible);
    void setLabelsPen(const QPen& pen);
    QPen labelsPen() const { return m_labelsPen;}
    void setLabelsBrush(const QBrush& brush);
    QBrush labelsBrush() const { return m_labelsBrush;}
    void setLabelsFont(const QFont& font);
    QFont labelFont() const { return m_labelsFont;}
    void setLabelsOrientation(LabelsOrientation orientation);
    LabelsOrientation labelsOrientation() const { return m_labelsOrientation;};

    //shades
    bool isShadesVisible() const { return m_shadesVisible;};
    void setShadesVisible(bool visible);
    void setShadesPen(const QPen& pen);
    QPen shadesPen() const { return m_shadesPen;}
    void setShadesBrush(const QBrush& brush);
    QBrush shadesBrush() const { return m_shadesBrush;}


private:

    bool m_axisVisible;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_gridVisible;
    QPen m_gridPen;

    bool m_labelsVisible;
    QPen m_labelsPen;
    QBrush m_labelsBrush;
    QFont m_labelsFont;

    bool m_shadesVisible;
    QPen m_shadesPen;
    QBrush m_shadesBrush;

    LabelsOrientation m_labelsOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif /* QCHARTAXIS_H_ */
