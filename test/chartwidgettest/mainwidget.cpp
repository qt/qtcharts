#include "mainwidget.h"
#include "dataseriedialog.h"
#include "qchartseries.h"
#include "qpieseries.h"
#include <qlinechartseries.h>
#include <qbarset.h>
#include <qbarcategory.h>
#include <barchartseries.h>
#include <stackedbarchartseries.h>
#include <percentbarchartseries.h>
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
    m_chartWidget = new QChartView(this);
    m_chartWidget->setRubberBandPolicy(QChartView::HorizonalRubberBand);

    // Grid layout for the controls for configuring the chart widget
    QGridLayout *grid = new QGridLayout();
    QPushButton *addSeriesButton = new QPushButton("Add series");
    connect(addSeriesButton, SIGNAL(clicked()), this, SLOT(addSeries()));
    grid->addWidget(addSeriesButton, 0, 1);
    initBackroundCombo(grid);
    initScaleControls(grid);
    initThemeCombo(grid);
    QCheckBox *zoomCheckBox = new QCheckBox("Drag'n drop Zoom");
    connect(zoomCheckBox, SIGNAL(toggled(bool)), m_chartWidget, SLOT(setZoomEnabled(bool)));
    zoomCheckBox->setChecked(true);
    grid->addWidget(zoomCheckBox, grid->rowCount(), 0);
    // add row with empty label to make all the other rows static
    grid->addWidget(new QLabel(""), grid->rowCount(), 0);
    grid->setRowStretch(grid->rowCount() - 1, 1);

    // Another grid layout as a main layout
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(grid, 0, 0);

    // Init series type specific controls
    initPieControls();
    mainLayout->addLayout(m_pieLayout, 2, 0);
    // Scatter series specific settings
//    m_scatterLayout = new QGridLayout();
//    m_scatterLayout->addWidget(new QLabel("scatter"), 0, 0);
//    m_scatterLayout->setEnabled(false);
//    mainLayout->addLayout(m_scatterLayout, 1, 0);

    // Add layouts and the chart widget to the main layout
    mainLayout->addWidget(m_chartWidget, 0, 1, 3, 1);
    setLayout(mainLayout);

    // force an update to test data
    testDataChanged(0);
}

// Combo box for selecting the chart's background
void MainWidget::initBackroundCombo(QGridLayout *grid)
{
    QComboBox *backgroundCombo = new QComboBox(this);
    backgroundCombo->addItem("Color");
    backgroundCombo->addItem("Gradient");
    backgroundCombo->addItem("Image");
    connect(backgroundCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(backgroundChanged(int)));

    grid->addWidget(new QLabel("Background:"), grid->rowCount(), 0);
    grid->addWidget(backgroundCombo, grid->rowCount() - 1, 1);
}

// Scale related controls (auto-scale vs. manual min-max values)
void MainWidget::initScaleControls(QGridLayout *grid)
{
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

    grid->addWidget(m_autoScaleCheck, grid->rowCount(), 0);
    grid->addWidget(new QLabel("x min:"), grid->rowCount(), 0);
    grid->addWidget(m_xMinSpin, grid->rowCount() - 1, 1);
    grid->addWidget(new QLabel("x max:"), grid->rowCount(), 0);
    grid->addWidget(m_xMaxSpin, grid->rowCount() - 1, 1);
    grid->addWidget(new QLabel("y min:"), grid->rowCount(), 0);
    grid->addWidget(m_yMinSpin, grid->rowCount() - 1, 1);
    grid->addWidget(new QLabel("y max:"), grid->rowCount(), 0);
    grid->addWidget(m_yMaxSpin, grid->rowCount() - 1, 1);

    m_autoScaleCheck->setChecked(true);
}

