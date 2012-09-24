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
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QLegend>
#include <QFormLayout>
#include <QPieSeries>
#include <QPieSlice>
#include <QLegendMarker>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Create buttons for ui
    m_buttonLayout = new QGridLayout();
    QPushButton *detachLegendButton = new QPushButton("Toggle attached");
    connect(detachLegendButton, SIGNAL(clicked()), this, SLOT(toggleAttached()));
    m_buttonLayout->addWidget(detachLegendButton, 0, 0);

    QPushButton *addSliceButton = new QPushButton("add slice");
    connect(addSliceButton, SIGNAL(clicked()), this, SLOT(addSlice()));
    m_buttonLayout->addWidget(addSliceButton, 2, 0);
    QPushButton *removeSliceButton = new QPushButton("remove slice");
    connect(removeSliceButton, SIGNAL(clicked()), this, SLOT(removeSlice()));
    m_buttonLayout->addWidget(removeSliceButton, 3, 0);

    QPushButton *alignButton = new QPushButton("Align (Bottom)");
    connect(alignButton, SIGNAL(clicked()), this, SLOT(setLegendAlignment()));
    m_buttonLayout->addWidget(alignButton, 4, 0);

    QPushButton *boldButton = new QPushButton("Toggle bold");
    connect(boldButton, SIGNAL(clicked()), this, SLOT(toggleBold()));
    m_buttonLayout->addWidget(boldButton, 5, 0);

    QPushButton *italicButton = new QPushButton("Toggle italic");
    connect(italicButton, SIGNAL(clicked()), this, SLOT(toggleItalic()));
    m_buttonLayout->addWidget(italicButton, 6, 0);

    QPushButton *infoButton = new QPushButton("Debug info");
    connect(infoButton, SIGNAL(clicked()), this, SLOT(showDebugInfo()));
    m_buttonLayout->addWidget(infoButton, 7, 0);

    QPushButton *connectButton = new QPushButton("Connect markers");
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectMarkers()));
    m_buttonLayout->addWidget(connectButton, 8, 0);

    QPushButton *disConnectButton = new QPushButton("Disconnect markers");
    connect(disConnectButton, SIGNAL(clicked()), this, SLOT(disconnectMarkers()));
    m_buttonLayout->addWidget(connectButton, 8, 0);


    m_legendPosX = new QDoubleSpinBox();
    m_legendPosY = new QDoubleSpinBox();
    m_legendWidth = new QDoubleSpinBox();
    m_legendHeight = new QDoubleSpinBox();

    connect(m_legendPosX, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(m_legendPosY, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(m_legendWidth, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));
    connect(m_legendHeight, SIGNAL(valueChanged(double)), this, SLOT(updateLegendLayout()));

    QFormLayout* legendLayout = new QFormLayout();
    legendLayout->addRow("HPos", m_legendPosX);
    legendLayout->addRow("VPos", m_legendPosY);
    legendLayout->addRow("Width", m_legendWidth);
    legendLayout->addRow("Height", m_legendHeight);
    m_legendSettings = new QGroupBox("Detached legend");
    m_legendSettings->setLayout(legendLayout);
    m_buttonLayout->addWidget(m_legendSettings);
    m_legendSettings->setVisible(false);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart, this);

    // Create spinbox to modify font size
    m_fontSize = new QDoubleSpinBox();
    m_fontSize->setValue(m_chart->legend()->font().pointSizeF());
    connect(m_fontSize, SIGNAL(valueChanged(double)), this, SLOT(fontSizeChanged()));

    QFormLayout* fontLayout = new QFormLayout();
    fontLayout->addRow("Legend font size", m_fontSize);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_buttonLayout, 0, 0);
    m_mainLayout->addLayout(fontLayout,1,0);
    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(m_mainLayout);

    createSeries();
}

void MainWidget::createSeries()
{
    m_series = new QPieSeries();
    addSlice();
    addSlice();
    addSlice();
    addSlice();

    m_chart->addSeries(m_series);
    m_chart->setTitle("Legend detach example");
    m_chart->createDefaultAxes();
//![1]
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
//![1]

    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWidget::showLegendSpinbox()
{
    m_legendSettings->setVisible(true);
    QRectF chartViewRect = m_chartView->rect();

    m_legendPosX->setMinimum(0);
    m_legendPosX->setMaximum(chartViewRect.width());
    m_legendPosX->setValue(150);

    m_legendPosY->setMinimum(0);
    m_legendPosY->setMaximum(chartViewRect.height());
    m_legendPosY->setValue(150);

    m_legendWidth->setMinimum(0);
    m_legendWidth->setMaximum(chartViewRect.width());
    m_legendWidth->setValue(150);

    m_legendHeight->setMinimum(0);
    m_legendHeight->setMaximum(chartViewRect.height());
    m_legendHeight->setValue(75);
}

void MainWidget::hideLegendSpinbox()
{
    m_legendSettings->setVisible(false);
}


void MainWidget::toggleAttached()
{
    QLegend *legend = m_chart->legend();
    if (legend->isAttachedToChart()) {
        //![2]
        legend->detachFromChart();
        m_chart->legend()->setBackgroundVisible(true);
        m_chart->legend()->setBrush(QBrush(QColor(128,128,128,128)));
        m_chart->legend()->setPen(QPen(QColor(192,192,192,192)));
        //![2]
        showLegendSpinbox();
        updateLegendLayout();
    } else {
        //![3]
        legend->attachToChart();
        legend->setBackgroundVisible(false);
        //![3]
        hideLegendSpinbox();
    }
    update();
}

void MainWidget::addSlice()
{
    QPieSlice* slice = new QPieSlice(QString("slice " + QString::number(m_series->count())), m_series->count()+1);
    m_series->append(slice);
}

void MainWidget::removeSlice()
{
    QList<QPieSlice*> slices = m_series->slices();
    if (slices.count() > 0) {
        m_series->remove(slices.at(slices.count()-1));
    }
}

void MainWidget::connectMarkers()
{
    // Example use case.
    // Explode slice via marker.
    // Should be doable via public api.

    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
        QObject::connect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
    }
}

void MainWidget::disconnectMarkers()
{
    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
    }
}

void MainWidget::setLegendAlignment()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

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

void MainWidget::toggleBold()
{
    QFont font = m_chart->legend()->font();
    font.setBold(!font.bold());
    m_chart->legend()->setFont(font);
}

void MainWidget::toggleItalic()
{
    QFont font = m_chart->legend()->font();
    font.setItalic(!font.italic());
    m_chart->legend()->setFont(font);
}

void MainWidget::showDebugInfo()
{
    qDebug() << "marker count:" << m_chart->legend()->markers().count();
    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        qDebug() << "marker series type:" << marker->series()->type();
        qDebug() << "peer object:" << marker->peerObject();
        qDebug() << "label:" << marker->label();
    }
}

void MainWidget::fontSizeChanged()
{
    QFont font = m_chart->legend()->font();
    font.setPointSizeF(m_fontSize->value());
    m_chart->legend()->setFont(font);
}

void MainWidget::updateLegendLayout()
{
//![4]
    m_chart->legend()->setGeometry(QRectF(m_legendPosX->value()
                                   ,m_legendPosY->value()
                                   ,m_legendWidth->value()
                                   ,m_legendHeight->value()));
    m_chart->legend()->update();
//![4]
}

void MainWidget::handleMarkerClicked()
{
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    qDebug() << "marker clicked:" << marker;

    QPieSlice* slice = qobject_cast<QPieSlice*> (marker->peerObject());
    Q_ASSERT(slice);

    slice->setExploded(!slice->isExploded());
}
