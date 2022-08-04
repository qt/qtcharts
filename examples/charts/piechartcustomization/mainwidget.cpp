// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include "mainwidget.h"
#include "customslice.h"
#include "pentool.h"
#include "brushtool.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFontDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

QT_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_slice(0)
{
    // create chart
    QChart *chart = new QChart;
    chart->setTitle("Piechart customization");
    chart->setAnimationOptions(QChart::AllAnimations);

    // create series
    m_series = new QPieSeries();
    *m_series << new CustomSlice("Slice 1", 10.0);
    *m_series << new CustomSlice("Slice 2", 20.0);
    *m_series << new CustomSlice("Slice 3", 30.0);
    *m_series << new CustomSlice("Slice 4", 40.0);
    *m_series << new CustomSlice("Slice 5", 50.0);
    m_series->setLabelsVisible();
    chart->addSeries(m_series);

    connect(m_series, &QPieSeries::clicked, this, &MainWidget::handleSliceClicked);

    // chart settings
    m_themeComboBox = new QComboBox();
    m_themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_themeComboBox->addItem("BlueCerulean", QChart::ChartThemeBlueCerulean);
    m_themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_themeComboBox->addItem("BrownSand", QChart::ChartThemeBrownSand);
    m_themeComboBox->addItem("BlueNcs", QChart::ChartThemeBlueNcs);
    m_themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    m_themeComboBox->addItem("Qt", QChart::ChartThemeQt);

    m_aaCheckBox = new QCheckBox();
    m_animationsCheckBox = new QCheckBox();
    m_animationsCheckBox->setCheckState(Qt::Checked);

    m_legendCheckBox = new QCheckBox();

    settingsScrollBar = new QScrollArea();
    QWidget *settingsContentWidget = new QWidget();

    QFormLayout *chartSettingsLayout = new QFormLayout(settingsContentWidget);
    chartSettingsLayout->addRow("Theme", m_themeComboBox);
    chartSettingsLayout->addRow("Antialiasing", m_aaCheckBox);
    chartSettingsLayout->addRow("Animations", m_animationsCheckBox);
    chartSettingsLayout->addRow("Legend", m_legendCheckBox);
    QGroupBox *chartSettings = new QGroupBox("Chart");
    chartSettings->setLayout(chartSettingsLayout);

    connect(m_themeComboBox, &QComboBox::currentIndexChanged,
            this, &MainWidget::updateChartSettings);
    connect(m_aaCheckBox, &QCheckBox::toggled, this, &MainWidget::updateChartSettings);
    connect(m_animationsCheckBox, &QCheckBox::toggled, this, &MainWidget::updateChartSettings);
    connect(m_legendCheckBox, &QCheckBox::toggled, this, &MainWidget::updateChartSettings);

    // series settings
    m_hPosition = new QDoubleSpinBox();
    m_hPosition->setMinimum(0.0);
    m_hPosition->setMaximum(1.0);
    m_hPosition->setSingleStep(0.1);
    m_hPosition->setValue(m_series->horizontalPosition());

    m_vPosition = new QDoubleSpinBox();
    m_vPosition->setMinimum(0.0);
    m_vPosition->setMaximum(1.0);
    m_vPosition->setSingleStep(0.1);
    m_vPosition->setValue(m_series->verticalPosition());

    m_sizeFactor = new QDoubleSpinBox();
    m_sizeFactor->setMinimum(0.0);
    m_sizeFactor->setMaximum(1.0);
    m_sizeFactor->setSingleStep(0.1);
    m_sizeFactor->setValue(m_series->pieSize());

    m_startAngle = new QDoubleSpinBox();
    m_startAngle->setMinimum(-720);
    m_startAngle->setMaximum(720);
    m_startAngle->setValue(m_series->pieStartAngle());
    m_startAngle->setSingleStep(1);

    m_endAngle = new QDoubleSpinBox();
    m_endAngle->setMinimum(-720);
    m_endAngle->setMaximum(720);
    m_endAngle->setValue(m_series->pieEndAngle());
    m_endAngle->setSingleStep(1);

    m_holeSize = new QDoubleSpinBox();
    m_holeSize->setMinimum(0.0);
    m_holeSize->setMaximum(1.0);
    m_holeSize->setSingleStep(0.1);
    m_holeSize->setValue(m_series->holeSize());

    QPushButton *appendSlice = new QPushButton("Append slice");
    QPushButton *insertSlice = new QPushButton("Insert slice");
    QPushButton *removeSlice = new QPushButton("Remove selected slice");

    QFormLayout *seriesSettingsLayout = new QFormLayout(settingsContentWidget);
    seriesSettingsLayout->addRow("Horizontal position", m_hPosition);
    seriesSettingsLayout->addRow("Vertical position", m_vPosition);
    seriesSettingsLayout->addRow("Size factor", m_sizeFactor);
    seriesSettingsLayout->addRow("Start angle", m_startAngle);
    seriesSettingsLayout->addRow("End angle", m_endAngle);
    seriesSettingsLayout->addRow("Hole size", m_holeSize);
    seriesSettingsLayout->addRow(appendSlice);
    seriesSettingsLayout->addRow(insertSlice);
    seriesSettingsLayout->addRow(removeSlice);
    QGroupBox *seriesSettings = new QGroupBox("Series");
    seriesSettings->setLayout(seriesSettingsLayout);

    connect(m_vPosition,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSerieSettings);
    connect(m_hPosition,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSerieSettings);
    connect(m_sizeFactor,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSerieSettings);
    connect(m_startAngle,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSerieSettings);
    connect(m_endAngle,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSerieSettings);
    connect(m_holeSize,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSerieSettings);
    connect(appendSlice, &QPushButton::clicked, this, &MainWidget::appendSlice);
    connect(insertSlice, &QPushButton::clicked, this, &MainWidget::insertSlice);
    connect(removeSlice, &QPushButton::clicked, this, &MainWidget::removeSlice);

    // slice settings
    m_sliceName = new QLineEdit("<click a slice>");
    m_sliceName->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
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
    m_labelBrush = new QPushButton();
    m_labelBrushTool = new BrushTool("Label brush", this);
    m_labelPosition = new QComboBox(this);
    m_labelPosition->addItem("Outside", QPieSlice::LabelOutside);
    m_labelPosition->addItem("Inside horizontal", QPieSlice::LabelInsideHorizontal);
    m_labelPosition->addItem("Inside tangential", QPieSlice::LabelInsideTangential);
    m_labelPosition->addItem("Inside normal", QPieSlice::LabelInsideNormal);

    QFormLayout *sliceSettingsLayout = new QFormLayout(settingsContentWidget);
    sliceSettingsLayout->addRow("Label", m_sliceName);
    sliceSettingsLayout->addRow("Value", m_sliceValue);
    sliceSettingsLayout->addRow("Pen", m_pen);
    sliceSettingsLayout->addRow("Brush", m_brush);
    sliceSettingsLayout->addRow("Label visible", m_sliceLabelVisible);
    sliceSettingsLayout->addRow("Label font", m_font);
    sliceSettingsLayout->addRow("Label brush", m_labelBrush);
    sliceSettingsLayout->addRow("Label position", m_labelPosition);
    sliceSettingsLayout->addRow("Label arm length", m_sliceLabelArmFactor);
    sliceSettingsLayout->addRow("Exploded", m_sliceExploded);
    sliceSettingsLayout->addRow("Explode distance", m_sliceExplodedFactor);
    QGroupBox *sliceSettings = new QGroupBox("Selected slice");
    sliceSettings->setLayout(sliceSettingsLayout);
    sliceSettings->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

    connect(m_sliceName, &QLineEdit::textChanged, this, &MainWidget::updateSliceSettings);
    connect(m_sliceValue,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateSliceSettings);
    connect(m_pen, &QPushButton::clicked, m_penTool, &PenTool::show);
    connect(m_penTool, &PenTool::changed, this, &MainWidget::updateSliceSettings);
    connect(m_brush, &QPushButton::clicked, m_brushTool, &BrushTool::show);
    connect(m_brushTool, &BrushTool::changed, this, &MainWidget::updateSliceSettings);
    connect(m_font, &QPushButton::clicked, this, &MainWidget::showFontDialog);
    connect(m_labelBrush, &QPushButton::clicked, m_labelBrushTool, &BrushTool::show);
    connect(m_labelBrushTool, &BrushTool::changed, this, &MainWidget::updateSliceSettings);
    connect(m_sliceLabelVisible, &QCheckBox::toggled, this, &MainWidget::updateSliceSettings);
    connect(m_sliceLabelVisible, &QCheckBox::toggled, this, &MainWidget::updateSliceSettings);
    connect(m_sliceLabelArmFactor, &QDoubleSpinBox::valueChanged,
            this, &MainWidget::updateSliceSettings);
    connect(m_sliceExploded, &QCheckBox::toggled, this, &MainWidget::updateSliceSettings);
    connect(m_sliceExplodedFactor, &QDoubleSpinBox::valueChanged,
            this, &MainWidget::updateSliceSettings);
    connect(m_labelPosition, &QComboBox::currentIndexChanged,
            this, &MainWidget::updateSliceSettings);

    // create chart view
    m_chartView = new QChartView(chart);

    // create main layout
    QVBoxLayout *settingsLayout = new QVBoxLayout();
    settingsLayout->addWidget(chartSettings);
    settingsLayout->addWidget(seriesSettings);
    settingsLayout->addWidget(sliceSettings);

    settingsContentWidget->setLayout(settingsLayout);

    settingsScrollBar->setWidget(settingsContentWidget);
    settingsScrollBar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    
    settingsScrollBar->setWidgetResizable(true);
    settingsScrollBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_chartView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    baseLayout = new QGridLayout();
    baseLayout->addWidget(settingsScrollBar, 0, 0);
    baseLayout->addWidget(m_chartView, 1, 0);
    setLayout(baseLayout);

    updateSerieSettings();
    updateChartSettings();
}


