#include "widget.h"
#include <QGridLayout>

#include <QPieSlice>
#include <QTime>
#include <QChartView>
#include <QTimer>

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      mainData(0)
{
    setMinimumSize(800, 600);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QChartView *chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAnimationOptions(QChart::AllAnimations);

    mainData = new QPieSeries;
    for (int j = 0; j < 4; j++) {

        // create new slice for the mainData
        QPieSlice *slice = new QPieSlice;
        slice->setLabelPosition(QPieSlice::LabelInside);
        slice->setLabelColor(Qt::white);
        mainData->append(slice);

        // create a new detailed data for the slice
        QPieSeries *donut = new QPieSeries;
        donut->setDonut();
        donut->setLabelsVisible();
        donut->setDonutInnerSize(mainData->pieSize());
        donut->setPieSize(mainData->pieSize() + 0.2);

        // when mainData slice is redrawn make sure the detailed data slices are aligned with it
        connect(slice, SIGNAL(startAngleChanged()), this, SLOT(updatedStartAngle()));
        connect(slice, SIGNAL(angleSpanChanged()), this, SLOT(updatedAngleSpan()));

        // create the detailed data
        for (int j = 0; j < 3; j++) {
            qreal value = 10 + qrand() % 100;
            QPieSlice *slice = new QPieSlice(QString("%1").arg(value), value);
            donut->append(slice);
            donut->slices().last()->setLabelVisible(true);
            donut->slices().last()->setLabelColor(Qt::white);
        }
        detailedData.append(donut);

        // update the value and label of mainData
        slice->setValue(donut->sum());
        slice->setLabel(QString("%1").arg(donut->sum()));
    }

    mainData->setLabelsVisible();
    chartView->chart()->addSeries(mainData);
    for (int i = 0; i < detailedData.count(); i++)
        chartView->chart()->addSeries(detailedData.at(i));

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    setLayout(mainLayout);

    // modify the value of one detailed slice every 2.5 sec
    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(highlight()));
    updateTimer->start(2500);
}

Widget::~Widget()
{
    
}

void Widget::updatedStartAngle()
{
    // when the mainData slice has been updated the detailed data QPieSeries object as well
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    QPieSeries *detailsDonut = detailedData.at(slice->series()->slices().indexOf(slice));
    detailsDonut->setPieStartAngle(slice->startAngle());
}

void Widget::updatedAngleSpan()
{
    // when the mainData slice has been updated the detailed data QPieSeries object as well
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    QPieSeries *detailsDonut = detailedData.at(slice->series()->slices().indexOf(slice));
    detailsDonut->setPieEndAngle(slice->startAngle() + slice->angleSpan());
}

void Widget::updateRotation()
{
    // update the selected slice
    qreal newValue = 10 + qrand() % 100;
    detailedData.at(detailIndex)->slices().at(sliceIndex)->setValue(newValue);
    detailedData.at(detailIndex)->slices().at(sliceIndex)->setLabel(QString("%1").arg(newValue));

    // update the mainData slice with a new sum of the detailed data values
    mainData->slices().at(detailIndex)->setValue(detailedData.at(detailIndex)->sum());
    mainData->slices().at(detailIndex)->setLabel(QString("%1").arg(detailedData.at(detailIndex)->sum()));

    // change the explode state of the selected slice back to normal
    detailedData.at(detailIndex)->slices().at(sliceIndex)->setExploded(false);
}

void Widget::highlight()
{
    // choose one random detailed data slice to be updated.
    detailIndex = qrand() % mainData->count();
    sliceIndex = qrand() % detailedData.at(detailIndex)->count();

    // set the slice to exploded to make the change easier to observe
    detailedData.at(detailIndex)->slices().at(sliceIndex)->setExploded();

    // give the user time to focus on the slice that will be changed
    QTimer::singleShot(1000, this, SLOT(updateRotation()));
}
