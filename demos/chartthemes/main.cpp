#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include <qbarseries.h>
#include <qpercentbarseries.h>
#include <qstackedbarseries.h>
#include <qbarset.h>
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
        int valueCount = 11;
        for (int i(0); i < listCount; i++) {
            DataList dataList;
            for (int j(0); j < valueCount; j++) {
                QPointF value(j + (qreal) rand() / (qreal) RAND_MAX, qrand() % valueMax);
                QString label = "Item " + QString::number(i) + ":" + QString::number(j);
                dataList << Data(value, label);
            }
            m_dataTable << dataList;
        }

        // create layout
        QGridLayout* baseLayout = new QGridLayout();

        // settings layout
        m_themeComboBox = new QComboBox();
        m_themeComboBox->addItem("Default", QChart::ChartThemeDefault);
        m_themeComboBox->addItem("Light", QChart::ChartThemeLight);
        m_themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
        m_themeComboBox->addItem("Dark", QChart::ChartThemeDark);
        m_themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
        m_themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
        m_themeComboBox->addItem("Icy", QChart::ChartThemeIcy);
        m_themeComboBox->addItem("Scientific", QChart::ChartThemeScientific);
        connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this ,SLOT(updateTheme()));
        QCheckBox *antialiasCheckBox = new QCheckBox("Anti aliasing");
        connect(antialiasCheckBox, SIGNAL(toggled(bool)), this ,SLOT(updateAntialiasing(bool)));
        QCheckBox *animatedCheckBox = new QCheckBox("Animated");
        connect(animatedCheckBox, SIGNAL(toggled(bool)), this ,SLOT(updateAnimations(bool)));
        QHBoxLayout *settingsLayout = new QHBoxLayout();
        settingsLayout->addWidget(new QLabel("Theme:"));
        settingsLayout->addWidget(m_themeComboBox);
        settingsLayout->addWidget(antialiasCheckBox);
        settingsLayout->addWidget(animatedCheckBox);
        settingsLayout->addStretch();
        baseLayout->addLayout(settingsLayout, 0, 0, 1, 3);

        // area chart
        QChartView *chart = new QChartView();
        chart->setChartTitle("Area chart");
        baseLayout->addWidget(chart, 1, 0);
        {
            for (int i(0); i < m_dataTable.count(); i++) {
                QLineSeries *series1 = new QLineSeries(chart);
                QLineSeries *series2 = new QLineSeries(chart);
                foreach (Data data, m_dataTable[i]) {
                    series1->add(data.first);
                    series2->add(QPointF(data.first.x(), 0.0));
                }
                QAreaSeries *area = new QAreaSeries(series1, series2);
                chart->addSeries(area);
            }
        }
        m_charts << chart;

        // bar chart
        chart = new QChartView();
        chart->setChartTitle("bar chart");
        baseLayout->addWidget(chart, 1, 1);
        {
            QStringList categories;
            // TODO: categories
            for (int i(0); i < valueCount; i++)
                categories << QString::number(i);
//            QBarSeries* series = new QBarSeries(categories, chart);
//            QPercentBarSeries* series = new QPercentBarSeries(categories, chart);
            QStackedBarSeries* series = new QStackedBarSeries(categories, chart);
            for (int i(0); i < m_dataTable.count(); i++) {
                QBarSet *set = new QBarSet("Set" + QString::number(i));
                foreach (Data data, m_dataTable[i])
                    *set << data.first.y();
                series->addBarSet(set);
            }
            chart->addSeries(series);
        }
        m_charts << chart;

        // line chart
        chart = new QChartView();
        chart->setChartTitle("line chart");
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
        baseLayout->addWidget(chart, 2, 0);
        qreal pieSize = 1.0 / m_dataTable.count();
        for (int i=0; i<m_dataTable.count(); i++) {
            QPieSeries *series = new QPieSeries(chart);
            foreach (Data data, m_dataTable[i]) {
                QPieSlice *slice = series->add(data.first.y(), data.second);
                if (data == m_dataTable[i].first()) {
                    slice->setLabelVisible();
                    slice->setExploded();
                }
            }
            qreal hPos = (pieSize / 2) + (i / (qreal) m_dataTable.count());
            series->setPieSize(pieSize);
            series->setPiePosition(hPos, 0.5);
            chart->addSeries(series);
        }
        m_charts << chart;

        // spine chart
        chart = new QChartView();
        chart->setChartTitle("spline chart");
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

        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    void updateAntialiasing(bool enabled)
    {
        foreach (QChartView *chart, m_charts)
            chart->setRenderHint(QPainter::Antialiasing, enabled);
    }

    void updateAnimations(bool animated)
    {
        QChart::AnimationOptions options = QChart::NoAnimation;
        if (animated)
            options = QChart::AllAnimations;

        foreach (QChartView *chart, m_charts)
            chart->setAnimationOptions(options);
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
