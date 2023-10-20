// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "selectedbarwidget.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QGraphicsLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QValueAxis>

SelectedBarWidget::SelectedBarWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    QBarSet *setChicken = createChickenSet();
    QBarSet *setPork = createPorkSet();
    QBarSet *setTurkey = createTurkeySet();
    QBarSet *setHam = createHamSet();
    qreal totalSum = setChicken->sum() + setPork->sum() + setTurkey->sum() + setHam->sum();
    QList<QBarSet *> setList = QList<QBarSet *>{setChicken, setPork, setTurkey, setHam};

    auto series = new QBarSeries;
    series->append(setList);
    //![1]

    //![2]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle(tr("Meat Consumption (Click on bars to select them)"));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    //![2]

    //![3]
    const auto barSets = series->barSets();
    for (QBarSet *barSet : barSets)
        barSet->setSelectedColor(barSet->brush().color().darker());
    //![3]

    //![4]
    QStringList categories = createYearCategories();
    auto axisX = new QBarCategoryAxis;
    axisX->setCategories(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setRange(0, 20);
    axisY->setTitleText(tr("Tons"));
    axisY->setLabelsAngle(-90);
    axisY->setTitleVisible(true);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    auto chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![5]

    //![6]
    auto labelWidget = new QWidget(this);
    auto labelLayout = new QHBoxLayout(labelWidget);
    labelLayout->setAlignment(Qt::AlignCenter);

    auto totalSumLabel = new QLabel(tr("Total sum: %1 T").arg(totalSum), this);
    labelLayout->addWidget(totalSumLabel);
    totalSumLabel->setContentsMargins(0, 0, 54, 0);

    auto selectedSumLabel = new QLabel(tr("Selected sum: 0 T"), this);
    labelLayout->addWidget(selectedSumLabel);

    auto unselectedSumLabel = new QLabel(tr("Unselected sum: %1 T").arg(totalSum), this);
    labelLayout->addWidget(unselectedSumLabel);
    unselectedSumLabel->setContentsMargins(54, 0, 0, 0);
    //![6]

    //![7]
    QObject::connect(series, &QAbstractBarSeries::clicked, series, [=](int index, QBarSet *set) {
        set->toggleSelection({index});
        qreal selectedSum = 0.;
        for (int i = 0; i < setList.size(); ++i) {
            auto selectedIndices = setList.at(i)->selectedBars();
            for (int k = 0; k < selectedIndices.size(); ++k)
                selectedSum += setList.at(i)->at(selectedIndices.at(k));
        }
        selectedSumLabel->setText(tr("Selected sum: %1 T").arg(selectedSum));
        // Because of rounding errors, selectedSum can result in being bigger than total sum
        qreal unselectedSum = totalSum - selectedSum < 0 ? 0. : totalSum - selectedSum;
        unselectedSumLabel->setText(
            tr("Unselected sum: %1 T")
                .arg(unselectedSum)
            );
    });
    //![7]

    //![8]
    auto mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(chartView);
    mainLayout->addWidget(labelWidget);
    //![8]
}

QBarSet *SelectedBarWidget::createChickenSet()
{
    auto set = new QBarSet(tr("Chicken"));
    set->append({15.0, 12.0, 8.0, 11.5, 13.7});
    return set;
}

QBarSet *SelectedBarWidget::createPorkSet()
{
    auto set = new QBarSet(tr("Pork"));
    set->append({9.0, 11.0, 9.0, 7, 12.2});
    return set;
}

QBarSet *SelectedBarWidget::createTurkeySet()
{
    auto set = new QBarSet(tr("Turkey"));
    set->append({5.0, 7.6, 9.3, 8, 8.1});
    return set;
}

QBarSet *SelectedBarWidget::createHamSet()
{
    auto set = new QBarSet(tr("Ham"));
    set->append({5.4, 7.1, 9.3, 12.3, 11.3});
    return set;
}

QStringList SelectedBarWidget::createYearCategories()
{
    return QStringList{tr("2017"),
                       tr("2018"),
                       tr("2019"),
                       tr("2020"),
                       tr("2021")};
}
