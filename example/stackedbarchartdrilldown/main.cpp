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
    DrilldownBarSeries(QStringList categories, QObject* parent=0) : QStackedBarSeries(categories,parent) {}

/*
public Q_SLOTS:
    void handleRightClick(QBarSet *barset, QString category)
    {
    }
*/
};
//! [1]

//! [2]
class DrilldownBarSet : public QBarSet
{
    Q_OBJECT
public:
    DrilldownBarSet(QString name, DrilldownBarSeries *parent) : QBarSet(name, parent), mSeries(parent) {}

    DrilldownBarSeries* drilldownSeries() { return mSeries; }

private:
    DrilldownBarSeries* mSeries;
};
//! [2]

//! [3]
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
    void handleRightClick(QBarSet* barset, QString category)
    {
        qDebug() << "DrilldownChart::handleRightClick" << barset->name() << category;
        // TODO: continue from here
//        DrilldownBarSet* drilldownBarSet = static_cast<DrilldownBarSet*>(barset);
//        changeSeries(drilldownBarSet->drilldownSeries());
    }

private:
    QSeries* m_currentSeries;
};
//! [3]


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    DrilldownChart* drilldownChart =  new DrilldownChart(&window);
    drilldownChart->setChartTheme(QChart::ChartThemeIcy);

    //! [1]
    // Define categories
    QStringList months;
    months << "Jun" << "Jul" << "Aug" << "Oct";
    QStringList weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4";
    QStringList plants;
    plants << "Habanero" << "Lemon Drop" << "Starfish" << "Aji Amarillo";
    //! [1]

    DrilldownBarSeries* seasonSeries = new DrilldownBarSeries(months, drilldownChart);
    seasonSeries->setTitle("Crop by month - Season");

    foreach (QString plant, plants) {
        DrilldownBarSet *seasonCrop = new DrilldownBarSet(plant, seasonSeries);
        foreach(QString month, months) {
            DrilldownBarSeries* monthSeries = new DrilldownBarSeries(weeks, drilldownChart);
            DrilldownBarSet *monthCrop = new DrilldownBarSet(plant, monthSeries);
            foreach(QString week, weeks) {
                *monthCrop << (qrand() % 20);
            }
            monthSeries->addBarSet(monthCrop);
            *seasonCrop << monthCrop->valueAt(plants.indexOf(plant));
        }

        // We want floating values!
        QObject::connect(seasonCrop,SIGNAL(clicked(QString)),seasonCrop,SIGNAL(toggleFloatingValues()));
        seasonSeries->addBarSet(seasonCrop);
    }

    QObject::connect(seasonSeries,SIGNAL(rightClicked(QBarSet*,QString)),drilldownChart,SLOT(handleRightClick(QBarSet*,QString)));

    seasonSeries->setToolTipEnabled(true);

    drilldownChart->addSeries(seasonSeries);

    drilldownChart->axisX()->setAxisVisible(false);
    drilldownChart->axisX()->setGridVisible(false);
    drilldownChart->axisX()->setLabelsVisible(false);

    window.setCentralWidget(drilldownChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

#include "main.moc"
