/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#include "chart-widget.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QHorizontalPercentBarSeries>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCore/QTime>
#include <QElapsedTimer>
#include <QDebug>

const int initialCount = 20;
const int visibleCount = 40;
const int storeCount = 100000000;
const int interval = 600;
const int initialSetCount = 3;
const int maxSetCount = 3;
const bool removeSets = true;
const int extraSetFrequency = 30;
const bool initialLabels = false;
const int labelsTrigger = -1;
const int visibleTrigger = -1;
const int appendFrequency = 1;
const int animationTrigger = -1;
const bool sameNumberOfBars = false;
const bool animation = true;
const int animationDuration = 500;

const bool horizontal = false;
const bool percent = false;
const bool stacked = false;

// Negative indexes are counted from end of the set.
const bool doReplace = false;
const bool doRemove = false;
const bool doInsert = false;
const bool singleReplace = false;
const bool singleRemove = false;
const bool singleInsert = false;
const int removeIndex = -7;
const int replaceIndex = -3;
const int insertIndex = -5;

const bool logarithmic = false;
// Note: reverse axes are not fully supported for bars (animation and label positioning break a bit)
const bool reverseBar = false;
const bool reverseValue = false;

static int counter = 1;
static const QString nameTemplate = QStringLiteral("Set %1");

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    m_chart(new QChart()),
    m_chartView(new QChartView(this)),
    m_barAxis(new QValueAxis()),
    m_series(nullptr),
    m_setCount(initialSetCount)
{
    m_elapsedTimer.start();

    if (logarithmic) {
        QLogValueAxis *logAxis = new QLogValueAxis;
        logAxis->setBase(2);
        m_valueAxis = logAxis;
    } else {
        m_valueAxis = new QValueAxis;
    }

    m_barAxis->setReverse(reverseBar);
    m_valueAxis->setReverse(reverseValue);

    if (horizontal) {
        if (percent)
            m_series = new QHorizontalPercentBarSeries;
        else if (stacked)
            m_series = new QHorizontalStackedBarSeries;
        else
            m_series = new QHorizontalBarSeries;
    } else {
        if (percent)
            m_series = new QPercentBarSeries;
        else if (stacked)
            m_series = new QStackedBarSeries;
        else
            m_series = new QBarSeries;
    }

    qsrand((uint) QTime::currentTime().msec());

    resize(800, 300);
    m_horizontalLayout = new QHBoxLayout(this);
    m_horizontalLayout->setSpacing(6);
    m_horizontalLayout->setContentsMargins(11, 11, 11, 11);
    m_horizontalLayout->addWidget(m_chartView);

    qDebug() << "UI setup time:"<< m_elapsedTimer.restart();

    m_chartView->setRenderHint(QPainter::Antialiasing);

    createChart();
    qDebug() << "Chart creation time:"<< m_elapsedTimer.restart();

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

    m_timer.setInterval(interval);
    m_timer.start();
}

ChartWidget::~ChartWidget()
{
}

