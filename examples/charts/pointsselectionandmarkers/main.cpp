/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "utilities.h"

#include <QApplication>
#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QSplineSeries>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Chart");

    //![1]
    constexpr qreal marker_size = 20.;

    QSplineSeries *series = new QSplineSeries();
    series->append({QPointF(0., 0.),
                    QPointF(0.5, 2.27),
                    QPointF(1.5, 2.2),
                    QPointF(3.3, 1.7),
                    QPointF(4.23, 3.1),
                    QPointF(5.3, 2.3),
                    QPointF(6.47, 4.1)
                   });
    series->setMarkerSize(marker_size);
    series->setLightMarker(Utilities::redRectangle(marker_size));
    series->setSelectedLightMarker(Utilities::blueTriangle(marker_size));
    QObject::connect(series, &QXYSeries::clicked, series, [&](const QPointF &point) {
       int index = series->points().indexOf(point);
       if (index != -1)
           series->toggleSelection({index});
    });
    //![1]

    //![2]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget *controlWidget = new QWidget(&mainWindow);
    QGridLayout *controlLayout = new QGridLayout(controlWidget);
    //![2]

    //![3]
    QComboBox *charPointCombobox = new QComboBox();
    QComboBox *charPointSelectedCombobox = new QComboBox();
    QComboBox *lineColorCombobox = new QComboBox();
    QCheckBox *showUnselectedPointsCheckbox = new QCheckBox();
    //![3]

    //![4]
    QLabel *charPoint = new QLabel(QCoreApplication::tr("Char point: "));
    charPointCombobox->addItems({QCoreApplication::tr("Red rectangle"),
                                 QCoreApplication::tr("Green triangle"),
                                 QCoreApplication::tr("Orange circle")
                                });
    QObject::connect(charPointCombobox, &QComboBox::currentIndexChanged, series, [&](const int index) {
        if (showUnselectedPointsCheckbox->isChecked())
            series->setLightMarker(Utilities::getPointRepresentation(Utilities::PointType(index), marker_size));
    });
    //![4]

    //![5]
    QLabel *charPointSelected = new QLabel(QCoreApplication::tr("Char point selected: "));
    charPointSelectedCombobox->addItems({QCoreApplication::tr("Blue triangle"),
                                         QCoreApplication::tr("Yellow rectangle"),
                                         QCoreApplication::tr("Lavender circle")
                                        });
    QObject::connect(charPointSelectedCombobox, &QComboBox::currentIndexChanged, series, [&](const int index) {
        series->setSelectedLightMarker(Utilities::getSelectedPointRepresentation(Utilities::SelectedPointType(index), marker_size));
    });

    QLabel *lineColorLabel = new QLabel(QCoreApplication::tr("Line color: "));
    lineColorCombobox->addItems({QCoreApplication::tr("Blue"),
                                 QCoreApplication::tr("Black"),
                                 QCoreApplication::tr("Mint")
                                });
    QObject::connect(lineColorCombobox, &QComboBox::currentIndexChanged, series, [&](const int index) {
        series->setColor(Utilities::makeLineColor(Utilities::LineColor(index)));
    });
    //![5]

    //![6]
    QLabel *showUnselectedPointsLabel = new QLabel(QCoreApplication::tr("Display unselected points: "));
    showUnselectedPointsCheckbox->setChecked(true);
    QObject::connect(showUnselectedPointsCheckbox, &QCheckBox::stateChanged, series, [&](const int state) {
        if (state) {
            series->setLightMarker(Utilities::getPointRepresentation(Utilities::PointType(charPointCombobox->currentIndex()), marker_size));
        } else {
            series->setLightMarker(QImage());
        }
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

    QWidget *mainWidget = new QWidget(&mainWindow);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(controlWidget);

    mainWindow.setCentralWidget(mainWidget);
    mainWindow.resize(1080, 720);
    mainWindow.show();
    return a.exec();
    //![7]
}
