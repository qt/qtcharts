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

#include "window.h"
#include "view.h"
#include "charts.h"

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QPercentBarSeries>
#include <QStackedBarSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QLineSeries>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QAreaSeries>
#include <QLegend>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QTime>
#include <QBarCategoriesAxis>
#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QGLWidget>
#include <QApplication>
#include <QDebug>

Window::Window(QWidget* parent) :
    QMainWindow(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_scene(new QGraphicsScene(this)),
    m_view(0),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    m_form(0),
    m_themeComboBox(0),
    m_antialiasCheckBox(0),
    m_animatedComboBox(0),
    m_legendComboBox(0),
    m_openGLCheckBox(0),
    m_zoomCheckBox(0),
    m_scrollCheckBox(0),
    m_rubberBand(new QGraphicsRectItem()),
    m_isScrolling(false),
    m_isZooming(false),
    m_scroll(false),
    m_zoom(false)
{
    createProxyWidgets();
    connectSignals();

    // create layout
    QGraphicsGridLayout* baseLayout = new QGraphicsGridLayout();
    QGraphicsLinearLayout *settingsLayout = new QGraphicsLinearLayout();
    settingsLayout->setOrientation(Qt::Vertical);
    settingsLayout->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    settingsLayout->addItem(m_widgetHash["openGLCheckBox"]);
    settingsLayout->addItem(m_widgetHash["antialiasCheckBox"]);
    settingsLayout->addItem(m_widgetHash["themeLabel"]);
    settingsLayout->addItem(m_widgetHash["themeComboBox"]);
    settingsLayout->addItem(m_widgetHash["animationsLabel"]);
    settingsLayout->addItem(m_widgetHash["animatedComboBox"]);
    settingsLayout->addItem(m_widgetHash["legendLabel"]);
    settingsLayout->addItem(m_widgetHash["legendComboBox"]);
    settingsLayout->addItem(m_widgetHash["scrollCheckBox"]);
    settingsLayout->addItem(m_widgetHash["zoomCheckBox"]);
    settingsLayout->addStretch();
    baseLayout->addItem(settingsLayout, 0, 3, 2, 1);
    //create charts

    int i = m_widgetHash.count();
    foreach(QGraphicsProxyWidget* widget , m_widgetHash) {
        widget->setZValue(i--);
        widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }


    Charts::ChartList list = Charts::chartList();

    for(int i = 0 ; i < 6 ; ++i)
    {
        if(!(i<list.size()) || list.isEmpty()) break;
        QChart* chart = list.at(i)->createChart(m_dataTable);
        baseLayout->addItem(chart, i/3, i%3);
        m_chartList << chart;
    }

    m_form = new QGraphicsWidget();
    m_form->setLayout(baseLayout);
    m_scene->addItem(m_form);
    m_scene->addItem(m_rubberBand);
    m_rubberBand->setVisible(false);

    m_view = new View(m_scene, m_form);
    m_view->setMinimumSize(m_form->preferredSize().toSize());

    // Set defaults
    m_antialiasCheckBox->setChecked(true);
    updateUI();
    setCentralWidget(m_view);
}

Window::~Window()
{
}

void Window::connectSignals()
{
    connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_openGLCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_zoomCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_scrollCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
}

DataTable Window::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal) (qrand() % valueMax) / (qreal) valueCount;
            QPointF value(
                (j + (qreal) qrand() / (qreal) RAND_MAX)
                    * ((qreal) m_valueMax / (qreal) valueCount), yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

void Window::createProxyWidgets()
{
    m_themeComboBox = createThemeBox();
    m_antialiasCheckBox = new QCheckBox(tr("Anti-aliasing"));
    m_animatedComboBox = createAnimationBox();
    m_legendComboBox = createLegendBox();
    m_openGLCheckBox = new QCheckBox(tr("OpenGL"));
    m_zoomCheckBox = new QCheckBox(tr("Zoom"));
    m_scrollCheckBox = new QCheckBox(tr("Scroll"));
    m_widgetHash["themeComboBox"] = m_scene->addWidget(m_themeComboBox);
    m_widgetHash["antialiasCheckBox"] = m_scene->addWidget(m_antialiasCheckBox);
    m_widgetHash["animatedComboBox"] = m_scene->addWidget(m_animatedComboBox);
    m_widgetHash["legendComboBox"] = m_scene->addWidget(m_legendComboBox);
    m_widgetHash["openGLCheckBox"] = m_scene->addWidget(m_openGLCheckBox);
    m_widgetHash["themeLabel"] = m_scene->addWidget(new QLabel("Theme"));
    m_widgetHash["animationsLabel"] = m_scene->addWidget(new QLabel("Animations"));
    m_widgetHash["legendLabel"] = m_scene->addWidget(new QLabel("Legend"));
    m_widgetHash["zoomCheckBox"] = m_scene->addWidget(m_zoomCheckBox);
    m_widgetHash["scrollCheckBox"] = m_scene->addWidget(m_scrollCheckBox);
}

QComboBox* Window::createThemeBox() const
{
    // settings layoutQGLWidget’
    QComboBox* themeComboBox = new QComboBox();
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    return themeComboBox;
}

QComboBox* Window::createAnimationBox() const
{
    // settings layout
    QComboBox* animationComboBox = new QComboBox();
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);
    return animationComboBox;
}

QComboBox* Window::createLegendBox() const
{
    QComboBox* legendComboBox = new QComboBox();
    legendComboBox->addItem("No Legend ", 0);
    legendComboBox->addItem("Legend Top", Qt::AlignTop);
    legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    legendComboBox->addItem("Legend Right", Qt::AlignRight);
    return legendComboBox;
}

