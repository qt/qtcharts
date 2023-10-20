// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "legendwidget.h"

#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLegend>
#include <QPushButton>

LegendWidget::LegendWidget(QWidget *parent)
    : ContentWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart;
    m_chartView = new QChartView(m_chart, this);

    m_chart->setTitle("Legend Options");

    createUi();

    connect(m_toggleAttachedButton, &QPushButton::clicked, this, &LegendWidget::toggleAttached);
    connect(m_interactiveButton, &QPushButton::clicked, this, &LegendWidget::toggleInteractive);
    connect(m_boldButton, &QPushButton::clicked, this, &LegendWidget::toggleBold);
    connect(m_italicButton, &QPushButton::clicked, this, &LegendWidget::toggleItalic);
    connect(m_addSetButton, &QPushButton::clicked, this, &LegendWidget::addBarset);
    connect(m_removeSetButton, &QPushButton::clicked, this, &LegendWidget::removeBarset);
    connect(m_alignmentButton, &QPushButton::clicked, this, &LegendWidget::setLegendAlignment);
    connect(m_fontSize,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &LegendWidget::fontSizeChanged);
    connect(m_legendPosX,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &LegendWidget::updateLegendLayout);
    connect(m_legendPosY,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &LegendWidget::updateLegendLayout);
    connect(m_legendWidth,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &LegendWidget::updateLegendLayout);
    connect(m_legendHeight,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &LegendWidget::updateLegendLayout);

    QLegend *legend = m_chart->legend();
    legend->setShowToolTips(true);
    legend->setBrush(QBrush(QColor(128, 128, 128, 128)));
    legend->setPen(QPen(QColor(192, 192, 192, 192)));
    //![5]
    legend->setInteractive(true);
    //![5]

    //![4]
    connect(legend, &QLegend::attachedToChartChanged, [legend, this](bool attachedToChart) {
        m_toggleAttachedButton->setChecked(attachedToChart);
        legend->setBackgroundVisible(!attachedToChart);
        m_geometrySettings->setDisabled(attachedToChart);
    });
    //![4]
    connect(legend, &QGraphicsWidget::geometryChanged, this, &LegendWidget::updateLegendSpinbox);

    createSeries();
    m_chart->createDefaultAxes();

    //![1]
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    //![1]

    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chart->layout()->setContentsMargins(0, 0, 0, 0);
}

void LegendWidget::resizeEvent(QResizeEvent *)
{
    QRectF chartViewRect = m_chartView->rect();
    m_legendPosX->setMaximum(chartViewRect.width());
    m_legendPosY->setMaximum(chartViewRect.height());
    m_legendWidth->setMaximum(chartViewRect.width());
    m_legendHeight->setMaximum(chartViewRect.height());
}

void LegendWidget::createUi()
{
    QLegend *legend = m_chart->legend();
    // Create buttons for ui
    auto buttonLayout = new QGridLayout;
    m_toggleAttachedButton = new QCheckBox("Attached", this);
    m_toggleAttachedButton->setChecked(true);
    buttonLayout->addWidget(m_toggleAttachedButton, 0, 0);

    m_interactiveButton = new QCheckBox("Interactive", this);
    m_interactiveButton->setChecked(true);
    buttonLayout->addWidget(m_interactiveButton, 1, 0);

    m_boldButton = new QCheckBox("Bold", this);
    buttonLayout->addWidget(m_boldButton, 2, 0);

    m_italicButton = new QCheckBox("Italic", this);
    buttonLayout->addWidget(m_italicButton, 3, 0);

    m_addSetButton = new QPushButton("Add Barset", this);
    buttonLayout->addWidget(m_addSetButton, 4, 0);

    m_removeSetButton = new QPushButton("Remove Barset", this);
    buttonLayout->addWidget(m_removeSetButton, 5, 0);

    m_alignmentButton = new QPushButton("Align (Bottom)", this);
    buttonLayout->addWidget(m_alignmentButton, 6, 0);

    buttonLayout->setRowStretch(7, 1);

    m_legendPosX = new QDoubleSpinBox(this);
    m_legendPosY = new QDoubleSpinBox(this);
    m_legendWidth = new QDoubleSpinBox(this);
    m_legendHeight = new QDoubleSpinBox(this);

    auto legendLayout = new QFormLayout;
    legendLayout->addRow("HPos", m_legendPosX);
    legendLayout->addRow("VPos", m_legendPosY);
    legendLayout->addRow("Width", m_legendWidth);
    legendLayout->addRow("Height", m_legendHeight);
    m_geometrySettings = new QGroupBox("Detached legend", this);
    m_geometrySettings->setLayout(legendLayout);
    buttonLayout->addWidget(m_geometrySettings, 8, 0);
    m_geometrySettings->setDisabled(true);

    // Create spinbox to modify font size
    m_fontSize = new QDoubleSpinBox(this);
    QFont lfont = legend->font();
    lfont.setPointSizeF(12.0);
    legend->setFont(lfont);
    m_fontSize->setValue(legend->font().pointSizeF());
    m_fontSize->setMinimum(1.);

    auto fontLayout = new QFormLayout;
    fontLayout->addRow("Legend font size", m_fontSize);

    // Create layout for grid and detached legend
    auto mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->addLayout(buttonLayout, 0, 0);
    mainLayout->addLayout(fontLayout, 1, 0);
    mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(mainLayout);
}

