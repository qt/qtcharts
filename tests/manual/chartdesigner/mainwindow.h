// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QtCore/QMap>


QT_BEGIN_NAMESPACE
class QChartView;
class QAbstractSeries;
QT_END_NAMESPACE

class QGraphicsScene;
class InspectorWidget;
class BrushWidget;
class PenWidget;
class QTableView;
class Engine;

QT_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private slots:
    void handleNewAction();
    void handleAddSeriesMenu();
    void handleRemoveAllSeriesAction();
    void updateUI();
    void handleThemeMenu();
    void handleAnimationMenu();
    void handleZoomMenu();
    void handleAntialiasingAction();
    void handleLegendAction();
    void handleSaveAction();
    void handleLoadAction();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createMenus();
    void createDockWidgets();
    void createModel();
    void createLayout();
    void createTable();

private:
    Engine *m_engine;
    QChartView *m_view;
    QGraphicsScene *m_scene;
    QTableView *m_table;
    InspectorWidget *m_inspectorWidget;
    PenWidget *m_penWidget;
    BrushWidget *m_brushWidget;
    QMenu *m_addSeriesMenu;
    QMenu *m_seriesMenu;
    QMenu *m_chartMenu;
    QMenu *m_themeMenu;
    QMenu *m_animationMenu;
    QMenu *m_zoomMenu;

    QAction *m_removeAllAction;
    QAction *m_legendAction;
    QAction *m_antialiasingAction;
    QString m_filename;

    QMap<QString,QAbstractSeries*> m_series;

};

#endif /* MAINWINDOW_H */
