#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qstackedbarseries.h>
#include <qbarset.h>
#include <qchartaxis.h>
#include <qlegend.h>
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
class DrilldownChart : public QChartView
{
    Q_OBJECT
public:
    explicit DrilldownChart(QWidget *parent = 0) : QChartView(parent), m_currentSeries(0) {}

    void changeSeries(QSeries* series)
    {
        if (m_currentSeries)
            removeSeries(m_currentSeries);
        m_currentSeries = series;
        addSeries(series);
        setChartTitle(series->title());
    }

public Q_SLOTS:
    void handleRightClick(QBarSet *barset, QString category)
    {
//        qDebug() << "DrilldownChart::handleRightClick" << barset->name() << category;
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

    DrilldownChart* drilldownChart =  new DrilldownChart(&window);
    drilldownChart->setChartTheme(QChart::ChartThemeIcy);

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
    seasonSeries->setTitle("Crop by month - Season");

    // Each month in season series has drilldown series for weekly data
    foreach (QString month, months) {

        // Create drilldown series for every week
        DrilldownBarSeries* weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        seasonSeries->mapDrilldownSeries(month, weeklySeries);

        // Drilling down from weekly data brings us back to season data.
        foreach (QString week, weeks) {
            weeklySeries->mapDrilldownSeries(week, seasonSeries);
            weeklySeries->setTitle(QString("Crop by week - " + month));
        }

        // Use right click signal to implement drilldown
        QObject::connect(weeklySeries,SIGNAL(rightClicked(QBarSet*,QString)),drilldownChart,SLOT(handleRightClick(QBarSet*,QString)));
    }

    // Enable drilldown from season series using right click.
    QObject::connect(seasonSeries,SIGNAL(rightClicked(QBarSet*,QString)),drilldownChart,SLOT(handleRightClick(QBarSet*,QString)));
    //! [4]

    //! [5]
    // Fill monthly and weekly series with data
    foreach (QString plant, plants) {
        QBarSet* monthlyCrop = new QBarSet(plant);
        foreach (QString month, months) {
            QBarSet* weeklyCrop = new QBarSet(plant);
            foreach (QString week, weeks ) {
                *weeklyCrop << (qrand() % 20);
            }
            // Get the drilldown series from season series and add crop to it.
            seasonSeries->drilldownSeries(month)->addBarSet(weeklyCrop);
            seasonSeries->drilldownSeries(month)->setToolTipEnabled(true);
            *monthlyCrop << weeklyCrop->total();

            QObject::connect(weeklyCrop,SIGNAL(clicked(QString)),weeklyCrop,SIGNAL(toggleFloatingValues()));
        }
        seasonSeries->addBarSet(monthlyCrop);
        QObject::connect(monthlyCrop,SIGNAL(clicked(QString)),monthlyCrop,SIGNAL(toggleFloatingValues()));
    }
    //! [5]

    seasonSeries->setToolTipEnabled(true);

    //! [6]
    // Show season series in initial view
    drilldownChart->changeSeries(seasonSeries);
    drilldownChart->setChartTitle(seasonSeries->title());
    //! [6]

    // Disable axis, since they don't really apply to bar chart
//    drilldownChart->axisX()->setAxisVisible(false);
    drilldownChart->axisX()->setGridLineVisible(false);
//    drilldownChart->axisX()->setLabelsVisible(false);

    QLegend* l = drilldownChart->legend();
    l->handleGeometryChanged(QRectF(20,20,100,100));

    window.setCentralWidget(drilldownChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

#include "main.moc"
