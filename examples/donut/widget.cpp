#include "widget.h"
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QTime>
#include <QGridLayout>
#include <QTimer>

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{    
    setMinimumSize(800, 600);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    qreal minSize = 0.1;
    qreal maxSize = 0.9;
    int donutsCount = 5;
    for (int i = 0; i < donutsCount; i++) {
        QPieSeries *donut = new QPieSeries;
        donut->setDonut();
        donut->setLabelsVisible();
        int sliceCount =  3 + qrand() % 3;
        for (int j = 0; j < sliceCount; j++) {
            qreal value = 100 + qrand() % 100;
            QPieSlice *slice = new QPieSlice(QString("%1").arg(value), value);
            connect(slice, SIGNAL(hovered(bool)), this, SLOT(explodeSlice(bool)));
            donut->append(slice);
            donut->slices().last()->setLabelVisible(true);
            donut->slices().last()->setLabelColor(Qt::white);
            donut->setDonutInnerSize(minSize + i * (maxSize - minSize) / donutsCount);
            donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutsCount);
        }
        m_donuts.append(donut);
        qreal phase = qrand() % 180;
        donut->setPieStartAngle(phase);
        donut->setPieEndAngle(360 + phase);
        chartView->chart()->addSeries(donut);
    }

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);

    chartView->chart()->setAnimationOptions(QChart::AllAnimations);

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateRotation()));
    updateTimer->start(750);
}

Widget::~Widget()
{
    
}

void Widget::updateRotation()
{
    //    int tobeupdated = qrand() % m_donutsGroup.count();
    for (int i = 0; i < m_donuts.count(); i++) {
        QPieSeries *donut = m_donuts.at(i);
        qreal phaseShift =  -50 + qrand() % 100;
        donut->setPieStartAngle(donut->pieStartAngle() + phaseShift);
        donut->setPieEndAngle(donut->pieEndAngle() + phaseShift);
    }
}

void Widget::explodeSlice(bool exploded)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (exploded) {
        updateTimer->stop();
        qreal sliceStartAngle = slice->startAngle();
        qreal sliceEndAngle = slice->startAngle() + slice->angleSpan();

        QPieSeries *donut = slice->series();
        qreal seriesIndex = m_donuts.indexOf(donut);
        for (int i = seriesIndex + 1; i < m_donuts.count(); i++) {
            m_donuts.at(i)->setPieStartAngle(sliceEndAngle);
            m_donuts.at(i)->setPieEndAngle(360 + sliceStartAngle);
        }
    } else {
        for (int i = 0; i < m_donuts.count(); i++) {
            m_donuts.at(i)->setPieStartAngle(0);
            m_donuts.at(i)->setPieEndAngle(360);
        }
        updateTimer->start();
    }
    slice->setExploded(exploded);
}
