#include "mainwidget.h"
#include "dataseriedialog.h"
#include "qpieseries.h"
#include "qscatterseries.h"
#include <qlineseries.h>
#include <qbarset.h>
#include <qbarseries.h>
#include <qstackedbarseries.h>
#include <qpercentbarseries.h>
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
    QWidget(parent),
    m_addSerieDialog(0),
    m_chartWidget(0)
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
    if (!m_addSerieDialog) {
        m_addSerieDialog = new DataSerieDialog(this);
        connect(m_addSerieDialog, SIGNAL(accepted(QString, int, int, QString, bool)),
                this, SLOT(addSeries(QString, int, int, QString, bool)));
    }
    m_addSerieDialog->exec();
}

QList<RealList> MainWidget::generateTestData(int columnCount, int rowCount, QString dataCharacteristics)
{
    // TODO: dataCharacteristics
    QList<RealList> testData;
    for (int j(0); j < columnCount; j++) {
        QList <qreal> newColumn;
        for (int i(0); i < rowCount; i++) {
            if (dataCharacteristics == "Sin") {
                newColumn.append(abs(sin(3.14159265358979 / 50 * i) * 100));
            } else if (dataCharacteristics == "Sin + random") {
                newColumn.append(abs(sin(3.14159265358979 / 50 * i) * 100) + (rand() % 5));
            } else if (dataCharacteristics == "Random") {
                newColumn.append(rand() % 5);
            } else if (dataCharacteristics == "Linear") {
                //newColumn.append(i * (j + 1.0));
                // TODO: temporary hack to make pie work; prevent zero values:
                newColumn.append(i * (j + 1.0) + 0.1);
            } else { // "constant"
                newColumn.append((j + 1.0));
            }
        }
        testData.append(newColumn);
    }
    return testData;
}

QStringList MainWidget::generateLabels(int count)
{
    QStringList result;
    for (int i(0); i < count; i++)
        result.append("label" + QString::number(i));
    return result;
}

void MainWidget::addSeries(QString seriesName, int columnCount, int rowCount, QString dataCharacteristics, bool labelsEnabled)
{
    qDebug() << "addSeries: " << seriesName
             << " columnCount: " << columnCount
             << " rowCount: " << rowCount
             << " dataCharacteristics: " << dataCharacteristics
             << " labels enabled: " << labelsEnabled;
    m_defaultSeriesName = seriesName;

    QList<RealList> data = generateTestData(columnCount, rowCount, dataCharacteristics);

    // Line series and scatter series use similar data
    if (seriesName.contains("line", Qt::CaseInsensitive)) {
        for (int j(0); j < data.count(); j ++) {
            QList<qreal> column = data.at(j);
            QLineSeries *series = new QLineSeries();
            for (int i(0); i < column.count(); i++) {
                series->add(i, column.at(i));
            }
            m_chartWidget->addSeries(series);
            setCurrentSeries(series);
        }
    } else if (seriesName.contains("scatter", Qt::CaseInsensitive)) {
        for (int j(0); j < data.count(); j++) {
            QList<qreal> column = data.at(j);
            QScatterSeries *series = new QScatterSeries();
            for (int i(0); i < column.count(); i++) {
               (*series) << QPointF(i, column.at(i));
            }
            m_chartWidget->addSeries(series);
            setCurrentSeries(series);
        }
    } else if (seriesName.contains("pie", Qt::CaseInsensitive)) {
        QStringList labels = generateLabels(rowCount);
        for (int j(0); j < data.count(); j++) {
            QPieSeries *series = new QPieSeries();
            QList<qreal> column = data.at(j);
            for (int i(0); i < column.count(); i++) {
                series->add(column.at(i), labels.at(i));
            }
            m_chartWidget->addSeries(series);
            setCurrentSeries(series);
        }
    } else if (seriesName == "Bar"
               || seriesName == "Stacked bar"
               || seriesName == "Percent bar") {
        QStringList category;
        QStringList labels = generateLabels(rowCount);
        foreach(QString label, labels)
            category << label;
        QBarSeries* series = 0;
        if (seriesName == "Bar")
            series = new QBarSeries(category, this);
        else if (seriesName == "Stacked bar")
            series = new QStackedBarSeries(category, this);
        else
            series = new QPercentBarSeries(category, this);

        for (int j(0); j < data.count(); j++) {
            QList<qreal> column = data.at(j);
            QBarSet *set = new QBarSet("set" + QString::number(j));
            for (int i(0); i < column.count(); i++) {
                *set << column.at(i);
            }
            series->addBarSet(set);
        }
        series->setFloatingValuesEnabled(true);
        series->setToolTipEnabled(true);
        series->setSeparatorsEnabled(false);
        m_chartWidget->addSeries(series);
        setCurrentSeries(series);
    }

    // TODO: spline and area
}

void MainWidget::setCurrentSeries(QSeries *series)
{
    if (series) {
        m_currentSeries = series;
        switch (m_currentSeries->type()) {
        case QSeries::SeriesTypeLine:
            break;
        case QSeries::SeriesTypeScatter:
            break;
        case QSeries::SeriesTypePie:
            break;
        case QSeries::SeriesTypeBar:
            qDebug() << "setCurrentSeries (bar)";
            break;
        case QSeries::SeriesTypeStackedBar:
            qDebug() << "setCurrentSeries (Stackedbar)";
            break;
        case QSeries::SeriesTypePercentBar:
            qDebug() << "setCurrentSeries (Percentbar)";
            break;
        default:
            Q_ASSERT(false);
            break;
        }
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
