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

    for (int i = 0; i < 7; i++) {
        QPieSeries *donut = new QPieSeries;
        donut->setLabelsVisible();
        for (int j = 0; j < 4; j++) {
            qreal value = 100 + qrand() % 100;
            donut->append(QString("%1").arg(value), value);
            donut->slices().last()->setLabelVisible(true);
//            QFont labelFont = donut->slices().last()->labelFont();
//            //            labelFont.setUnderline(true);
//            labelFont.setBold(true);
//            donut->slices().last()->setLabelFont(labelFont);
                        donut->slices().last()->setLabelColor(Qt::white);
        }
        qreal phase = qrand() % 180;
        donut->setPieStartAngle(phase);
        donut->setPieEndAngle(360 + phase);
        chartView->chart()->addSeries(donut);
        m_donutsGroup.append(donut);
    }

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);

    chartView->chart()->setAnimationOptions(QChart::AllAnimations);

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateRotation()));
    updateTimer->start(750);
}

Widget::~Widget()
{
    
}

void Widget::updateRotation()
{
    for (int i = 0; i < m_donutsGroup.count(); i++) {
        QPieSeries *donut = m_donutsGroup.donuts().at(i);
        qreal phaseShift =  -50 + qrand() % 100;
        donut->setPieStartAngle(donut->pieStartAngle() + phaseShift);
        donut->setPieEndAngle(donut->pieEndAngle() + phaseShift);
    }
}
