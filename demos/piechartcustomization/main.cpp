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
#include <QPushButton>
#include <QColorDialog>

QTCOMMERCIALCHART_USE_NAMESPACE

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

public:
    QBrush originalBrush()
    {
        return m_originalBrush;
    }

public Q_SLOTS:

    void handleHoverEnter()
    {
        QBrush brush = this->sliceBrush();
        m_originalBrush = brush;
        brush.setColor(brush.color().lighter());
        setSliceBrush(brush);
    }

    void handleHoverLeave()
    {
        setSliceBrush(m_originalBrush);
    }

private:
    QBrush m_originalBrush;
};

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = 0)
        :QWidget(parent),
        m_slice(0)
    {
        // create chart
        m_chartView =  new QChartView();
        m_chartView->setChartTitle("Piechart customization");

        // create series
        m_series = new QPieSeries();
        *m_series << new CustomSlice(10.0, "Slice 1");
        *m_series << new CustomSlice(20.0, "Slice 2");
        *m_series << new CustomSlice(30.0, "Slice 3");
        *m_series << new CustomSlice(40.0, "Slice 4");
        *m_series << new CustomSlice(50.0, "Slice 5");
        m_chartView->addSeries(m_series);

        connect(m_series, SIGNAL(clicked(QPieSlice*)), this, SLOT(handleSliceClicked(QPieSlice*)));

        // chart settings
        m_themeComboBox = new QComboBox();
        m_themeComboBox->addItem("Default", QChart::ChartThemeDefault);
        m_themeComboBox->addItem("Vanilla", QChart::ChartThemeVanilla);
        m_themeComboBox->addItem("Icy", QChart::ChartThemeIcy);
        m_themeComboBox->addItem("Grayscale", QChart::ChartThemeGrayscale);
        m_themeComboBox->addItem("Scientific", QChart::ChartThemeScientific);

        m_aaCheckBox = new QCheckBox();

        QFormLayout* chartSettingsLayout = new QFormLayout();
        chartSettingsLayout->addRow("Theme", m_themeComboBox);
        chartSettingsLayout->addRow("Antialiasing", m_aaCheckBox);
        QGroupBox* chartSettings = new QGroupBox("Chart");
        chartSettings->setLayout(chartSettingsLayout);

        connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this ,SLOT(updateChartSettings()));
        connect(m_aaCheckBox, SIGNAL(toggled(bool)), this ,SLOT(updateChartSettings()));

        // series settings
        m_hPosition = new QDoubleSpinBox();
        m_hPosition->setMinimum(0.0);
        m_hPosition->setMaximum(1.0);
        m_hPosition->setSingleStep(0.1);
        m_hPosition->setValue(m_series->pieHorizontalPosition());

        m_vPosition = new QDoubleSpinBox();
        m_vPosition->setMinimum(0.0);
        m_vPosition->setMaximum(1.0);
        m_vPosition->setSingleStep(0.1);
        m_vPosition->setValue(m_series->pieVerticalPosition());

        m_sizeFactor = new QDoubleSpinBox();
        m_sizeFactor->setMinimum(0.0);
        m_sizeFactor->setMaximum(1.0);
        m_sizeFactor->setSingleStep(0.1);
        m_sizeFactor->setValue(m_series->pieSize());

        m_startAngle = new QDoubleSpinBox();
        m_startAngle->setMinimum(0.0);
        m_startAngle->setMaximum(360);
        m_startAngle->setValue(m_series->pieStartAngle());
        m_startAngle->setSingleStep(1);

        m_endAngle = new QDoubleSpinBox();
        m_endAngle->setMinimum(0.0);
        m_endAngle->setMaximum(360);
        m_endAngle->setValue(m_series->pieEndAngle());
        m_endAngle->setSingleStep(1);

        QFormLayout* seriesSettingsLayout = new QFormLayout();
        seriesSettingsLayout->addRow("Horizontal position", m_hPosition);
        seriesSettingsLayout->addRow("Vertical position", m_vPosition);
        seriesSettingsLayout->addRow("Size factor", m_sizeFactor);
        seriesSettingsLayout->addRow("Start angle", m_startAngle);
        seriesSettingsLayout->addRow("End angle", m_endAngle);
        QGroupBox* seriesSettings = new QGroupBox("Series");
        seriesSettings->setLayout(seriesSettingsLayout);

        connect(m_vPosition, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
        connect(m_hPosition, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
        connect(m_sizeFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
        connect(m_startAngle, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
        connect(m_endAngle, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));

        // slice settings
        m_sliceName = new QLabel("<click a slice>");
        m_sliceValue = new QDoubleSpinBox();
        m_sliceValue->setMaximum(1000);
        m_sliceLabelVisible = new QCheckBox();
        m_sliceLabelArmFactor = new QDoubleSpinBox();
        m_sliceLabelArmFactor->setSingleStep(0.01);
        m_sliceExploded = new QCheckBox();
        m_sliceExplodedFactor = new QDoubleSpinBox();
        m_sliceExplodedFactor->setSingleStep(0.01);
        m_penWidth = new QDoubleSpinBox();
        m_penColor = new QPushButton();
        m_brushColor = new QPushButton();

        QFormLayout* sliceSettingsLayout = new QFormLayout();
        sliceSettingsLayout->addRow("Selected", m_sliceName);
        sliceSettingsLayout->addRow("Value", m_sliceValue);
        sliceSettingsLayout->addRow("Pen color", m_penColor);
        sliceSettingsLayout->addRow("Pen width", m_penWidth);
        sliceSettingsLayout->addRow("Brush color", m_brushColor);
        sliceSettingsLayout->addRow("Label visible", m_sliceLabelVisible);
        sliceSettingsLayout->addRow("Label arm length", m_sliceLabelArmFactor);
        sliceSettingsLayout->addRow("Exploded", m_sliceExploded);
        sliceSettingsLayout->addRow("Explode distance", m_sliceExplodedFactor);


        QGroupBox* sliceSettings = new QGroupBox("Slice");
        sliceSettings->setLayout(sliceSettingsLayout);

        connect(m_sliceValue, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
        connect(m_penColor, SIGNAL(clicked()), this, SLOT(showPenColorDialog()));
        connect(m_penWidth, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
        connect(m_brushColor, SIGNAL(clicked()), this, SLOT(showBrushColorDialog()));
        connect(m_sliceLabelVisible, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
        connect(m_sliceLabelArmFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
        connect(m_sliceExploded, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
        connect(m_sliceExplodedFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));

        // create main layout
        QVBoxLayout *settingsLayout = new QVBoxLayout();
        settingsLayout->addWidget(chartSettings);
        settingsLayout->addWidget(seriesSettings);
        settingsLayout->addWidget(sliceSettings);
        settingsLayout->addStretch();

        QGridLayout* baseLayout = new QGridLayout();
        baseLayout->addLayout(settingsLayout, 0, 0);
        baseLayout->addWidget(m_chartView, 0, 1);
        setLayout(baseLayout);

        updateSerieSettings();
    }

public Q_SLOTS:

    void updateChartSettings()
    {
        QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(m_themeComboBox->currentIndex()).toInt();
        m_chartView->setChartTheme(theme);
        m_chartView->setRenderHint(QPainter::Antialiasing, m_aaCheckBox->isChecked());
    }

    void updateSerieSettings()
    {
        m_series->setPiePosition(m_vPosition->value(), m_hPosition->value());
        m_series->setPieSize(m_sizeFactor->value());
        m_series->setPieStartAngle(m_startAngle->value());
        m_series->setPieEndAngle(m_endAngle->value());
    }

    void updateSliceSettings()
    {
        if (!m_slice)
            return;

        m_slice->setValue(m_sliceValue->value());

        QPen pen = m_slice->slicePen();
        pen.setWidthF(m_penWidth->value());
        m_slice->setSlicePen(pen);

        m_slice->setLabelVisible(m_sliceLabelVisible->isChecked());
        m_slice->setLabelArmLengthFactor(m_sliceLabelArmFactor->value());

        m_slice->setExploded(m_sliceExploded->isChecked());
        m_slice->setExplodeDistanceFactor(m_sliceExplodedFactor->value());
    }

    void handleSliceClicked(QPieSlice* slice)
    {
        m_slice = static_cast<CustomSlice*>(slice);

        m_sliceName->setText(slice->label());

        m_sliceValue->blockSignals(true);
        m_sliceValue->setValue(slice->value());
        m_sliceValue->blockSignals(false);

        m_penColor->setText(m_slice->slicePen().color().name());

        m_sliceValue->blockSignals(true);
        m_penWidth->setValue(slice->slicePen().widthF());
        m_sliceValue->blockSignals(false);

        m_brushColor->setText(m_slice->originalBrush().color().name());

        m_sliceLabelVisible->blockSignals(true);
        m_sliceLabelVisible->setChecked(slice->isLabelVisible());
        m_sliceLabelVisible->blockSignals(false);

        m_sliceLabelArmFactor->blockSignals(true);
        m_sliceLabelArmFactor->setValue(slice->labelArmLengthFactor());
        m_sliceLabelArmFactor->blockSignals(false);

        m_sliceExploded->blockSignals(true);
        m_sliceExploded->setChecked(slice->isExploded());
        m_sliceExploded->blockSignals(false);

        m_sliceExplodedFactor->blockSignals(true);
        m_sliceExplodedFactor->setValue(slice->explodeDistanceFactor());
        m_sliceExplodedFactor->blockSignals(false);
    }

    void showBrushColorDialog()
    {
        if (!m_slice)
            return;

        QColorDialog dialog(m_slice->originalBrush().color());
        dialog.show();
        dialog.exec();

        QBrush brush = m_slice->originalBrush();
        brush.setColor(dialog.currentColor());
        m_slice->setSliceBrush(brush);

        m_brushColor->setText(dialog.currentColor().name());
    }

    void showPenColorDialog()
    {
        if (!m_slice)
            return;

        QColorDialog dialog(m_slice->slicePen().color());
        dialog.show();
        dialog.exec();

        QPen pen = m_slice->slicePen();
        pen.setColor(dialog.currentColor());
        m_slice->setSlicePen(pen);

        m_penColor->setText(dialog.currentColor().name());
    }

private:
    QComboBox *m_themeComboBox;
    QCheckBox *m_aaCheckBox;

    QChartView* m_chartView;
    QPieSeries* m_series;
    CustomSlice* m_slice;

    QDoubleSpinBox* m_hPosition;
    QDoubleSpinBox* m_vPosition;
    QDoubleSpinBox* m_sizeFactor;
    QDoubleSpinBox* m_startAngle;
    QDoubleSpinBox* m_endAngle;

    QLabel* m_sliceName;
    QDoubleSpinBox* m_sliceValue;
    QCheckBox* m_sliceLabelVisible;
    QDoubleSpinBox* m_sliceLabelArmFactor;
    QCheckBox* m_sliceExploded;
    QDoubleSpinBox* m_sliceExplodedFactor;
    QPushButton *m_brushColor;
    QPushButton *m_penColor;
    QDoubleSpinBox* m_penWidth;
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
