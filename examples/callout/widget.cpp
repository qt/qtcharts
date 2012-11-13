#include "widget.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QChart>
#include <QLineSeries>
#include <QSplineSeries>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include "callout.h"

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_scene(0),
      m_chart(0),
      m_view(0),
      m_tooltip(0)
{
    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    m_chart->setTitle("Hover the line to show callout. Click the line to make it stay");
    m_chart->legend()->hide();
    QLineSeries *series = new QLineSeries;
    series->append(1, 3);
    series->append(4, 5);
    series->append(5, 4.5);
    series->append(7, 1);
    series->append(11, 2);
    m_chart->addSeries(series);

    QSplineSeries *series2 = new QSplineSeries;
    series2->append(1.6, 1.4);
    series2->append(2.4, 3.5);
    series2->append(3.7, 2.5);
    series2->append(7, 4);
    series2->append(10, 2);
    m_chart->addSeries(series2);

    m_chart->createDefaultAxes();

    m_scene = new QGraphicsScene;
    m_view = new QGraphicsView(m_scene);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_scene->addItem(m_chart);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    setLayout(mainLayout);

    connect(series, SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));

    connect(series2, SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series2, SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
}

Widget::~Widget()
{
    
}

void Widget::keepCallout()
{
    m_tooltip = new Callout(m_chart);
}

void Widget::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chart);

    if (state) {
        m_tooltip->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(m_chart->mapFromParent(m_view->mapToScene(m_view->mapFromGlobal(QCursor::pos()))));
        m_tooltip->setPos(m_chart->mapFromParent(m_view->mapToScene(m_view->mapFromGlobal(QCursor::pos() + QPoint(10, -50)))));
        m_tooltip->setZValue(11);
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}
