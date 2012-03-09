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
#include <QFontDialog>

QTCOMMERCIALCHART_USE_NAMESPACE

class PenTool : public QWidget
{
    Q_OBJECT

public:
    explicit PenTool(QString title, QWidget *parent = 0)
        :QWidget(parent)
    {
        setWindowTitle(title);
        setWindowFlags(Qt::Tool);

        m_colorButton = new QPushButton();
        m_widthSpinBox = new QDoubleSpinBox();

        QFormLayout *layout = new QFormLayout();
        layout->addRow("Color", m_colorButton);
        layout->addRow("Width", m_widthSpinBox);
        setLayout(layout);

        connect(m_colorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));
        connect(m_widthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateWidth(double)));
    }

    void setPen(QPen pen)
    {
        m_pen = pen;
        m_colorButton->setText(m_pen.color().name());
        m_widthSpinBox->setValue(m_pen.widthF());
    }

    QPen pen() const
    {
        return m_pen;
    }

    QString name()
    {
        return name(m_pen);
    }

    static QString name(const QPen &pen)
    {
        return pen.color().name() + ":" + QString::number(pen.widthF());
    }

Q_SIGNALS:
    void changed();

public Q_SLOTS:

    void showColorDialog()
    {
        QColorDialog dialog(m_pen.color());
        dialog.show();
        dialog.exec();
        m_pen.setColor(dialog.selectedColor());
        m_colorButton->setText(m_pen.color().name());
        emit changed();
    }

    void updateWidth(double width)
    {
        if (width != m_pen.widthF()) {
            m_pen.setWidthF(width);
            emit changed();
        }
    }

private:
    QPen m_pen;
    QPushButton *m_colorButton;
    QDoubleSpinBox *m_widthSpinBox;
};

class BrushTool : public QWidget
{
    Q_OBJECT

public:
    explicit BrushTool(QString title, QWidget *parent = 0)
        :QWidget(parent)
    {
        setWindowTitle(title);
        setWindowFlags(Qt::Tool);

        m_colorButton = new QPushButton();
        m_styleCombo = new QComboBox();
        m_styleCombo->addItem("Nobrush", Qt::NoBrush);
        m_styleCombo->addItem("Solidpattern", Qt::SolidPattern);
        m_styleCombo->addItem("Dense1pattern", Qt::Dense1Pattern);
        m_styleCombo->addItem("Dense2attern", Qt::Dense2Pattern);
        m_styleCombo->addItem("Dense3Pattern", Qt::Dense3Pattern);
        m_styleCombo->addItem("Dense4Pattern", Qt::Dense4Pattern);
        m_styleCombo->addItem("Dense5Pattern", Qt::Dense5Pattern);
        m_styleCombo->addItem("Dense6Pattern", Qt::Dense6Pattern);
        m_styleCombo->addItem("Dense7Pattern", Qt::Dense7Pattern);
        m_styleCombo->addItem("HorPattern", Qt::HorPattern);
        m_styleCombo->addItem("VerPattern", Qt::VerPattern);
        m_styleCombo->addItem("CrossPattern", Qt::CrossPattern);
        m_styleCombo->addItem("BDiagPattern", Qt::BDiagPattern);
        m_styleCombo->addItem("FDiagPattern", Qt::FDiagPattern);
        m_styleCombo->addItem("DiagCrossPattern", Qt::DiagCrossPattern);

        QFormLayout *layout = new QFormLayout();
        layout->addRow("Color", m_colorButton);
        layout->addRow("Style", m_styleCombo);
        setLayout(layout);

        connect(m_colorButton, SIGNAL(clicked()), this, SLOT(showColorDialog()));
        connect(m_styleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStyle()));
    }

    void setBrush(QBrush brush)
    {
        m_brush = brush;
        m_colorButton->setText(m_brush.color().name());
        m_styleCombo->setCurrentIndex(m_brush.style()); // index matches the enum
    }

    QBrush brush() const
    {
        return m_brush;
    }

    QString name()
    {
        return name(m_brush);
    }

    static QString name(const QBrush &brush)
    {
        return brush.color().name();
    }

Q_SIGNALS:
    void changed();

public Q_SLOTS:

    void showColorDialog()
    {
        QColorDialog dialog(m_brush.color());
        dialog.show();
        dialog.exec();
        m_brush.setColor(dialog.selectedColor());
        m_colorButton->setText(m_brush.color().name());
        emit changed();
    }

    void updateStyle()
    {
        Qt::BrushStyle style = (Qt::BrushStyle) m_styleCombo->itemData(m_styleCombo->currentIndex()).toInt();
        if (m_brush.style() != style) {
            m_brush.setStyle(style);
            emit changed();
        }
    }

