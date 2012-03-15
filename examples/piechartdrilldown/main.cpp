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
        label += " " + QString::number(this->value())+ "e (";
        label += QString::number(this->percentage()*100, 'f', 1) + "%)";
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
        // NOTE: if the series is owned by the chart it will be deleted
        // here the "window" owns the series...
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

    QPieSeries* yearSeries = new QPieSeries(&window);
    yearSeries->setTitle("Sales by year - All");

    QList<QString> months;
    months << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    QList<QString> names;
    names << "Jane" << "John" << "Axel" << "Mary" << "Samantha" << "Bob";

    foreach (QString name, names) {
        QPieSeries* series = new QPieSeries(&window);
        series->setTitle("Sales by month - " + name);

        foreach (QString month, months)
            *series << new DrilldownSlice(qrand() % 1000, month, yearSeries);

        QObject::connect(series, SIGNAL(clicked(QPieSlice*)), drilldownChart, SLOT(handleSliceClicked(QPieSlice*)));

        *yearSeries << new DrilldownSlice(series->total(), name, series);
    }

    QObject::connect(yearSeries, SIGNAL(clicked(QPieSlice*)), drilldownChart, SLOT(handleSliceClicked(QPieSlice*)));

    drilldownChart->changeSeries(yearSeries);

    window.setCentralWidget(drilldownChart);
    window.resize(800, 600);
    window.show();

    return a.exec();
}

#include "main.moc"
