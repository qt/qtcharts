#ifndef QPIESLICE_P_H
#define QPIESLICE_P_H

#include <QObject>
#include "qpieslice.h"
#include "pieslicedata_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSeries;

class QPieSlicePrivate : public QObject
{
    Q_OBJECT

public:
    QPieSlicePrivate(QPieSlice *parent);
    ~QPieSlicePrivate();

    static QPieSlicePrivate* fromSlice(QPieSlice *slice);

    void setPen(const QPen &pen, bool themed);
    void setBrush(const QBrush &brush, bool themed);
    void setLabelBrush(const QBrush &brush, bool themed);
    void setLabelFont(const QFont &font, bool themed);

    void setPercentage(qreal percentage);
    void setStartAngle(qreal angle);
    void setAngleSpan(qreal span);

private:
    friend class QPieSeries;
    friend class QPieSeriesPrivate;
    friend class ChartTheme;
    friend class PieChartItem;

    QPieSlice * const q_ptr;
    Q_DECLARE_PUBLIC(QPieSlice)

    PieSliceData m_data;
    QPieSeries *m_series;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICE_P_H