void LegendWidget::createSeries()
{
    m_series = new QBarSeries;
    addBarset();
    addBarset();
    addBarset();
    addBarset();

    m_chart->addSeries(m_series);
}

void LegendWidget::updateLegendSpinbox()
{
    QLegend *legend = m_chart->legend();
    double newPosX = legend->x();
    double newPosY = legend->y();
    QSizeF newSize = legend->size();
    if (!qFuzzyCompare(m_legendPosX->value(), newPosX))
        m_legendPosX->setValue(newPosX);
    if (!qFuzzyCompare(m_legendPosY->value(), newPosY))
        m_legendPosY->setValue(newPosY);
     if (!qFuzzyCompare(m_legendWidth->value(), newSize.width()))
        m_legendWidth->setValue(newSize.width());
    if (!qFuzzyCompare(m_legendHeight->value(), newSize.height()))
        m_legendHeight->setValue(newSize.height());
}


void LegendWidget::toggleAttached()
{
    QLegend *legend = m_chart->legend();
    if (legend->isAttachedToChart()) {
        //![2]
        legend->detachFromChart();
        //![2]
    } else {
        //![3]
        legend->attachToChart();
        //![3]
    }
    update();
}

void LegendWidget::toggleInteractive()
{
    m_chart->legend()->setInteractive(!m_chart->legend()->isInteractive());
}

void LegendWidget::toggleBold()
{
    QFont font = m_chart->legend()->font();
    font.setBold(!font.bold());
    m_chart->legend()->setFont(font);
}

void LegendWidget::toggleItalic()
{
    QFont font = m_chart->legend()->font();
    font.setItalic(!font.italic());
    m_chart->legend()->setFont(font);
}

void LegendWidget::addBarset()
{
    auto barSet = new QBarSet(QString("set ") + QString::number(m_series->count()));
    qreal delta = m_series->count() * 0.1;
    *barSet << 1 + delta << 2 + delta << 3 + delta << 4 + delta;
    m_series->append(barSet);
}

void LegendWidget::removeBarset()
{
    QList<QBarSet *> sets = m_series->barSets();
    if (sets.count() > 0) {
        m_series->remove(sets.at(sets.count() - 1));
    }
}

void LegendWidget::setLegendAlignment()
{
    auto button = qobject_cast<QPushButton *>(sender());

    switch (m_chart->legend()->alignment()) {
    case Qt::AlignTop:
        m_chart->legend()->setAlignment(Qt::AlignLeft);
        if (button)
            button->setText("Align (Left)");
        break;
    case Qt::AlignLeft:
        m_chart->legend()->setAlignment(Qt::AlignBottom);
        if (button)
            button->setText("Align (Bottom)");
        break;
    case Qt::AlignBottom:
        m_chart->legend()->setAlignment(Qt::AlignRight);
        if (button)
            button->setText("Align (Right)");
        break;
    default:
        if (button)
            button->setText("Align (Top)");
        m_chart->legend()->setAlignment(Qt::AlignTop);
        break;
    }
}

void LegendWidget::fontSizeChanged()
{
    QFont font = m_chart->legend()->font();
    font.setPointSizeF(m_fontSize->value());
    m_chart->legend()->setFont(font);
}

void LegendWidget::updateLegendLayout()
{
//![6]
    QRectF geom = m_chart->legend()->geometry();
    if (qFuzzyCompare(geom.x(), m_legendPosX->value())
            && qFuzzyCompare(geom.y(), m_legendPosY->value())
            && qFuzzyCompare(geom.width(), m_legendWidth->value())
            && qFuzzyCompare(geom.height(), m_legendHeight->value()))
        return;

    m_chart->legend()->setGeometry(QRectF(m_legendPosX->value(),
                                          m_legendPosY->value(),
                                          m_legendWidth->value(),
                                          m_legendHeight->value()));
    m_chart->legend()->update();
//![6]
}
