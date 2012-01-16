#ifndef CHARTVIEW_H_
#define CHARTVIEW_H_
#include <qchartwidget.h>
#include <QGraphicsView>

class QGraphicsScene;

QCHART_USE_NAMESPACE

class ChartView: public QGraphicsView
{
public:
	ChartView (QChartWidget* chartWidget,QWidget* parent=0);
	virtual ~ChartView();
    void resizeEvent(QResizeEvent *event);

private:
	QChartWidget* m_chartWidget;
	QGraphicsScene* m_scene;
};

#endif /* CHARTVIEW_H_ */