void MainWidget::updateChartSettings()
{
    QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(m_themeComboBox->itemData(
                m_themeComboBox->currentIndex()).toInt());
    m_chartView->chart()->setTheme(theme);
    m_chartView->setRenderHint(QPainter::Antialiasing, m_aaCheckBox->isChecked());

    if (m_animationsCheckBox->checkState() == Qt::Checked)
        m_chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    else
        m_chartView->chart()->setAnimationOptions(QChart::NoAnimation);

    if (m_legendCheckBox->checkState() == Qt::Checked)
        m_chartView->chart()->legend()->show();
    else
        m_chartView->chart()->legend()->hide();
}

void MainWidget::updateSerieSettings()
{
    m_series->setHorizontalPosition(m_hPosition->value());
    m_series->setVerticalPosition(m_vPosition->value());
    m_series->setPieSize(m_sizeFactor->value());
    m_holeSize->setMaximum(m_sizeFactor->value());
    m_series->setPieStartAngle(m_startAngle->value());
    m_series->setPieEndAngle(m_endAngle->value());
    m_series->setHoleSize(m_holeSize->value());
}

void MainWidget::updateSliceSettings()
{
    if (!m_slice)
        return;

    m_slice->setLabel(m_sliceName->text());

    m_slice->setValue(m_sliceValue->value());

    m_slice->setPen(m_penTool->pen());
    m_slice->setBrush(m_brushTool->brush());

    m_slice->setLabelBrush(m_labelBrushTool->brush());
    m_slice->setLabelVisible(m_sliceLabelVisible->isChecked());
    m_slice->setLabelArmLengthFactor(m_sliceLabelArmFactor->value());
    // We assume that label position index is in sync with the enum
    m_slice->setLabelPosition((QPieSlice::LabelPosition)m_labelPosition->currentIndex());

    m_slice->setExploded(m_sliceExploded->isChecked());
    m_slice->setExplodeDistanceFactor(m_sliceExplodedFactor->value());
}

