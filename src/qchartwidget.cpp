#include "qchartwidget.h"
#include "qxyseries.h"
#include "xylinechart_p.h"
#include <QGraphicsView>
#include <QGraphicsScene>

QCHART_BEGIN_NAMESPACE

class QChartWidgetPrivate
{
public:
    QChartWidgetPrivate(QWidget *parent) : m_view(0), m_scene(0), m_chart(0) {
        m_scene = new QGraphicsScene();
        m_view = new QGraphicsView(m_scene, parent);
        m_view->resize(490, 300);
        m_view->show();
    }
    ~QChartWidgetPrivate() {
        delete m_view;
        delete m_scene;
    }

    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    QChart* m_chart;
};

QChartWidget::QChartWidget(QWidget *parent) :
    QWidget(parent),
    d(new QChartWidgetPrivate(this))
{
    setMinimumSize(d->m_view->size());
}

QChartWidget::~QChartWidget()
{
    delete d;
}

void QChartWidget::addDataSeries(
        QChart::DataSeriesType dataSeriesType,
        QList<QXYSeries*> dataset)
{
    // TODO: implement management of several data series of different types

    d->m_chart = QChart::createXYLineChart(dataset);
    d->m_scene->addItem(d->m_chart);
    d->m_chart->setSize(this->size());
}

#include "moc_qchartwidget.cpp"

QCHART_END_NAMESPACE
