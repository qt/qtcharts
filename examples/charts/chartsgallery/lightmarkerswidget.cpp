// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "lightmarkerswidget.h"

#include <QBrush>
#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QComboBox>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QPainterPath>
#include <QSplineSeries>

LightMarkersWidget::LightMarkersWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    constexpr qreal marker_size = 20.;

    auto series = new QSplineSeries;
    series->append({QPointF(0., 0.),
                    QPointF(0.5, 2.27),
                    QPointF(1.5, 2.2),
                    QPointF(3.3, 1.7),
                    QPointF(4.23, 3.1),
                    QPointF(5.3, 2.3),
                    QPointF(6.47, 4.1)
    });
    series->setMarkerSize(marker_size);
    series->setLightMarker(rectangle(marker_size, Qt::red));
    series->setSelectedLightMarker(blueTriangle(marker_size));

    QObject::connect(series, &QXYSeries::clicked, series, [=](const QPointF &point) {
        int index = series->points().indexOf(point);
        if (index != -1)
            series->toggleSelection({index});
    });
    //![1]

    //![2]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setTitle("Select points with mouse click");

    auto chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    auto controlWidget = new QWidget(this);
    auto controlLayout = new QGridLayout(controlWidget);
    //![2]

    //![3]
    auto charPointCombobox = new QComboBox(controlWidget);
    auto charPointSelectedCombobox = new QComboBox(controlWidget);
    auto lineColorCombobox = new QComboBox(controlWidget);
    auto showUnselectedPointsCheckbox = new QCheckBox(controlWidget);
    //![3]

    //![4]
    auto charPoint = new QLabel(tr("Char point: "), controlWidget);
    charPointCombobox->addItems({tr("Red rectangle"),
                                 tr("Green triangle"),
                                 tr("Orange circle")
    });
    QObject::connect(charPointCombobox, &QComboBox::currentIndexChanged, series, [=](const int index) {
        if (showUnselectedPointsCheckbox->isChecked())
            series->setLightMarker(getPointRepresentation(PointType(index), marker_size));
    });
    //![4]

    //![5]
    auto charPointSelected = new QLabel(tr("Char point selected: "), controlWidget);
    charPointSelectedCombobox->addItems({tr("Blue triangle"),
                                         tr("Yellow rectangle"),
                                         tr("Lavender circle")
    });
    QObject::connect(charPointSelectedCombobox, &QComboBox::currentIndexChanged, series, [=](const int index) {
        series->setSelectedLightMarker(getSelectedPointRepresentation(SelectedPointType(index), marker_size));
    });

    auto lineColorLabel = new QLabel(tr("Line color: "), controlWidget);
    lineColorCombobox->addItems({tr("Blue"),
                                 tr("Black"),
                                 tr("Mint")
    });
    QObject::connect(lineColorCombobox, &QComboBox::currentIndexChanged, series, [=](const int index) {
        series->setColor(makeLineColor(LineColor(index)));
    });
    //![5]

    //![6]
    auto showUnselectedPointsLabel = new QLabel(tr("Display unselected points: "), controlWidget);
    showUnselectedPointsCheckbox->setChecked(true);
    QObject::connect(showUnselectedPointsCheckbox, &QCheckBox::stateChanged, series, [=](const int state) {
        if (state)
            series->setLightMarker(getPointRepresentation(PointType(charPointCombobox->currentIndex()), marker_size));
        else
            series->setLightMarker(QImage());
    });
    //![6]

    //![7]
    controlLayout->addWidget(charPoint, 0, 0);
    controlLayout->addWidget(charPointCombobox, 0, 1);

    controlLayout->addWidget(charPointSelected, 1, 0);
    controlLayout->addWidget(charPointSelectedCombobox, 1, 1);

    controlLayout->addWidget(lineColorLabel, 2, 0);
    controlLayout->addWidget(lineColorCombobox, 2, 1);

    controlLayout->addWidget(showUnselectedPointsLabel, 3, 0);
    controlLayout->addWidget(showUnselectedPointsCheckbox, 3, 1, 1, 2);

    m_mainWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(m_mainWidget);
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(controlWidget);
    //![7]
}

void LightMarkersWidget::resizeEvent(QResizeEvent *)
{
    m_mainWidget->resize(size());
}

QImage LightMarkersWidget::rectangle(qreal imageSize, const QColor &color)
{
    QImage image(imageSize, imageSize, QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&image);
    painter.fillRect(0, 0, imageSize, imageSize, color);
    painter.end();
    return image;
}

QImage LightMarkersWidget::circle(qreal imageSize, const QColor &color)
{
    QImage image(imageSize, imageSize, QImage::Format_ARGB32);
    image.fill(QColor(0, 0, 0, 0));
    QPainter paint;
    paint.begin(&image);
    paint.setBrush(color);
    QPen pen = paint.pen();
    pen.setWidth(0);
    paint.setPen(pen);
    paint.drawEllipse(0, 0, imageSize * 0.9, imageSize * 0.9);
    paint.end();
    return image;
}

QImage LightMarkersWidget::blueTriangle(qreal imageSize)
{
    return QImage(":/blue_triangle").scaled(imageSize, imageSize);
}

QImage LightMarkersWidget::greenTriangle(qreal imageSize)
{
    return QImage(":/green_triangle").scaled(imageSize, imageSize);
}

QImage LightMarkersWidget::getPointRepresentation(PointType pointType, int imageSize)
{
    switch (pointType) {
    case PointType::RedRectangle:
        return rectangle(imageSize, Qt::red);
    case PointType::GreenTriangle:
        return greenTriangle(imageSize);
    case PointType::OrangeCircle:
        return circle(imageSize, QColor(255, 127, 80));
    default:
        return rectangle(imageSize, Qt::red);
    }
}

QImage LightMarkersWidget::getSelectedPointRepresentation(SelectedPointType pointType, int imageSize)
{
    switch (pointType) {
    case SelectedPointType::BlueTriangle:
        return blueTriangle(imageSize);
    case SelectedPointType::YellowRectangle:
        return rectangle(imageSize, Qt::yellow);
    case SelectedPointType::LavenderCircle:
        return circle(imageSize, QColor(147, 112, 219));
    default:
        return blueTriangle(imageSize);
    }
}

QColor LightMarkersWidget::makeLineColor(LineColor lineColor)
{
    switch (lineColor) {
    case LineColor::Blue:
        return QColor(65, 105, 225);
    case LineColor::Black:
        return QColor(0, 0, 0);
    case LineColor::Mint:
        return QColor(70, 203, 155);
    default:
        return QColor(0, 0, 0);
    }
}