void MainWidget::handleSliceClicked(QPieSlice *slice)
{
    m_slice = static_cast<CustomSlice *>(slice);

    // name
    m_sliceName->blockSignals(true);
    m_sliceName->setText(slice->label());
    m_sliceName->blockSignals(false);

    // value
    m_sliceValue->blockSignals(true);
    m_sliceValue->setValue(slice->value());
    m_sliceValue->blockSignals(false);

    // pen
    m_pen->setText(PenTool::name(m_slice->pen()));
    m_penTool->setPen(m_slice->pen());

    // brush
    m_brush->setText(m_slice->originalBrush().color().name());
    m_brushTool->setBrush(m_slice->originalBrush());

    // label
    m_labelBrush->setText(BrushTool::name(m_slice->labelBrush()));
    m_labelBrushTool->setBrush(m_slice->labelBrush());
    m_font->setText(slice->labelFont().toString());
    m_sliceLabelVisible->blockSignals(true);
    m_sliceLabelVisible->setChecked(slice->isLabelVisible());
    m_sliceLabelVisible->blockSignals(false);
    m_sliceLabelArmFactor->blockSignals(true);
    m_sliceLabelArmFactor->setValue(slice->labelArmLengthFactor());
    m_sliceLabelArmFactor->blockSignals(false);
    m_labelPosition->blockSignals(true);
    // We assume that label position index is in sync with the enum
    m_labelPosition->setCurrentIndex(slice->labelPosition());
    m_labelPosition->blockSignals(false);

    // exploded
    m_sliceExploded->blockSignals(true);
    m_sliceExploded->setChecked(slice->isExploded());
    m_sliceExploded->blockSignals(false);
    m_sliceExplodedFactor->blockSignals(true);
    m_sliceExplodedFactor->setValue(slice->explodeDistanceFactor());
    m_sliceExplodedFactor->blockSignals(false);
}

