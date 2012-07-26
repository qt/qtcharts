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

#ifndef CHARTWINDOW_H_
#define CHARTWINDOW_H_
#include <QMainWindow>
#include <QChartGlobal>
#include <QHash>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsWidget>

class QComboBox;
class QCheckBox;

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QChart;
QTCOMMERCIALCHART_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class QGraphicsScene;

QTCOMMERCIALCHART_USE_NAMESPACE


class GraphicsView: public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene *scene, QGraphicsWidget *form , QWidget *parent = 0):QGraphicsView(scene,parent), m_form(form)
    {
        setWindowTitle(tr("Charts"));
    }

protected:
    void resizeEvent(QResizeEvent *event)
    {
        if (scene())
            scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        if (m_form)
            m_form->resize(QSizeF(event->size()));
        QGraphicsView::resizeEvent(event);
    }
private:
    QGraphicsWidget *m_form;
};


class ChartWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit ChartWindow(QWidget *parent = 0);
    ~ChartWindow();

private Q_SLOTS:
    void updateUI();

private:
    DataTable generateRandomData(int listCount,int valueMax,int valueCount) const;
    QComboBox* createThemeBox() const;
    QComboBox* createAnimationBox() const;
    QComboBox* createLegendBox() const;
    void connectSignals();
    QChart* createAreaChart() const;
    QChart* createBarChart(int valueCount) const;
    QChart* createPieChart() const;
    QChart* createLineChart() const;
    QChart* createSplineChart() const;
    QChart* createScatterChart() const;
    void createProxyWidgets();

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QGraphicsScene* m_scene;
    GraphicsView* m_view;
    QHash<QString, QGraphicsProxyWidget*> m_widgetHash;
    QList<QChart*> m_chartList;
    DataTable m_dataTable;

    QGraphicsWidget *m_form;
    QComboBox *m_themeComboBox;
    QCheckBox *m_antialiasCheckBox;
    QComboBox *m_animatedComboBox;
    QComboBox *m_legendComboBox;
    QCheckBox *m_openGLCheckBox;
};

#endif
