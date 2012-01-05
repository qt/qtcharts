#include "mainwidget.h"
#include <chartwidget.h>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    m_chartWidget = new ChartWidget(this);
    m_chartWidget->resize(QSize(200,200));
    m_chartWidget->setColor(Qt::red);

    // Chart type
    QComboBox *chartTypeCombo = new QComboBox(this);
    chartTypeCombo->addItem("Line");
    chartTypeCombo->addItem("Area");
    chartTypeCombo->addItem("Bar");
    chartTypeCombo->addItem("Pie");
    chartTypeCombo->addItem("Scatter");
    chartTypeCombo->addItem("Spline");
    connect(chartTypeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(chartTypeChanged(int)));

    // Test data selector
    QComboBox *dataCombo = new QComboBox(this);
    dataCombo->addItem("todo: add test data");
    connect(dataCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(dataChanged(QString)));

    // Chart background
    QComboBox *backgroundCombo = new QComboBox(this);
    backgroundCombo->addItem("todo: add background types");
    connect(backgroundCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(backgroundChanged(int)));

    // Axis
    // Allow setting also non-sense values (like -2147483648 and 2147483647)
    QSpinBox *xMinSpin = new QSpinBox();
    xMinSpin->setMinimum(INT_MIN);
    xMinSpin->setMaximum(INT_MAX);
    xMinSpin->setValue(0);
    connect(xMinSpin, SIGNAL(valueChanged(int)), this, SLOT(xMinChanged(int)));
    QSpinBox *xMaxSpin = new QSpinBox();
    xMaxSpin->setMinimum(INT_MIN);
    xMaxSpin->setMaximum(INT_MAX);
    xMaxSpin->setValue(10);
    connect(xMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(xMaxChanged(int)));
    QSpinBox *yMinSpin = new QSpinBox();
    yMinSpin->setMinimum(INT_MIN);
    yMinSpin->setMaximum(INT_MAX);
    yMinSpin->setValue(0);
    connect(yMinSpin, SIGNAL(valueChanged(int)), this, SLOT(yMinChanged(int)));
    QSpinBox *yMaxSpin = new QSpinBox();
    yMaxSpin->setMinimum(INT_MIN);
    yMaxSpin->setMaximum(INT_MAX);
    yMaxSpin->setValue(10);
    connect(yMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(yMaxChanged(int)));

    QGridLayout *grid = new QGridLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    grid->addWidget(new QLabel("Chart type:"), 0, 0);
    grid->addWidget(chartTypeCombo, 0, 1);
    grid->addWidget(new QLabel("Data:"), 1, 0);
    grid->addWidget(dataCombo, 1, 1);
    grid->addWidget(new QLabel("Background:"), 2, 0);
    grid->addWidget(backgroundCombo, 2, 1);
    grid->addWidget(new QLabel("x min:"), 3, 0);
    grid->addWidget(xMinSpin, 3, 1);
    grid->addWidget(new QLabel("x max:"), 4, 0);
    grid->addWidget(xMaxSpin, 4, 1);
    grid->addWidget(new QLabel("y min:"), 5, 0);
    grid->addWidget(yMinSpin, 5, 1);
    grid->addWidget(new QLabel("y max:"), 6, 0);
    grid->addWidget(yMaxSpin, 6, 1);
    // add row with empty label to make all the other rows static
    grid->addWidget(new QLabel(""), 7, 0);
    grid->setRowStretch(7, 1);

    hbox->addLayout(grid);
    hbox->addWidget(m_chartWidget);
    hbox->setStretch(1, 1);

    setLayout(hbox);
}

void MainWidget::chartTypeChanged(int itemIndex)
{
    qDebug() << "chartTypeChanged: " << itemIndex;

    switch (itemIndex) {
//    case 0:
//        m_chartWidget->setType(ChartWidget::TypeLine);
//        break;
    default:
        // TODO: api for setting chart type?
        QMessageBox msg;
        msg.setText("TODO: API for setting chart type");
        msg.exec();
        break;
    }
}

void MainWidget::dataChanged(QString itemText)
{
    qDebug() << "dataChanged: " << itemText;
}

void MainWidget::backgroundChanged(int itemIndex)
{
    qDebug() << "backgroundChanged: " << itemIndex;
}

void MainWidget::xMinChanged(int value)
{
    qDebug() << "xMinChanged: " << value;
}

void MainWidget::xMaxChanged(int value)
{
    qDebug() << "xMaxChanged: " << value;
}

void MainWidget::yMinChanged(int value)
{
    qDebug() << "yMinChanged: " << value;
}

void MainWidget::yMaxChanged(int value)
{
    qDebug() << "yMaxChanged: " << value;
}
