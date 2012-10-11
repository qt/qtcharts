#include "widget.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QChart>
#include <QLineSeries>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include "callout.h"

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_scene(0),
      m_chart(0),
      m_view(0)
{
    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    QLineSeries *series = new QLineSeries;
    series->setName("Click the line to create a movable callout");
    series->append(1, 3);
    series->append(4, 5);
    series->append(5, 4.5);
    series->append(7, 1);
    series->append(11, 2);
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();

    m_scene = new QGraphicsScene;
    m_view = new QGraphicsView(m_scene);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_scene->addItem(m_chart);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    setLayout(mainLayout);

    connect(series, SIGNAL(clicked(QPointF)), this, SLOT(addCallout(QPointF)));
}

Widget::~Widget()
{
    
}

void Widget::addCallout(QPointF point)
{
    Callout *label = new Callout(m_chart);
    label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));
    label->setAnchor(m_chart->mapFromParent(m_view->mapToScene(m_view->mapFromGlobal(QCursor::pos()))));
    label->setPos(m_chart->mapFromParent(m_view->mapToScene(m_view->mapFromGlobal(QCursor::pos() + QPoint(10, -50)))));
    label->setZValue(11);
}
