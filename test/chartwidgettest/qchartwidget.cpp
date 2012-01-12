#include "qchartwidget.h"
#include "qscatterseries.h"
#include <QGraphicsView>
#include <QGraphicsScene>

QChartWidget::QChartWidget(QWidget *parent) :
    QWidget(parent)
{
    // scatter
    m_scene = new QGraphicsScene();
    m_view = new QGraphicsView(m_scene, this);
    m_view->resize(300, 300);

    // TODO: implement graphics item for axis
    m_scene->addLine(0, 0, 0, 100);
    m_scene->addLine(0, 100, 100, 100);

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