void MainWidget::showFontDialog()
{
    if (!m_slice)
        return;

    QFontDialog dialog(m_slice->labelFont());
    dialog.show();
    dialog.exec();

    m_slice->setLabelFont(dialog.currentFont());
    m_font->setText(dialog.currentFont().toString());
}

void MainWidget::appendSlice()
{
    *m_series << new CustomSlice("Slice " + QString::number(m_series->count() + 1), 10.0);
}

void MainWidget::insertSlice()
{
    if (!m_slice)
        return;

    int i = m_series->slices().indexOf(m_slice);

    m_series->insert(i, new CustomSlice("Slice " + QString::number(m_series->count() + 1), 10.0));
}

void MainWidget::removeSlice()
{
    if (!m_slice)
        return;

    m_sliceName->setText("<click a slice>");

    m_series->remove(m_slice);
    m_slice = 0;
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
    if (width() == 0 || height() == 0)
        return;

    const double aspectRatio = double(width()) / double(height());

    if ((aspectRatio < 1.0) && (oldAspectRatio > 1.0)) {
        baseLayout->removeWidget(m_chartView);
        baseLayout->removeWidget(settingsScrollBar);

        baseLayout->addWidget(m_chartView, 0, 0);
        baseLayout->addWidget(settingsScrollBar, 1, 0);

        oldAspectRatio = aspectRatio;
    }
    else if ((aspectRatio > 1.0) && (oldAspectRatio < 1.0)) {
        baseLayout->removeWidget(m_chartView);
        baseLayout->removeWidget(settingsScrollBar);

        baseLayout->addWidget(m_chartView, 0, 0);
        baseLayout->addWidget(settingsScrollBar, 0, 1);

        oldAspectRatio = aspectRatio;
    }
}


#include "moc_mainwidget.cpp"