void ChartWidget::handleTimeout()
{
    qDebug() << "Intervening time:" << m_elapsedTimer.restart();

    qDebug() << "----------" << counter << "----------";

    bool doScroll = false;

    if (counter % appendFrequency == 0) {
        for (int i = 0; i < maxSetCount; i++) {
            QBarSet *set = m_sets.at(i);
            qreal value = (counter % 100) / qreal(i+1);
            set->append(value);
            if (set->count() > storeCount)
                set->remove(5, set->count() - storeCount);
            if (set->count() > visibleCount)
                doScroll = true;
        }
        qDebug() << "Append time:" << m_elapsedTimer.restart();
    }

    if (doScroll) {
        doScroll = false;
        if (horizontal)
            m_chart->scroll(0, m_chart->plotArea().height() / visibleCount);
        else
            m_chart->scroll(m_chart->plotArea().width() / visibleCount, 0);
        qDebug() << "Scroll time:" << m_elapsedTimer.restart();
    }

    if (doRemove || doReplace || doInsert) {
        for (int i = 0; i < m_setCount; i++) {
            QBarSet *set = m_sets.at(i);
            qreal value = ((counter + 20) % 100) / qreal(i+1);
            if (doReplace && (!singleReplace || i == 0)) {
                int index = replaceIndex < 0 ? set->count() + replaceIndex : replaceIndex;
                set->replace(index, value);
            }
            if (doRemove && (!singleRemove || i == 0)) {
                int index = removeIndex < 0 ? set->count() + removeIndex : removeIndex;
                set->remove(index, 1);
            }
            if (doInsert && (!singleInsert || i == 0)) {
                int index = insertIndex < 0 ? set->count() + insertIndex : insertIndex;
                set->insert(index, value);
            }
        }
        qDebug() << "R/R    time:" << m_elapsedTimer.restart();
    }

//    if (counter % 5 == 0) {
//        m_sets.at(0)->setPen(QPen(QColor(counter % 255, counter % 255, counter % 255), 2));
//    }

    if (counter % extraSetFrequency == 0) {
        if (m_setCount <= maxSetCount) {
            qDebug() << "Adjusting setcount, current count:" << m_setCount;
            static int setCountAdder = 1;
            if (m_setCount == maxSetCount) {
                if (removeSets)
                    setCountAdder = -1;
                else
                    setCountAdder = 0;
            } else if (m_setCount == 0) {
                setCountAdder = 1;
            }
            if (setCountAdder < 0) {
                int barCount = m_sets.at(m_setCount - 1)->count();
                m_series->remove(m_sets.at(m_setCount - 1));
                // Since remove deletes the set, recreate it in our list
                QBarSet *set = new QBarSet(nameTemplate.arg(m_setCount - 1));
                m_sets[m_setCount - 1] = set;
                set->setLabelBrush(QColor("black"));
                set->setPen(QPen(QColor("black"), 0.3));
                QList<qreal> valueList;
                valueList.reserve(barCount);
                for (int j = 0; j < barCount; ++j)
                    valueList.append(counter % 100);
                set->append(valueList);

            } else if (m_setCount < maxSetCount) {
                m_series->append(m_sets.at(m_setCount));
            }
            m_setCount += setCountAdder;
        }
    }

    if (labelsTrigger > 0 && counter % labelsTrigger == 0) {
        m_series->setLabelsVisible(!m_series->isLabelsVisible());
        qDebug() << "Label visibility changed";
    }

    if (visibleTrigger > 0 && counter % visibleTrigger == 0) {
        m_series->setVisible(!m_series->isVisible());
        qDebug() << "Series visibility changed";
    }

    if (animationTrigger > 0 && counter % animationTrigger == 0) {
        if (m_chart->animationOptions() == QChart::SeriesAnimations)
            m_chart->setAnimationOptions(QChart::NoAnimation);
        else
            m_chart->setAnimationOptions(QChart::SeriesAnimations);
        qDebug() << "Series animation changed";
    }

    qDebug() << "Restof time:" << m_elapsedTimer.restart();

    qDebug() << "Item Count:" << m_chart->scene()->items().size();
    counter++;
}

void ChartWidget::createChart()
{
    qDebug() << "Initial bar count:" << initialCount;

    QList<qreal> valueList;
    valueList.reserve(initialCount);
    for (int j = 0; j < initialCount; ++j)
        valueList.append(counter++ % 100);

    for (int i = 0; i < maxSetCount; i++) {
        QBarSet *set = new QBarSet(nameTemplate.arg(i));
        m_sets.append(set);
        set->setLabelBrush(QColor("black"));
        set->setPen(QPen(QColor("black"), 0.3));
        if (sameNumberOfBars) {
            set->append(valueList);
        } else {
            QList<qreal> tempList = valueList;
            for (int j = 0; j < i; j++) {
                tempList.removeLast();
                tempList.removeLast();
                tempList.removeLast();
            }
            set->append(tempList);
        }
    }

    m_series->setName("bar");
    for (int i = 0; i < initialSetCount; i++)
        m_series->append(m_sets.at(i));

    m_series->append(m_sets.at(0));
    m_series->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
    m_series->setLabelsVisible(initialLabels);
    m_series->setBarWidth(0.9);

    m_chart->addSeries(m_series);
    m_chart->setTitle("Chart");
    if (animation) {
        m_chart->setAnimationOptions(QChart::SeriesAnimations);
        m_chart->setAnimationDuration(animationDuration);
    }

    if (horizontal) {
        m_chart->setAxisX(m_valueAxis, m_series);
        m_chart->setAxisY(m_barAxis, m_series);
    } else {
        m_chart->setAxisX(m_barAxis, m_series);
        m_chart->setAxisY(m_valueAxis, m_series);
    }
    m_barAxis->setTickCount(11);
    if (initialCount > visibleCount)
        m_barAxis->setRange(initialCount - visibleCount, initialCount);
    else
        m_barAxis->setRange(0, visibleCount);

    m_valueAxis->setRange(logarithmic ? 1 : 0, stacked ? 200 : 100);

    m_chartView->setChart(m_chart);
}
