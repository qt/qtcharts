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

QTCOMMERCIALCHART_USE_NAMESPACE

Q_DECLARE_METATYPE(QPieSeries::PiePosition)

class CustomSlice : public QPieSlice
{
    Q_OBJECT
public:
    CustomSlice(qreal value, QString label)
        :QPieSlice(value, label)
    {
        connect(this, SIGNAL(hoverEnter()), this, SLOT(handleHoverEnter()));
        connect(this, SIGNAL(hoverLeave()), this, SLOT(handleHoverLeave()));
    }

public Q_SLOTS:

    void handleHoverEnter()
    {
        QBrush brush = this->brush();
        m_originalBrush = brush;
        brush.setColor(brush.color().lighter());
        setBrush(brush);
    }

    void handleHoverLeave()
    {
        setBrush(m_originalBrush);
    }

private:
    QBrush m_originalBrush;
};

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = 0)
        :QWidget(parent)
    {
        m_chartView =  new QChartView();
        m_chartView->setChartTitle("Piechart customization");
        //m_chartView->setRenderHint(QPainter::Antialiasing);

        m_series = new QPieSeries();
        *m_series << new CustomSlice(10.0, "Slice 1");
        *m_series << new CustomSlice(20.0, "Slice 2");
        *m_series << new CustomSlice(30.0, "Slice 3");
        *m_series << new CustomSlice(40.0, "Slice 4");
        *m_series << new CustomSlice(50.0, "Slice 5");
        m_chartView->addSeries(m_series);

        m_vPosition = new QComboBox();
        m_vPosition->addItem("Top", QPieSeries::PiePositionTop);
        m_vPosition->addItem("Bottom", QPieSeries::PiePositionBottom);
        m_vPosition->addItem("Center", QPieSeries::PiePositionVCenter);

        m_hPosition = new QComboBox();
        m_hPosition->addItem("Left", QPieSeries::PiePositionLeft);
        m_hPosition->addItem("Right", QPieSeries::PiePositionRight);
        m_hPosition->addItem("Center", QPieSeries::PiePositionHCenter);

        m_sizePolicy = new QComboBox();
        m_sizePolicy->addItem("Maximized", QPieSeries::PieSizePolicyMaximized);
        m_sizePolicy->addItem("Space for labels", QPieSeries::PieSizePolicyReserveSpaceForLabels);
        m_sizePolicy->addItem("Space for exploding", QPieSeries::PieSizePolicyReserveSpaceForExploding);
        m_sizePolicy->addItem("Space for all", QPieSeries::PieSizePolicyReserveSpaceForAll);

        m_sizeFactor = new QDoubleSpinBox();
        m_sizeFactor->setMinimum(0.0);
        m_sizeFactor->setMaximum(1.0);
        m_sizeFactor->setValue(m_series->sizeFactor());
        m_sizeFactor->setSingleStep(0.1);

        m_startAngle = new QDoubleSpinBox();
        m_startAngle->setMinimum(0.0);
        m_startAngle->setMaximum(360);
        m_startAngle->setValue(m_series->startAngle());
        m_startAngle->setSingleStep(1);

        m_endAngle = new QDoubleSpinBox();
        m_endAngle->setMinimum(0.0);
        m_endAngle->setMaximum(360);
        m_endAngle->setValue(m_series->endAngle());
        m_endAngle->setSingleStep(1);

        QFormLayout* seriesSettingsLayout = new QFormLayout();
        seriesSettingsLayout->addRow("Vertical position", m_vPosition);
        seriesSettingsLayout->addRow("Horizontal position", m_hPosition);
        seriesSettingsLayout->addRow("Size policy", m_sizePolicy);
        seriesSettingsLayout->addRow("Size factor", m_sizeFactor);
        seriesSettingsLayout->addRow("Start angle", m_startAngle);
        seriesSettingsLayout->addRow("End angle", m_endAngle);
        QGroupBox* seriesSettings = new QGroupBox("Series");
        seriesSettings->setLayout(seriesSettingsLayout);

        m_sliceName = new QLabel("<click a slice>");
        m_sliceValue = new QDoubleSpinBox();
        m_sliceValue->setMaximum(1000);
        m_sliceLabelVisible = new QCheckBox();
        m_sliceExploded = new QCheckBox();

        QFormLayout* sliceSettingsLayout = new QFormLayout();
        sliceSettingsLayout->addRow("Selected", m_sliceName);
        sliceSettingsLayout->addRow("Value", m_sliceValue);
        sliceSettingsLayout->addRow("Label visible", m_sliceLabelVisible);
        sliceSettingsLayout->addRow("Exploded", m_sliceExploded);
        QGroupBox* sliceSettings = new QGroupBox("Slice");
        sliceSettings->setLayout(sliceSettingsLayout);

        QGridLayout* baseLayout = new QGridLayout();
        baseLayout->addWidget(seriesSettings, 0, 0);
        baseLayout->addWidget(sliceSettings, 1, 0);
        baseLayout->addWidget(m_chartView, 0, 1, 2, 1);
        setLayout(baseLayout);

        connect(m_vPosition, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSerieSettings()));
        connect(m_hPosition, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSerieSettings()));
        connect(m_sizePolicy, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSerieSettings()));
        connect(m_sizeFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
        connect(m_startAngle, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
        connect(m_endAngle, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));

        connect(m_sliceValue, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
        connect(m_sliceLabelVisible, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
        connect(m_sliceExploded, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));

        connect(m_series, SIGNAL(clicked(QPieSlice*)), this, SLOT(handleSliceClicked(QPieSlice*)));

        updateSerieSettings();
    }

public Q_SLOTS:

    void updateSerieSettings()
    {
        QPieSeries::PiePosition vPos(m_vPosition->itemData(m_vPosition->currentIndex()).toInt());
        QPieSeries::PiePosition hPos(m_hPosition->itemData(m_hPosition->currentIndex()).toInt());
        m_series->setPosition(vPos | hPos);

        QPieSeries::PieSizePolicy policy(m_sizePolicy->itemData(m_sizePolicy->currentIndex()).toInt());
        m_series->setSizePolicy(policy);

        m_series->setSizeFactor(m_sizeFactor->value());

        m_series->setStartAngle(m_startAngle->value());
        m_series->setEndAngle(m_endAngle->value());
    }

    void updateSliceSettings()
    {
        m_slice->setValue(m_sliceValue->value());
        m_slice->setLabelVisible(m_sliceLabelVisible->isChecked());
        m_slice->setExploded(m_sliceExploded->isChecked());
    }

    void handleSliceClicked(QPieSlice* slice)
    {
        m_slice = slice;
        m_sliceName->setText(slice->label());

        m_sliceValue->blockSignals(true);
        m_sliceValue->setValue(slice->value());
        m_sliceValue->blockSignals(false);

        m_sliceLabelVisible->blockSignals(true);
        m_sliceLabelVisible->setChecked(slice->isLabelVisible());
        m_sliceLabelVisible->blockSignals(false);

        m_sliceExploded->blockSignals(true);
        m_sliceExploded->setChecked(slice->isExploded());
        m_sliceExploded->blockSignals(false);
    }

private:
    QChartView* m_chartView;
    QPieSeries* m_series;
    QPieSlice* m_slice;

    QComboBox* m_vPosition;
    QComboBox* m_hPosition;
    QComboBox* m_sizePolicy;
    QDoubleSpinBox* m_sizeFactor;
    QDoubleSpinBox* m_startAngle;
    QDoubleSpinBox* m_endAngle;

    QLabel* m_sliceName;
    QDoubleSpinBox* m_sliceValue;
    QCheckBox* m_sliceLabelVisible;
    QCheckBox* m_sliceExploded;
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