private:
    QBrush m_brush;
    QPushButton *m_colorButton;
    QComboBox *m_styleCombo;
};

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
        m_pen = new QPushButton();
        m_penTool = new PenTool("Slice pen", this);
        m_brush = new QPushButton();
        m_brushTool = new BrushTool("Slice brush", this);
        m_font = new QPushButton();
        m_labelArmPen = new QPushButton();
        m_labelArmPenTool = new PenTool("Label arm pen", this);

        QFormLayout* sliceSettingsLayout = new QFormLayout();
        sliceSettingsLayout->addRow("Selected", m_sliceName);
        sliceSettingsLayout->addRow("Value", m_sliceValue);
        sliceSettingsLayout->addRow("Pen", m_pen);
        sliceSettingsLayout->addRow("Brush", m_brush);
        sliceSettingsLayout->addRow("Label visible", m_sliceLabelVisible);
        sliceSettingsLayout->addRow("Label font", m_font);
        sliceSettingsLayout->addRow("Label arm pen", m_labelArmPen);
        sliceSettingsLayout->addRow("Label arm length", m_sliceLabelArmFactor);
        sliceSettingsLayout->addRow("Exploded", m_sliceExploded);
        sliceSettingsLayout->addRow("Explode distance", m_sliceExplodedFactor);
        QGroupBox* sliceSettings = new QGroupBox("Slice");
        sliceSettings->setLayout(sliceSettingsLayout);

        connect(m_sliceValue, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
        connect(m_pen, SIGNAL(clicked()), m_penTool, SLOT(show()));
        connect(m_penTool, SIGNAL(changed()), this, SLOT(updateSliceSettings()));
        connect(m_brush, SIGNAL(clicked()), m_brushTool, SLOT(show()));
        connect(m_brushTool, SIGNAL(changed()), this, SLOT(updateSliceSettings()));
        connect(m_font, SIGNAL(clicked()), this, SLOT(showFontDialog()));
        connect(m_labelArmPen, SIGNAL(clicked()), m_labelArmPenTool, SLOT(show()));
        connect(m_labelArmPenTool, SIGNAL(changed()), this, SLOT(updateSliceSettings()));
        connect(m_sliceLabelVisible, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
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

        m_slice->setSlicePen(m_penTool->pen());
        m_slice->setSliceBrush(m_brushTool->brush());

        m_slice->setLabelArmPen(m_labelArmPenTool->pen());
        m_slice->setLabelVisible(m_sliceLabelVisible->isChecked());
        m_slice->setLabelArmLengthFactor(m_sliceLabelArmFactor->value());

        m_slice->setExploded(m_sliceExploded->isChecked());
        m_slice->setExplodeDistanceFactor(m_sliceExplodedFactor->value());
    }

    void handleSliceClicked(QPieSlice* slice)
    {
        m_slice = static_cast<CustomSlice*>(slice);

        // name
        m_sliceName->setText(slice->label());

        // value
        m_sliceValue->blockSignals(true);
        m_sliceValue->setValue(slice->value());
        m_sliceValue->blockSignals(false);

        // pen
        m_pen->setText(PenTool::name(m_slice->slicePen()));
        m_penTool->setPen(m_slice->slicePen());

        // brush
        m_brush->setText(m_slice->originalBrush().color().name());
        m_brushTool->setBrush(m_slice->originalBrush());

        // label
        m_labelArmPen->setText(PenTool::name(m_slice->labelArmPen()));
        m_labelArmPenTool->setPen(m_slice->labelArmPen());
        m_font->setText(slice->labelFont().toString());
        m_sliceLabelVisible->blockSignals(true);
        m_sliceLabelVisible->setChecked(slice->isLabelVisible());
        m_sliceLabelVisible->blockSignals(false);
        m_sliceLabelArmFactor->blockSignals(true);
        m_sliceLabelArmFactor->setValue(slice->labelArmLengthFactor());
        m_sliceLabelArmFactor->blockSignals(false);

        // exploded
        m_sliceExploded->blockSignals(true);
        m_sliceExploded->setChecked(slice->isExploded());
        m_sliceExploded->blockSignals(false);
        m_sliceExplodedFactor->blockSignals(true);
        m_sliceExplodedFactor->setValue(slice->explodeDistanceFactor());
        m_sliceExplodedFactor->blockSignals(false);
    }

    void showFontDialog()
    {
        if (!m_slice)
            return;

        QFontDialog dialog(m_slice->labelFont());
        dialog.show();
        dialog.exec();

        m_slice->setLabelFont(dialog.currentFont());
        m_font->setText(dialog.currentFont().toString());
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
    QPushButton *m_brush;
    BrushTool *m_brushTool;
    QPushButton *m_pen;
    PenTool *m_penTool;
    QPushButton *m_font;
    QPushButton *m_labelArmPen;
    PenTool *m_labelArmPenTool;
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
