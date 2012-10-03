#include "widget.h"

// Qt
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>

// Charts
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_axisX(0),
      m_axisY(0)
{
    QChartView *chartView = new QChartView;
    chartView->setAccessibleName("Chart");
    QChart *chart = chartView->chart();

    QLineSeries *series = new QLineSeries;
    series->setName("Series 1");
    series->append(1, 2);
    series->append(3, 1);
    series->append(5, 4);

    chart->addSeries(series);
    m_axisX = new QValueAxis;
    m_axisY = new QValueAxis;
    chart->setAxisX(m_axisX, series);
    chart->setAxisY(m_axisY, series);

    // buttons
    QVBoxLayout *buttonsLayout = createButtons();
    setAccessibleName("uitest");
    window()->setAccessibleName("uitest");
    setWindowTitle("uitest");

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->addLayout(buttonsLayout, 1, 2);
    setLayout(mainLayout);
}

Widget::~Widget()
{
    
}

QVBoxLayout* Widget::createButtons()
{
    QVBoxLayout *buttonsLayout = new QVBoxLayout;

    QPushButton *button = new QPushButton("Tick+");
    button->setAccessibleName("TickUp");
    buttonsLayout->addWidget(button);
    connect(button,SIGNAL(clicked()), this, SLOT(handleClick()));

    button = new QPushButton("Tick-");
    button->setAccessibleName("TickDown");
    buttonsLayout->addWidget(button);
    connect(button,SIGNAL(clicked()), this, SLOT(handleClick()));

    button = new QPushButton("RangeMax+");
    button->setAccessibleName("RangeMaxUp");
    buttonsLayout->addWidget(button);
    connect(button,SIGNAL(clicked()), this, SLOT(handleClick()));

    button = new QPushButton("RangeMax-");
    button->setAccessibleName("RangeMaxDown");
    buttonsLayout->addWidget(button);
    connect(button,SIGNAL(clicked()), this, SLOT(handleClick()));

    button = new QPushButton("RangeMin+");
    button->setAccessibleName("RangeMinUp");
    buttonsLayout->addWidget(button);
    connect(button,SIGNAL(clicked()), this, SLOT(handleClick()));

    button = new QPushButton("RangeMin-");
    button->setAccessibleName("RangeMinDown");
    buttonsLayout->addWidget(button);
    connect(button,SIGNAL(clicked()), this, SLOT(handleClick()));

    buttonsLayout->addStretch();

    return buttonsLayout;
}

void Widget::handleClick()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString buttonName = button->text();

    if (buttonName == "Tick+")
        m_axisX->setTickCount(m_axisX->tickCount() + 1);
    else if (buttonName == "Tick-")
        m_axisX->setTickCount(m_axisX->tickCount() - 1);
    else if (buttonName == "RangeMax+")
        m_axisX->setMax(m_axisX->max() + 1);
    else if (buttonName == "RangeMax-")
        m_axisX->setMax(m_axisX->max() - 1);
    else if (buttonName == "RangeMin+")
        m_axisX->setMin(m_axisX->min() + 1);
    else if (buttonName == "RangeMin-")
        m_axisX->setMin(m_axisX->min() - 1);
}
