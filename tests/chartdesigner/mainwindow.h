/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartGlobal>
#include <QMap>


QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QAbstractSeries;
QT_CHARTS_END_NAMESPACE

class QGraphicsScene;
class InspectorWidget;
class BrushWidget;
class PenWidget;
class QTableView;
class Engine;

QT_CHARTS_USE_NAMESPACE

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
