// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "pointconfigurationwidget.h"

#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QLineSeries>

//![1]
PointConfigurationWidget::PointConfigurationWidget(QWidget *parent)
    : ContentWidget(parent)
{
//![1]
    //![2]
    m_series = new QLineSeries;
    m_series->setPointsVisible(true);
    m_series->append({QPointF(0, 7),  QPointF(2, 4),
                      QPointF(3, 5),  QPointF(7, 4),
                      QPointF(10, 5), QPointF(11, 1),
                      QPointF(13, 3), QPointF(17, 6),
                      QPointF(18, 3), QPointF(20, 2)});
    //![2]

    //![3]
    auto selectedPointIndexLabel = new QLabel(tr("Selected Point: "), this);
    m_selectedPointIndexLineEdit = new QLineEdit(this);
    m_selectedPointIndexLineEdit->setReadOnly(true);

    auto colorLabel = new QLabel(tr("Color: "), this);
    m_colorCombobox = new QComboBox(this);
    QStringList colorStrings = {"red", "orange", "yellow", "green", "blue",
                                "indigo", "violet", "black"};
    QStringList trColorStrings = {tr("red"), tr("orange"), tr("yellow"),
                                  tr("green"), tr("blue"), tr("indigo"),
                                  tr("violet"), tr("black")};
    for (int i = 0; i < colorStrings.size(); i++)
        m_colorCombobox->addItem(QIcon(), trColorStrings[i], QColor(colorStrings[i]));

    auto sizeLabel = new QLabel(tr("Size: "), this);
    m_sizeCombobox = new QComboBox(this);
    for (auto size : { 2, 3, 4, 6, 8, 10, 12, 15 })
        m_sizeCombobox->addItem(QIcon(), QString::number(size), size);

    auto labelVisibilityLabel = new QLabel(tr("Label Visibility: "), this);
    m_labelVisibilityCheckbox = new QCheckBox(this);

    auto customLabelLabel = new QLabel(tr("Custom Label: "), this);
    m_customLabelLineEdit = new QLineEdit(this);
    //![3]

    //![4]
    QObject::connect(m_series, &QXYSeries::clicked, m_series, [&](const QPointF &point) {
        int index = m_series->points().indexOf(point.toPoint());
        if (index != -1) {
            m_series->deselectAllPoints();
            m_series->selectPoint(index);
            m_selectedPointIndex = index;
            m_selectedPointConfig = m_series->pointConfiguration(index);
            const QPointF selectedPoint(m_series->at(index));
            m_selectedPointIndexLineEdit->setText("(" + QString::number(selectedPoint.x()) + ", " +
                                                  QString::number(selectedPoint.y()) + ")");
            PointConfigurations config = m_series->pointConfiguration(index);

            QVariant colorVar = config[QXYSeries::PointConfiguration::Color];
            QColor color = colorVar.isValid() ? colorVar.value<QColor>() : m_series->color();
            if (m_colorCombobox->findData(color) < 0)
                m_colorCombobox->addItem(color.name(), color);
            m_colorCombobox->setCurrentIndex(m_colorCombobox->findData(color));

            QVariant sizeVar = config[QXYSeries::PointConfiguration::Size];
            qreal size = sizeVar.isValid() ? sizeVar.toReal() : m_series->markerSize();
            if (m_sizeCombobox->findData(size) < 0)
                m_sizeCombobox->addItem(QString::number(size), size);
            m_sizeCombobox->setCurrentIndex(m_sizeCombobox->findData(size));

            QVariant labelVisibilityVar = config[QXYSeries::PointConfiguration::LabelVisibility];
            bool labelVisibility = labelVisibilityVar.isValid() ? labelVisibilityVar.toBool() :
                                                                  m_series->pointLabelsVisible();
            m_labelVisibilityCheckbox->setChecked(labelVisibility);

            QVariant customLabelVar = config[QXYSeries::PointConfiguration::LabelFormat];
            QString customLabel = customLabelVar.isValid() ? customLabelVar.toString() : "";
            m_customLabelLineEdit->setText(customLabel);
        }
    });
    //![4]

    //![5]
    QObject::connect(m_colorCombobox, &QComboBox::activated, m_series, [&](const int) {
        m_selectedPointConfig[QXYSeries::PointConfiguration::Color] = m_colorCombobox->currentData();
        m_series->setPointConfiguration(m_selectedPointIndex, m_selectedPointConfig);
    });
    QObject::connect(m_sizeCombobox, &QComboBox::activated, m_series, [&](const int) {
        m_selectedPointConfig[QXYSeries::PointConfiguration::Size] = m_sizeCombobox->currentData();
        m_series->setPointConfiguration(m_selectedPointIndex, m_selectedPointConfig);
    });
    QObject::connect(m_labelVisibilityCheckbox, &QAbstractButton::clicked, m_series, [&](const bool checked) {
        m_selectedPointConfig[QXYSeries::PointConfiguration::LabelVisibility] = checked;
        m_series->setPointConfiguration(m_selectedPointIndex, m_selectedPointConfig);
    });
    QObject::connect(m_customLabelLineEdit, &QLineEdit::editingFinished, m_series, [&]() {
        m_selectedPointConfig[QXYSeries::PointConfiguration::LabelFormat] = m_customLabelLineEdit->text();
        m_series->setPointConfiguration(m_selectedPointIndex, m_selectedPointConfig);
    });
    //![5]

    //![6]
    auto chart = new QChart;
    chart->addSeries(m_series);
    chart->createDefaultAxes();
    chart->setTitle("Select points with mouse click");
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->legend()->setVisible(false);

    m_selectInitialPointConnection = QObject::connect(chart, &QChart::geometryChanged, chart, [&]() {
        m_series->selectPoint(4);
        m_series->clicked(m_series->at(m_series->selectedPoints()[0]));
        disconnect(m_selectInitialPointConnection);
    });

    auto chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    auto controlWidget = new QWidget(this);
    auto controlLayout = new QGridLayout(controlWidget);
    controlLayout->setColumnStretch(1, 1);

    controlLayout->addWidget(selectedPointIndexLabel, 0, 0);
    controlLayout->addWidget(m_selectedPointIndexLineEdit, 0, 1);

    controlLayout->addWidget(colorLabel, 1, 0);
    controlLayout->addWidget(m_colorCombobox, 1, 1);

    controlLayout->addWidget(sizeLabel, 2, 0);
    controlLayout->addWidget(m_sizeCombobox, 2, 1);

    controlLayout->addWidget(labelVisibilityLabel, 3, 0);
    controlLayout->addWidget(m_labelVisibilityCheckbox, 3, 1, 1, 2);

    controlLayout->addWidget(customLabelLabel, 4, 0);
    controlLayout->addWidget(m_customLabelLineEdit, 4, 1);

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(chartView);
    mainLayout->setStretch(0, 1);
    mainLayout->addWidget(controlWidget);
    //![6]
//![7]
}
//![7]
