#include "mainwidget.h"
#include "qchartwidget.h"
//#include <chartwidget.h>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <cmath>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    m_chartWidget = new QChartWidget(this);
//    m_chartWidget->resize(QSize(200,200));
//    m_chartWidget->setColor(Qt::red);
    // Chart type
    // TODO: How about multiple types?
    // Should the type be a property of a graph instead of the chart?
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
    QComboBox *testDataCombo = new QComboBox(this);
    testDataCombo->addItem("linear");
    testDataCombo->addItem("SIN");
    testDataCombo->addItem("SIN + random component");
    testDataCombo->addItem("TODO From file...");
    testDataCombo->addItem("TODO From URL...");
    connect(testDataCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(testDataChanged(int)));

    // Chart background
    QComboBox *backgroundCombo = new QComboBox(this);
    backgroundCombo->addItem("None");
    backgroundCombo->addItem("TODO Grid");
    backgroundCombo->addItem("TODO Image");
    connect(backgroundCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(backgroundChanged(int)));

    // Axis
    // TODO: multiple axes?
    m_autoScaleCheck = new QCheckBox("Automatic scaling");
    connect(m_autoScaleCheck, SIGNAL(stateChanged(int)), this, SLOT(autoScaleChanged(int)));
    // Allow setting also non-sense values (like -2147483648 and 2147483647)
    m_xMinSpin = new QSpinBox();
    m_xMinSpin->setMinimum(INT_MIN);
    m_xMinSpin->setMaximum(INT_MAX);
    m_xMinSpin->setValue(0);
    connect(m_xMinSpin, SIGNAL(valueChanged(int)), this, SLOT(xMinChanged(int)));
    m_xMaxSpin = new QSpinBox();
    m_xMaxSpin->setMinimum(INT_MIN);
    m_xMaxSpin->setMaximum(INT_MAX);
    m_xMaxSpin->setValue(10);
    connect(m_xMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(xMaxChanged(int)));
    m_yMinSpin = new QSpinBox();
    m_yMinSpin->setMinimum(INT_MIN);
    m_yMinSpin->setMaximum(INT_MAX);
    m_yMinSpin->setValue(0);
    connect(m_yMinSpin, SIGNAL(valueChanged(int)), this, SLOT(yMinChanged(int)));
    m_yMaxSpin = new QSpinBox();
    m_yMaxSpin->setMinimum(INT_MIN);
    m_yMaxSpin->setMaximum(INT_MAX);
    m_yMaxSpin->setValue(10);
    connect(m_yMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(yMaxChanged(int)));

    QGridLayout *grid = new QGridLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    grid->addWidget(new QLabel("Chart type:"), 0, 0);
    grid->addWidget(chartTypeCombo, 0, 1);
    grid->addWidget(new QLabel("Data:"), 1, 0);
    grid->addWidget(testDataCombo, 1, 1);
    grid->addWidget(new QLabel("Background:"), 2, 0);
    grid->addWidget(backgroundCombo, 2, 1);
    grid->addWidget(m_autoScaleCheck, 3, 0);
    grid->addWidget(new QLabel("x min:"), 4, 0);
    grid->addWidget(m_xMinSpin, 4, 1);
    grid->addWidget(new QLabel("x max:"), 5, 0);
    grid->addWidget(m_xMaxSpin, 5, 1);
    grid->addWidget(new QLabel("y min:"), 6, 0);
    grid->addWidget(m_yMinSpin, 6, 1);
    grid->addWidget(new QLabel("y max:"), 7, 0);
    grid->addWidget(m_yMaxSpin, 7, 1);
    // add row with empty label to make all the other rows static
    grid->addWidget(new QLabel(""), 8, 0);
    grid->setRowStretch(8, 1);

    hbox->addLayout(grid);
    hbox->addWidget(m_chartWidget);
    hbox->setStretch(1, 1);

    setLayout(hbox);

    m_autoScaleCheck->setChecked(true);
    chartTypeChanged(4);
    testDataChanged(0);
}

void MainWidget::chartTypeChanged(int itemIndex)
{
    // TODO: change chart type
    switch (itemIndex) {
    case 4:
        m_chartWidget->setType(4);
        break;
    default: {
        m_chartWidget->setType(0);
        break;
    }
    }
}

void MainWidget::testDataChanged(int itemIndex)
{
    qDebug() << "testDataChanged: " << itemIndex;

    switch (itemIndex) {
    case 0: {
        QList<QChartDataPoint> data;
        for (int x = 0; x < 20; x++) {
            data.append(QChartDataPoint() << x << x / 2);
        }
        m_chartWidget->setData(data);
        break;
    }
    case 1: {
        QList<QChartDataPoint> data;
        for (int x = 0; x < 100; x++) {
            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100));
        }
        m_chartWidget->setData(data);
        break;
    }
    case 2: {
        QList<QChartDataPoint> data;
        for (int x = 0; x < 1000; x++) {
            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100) + (rand() % 100 * 0.2));
            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100) + (rand() % 100 * 0.2));
            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100) + (rand() % 100 * 0.2));
        }
        m_chartWidget->setData(data);
        break;
    }
    default:
        break;
    }

}

void MainWidget::backgroundChanged(int itemIndex)
{
    qDebug() << "backgroundChanged: " << itemIndex;
}

void MainWidget::autoScaleChanged(int value)
{
    if (value) {
        // TODO: enable auto scaling
    } else {
        // TODO: set scaling manually (and disable auto scaling)
    }

    m_xMinSpin->setEnabled(!value);
    m_xMaxSpin->setEnabled(!value);
    m_yMinSpin->setEnabled(!value);
    m_yMaxSpin->setEnabled(!value);
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
