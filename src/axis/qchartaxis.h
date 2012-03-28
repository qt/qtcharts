#ifndef QCHARTAXIS_H_
#define QCHARTAXIS_H_

#include <qchartglobal.h>
#include <qchartaxiscategories.h>
#include <QPen>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QChartAxis : public QObject
{
	Q_OBJECT
public:

    QChartAxis(QObject *parent =0);
    ~QChartAxis();

    //axis handling
    bool isAxisVisible() const { return m_axisVisible; }
    void setAxisVisible(bool visible);
    void setAxisPen(const QPen &pen);
    QPen axisPen() const { return m_axisPen; }

    //grid handling
    bool isGridLineVisible() const { return m_gridLineVisible; }
    void setGridLineVisible(bool visible);
    void setGridLinePen(const QPen &pen);
    QPen gridLinePen() const { return m_gridLinePen; }

    //labels handling
    bool labelsVisible() const { return m_labelsVisible; }
    void setLabelsVisible(bool visible);
    void setLabelsPen(const QPen &pen);
    QPen labelsPen() const { return m_labelsPen;}
    void setLabelsBrush(const QBrush &brush);
    QBrush labelsBrush() const { return m_labelsBrush; }
    void setLabelsFont(const QFont &font);
    QFont labelsFont() const { return m_labelsFont; }
    void setLabelsAngle(int angle);
    int labelsAngle() const { return m_labelsAngle; }

    //shades handling
    bool shadesVisible() const { return m_shadesVisible; }
    void setShadesVisible(bool visible);
    void setShadesPen(const QPen &pen);
    QPen shadesPen() const { return m_shadesPen; }
    void setShadesBrush(const QBrush &brush);
    QBrush shadesBrush() const { return m_shadesBrush; }
    void setShadesOpacity(qreal opacity);
    qreal shadesOpacity() const { return m_shadesOpacity; }

    //range handling
    void setMin(qreal min);
    qreal min() const { return m_min; }
    void setMax(qreal max);
    qreal max() const { return m_max; }
    void setRange(qreal min, qreal max);

    //ticks handling
    void setTicksCount(int count);
    int ticksCount() const { return m_ticksCount;}

    void setNiceNumbers(bool enabled);
    bool niceNumbers() const { return m_niceNumbers;}

    QChartAxisCategories* categories() { return &m_category; }

    void show();
    void hide();

signals:
	void minChanged(qreal min);
	void maxChanged(qreal max);
	void rangeChanged(qreal min, qreal max);
	void ticksCountChanged(int count);

//interal signal
	void updated();
	void changed(qreal min, qreal max, int tickCount,bool niceNumbers);
//internal slot
public slots:
	void handleAxisRangeChanged(qreal min, qreal max,int count);

private:
    bool m_axisVisible;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_gridLineVisible;
    QPen m_gridLinePen;

    bool m_labelsVisible;
    QPen m_labelsPen;
    QBrush m_labelsBrush;
    QFont m_labelsFont;
    int m_labelsAngle;

    bool m_shadesVisible;
    QPen m_shadesPen;
    QBrush m_shadesBrush;
    qreal m_shadesOpacity;

    qreal m_min;
    qreal m_max;

    int m_ticksCount;
    QChartAxisCategories m_category;

    bool m_niceNumbers;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif /* QCHARTAXIS_H_ */
