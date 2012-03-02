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
    DrilldownBarSeries(QStringList categories, QObject* parent = 0) : QStackedBarSeries(categories,parent) {}


public Q_SLOTS:
    void handleRightClick(QBarSet *barset, QString category)
    {
        qDebug() << "DrilldownBarSeries::handleRightClick" << barset->name() << category;
//        mChart->changeSeries(this);
    }

};
//! [1]

//! [2]
class DrilldownBarSet : public QBarSet
{
    Q_OBJECT
public:
    DrilldownBarSet(QString name, DrilldownBarSeries* drilldownSeries) : QBarSet(name) , mSeries(drilldownSeries) {}

    DrilldownBarSeries* drilldownSeries(QString category)
        {
        return mSeries;
        }

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
    void  handleRightClick(QBarSet *barset, QString category)
    {
        qDebug() << "DrilldownChart::handleRightClick" << barset->name() << category;
        // TODO: continue from here
        DrilldownBarSet* drilldownBarSet = static_cast<DrilldownBarSet*>(barset);
        changeSeries(drilldownBarSet->drilldownSeries(category));
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

    //! [4]
    // Define categories
    QStringList months;
    months << "Jun" << "Jul" << "Aug" << "Sep";
    QStringList weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4";
    QStringList plants;
    plants << "Habanero" << "Lemon Drop" << "Starfish" << "Aji Amarillo";
    //! [4]

    DrilldownBarSeries* monthlySeries = new DrilldownBarSeries(months, drilldownChart);
    monthlySeries->setTitle("Crop by month - Season");

    foreach (QString plant, plants) {
        DrilldownBarSeries* weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        DrilldownBarSet* monthlyCrop = new DrilldownBarSet(plant,weeklySeries);
        weeklySeries->setTitle("Crop by week - Month");

        foreach(QString month, months) {
            DrilldownBarSet* weeklyCrop = new DrilldownBarSet(plant,monthlySeries);

            foreach (QString week, weeks ) {
                *weeklyCrop << (qrand() % 20);
            }

            weeklySeries->addBarSet(weeklyCrop);
            weeklySeries->setToolTipEnabled(true);
            *monthlyCrop << weeklyCrop->total();

            QObject::connect(weeklyCrop,SIGNAL(clicked(QString)),weeklyCrop,SIGNAL(toggleFloatingValues()));
            QObject::connect(weeklySeries,SIGNAL(rightClicked(QBarSet*,QString)),drilldownChart,SLOT(handleRightClick(QBarSet*,QString)));
        }

        QObject::connect(monthlyCrop,SIGNAL(clicked(QString)),monthlyCrop,SIGNAL(toggleFloatingValues()));
        monthlySeries->addBarSet(monthlyCrop);
    }

/*
    foreach (QString plant, plants) {
        DrilldownBarSeries* weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        DrilldownBarSet* monthlyCrop = new DrilldownBarSet(plant,weeklySeries);
        weeklySeries->setTitle("Crop by week - Month");
        foreach(QString month, months) {
            DrilldownBarSet* weeklyCrop = new DrilldownBarSet(plant,monthlySeries);
            foreach (QString week, weeks ) {
                *weeklyCrop << (qrand() % 20);
            }
            weeklySeries->addBarSet(weeklyCrop);
            weeklySeries->setToolTipEnabled(true);
            *monthlyCrop << weeklyCrop->total();
            QObject::connect(weeklyCrop,SIGNAL(clicked(QString)),weeklyCrop,SIGNAL(toggleFloatingValues()));
            QObject::connect(weeklySeries,SIGNAL(rightClicked(QBarSet*,QString)),drilldownChart,SLOT(handleRightClick(QBarSet*,QString)));
        }
        QObject::connect(monthlyCrop,SIGNAL(clicked(QString)),monthlyCrop,SIGNAL(toggleFloatingValues()));
        monthlySeries->addBarSet(monthlyCrop);
    }
*/
    QObject::connect(monthlySeries,SIGNAL(rightClicked(QBarSet*,QString)),drilldownChart,SLOT(handleRightClick(QBarSet*,QString)));

    monthlySeries->setToolTipEnabled(true);
    drilldownChart->changeSeries(monthlySeries);
    drilldownChart->setChartTitle(monthlySeries->title());

    drilldownChart->axisX()->setAxisVisible(false);
    drilldownChart->axisX()->setGridVisible(false);
    drilldownChart->axisX()->setLabelsVisible(false);

    window.setCentralWidget(drilldownChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

#include "main.moc"
