/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/
#include "mainwidget.h"
#include "customslice.h"
#include "pentool.h"
#include "brushtool.h"
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QFontDialog>
#include <QChartView>
#include <QPieSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget* parent)
    :QWidget(parent),
    m_slice(0)
{
    // create chart
    QChart *chart = new QChart;
    chart->setTitle("Piechart customization");
    chart->setAnimationOptions(QChart::AllAnimations);

    // create series
    m_series = new QPieSeries();
    *m_series << new CustomSlice(10.0, "Slice 1");
    *m_series << new CustomSlice(20.0, "Slice 2");
    *m_series << new CustomSlice(30.0, "Slice 3");
    *m_series << new CustomSlice(40.0, "Slice 4");
    *m_series << new CustomSlice(50.0, "Slice 5");
    m_series->setLabelsVisible();
    chart->addSeries(m_series);

    connect(m_series, SIGNAL(clicked(QPieSlice*, Qt::MouseButtons)), this, SLOT(handleSliceClicked(QPieSlice*, Qt::MouseButtons)));

    // chart settings
    m_themeComboBox = new QComboBox();
    m_themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_themeComboBox->addItem("BlueCerulean", QChart::ChartThemeBlueCerulean);
    m_themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_themeComboBox->addItem("BrownSand", QChart::ChartThemeBrownSand);
    m_themeComboBox->addItem("BlueNcs", QChart::ChartThemeBlueNcs);
    m_themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);

    m_aaCheckBox = new QCheckBox();
    m_animationsCheckBox = new QCheckBox();
    m_animationsCheckBox->setCheckState(Qt::Checked);

    QFormLayout* chartSettingsLayout = new QFormLayout();
    chartSettingsLayout->addRow("Theme", m_themeComboBox);
    chartSettingsLayout->addRow("Antialiasing", m_aaCheckBox);
    chartSettingsLayout->addRow("Animations", m_animationsCheckBox);
    QGroupBox* chartSettings = new QGroupBox("Chart");
    chartSettings->setLayout(chartSettingsLayout);

    connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this ,SLOT(updateChartSettings()));
    connect(m_aaCheckBox, SIGNAL(toggled(bool)), this ,SLOT(updateChartSettings()));
    connect(m_animationsCheckBox, SIGNAL(toggled(bool)), this ,SLOT(updateChartSettings()));

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
    m_startAngle->setMinimum(0.0);
    m_startAngle->setMaximum(360);
    m_startAngle->setValue(m_series->pieStartAngle());
    m_startAngle->setSingleStep(1);

    m_endAngle = new QDoubleSpinBox();
    m_endAngle->setMinimum(0.0);
    m_endAngle->setMaximum(360);
    m_endAngle->setValue(m_series->pieEndAngle());
    m_endAngle->setSingleStep(1);

    QPushButton *addSlice = new QPushButton("Add slice");
    QPushButton *insertSlice = new QPushButton("Insert slice");

    QFormLayout* seriesSettingsLayout = new QFormLayout();
    seriesSettingsLayout->addRow("Horizontal position", m_hPosition);
    seriesSettingsLayout->addRow("Vertical position", m_vPosition);
    seriesSettingsLayout->addRow("Size factor", m_sizeFactor);
    seriesSettingsLayout->addRow("Start angle", m_startAngle);
    seriesSettingsLayout->addRow("End angle", m_endAngle);
    seriesSettingsLayout->addRow(addSlice);
    seriesSettingsLayout->addRow(insertSlice);
    QGroupBox* seriesSettings = new QGroupBox("Series");
    seriesSettings->setLayout(seriesSettingsLayout);

    connect(m_vPosition, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
    connect(m_hPosition, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
    connect(m_sizeFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
    connect(m_startAngle, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
    connect(m_endAngle, SIGNAL(valueChanged(double)), this, SLOT(updateSerieSettings()));
    connect(addSlice, SIGNAL(clicked()), this, SLOT(addSlice()));
    connect(insertSlice, SIGNAL(clicked()), this, SLOT(insertSlice()));

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
    m_labelPen = new QPushButton();
    m_labelPenTool = new PenTool("Label pen", this);
    QPushButton *removeSlice = new QPushButton("Remove slice");

    QFormLayout* sliceSettingsLayout = new QFormLayout();
    sliceSettingsLayout->addRow("Selected", m_sliceName);
    sliceSettingsLayout->addRow("Value", m_sliceValue);
    sliceSettingsLayout->addRow("Pen", m_pen);
    sliceSettingsLayout->addRow("Brush", m_brush);
    sliceSettingsLayout->addRow("Label visible", m_sliceLabelVisible);
    sliceSettingsLayout->addRow("Label font", m_font);
    sliceSettingsLayout->addRow("Label pen", m_labelPen);
    sliceSettingsLayout->addRow("Label arm length", m_sliceLabelArmFactor);
    sliceSettingsLayout->addRow("Exploded", m_sliceExploded);
    sliceSettingsLayout->addRow("Explode distance", m_sliceExplodedFactor);
    sliceSettingsLayout->addRow(removeSlice);
    QGroupBox* sliceSettings = new QGroupBox("Slice");
    sliceSettings->setLayout(sliceSettingsLayout);

    connect(m_sliceValue, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
    connect(m_pen, SIGNAL(clicked()), m_penTool, SLOT(show()));
    connect(m_penTool, SIGNAL(changed()), this, SLOT(updateSliceSettings()));
    connect(m_brush, SIGNAL(clicked()), m_brushTool, SLOT(show()));
    connect(m_brushTool, SIGNAL(changed()), this, SLOT(updateSliceSettings()));
    connect(m_font, SIGNAL(clicked()), this, SLOT(showFontDialog()));
    connect(m_labelPen, SIGNAL(clicked()), m_labelPenTool, SLOT(show()));
    connect(m_labelPenTool, SIGNAL(changed()), this, SLOT(updateSliceSettings()));
    connect(m_sliceLabelVisible, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
    connect(m_sliceLabelVisible, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
    connect(m_sliceLabelArmFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
    connect(m_sliceExploded, SIGNAL(toggled(bool)), this, SLOT(updateSliceSettings()));
    connect(m_sliceExplodedFactor, SIGNAL(valueChanged(double)), this, SLOT(updateSliceSettings()));
    connect(removeSlice, SIGNAL(clicked()), this, SLOT(removeSlice()));

    // create chart view
    m_chartView = new QChartView(chart);

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


void MainWidget::updateChartSettings()
{
    QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(m_themeComboBox->currentIndex()).toInt();
    m_chartView->chart()->setTheme(theme);
    m_chartView->setRenderHint(QPainter::Antialiasing, m_aaCheckBox->isChecked());

    if (m_animationsCheckBox->checkState() == Qt::Checked)
        m_chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    else
        m_chartView->chart()->setAnimationOptions(QChart::NoAnimation);
}

void MainWidget::updateSerieSettings()
{
    m_series->setHorizontalPosition(m_hPosition->value());
    m_series->setVerticalPosition(m_vPosition->value());
    m_series->setPieSize(m_sizeFactor->value());
    m_series->setPieStartAngle(m_startAngle->value());
    m_series->setPieEndAngle(m_endAngle->value());
}

void MainWidget::updateSliceSettings()
{
    if (!m_slice)
        return;

    m_slice->setValue(m_sliceValue->value());

    m_slice->setPen(m_penTool->pen());
    m_slice->setBrush(m_brushTool->brush());

    m_slice->setLabelPen(m_labelPenTool->pen());
    m_slice->setLabelVisible(m_sliceLabelVisible->isChecked());
    m_slice->setLabelArmLengthFactor(m_sliceLabelArmFactor->value());

    m_slice->setExploded(m_sliceExploded->isChecked());
    m_slice->setExplodeDistanceFactor(m_sliceExplodedFactor->value());
}

void MainWidget::handleSliceClicked(QPieSlice* slice, Qt::MouseButtons buttons)
{
    Q_UNUSED(buttons);

    m_slice = static_cast<CustomSlice*>(slice);

    // name
    m_sliceName->setText(slice->label());

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
    m_labelPen->setText(PenTool::name(m_slice->labelPen()));
    m_labelPenTool->setPen(m_slice->labelPen());
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

void MainWidget::addSlice()
{
    *m_series << new CustomSlice(10.0, "Slice " + QString::number(m_series->count()+1));
}

void MainWidget::insertSlice()
{
    if (!m_slice)
        return;

    int i = m_series->slices().indexOf(m_slice);

    m_series->insert(i, new CustomSlice(10.0, "Slice " + QString::number(m_series->count()+1)));
}

void MainWidget::removeSlice()
{
    if (!m_slice)
        return;

    m_series->remove(m_slice);
    m_slice = 0;
}

#include "moc_mainwidget.cpp"
