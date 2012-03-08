#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QTime>
#include <qlineseries.h>
#include <qsplineseries.h>
#include <qscatterseries.h>
#include <qareaseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = 0)
        :QWidget(parent)
    {
        // set seed for random stuff
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

        // generate random data
        int listCount = 3;
        int valueMax = 100;
        int valueCount = 50;
        for (int i=0; i<listCount; i++) {
            DataList dataList;
            for (int j=0; j<valueCount; j++) {
                QPointF value(qrand() % valueMax, qrand() % valueMax);
                QString label = QString::number(i) + ":" + QString::number(j);
                dataList << Data(value, label);
            }
            m_dataTable << dataList;
        }

        // create layout
        QGridLayout* baseLayout = new QGridLayout();

        // theme combo
        m_themeComboBox = new QComboBox();
        m_themeComboBox->addItem("Default", QChart::ChartThemeDefault);
        m_themeComboBox->addItem("Vanilla", QChart::ChartThemeVanilla);
        m_themeComboBox->addItem("Icy", QChart::ChartThemeIcy);
        m_themeComboBox->addItem("Grayscale", QChart::ChartThemeGrayscale);
        m_themeComboBox->addItem("Scientific", QChart::ChartThemeScientific);
        connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this ,SLOT(updateTheme()));
        baseLayout->addWidget(new QLabel("Theme:"), 0, 0);
        baseLayout->addWidget(m_themeComboBox, 0, 1);

        // area chart
        QChartView *chart = new QChartView();
        chart->setChartTitle("Area chart");
        chart->setRenderHint(QPainter::Antialiasing);
        baseLayout->addWidget(chart, 1, 0);
        {
            QLineSeries *series1 = new QLineSeries(chart);
            foreach (Data data, m_dataTable.first())
                series1->add(data.first);
            QLineSeries *series2 = new QLineSeries(chart);
            foreach (Data data, m_dataTable.last())
                series2->add(data.first);
            QAreaSeries *series = new QAreaSeries(series1, series2);
            chart->addSeries(series);
        }
        m_charts << chart;

        // bar chart
        chart = new QChartView();
        chart->setChartTitle("bar chart");
        chart->setRenderHint(QPainter::Antialiasing);
        baseLayout->addWidget(chart, 1, 1);
        m_charts << chart;

        // line chart
        chart = new QChartView();
        chart->setChartTitle("line chart");
        chart->setRenderHint(QPainter::Antialiasing);
        baseLayout->addWidget(chart, 1, 2);
        foreach (DataList list, m_dataTable) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, list)
                series->add(data.first);
            chart->addSeries(series);
        }
        m_charts << chart;

        // pie chart
        chart = new QChartView();
        chart->setChartTitle("pie chart");
        chart->setRenderHint(QPainter::Antialiasing);
        baseLayout->addWidget(chart, 2, 0);

        qreal pieSize = 1.0 / m_dataTable.count();
        for (int i=0; i<m_dataTable.count(); i++) {
            QPieSeries *series = new QPieSeries(chart);
            foreach (Data data, m_dataTable[i])
                series->add(data.first.x(), data.second);
            qreal hPos = (pieSize / 2) + (i / (qreal) m_dataTable.count());
            series->setPieSize(pieSize);
            series->setPiePosition(hPos, 0.5);
            chart->addSeries(series);
        }
        m_charts << chart;

        // spine chart
        chart = new QChartView();
        chart->setChartTitle("spline chart");
        chart->setRenderHint(QPainter::Antialiasing);
        baseLayout->addWidget(chart, 2, 1);
        foreach (DataList list, m_dataTable) {
            QSplineSeries *series = new QSplineSeries(chart);
            foreach (Data data, list)
                series->add(data.first);
            chart->addSeries(series);
        }
        m_charts << chart;

        // scatter chart
        chart = new QChartView();
        chart->setChartTitle("scatter chart");
        chart->setRenderHint(QPainter::Antialiasing);
        baseLayout->addWidget(chart, 2, 2);
        foreach (DataList list, m_dataTable) {
            QScatterSeries *series = new QScatterSeries(chart);
            foreach (Data data, list)
                series->add(data.first);
            chart->addSeries(series);
        }
        m_charts << chart;

        setLayout(baseLayout);
    }

public Q_SLOTS:

    void updateTheme()
    {
        QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(m_themeComboBox->currentIndex()).toInt();
        foreach (QChartView *chart, m_charts)
            chart->setChartTheme(theme);
    }

private:
    QList<QChartView*> m_charts;
    QComboBox *m_themeComboBox;
    DataTable m_dataTable;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    MainWidget* widget = new MainWidget();

    window.setCentralWidget(widget);
    window.resize(900, 600);
    window.show();

    return a.exec();
}

#include "main.moc"
