#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include <QTime>

QTCOMMERCIALCHART_USE_NAMESPACE

class DrilldownSlice : public QPieSlice
{
    Q_OBJECT

public:
    DrilldownSlice(qreal value, QString prefix, QSeries* drilldownSeries)
        :m_drilldownSeries(drilldownSeries),
        m_prefix(prefix)
    {
        setValue(value);
        setLabelVisible(true);
        updateLabel();
        connect(this, SIGNAL(changed()), this, SLOT(updateLabel()));
    }

    QSeries* drilldownSeries() const { return m_drilldownSeries; }

public Q_SLOTS:
    void updateLabel()
    {
        QString label = m_prefix;
        label += " - " + QString::number(this->value())+ "e (";
        label += QString::number(this->percentage()*100, 'f', 1) + "%)";
        qDebug() << "updateLabel" << label;
        setLabel(label);
    }

private:
    QSeries* m_drilldownSeries;
    QString m_prefix;
};

class DrilldownChart : public QChartView
{
    Q_OBJECT
public:
    explicit DrilldownChart(QWidget *parent = 0):QChartView(parent), m_currentSeries(0) {}

    void changeSeries(QSeries* series)
    {
        if (m_currentSeries)
            removeSeries(m_currentSeries);
        m_currentSeries = series;
        addSeries(series);
        setChartTitle(series->title());
    }

public Q_SLOTS:
    void handleSliceClicked(QPieSlice* slice)
    {
        DrilldownSlice* drilldownSlice = static_cast<DrilldownSlice*>(slice);
        changeSeries(drilldownSlice->drilldownSeries());
    }

private:
    QSeries* m_currentSeries;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QMainWindow window;

    DrilldownChart* drilldownChart =  new DrilldownChart(&window);
    drilldownChart->setRenderHint(QPainter::Antialiasing);
    drilldownChart->setChartTheme(QChart::ChartThemeVanilla);

    QPieSeries* yearSeries = new QPieSeries(drilldownChart);
    yearSeries->setTitle("Sales by year - All");
    yearSeries->setHoverHighlighting();

    QList<QString> months;
    months << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    int max = 1000;

    QPieSeries* monthSeriesJane = new QPieSeries(drilldownChart);
    monthSeriesJane->setTitle("Sales by month - Jane");
    monthSeriesJane->setHoverHighlighting();
    foreach (QString month, months)
        *monthSeriesJane << new DrilldownSlice(qrand() % max, month, yearSeries);

    QPieSeries* monthSeriesJohn = new QPieSeries(drilldownChart);
    monthSeriesJohn->setTitle("Sales by month - John");
    monthSeriesJohn->setHoverHighlighting();
    foreach (QString month, months)
        *monthSeriesJohn << new DrilldownSlice(qrand() % max, month, yearSeries);

    QPieSeries* monthSeriesAxel = new QPieSeries(drilldownChart);
    monthSeriesAxel->setTitle("Sales by month - Axel");
    monthSeriesAxel->setHoverHighlighting();
    foreach (QString month, months)
        *monthSeriesAxel << new DrilldownSlice(qrand() % max, month, yearSeries);

    *yearSeries << new DrilldownSlice(monthSeriesJane->total(), "Jane", monthSeriesJane);
    *yearSeries << new DrilldownSlice(monthSeriesJohn->total(), "John", monthSeriesJohn);
    *yearSeries << new DrilldownSlice(monthSeriesAxel->total(), "Axel", monthSeriesAxel);

    QObject::connect(monthSeriesJane, SIGNAL(clicked(QPieSlice*)), drilldownChart, SLOT(handleSliceClicked(QPieSlice*)));
    QObject::connect(monthSeriesJohn, SIGNAL(clicked(QPieSlice*)), drilldownChart, SLOT(handleSliceClicked(QPieSlice*)));
    QObject::connect(monthSeriesAxel, SIGNAL(clicked(QPieSlice*)), drilldownChart, SLOT(handleSliceClicked(QPieSlice*)));
    QObject::connect(yearSeries, SIGNAL(clicked(QPieSlice*)), drilldownChart, SLOT(handleSliceClicked(QPieSlice*)));

    drilldownChart->changeSeries(yearSeries);

    window.setCentralWidget(drilldownChart);
    window.resize(600, 600);
    window.show();

    return a.exec();
}

#include "main.moc"
