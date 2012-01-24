#include "mainwidget.h"
#include "dataseriedialog.h"
#include "qchartseries.h"
#include "qpieseries.h"
#include <qxychartseries.h>
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

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    QPushButton *addSeriesButton = new QPushButton("Add series");
    connect(addSeriesButton, SIGNAL(clicked()), this, SLOT(addSeries()));

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
    QGridLayout *mainLayout = new QGridLayout();
    //grid->addWidget(new QLabel("Add series:"), 0, 0);
    grid->addWidget(addSeriesButton, 0, 1);
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

    mainLayout->addLayout(grid, 0, 0);

    // Scatter specific settings
    m_scatterLayout = new QGridLayout();
    m_scatterLayout->addWidget(new QLabel("scatter"), 0, 0);
    m_scatterLayout->setEnabled(false);

    // Pie specific settings
    m_pieLayout = new QGridLayout();
    m_pieLayout->addWidget(new QLabel("Pie size factor"), 0, 0);
    QDoubleSpinBox *pieSizeSpin = new QDoubleSpinBox();
    pieSizeSpin->setMinimum(LONG_MIN);
    pieSizeSpin->setMaximum(LONG_MAX);
    pieSizeSpin->setValue(1.0);
    pieSizeSpin->setSingleStep(0.1);
    connect(pieSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(setPieSizeFactor(double)));
    m_pieLayout->setEnabled(false);
    m_pieLayout->addWidget(pieSizeSpin, 0, 1);

    mainLayout->addLayout(m_scatterLayout, 1, 0);
    mainLayout->addLayout(m_pieLayout, 2, 0);

    m_chartWidget = new QChartWidget(this);
    //m_chartWidget->setColor(Qt::red);
    mainLayout->addWidget(m_chartWidget, 0, 1, 3, 1);
//    hbox->setStretch(1, 1);

    setLayout(mainLayout);

    m_autoScaleCheck->setChecked(true);
    testDataChanged(0);
}

void MainWidget::addSeries()
{
    DataSerieDialog dialog(m_defaultSeriesName, this);
    connect(&dialog, SIGNAL(accepted(QString, QString)), this, SLOT(addSeries(QString, QString)));
    dialog.exec();
}

void MainWidget::addSeries(QString series, QString data)
{
    qDebug() << "addSeries: " << series << " data: " << data;
    m_defaultSeriesName = series;
    QChartSeries *newSeries = QXYChartSeries::create();

    // TODO: a dedicated data class for storing x and y values
    QList<qreal> x;
    QList<qreal> y;

    if (data == "linear") {
        for (int i = 0; i < 20; i++) {
            x.append(i);
            y.append(i);
        }
        for (int i = 0; i < 20; i++)
            ((QXYChartSeries *)newSeries)->add(i, i);
    } else if (data == "linear, 1M") {
        for (int i = 0; i < 10000; i++) {
            x.append(i);
            y.append(20);
        }
        for (int i = 0; i < 1000000; i++)
            ((QXYChartSeries *)newSeries)->add(i, 10);
    } else if (data == "SIN") {
        for (int i = 0; i < 100; i++) {
            x.append(i);
            y.append(abs(sin(3.14159265358979 / 50 * i) * 100));
        }
        for (int i = 0; i < 100; i++)
            ((QXYChartSeries *)newSeries)->add(i, abs(sin(3.14159265358979 / 50 * i) * 100));
    } else if (data == "SIN + random") {
        for (qreal i = 0; i < 100; i += 0.1) {
            x.append(i + (rand() % 5));
            y.append(abs(sin(3.14159265358979 / 50 * i) * 100) + (rand() % 5));
        }
        for (qreal i = 0; i < 100; i += 0.1)
            ((QXYChartSeries *)newSeries)->add(i + (rand() % 5), abs(sin(3.14159265358979 / 50 * i) * 100) + (rand() % 5));
    } else {
        // TODO: check if data has a valid file name
    }

    // TODO: color of the series
    if (series == "Scatter") {
        newSeries = m_chartWidget->createSeries(x, y, QChartSeries::SeriesTypeScatter);
    } else if (series == "Pie") {
        newSeries = m_chartWidget->createSeries(x, y, QChartSeries::SeriesTypePie);
    } else if (series == "Line") {
        m_chartWidget->addSeries(newSeries);
    } else {
        // TODO
    }

    setCurrentSeries(newSeries);
}

void MainWidget::setCurrentSeries(QChartSeries *series)
{
    m_currentSeries = series;
    switch (m_currentSeries->type()) {
    case QChartSeries::SeriesTypeLine:
        break;
    case QChartSeries::SeriesTypeScatter:
        break;
    case QChartSeries::SeriesTypePie:
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}

void MainWidget::testDataChanged(int itemIndex)
{
    qDebug() << "testDataChanged: " << itemIndex;

//    switch (itemIndex) {
//    case 0: {
//        QList<QChartDataPoint> data;
//        for (int x = 0; x < 20; x++) {
//            data.append(QChartDataPoint() << x << x / 2);
//        }
//        m_chartWidget->setData(data);
//        break;
//    }
//    case 1: {
//        QList<QChartDataPoint> data;
//        for (int x = 0; x < 100; x++) {
//            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100));
//        }
//        m_chartWidget->setData(data);
//        break;
//    }
//    case 2: {
//        QList<QChartDataPoint> data;
//        for (int x = 0; x < 1000; x++) {
//            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100) + (rand() % 100 * 0.2));
//            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100) + (rand() % 100 * 0.2));
//            data.append(QChartDataPoint() << x - 200 << 2 * (uint(sin(3.14159/50*x)*80) % 100) + (rand() % 100 * 0.2));
//        }
//        m_chartWidget->setData(data);
//        break;
//    }
//    default:
//        break;
//    }
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

void MainWidget::setPieSizeFactor(double size)
{
    QPieSeries *pie = qobject_cast<QPieSeries *>(m_currentSeries);
    Q_ASSERT(pie);
    pie->setSizeFactor(qreal(size));
}
