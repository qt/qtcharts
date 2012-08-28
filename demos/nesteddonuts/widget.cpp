#include "widget.h"
#include <QChartView>
#include <QChart>
#include <QLegend>
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

    //! [1]
    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart *chart = chartView->chart();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(false);
    chart->setTitle("Nested donuts demo");
    //! [1]

    //! [2]
    qreal minSize = 0.1;
    qreal maxSize = 0.9;
    int donutCount = 5;
    //! [2]

    //! [3]
    for (int i = 0; i < donutCount; i++) {
        QPieSeries *donut = new QPieSeries;
        int sliceCount =  3 + qrand() % 3;
        for (int j = 0; j < sliceCount; j++) {
            qreal value = 100 + qrand() % 100;
            QPieSlice *slice = new QPieSlice(QString("%1").arg(value), value);
            slice->setLabelVisible(true);
            slice->setLabelColor(Qt::white);
            slice->setLabelPosition(QPieSlice::LabelInsideTangential);
            connect(slice, SIGNAL(hovered(bool)), this, SLOT(explodeSlice(bool)));
            donut->append(slice);
            donut->setHoleSize(minSize + i * (maxSize - minSize) / donutCount);
            donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
        }
        m_donuts.append(donut);
        chartView->chart()->addSeries(donut);
    }
    //! [3]

    // create main layout
    //! [4]
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);
    //! [4]

    //! [5]
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateRotation()));
    updateTimer->start(1250);
    //! [5]
}

Widget::~Widget()
{
    
}

    //! [6]
void Widget::updateRotation()
{
    for (int i = 0; i < m_donuts.count(); i++) {
        QPieSeries *donut = m_donuts.at(i);
        qreal phaseShift =  -50 + qrand() % 100;
        donut->setPieStartAngle(donut->pieStartAngle() + phaseShift);
        donut->setPieEndAngle(donut->pieEndAngle() + phaseShift);
    }
}
    //! [6]

    //! [7]
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
    //! [7]