void Window::updateUI()
{
    bool opengl = m_openGLCheckBox->isChecked();
    bool isOpengl = qobject_cast<QGLWidget*>(m_view->viewport());
    if ((isOpengl && !opengl) || (!isOpengl && opengl)) {
        m_view->deleteLater();
        m_view = new View(m_scene, m_form);
        m_view->setViewport(!opengl ? new QWidget() : new QGLWidget());
        setCentralWidget(m_view);
    }

    QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(
        m_themeComboBox->currentIndex()).toInt();

    foreach (QChart *chart, m_chartList)
        chart->setTheme(theme);

    QPalette pal = window()->palette();
    if (theme == QChart::ChartThemeLight) {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else if (theme == QChart::ChartThemeDark) {
        pal.setColor(QPalette::Window, QRgb(0x121218));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    }
    else if (theme == QChart::ChartThemeBlueCerulean) {
        pal.setColor(QPalette::Window, QRgb(0x40434a));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    }
    else if (theme == QChart::ChartThemeBrownSand) {
        pal.setColor(QPalette::Window, QRgb(0x9e8965));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else if (theme == QChart::ChartThemeBlueNcs) {
        pal.setColor(QPalette::Window, QRgb(0x018bba));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else if (theme == QChart::ChartThemeHighContrast) {
        pal.setColor(QPalette::Window, QRgb(0xffab03));
        pal.setColor(QPalette::WindowText, QRgb(0x181818));
    }
    else if (theme == QChart::ChartThemeBlueIcy) {
        pal.setColor(QPalette::Window, QRgb(0xcee7f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    foreach(QGraphicsProxyWidget* widget , m_widgetHash) {
        widget->setPalette(pal);
    }
    m_view->setBackgroundBrush(pal.color((QPalette::Window)));
    m_rubberBand->setPen(pal.color((QPalette::WindowText)));

    QChart::AnimationOptions options(
        m_animatedComboBox->itemData(m_animatedComboBox->currentIndex()).toInt());
    if (!m_chartList.isEmpty() && m_chartList.at(0)->animationOptions() != options) {
        foreach (QChart *chart, m_chartList)
            chart->setAnimationOptions(options);
    }

    Qt::Alignment alignment(m_legendComboBox->itemData(m_legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        foreach (QChart *chart, m_chartList) {
            chart->legend()->hide();
        }
    }
    else {
        foreach (QChart *chart, m_chartList) {
            chart->legend()->setAlignment(alignment);
            chart->legend()->show();
        }
    }

    bool antialias = m_antialiasCheckBox->isChecked();

    if (opengl)
        m_view->setRenderHint(QPainter::HighQualityAntialiasing, antialias);
    else
        m_view->setRenderHint(QPainter::Antialiasing, antialias);

    bool scroll = m_scrollCheckBox->isChecked();

    if(!m_scroll & scroll){
        m_scroll=true;
        m_zoom=false;
        m_zoomCheckBox->setChecked(false);
    }

    bool zoom = m_zoomCheckBox->isChecked();

    if(!m_zoom & zoom){
           m_scroll=false;
           m_zoom=true;
           m_scrollCheckBox->setChecked(false);
    }

}

void Window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        m_origin = event->pos();
        m_isScrolling = false;
        m_isZooming = false;

        foreach (QChart *chart, m_chartList) {

            QRectF geometryRect = chart->geometry();
            QRectF plotArea = chart->plotArea();
            plotArea.translate(geometryRect.topLeft());
            if (plotArea.contains(m_origin)) {
                m_isScrolling = m_scroll;
                m_isZooming = m_zoom;
                break;
            }
        }

        if (m_isZooming) {
            m_rubberBand->setRect(QRectF(m_origin, QSize()));
            m_rubberBand->setVisible(true);
        }
        event->accept();
    }

    if (event->button() == Qt::RightButton) {
        m_origin = event->pos();
        m_isZooming = m_zoom;
    }
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isScrolling || m_isZooming) {

        foreach (QChart *chart, m_chartList) {

            QRectF geometryRect = chart->geometry();
            QRectF plotArea = chart->plotArea();
            plotArea.translate(geometryRect.topLeft());

            if (plotArea.contains(m_origin)) {
                if (m_isScrolling) {
                    QPointF delta = m_origin - event->pos();
                    chart->scroll(delta.x(), -delta.y());
                }
                if (m_isZooming && plotArea.contains(event->pos())) {
                    m_rubberBand->setRect(QRectF(m_origin, event->pos()).normalized());
                }
                break;
            }
        }
        if(m_isScrolling) m_origin = event->pos();
        event->accept();
    }
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isScrolling = false;
        if (m_isZooming) {
            m_isZooming = false;
            m_rubberBand->setVisible(false);

            foreach (QChart *chart, m_chartList) {

                QRectF geometryRect = chart->geometry();
                QRectF plotArea = chart->plotArea();
                plotArea.translate(geometryRect.topLeft());

                if (plotArea.contains(m_origin)) {
                    QRectF rect = m_rubberBand->rect();
                    rect.translate(-geometryRect.topLeft());
                    chart->zoomIn(rect);
                    break;
                }
            }
        }
        event->accept();
    }

    if (event->button() == Qt::RightButton) {

        if (m_isZooming) {
            foreach (QChart *chart, m_chartList) {

                QRectF geometryRect = chart->geometry();
                QRectF plotArea = chart->plotArea();
                plotArea.translate(geometryRect.topLeft());

                if (plotArea.contains(m_origin)) {
                    QRectF rect = m_rubberBand->rect();
                    chart->zoomOut();
                    break;
                }
            }
        }
    }
}
