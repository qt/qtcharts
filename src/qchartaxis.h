#ifndef QCHARTAXIS_H_
#define QCHARTAXIS_H_

#include <qchartglobal.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis
{
public:
    QChartAxis();
    virtual ~QChartAxis();

    bool isAxisVisible() const { return m_axisVisible;};
    void setAxisVisible(bool visible);
    bool isGridVisible() const { return m_girdVisible;};
    void setGridVisible(bool visible);
    bool isLabelsVisible() const { return m_labelsVisible;};
    void setLabelsVisible(bool visible);
    bool isRowShadesVisible() const { return m_rowShadesVisible;};
    void setRowShadesVisible(bool visible);

private:
    bool m_axisVisible;
    bool m_girdVisible;
    bool m_labelsVisible;
    bool m_rowShadesVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif /* QCHARTAXIS_H_ */