// Combo box for selecting theme
void MainWidget::initThemeCombo(QGridLayout *grid)
{
    QComboBox *chartTheme = new QComboBox();
    chartTheme->addItem("Default");
    chartTheme->addItem("Vanilla");
    chartTheme->addItem("Icy");
    chartTheme->addItem("Grayscale");
    chartTheme->addItem("Scientific");
    chartTheme->addItem("Unnamed1");
    connect(chartTheme, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeChartTheme(int)));
    grid->addWidget(new QLabel("Chart theme:"), 8, 0);
    grid->addWidget(chartTheme, 8, 1);
}

void MainWidget::initPieControls()
{
    // Pie series specific settings
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

    QBarSet *set0 = new QBarSet;
    QBarSet *set1 = new QBarSet;
    QBarSet *set2 = new QBarSet;
    QBarSet *set3 = new QBarSet;
    QBarSet *set4 = new QBarSet;

    if (data == "linear") {
        for (int i = 0; i < 20; i++) {
            x.append(i);
            y.append(i);
        }
    } else if (data == "linear, 1M") {
        // 1 million data points from 0.0001 to 100
        // TODO: What is the requirement? Should we be able to show this kind of data with
        // reasonable performance, or can we expect the application developer to do "data mining"
        // for us, so that the count of data points given to QtCommercial Chart is always
        // reasonable?
        for (qreal i = 0; i < 100; i += 0.0001) {
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
    } else if (data == "Table, 5 series"){
         // Create some test data to chart
        *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;
        *set1 << 5 << 0 << 0 << 4 << 0 << 7 << 8 << 9 << 9 << 0 << 4 << 2;
        *set2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 1 << 3 << 5;
        *set3 << 5 << 6 << 7 << 3 << 4 << 5 << 8 << 9 << 10 << 5 << 2 << 7;
        *set4 << 9 << 7 << 5 << 3 << 1 << 2 << 4 << 6 << 8 << 10 << 1 << 6;
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
        QLineChartSeries* series0 = new QLineChartSeries();
        for (int i(0); i < x.count() && i < y.count(); i++)
            series0->add(x.at(i), y.at(i));
        m_chartWidget->addSeries(series0);
        newSeries = series0;
    } else if (series == "Bar") {
        qDebug() << "Bar chart series";

        QBarCategory *category = new QBarCategory;
        *category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

        BarChartSeries* series0 = new BarChartSeries(category, this);

        series0->addBarSet(set0);
        series0->addBarSet(set1);
        series0->addBarSet(set2);
        series0->addBarSet(set3);
        series0->addBarSet(set4);

        m_chartWidget->addSeries(series0);
        newSeries = series0;
    } else if (series == "StackedBar") {
        qDebug() << "Stacked bar chart series";

        QBarCategory *category = new QBarCategory;
        *category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

        StackedBarChartSeries* series0 = new StackedBarChartSeries(category, this);

        series0->addBarSet(set0);
        series0->addBarSet(set1);
        series0->addBarSet(set2);
        series0->addBarSet(set3);
        series0->addBarSet(set4);

        m_chartWidget->addSeries(series0);
        newSeries = series0;
    } else if (series == "PercentBar") {
        qDebug() << "Percent bar chart series";

        QBarCategory *category = new QBarCategory;
        *category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

        PercentBarChartSeries* series0 = new PercentBarChartSeries(category, this);

        series0->addBarSet(set0);
        series0->addBarSet(set1);
        series0->addBarSet(set2);
        series0->addBarSet(set3);
        series0->addBarSet(set4);

        m_chartWidget->addSeries(series0);
        newSeries = series0;
    } else {
        qDebug() << "Something weird going on in MainWidget::addSeries";
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
    case QChartSeries::SeriesTypeStackedBar:
        qDebug() << "setCurrentSeries (Stackedbar)";
        break;
    case QChartSeries::SeriesTypePercentBar:
        qDebug() << "setCurrentSeries (Percentbar)";
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
    m_chartWidget->setChartTheme((QChart::ChartTheme) themeIndex);
    //TODO: remove this hack. This is just to make it so that theme change is seen immediately.
    QSize s = size();
    s.setWidth(s.width()+1);
    resize(s);
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
