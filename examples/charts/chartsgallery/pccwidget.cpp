// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "pccbrushtool.h"
#include "pcccustomslice.h"
#include "pccwidget.h"
#include "pccpentool.h"

#include <QChartView>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFontDialog>
#include <QFormLayout>
#include <QGraphicsLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPieSeries>
#include <QPushButton>

PccWidget::PccWidget(QWidget *parent)
    : ContentWidget(parent)
{
    // create chart
    auto chart = new QChart;
    chart->setTitle("Pie Chart Customization");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->layout()->setContentsMargins(0, 0, 0, 0);

    // create series
    m_series = new QPieSeries;
    *m_series << new PccCustomSlice("Slice 1", 10.0);
    *m_series << new PccCustomSlice("Slice 2", 20.0);
    *m_series << new PccCustomSlice("Slice 3", 30.0);
    *m_series << new PccCustomSlice("Slice 4", 40.0);
    *m_series << new PccCustomSlice("Slice 5", 50.0);
    m_series->setLabelsVisible();
    chart->addSeries(m_series);

    connect(m_series, &QPieSeries::clicked, this, &PccWidget::handleSliceClicked);

    // chart settings
    m_themeComboBox = new QComboBox(this);
    m_themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_themeComboBox->addItem("BlueCerulean", QChart::ChartThemeBlueCerulean);
    m_themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_themeComboBox->addItem("BrownSand", QChart::ChartThemeBrownSand);
    m_themeComboBox->addItem("BlueNcs", QChart::ChartThemeBlueNcs);
    m_themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    m_themeComboBox->addItem("Qt", QChart::ChartThemeQt);

    m_aaCheckBox = new QCheckBox(this);
    m_animationsCheckBox = new QCheckBox(this);
    m_animationsCheckBox->setCheckState(Qt::Checked);

    m_legendCheckBox = new QCheckBox(this);

    m_settingsScrollBar = new QScrollArea(this);
    auto settingsContentWidget = new QWidget(this);

    auto chartSettingsLayout = new QFormLayout(settingsContentWidget);
    chartSettingsLayout->addRow("Theme", m_themeComboBox);
    chartSettingsLayout->addRow("Antialiasing", m_aaCheckBox);
    chartSettingsLayout->addRow("Animations", m_animationsCheckBox);
    chartSettingsLayout->addRow("Legend", m_legendCheckBox);
    auto chartSettings = new QGroupBox("Chart", this);
    chartSettings->setLayout(chartSettingsLayout);

    connect(m_themeComboBox, &QComboBox::currentIndexChanged, this, &PccWidget::updateChartSettings);
    connect(m_aaCheckBox, &QCheckBox::toggled, this, &PccWidget::updateChartSettings);
    connect(m_animationsCheckBox, &QCheckBox::toggled, this, &PccWidget::updateChartSettings);
    connect(m_legendCheckBox, &QCheckBox::toggled, this, &PccWidget::updateChartSettings);

    // series settings
    m_hPosition = new QDoubleSpinBox(this);
    m_hPosition->setMinimum(0.0);
    m_hPosition->setMaximum(1.0);
    m_hPosition->setSingleStep(0.1);
    m_hPosition->setValue(m_series->horizontalPosition());

    m_vPosition = new QDoubleSpinBox(this);
    m_vPosition->setMinimum(0.0);
    m_vPosition->setMaximum(1.0);
    m_vPosition->setSingleStep(0.1);
    m_vPosition->setValue(m_series->verticalPosition());

    m_sizeFactor = new QDoubleSpinBox(this);
    m_sizeFactor->setMinimum(0.0);
    m_sizeFactor->setMaximum(1.0);
    m_sizeFactor->setSingleStep(0.1);
    m_sizeFactor->setValue(m_series->pieSize());

    m_startAngle = new QDoubleSpinBox(this);
    m_startAngle->setMinimum(-720);
    m_startAngle->setMaximum(720);
    m_startAngle->setValue(m_series->pieStartAngle());
    m_startAngle->setSingleStep(1);

    m_endAngle = new QDoubleSpinBox(this);
    m_endAngle->setMinimum(-720);
    m_endAngle->setMaximum(720);
    m_endAngle->setValue(m_series->pieEndAngle());
    m_endAngle->setSingleStep(1);

    m_holeSize = new QDoubleSpinBox(this);
    m_holeSize->setMinimum(0.0);
    m_holeSize->setMaximum(1.0);
    m_holeSize->setSingleStep(0.1);
    m_holeSize->setValue(m_series->holeSize());

    auto appendSlice = new QPushButton("Append slice", this);
    auto insertSlice = new QPushButton("Insert slice", this);
    auto removeSlice = new QPushButton("Remove selected slice", this);

    auto seriesSettingsLayout = new QFormLayout(settingsContentWidget);
    seriesSettingsLayout->addRow("Horizontal position", m_hPosition);
    seriesSettingsLayout->addRow("Vertical position", m_vPosition);
    seriesSettingsLayout->addRow("Size factor", m_sizeFactor);
    seriesSettingsLayout->addRow("Start angle", m_startAngle);
    seriesSettingsLayout->addRow("End angle", m_endAngle);
    seriesSettingsLayout->addRow("Hole size", m_holeSize);
    seriesSettingsLayout->addRow(appendSlice);
    seriesSettingsLayout->addRow(insertSlice);
    seriesSettingsLayout->addRow(removeSlice);
    auto seriesSettings = new QGroupBox("Series", this);
    seriesSettings->setLayout(seriesSettingsLayout);

    connect(m_vPosition,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSerieSettings);
    connect(m_hPosition,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSerieSettings);
    connect(m_sizeFactor,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSerieSettings);
    connect(m_startAngle,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSerieSettings);
    connect(m_endAngle,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSerieSettings);
    connect(m_holeSize,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSerieSettings);
    connect(appendSlice, &QPushButton::clicked, this, &PccWidget::appendSlice);
    connect(insertSlice, &QPushButton::clicked, this, &PccWidget::insertSlice);
    connect(removeSlice, &QPushButton::clicked, this, &PccWidget::removeSlice);

    // slice settings
    m_sliceName = new QLineEdit("<click a slice>", this);
    m_sliceName->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_sliceValue = new QDoubleSpinBox(this);
    m_sliceValue->setMaximum(1000);
    m_sliceLabelVisible = new QCheckBox(this);
    m_sliceLabelArmFactor = new QDoubleSpinBox(this);
    m_sliceLabelArmFactor->setSingleStep(0.01);
    m_sliceExploded = new QCheckBox(this);
    m_sliceExplodedFactor = new QDoubleSpinBox(this);
    m_sliceExplodedFactor->setSingleStep(0.01);
    m_pen = new QPushButton(this);
    m_penTool = new PccPenTool("Slice pen", this);
    m_brush = new QPushButton(this);
    m_brushTool = new PccBrushTool("Slice brush", this);
    m_font = new QPushButton(this);
    m_labelBrush = new QPushButton(this);
    m_labelBrushTool = new PccBrushTool("Label brush", this);
    m_labelPosition = new QComboBox(this);
    m_labelPosition->addItem("Outside", QPieSlice::LabelOutside);
    m_labelPosition->addItem("Inside horizontal", QPieSlice::LabelInsideHorizontal);
    m_labelPosition->addItem("Inside tangential", QPieSlice::LabelInsideTangential);
    m_labelPosition->addItem("Inside normal", QPieSlice::LabelInsideNormal);

    auto sliceSettingsLayout = new QFormLayout(settingsContentWidget);
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
    auto sliceSettings = new QGroupBox("Selected slice", this);
    sliceSettings->setLayout(sliceSettingsLayout);
    sliceSettings->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

    connect(m_sliceName, &QLineEdit::textChanged, this, &PccWidget::updateSliceSettings);
    connect(m_sliceValue,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &PccWidget::updateSliceSettings);
    connect(m_pen, &QPushButton::clicked, m_penTool, &PccPenTool::show);
    connect(m_penTool, &PccPenTool::changed, this, &PccWidget::updateSliceSettings);
    connect(m_brush, &QPushButton::clicked, m_brushTool, &PccBrushTool::show);
    connect(m_brushTool, &PccBrushTool::changed, this, &PccWidget::updateSliceSettings);
    connect(m_font, &QPushButton::clicked, this, &PccWidget::showFontDialog);
    connect(m_labelBrush, &QPushButton::clicked, m_labelBrushTool, &PccBrushTool::show);
    connect(m_labelBrushTool, &PccBrushTool::changed, this, &PccWidget::updateSliceSettings);
    connect(m_sliceLabelVisible, &QCheckBox::toggled, this, &PccWidget::updateSliceSettings);
    connect(m_sliceLabelVisible, &QCheckBox::toggled, this, &PccWidget::updateSliceSettings);
    connect(m_sliceLabelArmFactor, &QDoubleSpinBox::valueChanged,
            this, &PccWidget::updateSliceSettings);
    connect(m_sliceExploded, &QCheckBox::toggled, this, &PccWidget::updateSliceSettings);
    connect(m_sliceExplodedFactor, &QDoubleSpinBox::valueChanged,
            this, &PccWidget::updateSliceSettings);
    connect(m_labelPosition, &QComboBox::currentIndexChanged,
            this, &PccWidget::updateSliceSettings);

    // create chart view
    m_chartView = new QChartView(chart);

    // create main layout
    auto settingsLayout = new QVBoxLayout;
    settingsLayout->addWidget(chartSettings);
    settingsLayout->addWidget(seriesSettings);
    settingsLayout->addWidget(sliceSettings);

    settingsContentWidget->setLayout(settingsLayout);

    m_settingsScrollBar->setWidget(settingsContentWidget);
    m_settingsScrollBar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_settingsScrollBar->setWidgetResizable(true);
    m_settingsScrollBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_chartView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    m_baseLayout = new QGridLayout;
    m_baseLayout->addWidget(m_settingsScrollBar, 0, 0);
    m_baseLayout->addWidget(m_chartView, 1, 0);
    setLayout(m_baseLayout);

    updateSerieSettings();
    updateChartSettings();
}

