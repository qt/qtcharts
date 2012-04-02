#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qstackedbarseries.h>
#include <qbarset.h>
#include <qchartaxis.h>
#include <QStringList>
#include <QDebug>

QTCOMMERCIALCHART_USE_NAMESPACE

//! [1]
class DrilldownBarSeries : public QStackedBarSeries
{
    Q_OBJECT
public:
    DrilldownBarSeries(QStringList categories, QObject *parent = 0) : QStackedBarSeries(categories,parent) {}

    void mapDrilldownSeries(QString category, DrilldownBarSeries* drilldownSeries)
    {
        mDrilldownSeries[category] = drilldownSeries;
    }

    DrilldownBarSeries* drilldownSeries(QString category)
    {
        return mDrilldownSeries[category];
    }

public Q_SLOTS:

private:

    QMap<QString, DrilldownBarSeries*> mDrilldownSeries;
};
//! [1]

//! [2]
class DrilldownChart : public QChart
{
    Q_OBJECT
public:
    explicit DrilldownChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0) : QChart(parent, wFlags), m_currentSeries(0) {}

    void changeSeries(QSeries* series)
    {
        if (m_currentSeries)
            removeSeries(m_currentSeries);
        m_currentSeries = series;
        addSeries(series);
        setTitle(series->name());
    }

public Q_SLOTS:
    void handleClicked(QBarSet *barset, QString category, Qt::MouseButtons button)
    {
        Q_UNUSED(barset)
        DrilldownBarSeries* series = static_cast<DrilldownBarSeries*> (sender());
        changeSeries(series->drilldownSeries(category));
    }

private:
    QSeries* m_currentSeries;
};
//! [2]

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    DrilldownChart* drilldownChart =  new DrilldownChart();
    drilldownChart->setTheme(QChart::ChartThemeBlueIcy);
    drilldownChart->setAnimationOptions(QChart::SeriesAnimations);

    //! [3]
    // Define categories
    QStringList months;
    months << "May" << "Jun" << "Jul" << "Aug" << "Sep";
    QStringList weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4";
    QStringList plants;
    plants << "Habanero" << "Lemon Drop" << "Starfish" << "Aji Amarillo";
    //! [3]

    //! [4]
    // Create drilldown structure
    DrilldownBarSeries* seasonSeries = new DrilldownBarSeries(months, drilldownChart);
    seasonSeries->setName("Crop by month - Season");

    // Each month in season series has drilldown series for weekly data
    foreach (QString month, months) {

        // Create drilldown series for every week
        DrilldownBarSeries* weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        seasonSeries->mapDrilldownSeries(month, weeklySeries);

        // Drilling down from weekly data brings us back to season data.
        foreach (QString week, weeks) {
            weeklySeries->mapDrilldownSeries(week, seasonSeries);
            weeklySeries->setName(QString("Crop by week - " + month));
        }

        // Use right click signal to implement drilldown
        QObject::connect(weeklySeries, SIGNAL(clicked(QBarSet*,QString,Qt::MouseButtons)), drilldownChart, SLOT(handleClicked(QBarSet*,QString,Qt::MouseButtons)));
    }

    // Enable drilldown from season series using right click.
    QObject::connect(seasonSeries, SIGNAL(clicked(QBarSet*,QString,Qt::MouseButtons)), drilldownChart, SLOT(handleClicked(QBarSet*,QString,Qt::MouseButtons)));
    //! [4]

    //! [5]
    // Fill monthly and weekly series with data
    foreach (QString plant, plants) {
        QBarSet* monthlyCrop = new QBarSet(plant);
        foreach (QString month, months) {
            QBarSet* weeklyCrop = new QBarSet(plant);
            foreach (QString week, weeks )
                *weeklyCrop << (qrand() % 20);
            // Get the drilldown series from season series and add crop to it.
            seasonSeries->drilldownSeries(month)->appendBarSet(weeklyCrop);
            seasonSeries->drilldownSeries(month)->setToolTipEnabled(true);
            *monthlyCrop << weeklyCrop->total();
        }
        seasonSeries->appendBarSet(monthlyCrop);
    }
    //! [5]

    seasonSeries->setToolTipEnabled(true);

    //! [6]
    // Show season series in initial view
    drilldownChart->changeSeries(seasonSeries);
    drilldownChart->setTitle(seasonSeries->name());
    //! [6]

    drilldownChart->axisX()->setGridLineVisible(false);

    QChartView *chartView = new QChartView(drilldownChart);
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

#include "main.moc"
