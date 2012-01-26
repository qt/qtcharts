#include "mainwidget.h"
#include "dataseriedialog.h"
#include "qchartseries.h"
#include "qpieseries.h"
#include <qxychartseries.h>
#include <barchartseries.h>
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
#include <QStandardItemModel>


QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    m_chartWidget = new QChartWidget(this);

    QPushButton *addSeriesButton = new QPushButton("Add series");
    connect(addSeriesButton, SIGNAL(clicked()), this, SLOT(addSeries()));

    // Chart background
    QComboBox *backgroundCombo = new QComboBox(this);
    backgroundCombo->addItem("Color");
    backgroundCombo->addItem("Gradient");
    backgroundCombo->addItem("Image");
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

    QComboBox *chartTheme = new QComboBox();
    chartTheme->addItem("Vanilla");
    chartTheme->addItem("Icy");
    chartTheme->addItem("Grayscale");
    chartTheme->addItem("Unnamed1");
    connect(chartTheme, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeChartTheme(int)));

    QCheckBox *zoomCheckBox = new QCheckBox("Zoom enabled");
    connect(zoomCheckBox, SIGNAL(toggled(bool)), m_chartWidget, SLOT(setZoomEnabled(bool)));
    zoomCheckBox->setChecked(true);

    QGridLayout *grid = new QGridLayout();
    QGridLayout *mainLayout = new QGridLayout();
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
    grid->addWidget(new QLabel("Chart theme:"), 8, 0);
    grid->addWidget(chartTheme, 8, 1);
    grid->addWidget(zoomCheckBox, 9, 0);
    // add row with empty label to make all the other rows static
    grid->addWidget(new QLabel(""), 10, 0);
    grid->setRowStretch(10, 1);

    mainLayout->addLayout(grid, 0, 0);

    // Scatter specific settings
    m_scatterLayout = new QGridLayout();
    m_scatterLayout->addWidget(new QLabel("scatter"), 0, 0);
    m_scatterLayout->setEnabled(false);

    // Pie specific settings
    // Pie size factory
    QDoubleSpinBox *pieSizeSpin = new QDoubleSpinBox();
    pieSizeSpin->setMinimum(LONG_MIN);
    pieSizeSpin->setMaximum(LONG_MAX);
    pieSizeSpin->setValue(1.0);
    pieSizeSpin->setSingleStep(0.1);
    connect(pieSizeSpin, SIGNAL(valueChanged(double)), this, SLOT(setPieSizeFactor(double)));
    // Pie position
    QComboBox *piePosCombo = new QComboBox(this);
    piePosCombo->addItem("Maximized");
    piePosCombo->addItem("Top left");
    piePosCombo->addItem("Top right");
    piePosCombo->addItem("Bottom left");
    piePosCombo->addItem("Bottom right");
    connect(piePosCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setPiePosition(int)));
    m_pieLayout = new QGridLayout();
    m_pieLayout->setEnabled(false);
    m_pieLayout->addWidget(new QLabel("Pie size factor"), 0, 0);
    m_pieLayout->addWidget(pieSizeSpin, 0, 1);
    m_pieLayout->addWidget(new QLabel("Pie position"), 1, 0);
    m_pieLayout->addWidget(piePosCombo, 1, 1);

    mainLayout->addLayout(m_scatterLayout, 1, 0);
    mainLayout->addLayout(m_pieLayout, 2, 0);

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

    // TODO: a dedicated data class for storing x and y values
    QList<qreal> x;
    QList<qreal> y;

    if (data == "linear") {
        for (int i = 0; i < 20; i++) {
            x.append(i);
            y.append(i);
        }
    } else if (data == "linear, 1M") {
        for (int i = 0; i < 10000; i++) {
            x.append(i);
            y.append(20);
        }
    } else if (data == "SIN") {
        for (int i = 0; i < 100; i++) {
            x.append(i);
            y.append(abs(sin(3.14159265358979 / 50 * i) * 100));
        }
    } else if (data == "SIN + random") {
        for (qreal i = 0; i < 100; i += 0.1) {
            x.append(i + (rand() % 5));
            y.append(abs(sin(3.14159265358979 / 50 * i) * 100) + (rand() % 5));
        }
    } else {
        // TODO: check if data has a valid file name
        Q_ASSERT(false);
    }

    // TODO: color of the series
    QChartSeries *newSeries = 0;
    if (series == "Scatter") {
        newSeries = m_chartWidget->createSeries(QChartSeries::SeriesTypeScatter);
        Q_ASSERT(newSeries->setData(x, y));
    } else if (series == "Pie") {
        newSeries = m_chartWidget->createSeries(QChartSeries::SeriesTypePie);
        Q_ASSERT(newSeries->setData(y));
    } else if (series == "Line") {
        // TODO: adding data to an existing line series does not give any visuals for some reason
//        newSeries = m_chartWidget->createSeries(QChartSeries::SeriesTypeLine);
//        QXYChartSeries *lineSeries = static_cast<QXYChartSeries *>(newSeries);
//        lineSeries->setColor(Qt::blue);
//        for (int i(0); i < x.count() && i < y.count(); i++) {
//            lineSeries->add(x.at(i), y.at(i));
//        }
        //Q_ASSERT(newSeries->setData(x, y));
        QXYChartSeries* series0 = QXYChartSeries::create();
        for (int i(0); i < x.count() && i < y.count(); i++)
            series0->add(x.at(i), y.at(i));
        m_chartWidget->addSeries(series0);
        newSeries = series0;
    } else {
        // TODO
    }

    // BarChart
    if (series == "Bar") {
        // This is the another way of creating series. Should we create test cases for both ways, if we support them?
        qDebug() << "Bar chart series";
        newSeries = QChartSeries::create(QChartSeries::SeriesTypeBar, this);

        // Create some test data to chart
        QStandardItemModel dataModel(2,10,this);
        QModelIndex index;
        index = dataModel.index(0,0);
        // Series 1, items 6 to 9 missing.
        dataModel.setData(dataModel.index(0,0),1);
        dataModel.setData(dataModel.index(0,1),12);
        dataModel.setData(dataModel.index(0,2),5);
        dataModel.setData(dataModel.index(0,3),8);
        dataModel.setData(dataModel.index(0,4),17);
        dataModel.setData(dataModel.index(0,5),9);

        // Series 2, some other items missing
        dataModel.setData(dataModel.index(1,0),5);
        dataModel.setData(dataModel.index(1,3),4);
        dataModel.setData(dataModel.index(1,5),7);
        dataModel.setData(dataModel.index(1,6),8);
        dataModel.setData(dataModel.index(1,8),9);
        dataModel.setData(dataModel.index(1,9),9);

        newSeries->setData(&dataModel);

        m_chartWidget->addSeries(newSeries);
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
    case QChartSeries::SeriesTypeBar:
        qDebug() << "setCurrentSeries (bar)";
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

void MainWidget::changeChartTheme(int themeIndex)
{
    qDebug() << "changeChartTheme: " << themeIndex;
    m_chartWidget->setTheme((QChart::ChartThemeId) themeIndex);
}

void MainWidget::setPieSizeFactor(double size)
{
    QPieSeries *pie = qobject_cast<QPieSeries *>(m_currentSeries);
    if (pie)
        pie->setSizeFactor(qreal(size));
}

void MainWidget::setPiePosition(int position)
{
    QPieSeries *pie = qobject_cast<QPieSeries *>(m_currentSeries);
    if (pie)
        pie->setPosition((QPieSeries::PiePosition) position);
}