void PccWidget::updateChartSettings()
{
    auto theme = static_cast<QChart::ChartTheme>(m_themeComboBox->itemData(
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

void PccWidget::updateSerieSettings()
{
    m_series->setHorizontalPosition(m_hPosition->value());
    m_series->setVerticalPosition(m_vPosition->value());
    m_series->setPieSize(m_sizeFactor->value());
    m_holeSize->setMaximum(m_sizeFactor->value());
    m_series->setPieStartAngle(m_startAngle->value());
    m_series->setPieEndAngle(m_endAngle->value());
    m_series->setHoleSize(m_holeSize->value());
}

void PccWidget::updateSliceSettings()
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

void PccWidget::handleSliceClicked(QPieSlice *slice)
{
    m_slice = static_cast<PccCustomSlice *>(slice);

    // name
    m_sliceName->blockSignals(true);
    m_sliceName->setText(slice->label());
    m_sliceName->blockSignals(false);

    // value
    m_sliceValue->blockSignals(true);
    m_sliceValue->setValue(slice->value());
    m_sliceValue->blockSignals(false);

    // pen
    m_pen->setText(PccPenTool::name(m_slice->pen()));
    m_penTool->setPen(m_slice->pen());

    // brush
    m_brush->setText(m_slice->originalBrush().color().name());
    m_brushTool->setBrush(m_slice->originalBrush());

    // label
    m_labelBrush->setText(PccBrushTool::name(m_slice->labelBrush()));
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

void PccWidget::showFontDialog()
{
    if (!m_slice)
        return;

    QFontDialog dialog(m_slice->labelFont());
    dialog.show();
    dialog.exec();

    m_slice->setLabelFont(dialog.currentFont());
    m_font->setText(dialog.currentFont().toString());
}

void PccWidget::appendSlice()
{
    *m_series << new PccCustomSlice("Slice " + QString::number(m_series->count() + 1), 10.0);
}

void PccWidget::insertSlice()
{
    if (!m_slice)
        return;

    int i = m_series->slices().indexOf(m_slice);

    m_series->insert(i, new PccCustomSlice("Slice " + QString::number(m_series->count() + 1), 10.0));
}

void PccWidget::removeSlice()
{
    if (!m_slice)
        return;

    m_sliceName->setText("<click a slice>");

    m_series->remove(m_slice);
    m_slice = 0;
}

void PccWidget::resizeEvent(QResizeEvent *)
{
    if (width() == 0 || height() == 0)
        return;

    const double aspectRatio = double(width()) / double(height());

    if ((aspectRatio < 1.0) && (m_oldAspectRatio > 1.0)) {
        m_baseLayout->removeWidget(m_chartView);
        m_baseLayout->removeWidget(m_settingsScrollBar);

        m_baseLayout->addWidget(m_chartView, 0, 0);
        m_baseLayout->addWidget(m_settingsScrollBar, 1, 0);

        m_oldAspectRatio = aspectRatio;
    } else if ((aspectRatio > 1.0) && (m_oldAspectRatio < 1.0)) {
        m_baseLayout->removeWidget(m_chartView);
        m_baseLayout->removeWidget(m_settingsScrollBar);

        m_baseLayout->addWidget(m_chartView, 0, 0);
        m_baseLayout->addWidget(m_settingsScrollBar, 0, 1);

        m_oldAspectRatio = aspectRatio;
    }
}
