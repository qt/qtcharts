#include "qchartwidget.h"
#include "qscatterseries.h"
#include <QGraphicsView>
#include <QGraphicsScene>

QChartWidget::QChartWidget(QWidget *parent) :
    QWidget(parent),
    m_scatter(0)
{
    m_scene = new QGraphicsScene();
    m_view = new QGraphicsView(m_scene, this);
    m_view->resize(490, 300);
    m_view->show();
}

QChartWidget::~QChartWidget()
{
    delete m_view;
    delete m_scene;
}

void QChartWidget::setType(/*TODO QChart::Type*/ int type)
{
    if (type == 4) {
        if (!m_scatter) {
            m_scatter = new QScatterSeries();
            m_scene->addItem(m_scatter);
        }
    } else {
        if (m_scatter) {
            m_scene->removeItem(m_scatter);
            delete m_scatter;
            m_scatter = 0;
        }
    }
}

void QChartWidget::setData(QList<QChartDataPoint> data)
//void QChartWidget::setData(QList<int> data)
{
    // TODO: other chart types... this looks ugly
    if (m_scatter)
        m_scatter->setData(data);
}
