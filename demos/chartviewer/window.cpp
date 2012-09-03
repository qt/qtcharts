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
#include <QAreaSeries>
#include <QLegend>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QGLWidget>
#include <QApplication>
#include <QDebug>
#include <QMenu>

Window::Window(QWidget* parent) :
    QMainWindow(parent),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    m_scene(new QGraphicsScene(this)),
    m_view(0),
    m_dataTable(Model::generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    m_form(0),
    m_themeComboBox(0),
    m_antialiasCheckBox(0),
    m_animatedComboBox(0),
    m_legendComboBox(0),
    m_templateComboBox(0),
    m_openGLCheckBox(0),
    m_zoomCheckBox(0),
    m_scrollCheckBox(0),
    m_rubberBand(new QGraphicsRectItem()),
    m_baseLayout(new QGraphicsGridLayout()),
    m_menu(createMenu()),
    m_state(NoState),
    m_currentState(NoState),
    m_template(0)
{
    createProxyWidgets();
    connectSignals();

    // create layout
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
    settingsLayout->addItem(m_widgetHash["templateLabel"]);
    settingsLayout->addItem(m_widgetHash["templateComboBox"]);
    settingsLayout->addItem(m_widgetHash["scrollCheckBox"]);
    settingsLayout->addItem(m_widgetHash["zoomCheckBox"]);
    settingsLayout->addStretch();
    m_baseLayout->addItem(settingsLayout, 0, 3, 2, 1);

    //create charts
    Charts::ChartList list = Charts::chartList();

    for (int i = 0; i < 9; ++i) {
        QChart* chart = 0;
        if(i<list.size()){
        chart = list.at(i)->createChart(m_dataTable);
        }else{
        chart = new QChart();
        chart->setTitle(tr("Empty"));
        }

        m_baseLayout->addItem(chart, i / 3, i % 3);
        m_chartHash[chart] = i;
    }

    m_form = new QGraphicsWidget();
    m_form->setLayout(m_baseLayout);
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
    QObject::connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    QObject::connect(m_antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    QObject::connect(m_openGLCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    QObject::connect(m_zoomCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    QObject::connect(m_scrollCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    QObject::connect(m_animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    QObject::connect(m_legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    QObject::connect(m_templateComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
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
    m_templateComboBox= createTempleteBox();
    m_widgetHash["themeComboBox"] = m_scene->addWidget(m_themeComboBox);
    m_widgetHash["antialiasCheckBox"] = m_scene->addWidget(m_antialiasCheckBox);
    m_widgetHash["animatedComboBox"] = m_scene->addWidget(m_animatedComboBox);
    m_widgetHash["legendComboBox"] = m_scene->addWidget(m_legendComboBox);
    m_widgetHash["openGLCheckBox"] = m_scene->addWidget(m_openGLCheckBox);
    m_widgetHash["themeLabel"] = m_scene->addWidget(new QLabel("Theme"));
    m_widgetHash["animationsLabel"] = m_scene->addWidget(new QLabel("Animations"));
    m_widgetHash["legendLabel"] = m_scene->addWidget(new QLabel("Legend"));
    m_widgetHash["templateLabel"] = m_scene->addWidget(new QLabel("Chart template"));
    m_widgetHash["templateComboBox"] = m_scene->addWidget(m_templateComboBox);
    m_widgetHash["zoomCheckBox"] = m_scene->addWidget(m_zoomCheckBox);
    m_widgetHash["scrollCheckBox"] = m_scene->addWidget(m_scrollCheckBox);

}

QComboBox* Window::createThemeBox()
{
    QComboBox* themeComboBox = new ComboBox(this);
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    return themeComboBox;
}

QComboBox* Window::createAnimationBox()
{
    QComboBox* animationComboBox = new ComboBox(this);
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);
    return animationComboBox;
}

QComboBox* Window::createLegendBox()
{
    QComboBox* legendComboBox = new ComboBox(this);
    legendComboBox->addItem("No Legend ", 0);
    legendComboBox->addItem("Legend Top", Qt::AlignTop);
    legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    legendComboBox->addItem("Legend Right", Qt::AlignRight);
    return legendComboBox;
}

QComboBox* Window::createTempleteBox()
{
    QComboBox* templateComboBox = new ComboBox(this);
    templateComboBox->addItem("No Template", 0);

    Charts::ChartList list = Charts::chartList();
    QMultiMap<QString, Chart*> categoryMap;

    foreach(Chart* chart, list) {
          categoryMap.insertMulti(chart->category(), chart);
    }
    foreach(const QString& category, categoryMap.uniqueKeys()) {
        templateComboBox->addItem(category, category);
    }
    return templateComboBox;
}


void Window::updateUI()
{
    checkTemplate();
    checkOpenGL();
    checkTheme();
    checkAnimationOptions();
    checkLegend();
    checkState();
}

void Window::checkLegend()
{
    Qt::Alignment alignment(m_legendComboBox->itemData(m_legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        foreach (QChart *chart, m_chartHash.keys()) {
            chart->legend()->hide();
        }
    }
    else {
        foreach (QChart *chart, m_chartHash.keys()) {
            chart->legend()->setAlignment(alignment);
            chart->legend()->show();
        }
    }
}

void Window::checkOpenGL()
{
    bool opengl = m_openGLCheckBox->isChecked();
    bool isOpengl = qobject_cast<QGLWidget*>(m_view->viewport());
    if ((isOpengl && !opengl) || (!isOpengl && opengl)) {
        m_view->deleteLater();
        m_view = new View(m_scene, m_form);
        m_view->setViewport(!opengl ? new QWidget() : new QGLWidget());
        setCentralWidget(m_view);
    }

    bool antialias = m_antialiasCheckBox->isChecked();

       if (opengl)
           m_view->setRenderHint(QPainter::HighQualityAntialiasing, antialias);
       else
           m_view->setRenderHint(QPainter::Antialiasing, antialias);
}

void Window::checkAnimationOptions()
{
    QChart::AnimationOptions options(
           m_animatedComboBox->itemData(m_animatedComboBox->currentIndex()).toInt());
       if (!m_chartHash.isEmpty() && m_chartHash.keys().at(0)->animationOptions() != options) {
           foreach (QChart *chart, m_chartHash.keys())
               chart->setAnimationOptions(options);
       }
}

void Window::checkState()
{
    bool scroll = m_scrollCheckBox->isChecked();

    if (m_state != ScrollState && scroll) {
        m_state = ScrollState;
        m_zoomCheckBox->setChecked(false);
    }
    else if (!scroll && m_state == ScrollState) {
        m_state = NoState;
    }

    bool zoom = m_zoomCheckBox->isChecked();

    if (m_state != ZoomState && zoom) {
        m_state = ZoomState;
        m_scrollCheckBox->setChecked(false);
    }
    else if (!zoom && m_state == ZoomState) {
        m_state = NoState;
    }
}

void Window::checkTemplate()
{

    int index = m_templateComboBox->currentIndex();
    if (m_template == index || index == 0)
        return;

    m_template = index;

    QString category = m_templateComboBox->itemData(index).toString();
    Charts::ChartList list = Charts::chartList();

    QList<QChart*> qchartList = m_chartHash.keys();

    foreach(QChart* qchart,qchartList){
    for(int i = 0 ; i < m_baseLayout->count();++i)
           {
               if(m_baseLayout->itemAt(i)==qchart){
                   m_baseLayout->removeAt(i);
                   break;
               }
           }
    }

    m_chartHash.clear();
    qDeleteAll(qchartList);

    QChart* qchart(0);

    int j=0;
    for (int i = 0; i < list.size(); ++i) {
        Chart* chart = list.at(i);
        if (chart->category() == category && j < 9) {
            qchart = list.at(i)->createChart(m_dataTable);
            m_baseLayout->addItem(qchart, j / 3, j % 3);
            m_chartHash[qchart] = j;
            j++;
        }
    }
    for (; j < 9; ++j) {
        qchart = new QChart();
        qchart->setTitle(tr("Empty"));
        m_baseLayout->addItem(qchart, j / 3, j % 3);
        m_chartHash[qchart] = j;
    }
}

void Window::checkTheme()
{
    QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(
        m_themeComboBox->currentIndex()).toInt();

    foreach (QChart *chart, m_chartHash.keys())
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
}

void Window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        m_origin = event->pos();
        m_currentState = NoState;

        foreach (QChart *chart, m_chartHash.keys()) {

            QRectF geometryRect = chart->geometry();
            QRectF plotArea = chart->plotArea();
            plotArea.translate(geometryRect.topLeft());
            if (plotArea.contains(m_origin)) {
                m_currentState = m_state;

                if (m_currentState == NoState && m_templateComboBox->currentIndex()==0) {
                    handleMenu(chart);
                }
                break;
            }
        }

        if (m_currentState == ZoomState) {
            m_rubberBand->setRect(QRectF(m_origin, QSize()));
            m_rubberBand->setVisible(true);
        }

        event->accept();
    }

    if (event->button() == Qt::RightButton) {
        m_origin = event->pos();
        m_currentState = m_state;
    }
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    if ( m_currentState != NoState) {

        foreach (QChart *chart, m_chartHash.keys()) {

            QRectF geometryRect = chart->geometry();
            QRectF plotArea = chart->plotArea();
            plotArea.translate(geometryRect.topLeft());

            if (plotArea.contains(m_origin)) {
                if (m_currentState == ScrollState) {
                    QPointF delta = m_origin - event->pos();
                    chart->scroll(delta.x(), -delta.y());
                }
                if (m_currentState == ZoomState && plotArea.contains(event->pos())) {
                    m_rubberBand->setRect(QRectF(m_origin, event->pos()).normalized());
                }
                break;
            }
        }
        if(m_currentState == ScrollState) m_origin = event->pos();
        event->accept();
    }
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_currentState == ZoomState) {
            m_rubberBand->setVisible(false);

            foreach (QChart *chart, m_chartHash.keys()) {

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

        m_currentState = NoState;
        event->accept();
    }

    if (event->button() == Qt::RightButton) {

        if (m_currentState == ZoomState) {
            foreach (QChart *chart, m_chartHash.keys()) {

                QRectF geometryRect = chart->geometry();
                QRectF plotArea = chart->plotArea();
                plotArea.translate(geometryRect.topLeft());

                if (plotArea.contains(m_origin)) {
                    chart->zoomOut();
                    break;
                }
            }
        }
    }
}

void Window::comboBoxFocused(QComboBox *combobox)
{
    foreach(QGraphicsProxyWidget* widget , m_widgetHash) {
       if(widget->widget()==combobox)
        widget->setZValue(2.0);
       else
        widget->setZValue(0.0);
    }
}

void Window::handleMenu(QChart* qchart)
{
    QAction *chosen = m_menu->exec(QCursor::pos());

    if (chosen) {
        Chart* chart = (Chart *) chosen->data().value<void *>();
        int index = m_chartHash[qchart];
        //not in 4.7.2 m_baseLayout->removeItem(qchart);
        for(int i = 0 ; i < m_baseLayout->count();++i)
        {
            if(m_baseLayout->itemAt(i)==qchart){
                m_baseLayout->removeAt(i);
                break;
            }
        }

        m_chartHash.remove(qchart);
        QChart* newChart = chart->createChart(m_dataTable);
        m_baseLayout->addItem(newChart, index / 3, index % 3);
        m_chartHash[newChart] = index;
        delete qchart;
        updateUI();
    }

}

QMenu* Window::createMenu()
{
    Charts::ChartList list = Charts::chartList();
    QMultiMap<QString, Chart*> categoryMap;

    QMenu* result = new QMenu(this);

    foreach(Chart* chart, list) {
        categoryMap.insertMulti(chart->category(), chart);
    }

    foreach(const QString& category, categoryMap.uniqueKeys()) {
        QMenu* menu(0);
        QMultiMap<QString, Chart*> subCategoryMap;
        if (category.isEmpty()) {
            menu = result;
        }
        else {
            menu = new QMenu(category, this);
            result->addMenu(menu);
        }

        foreach(Chart* chart , categoryMap.values(category)) {
            subCategoryMap.insert(chart->subCategory(), chart);
        }

        foreach(const QString& subCategory, subCategoryMap.uniqueKeys()) {
            QMenu* subMenu(0);
            if (subCategory.isEmpty()) {
                subMenu = menu;
            }
            else {
                subMenu = new QMenu(subCategory, this);
                menu->addMenu(subMenu);
            }

            foreach(Chart* chart , subCategoryMap.values(subCategory)) {

                createMenuAction(subMenu, QIcon(), chart->name(),
                    qVariantFromValue((void *) chart));
            }
        }
    }

    return result;
}

QAction* Window::createMenuAction(QMenu *menu, const QIcon &icon, const QString &text,
    const QVariant &data)
{
    QAction *action = menu->addAction(icon, text);
    action->setCheckable(false);
    action->setData(data);
    return action;
}
