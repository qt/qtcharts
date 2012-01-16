#include "chartview.h"

ChartView::ChartView(QChartWidget* chartWidget,QWidget* parent):QGraphicsView(parent),
m_chartWidget(chartWidget),
m_scene(new QGraphicsScene(parent))
{
	setScene(m_scene);
	m_scene->addItem(chartWidget);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	// get rid off ugly default 1 pixel border
	setStyleSheet( "QGraphicsView { border-style: none; }" );
}

ChartView::~ChartView() {
	// TODO Auto-generated destructor stub
}

void ChartView::resizeEvent(QResizeEvent *event){
	m_chartWidget->resize(size());
	QGraphicsView::resizeEvent(event);
}
