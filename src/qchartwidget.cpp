#include "qchartwidget.h"
#include "qchartseries.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartWidgetPrivate
{
public:
    QChartWidgetPrivate(QChartWidget *parent) :
    m_view(0),
    m_scene(0),
    m_chart(0)
    {
        m_scene = new QGraphicsScene();
        m_view = new QGraphicsView(parent);
        m_view->setScene(m_scene);
        m_chart = new QChart();
        m_scene->addItem(m_chart);
    }

    ~QChartWidgetPrivate() {
    }

    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    QChart* m_chart;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

QChartWidget::QChartWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new QChartWidgetPrivate(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QChartWidget::~QChartWidget()
{
    delete d_ptr;
}

void QChartWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(QChartWidget);
    d->m_view->resize(size().width(),size().height());
    d->m_scene->setSceneRect(0,0,size().width(),size().height());
    d->m_chart->setSize(size());
    QWidget::resizeEvent(event);
}

QSize QChartWidget::sizeHint() const
{
    // TODO: calculate size hint based on contents?
    return QSize(100, 100);
}

void QChartWidget::addSeries(QChartSeries* series)
{
    Q_D(QChartWidget);
    d->m_chart->addSeries(series);
}

#include "moc_qchartwidget.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
